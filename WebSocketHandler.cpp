#include "WebSocketHandler.h"
#include <HardwareSerial.h>
const char *AP_SSID = "YourAPNetwork";
const char *AP_PASS = "YourPassword";

// const char *STA_SSID ;
// const char *STA_PASS ;
String ssidstring;
String passwordstring;

IPAddress local_IP(192, 168, 0, 106);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
Preferences preferences;

TaskHandle_t Task2;

std::map<char, ComponentCallback> componentCallbacks;

const char *value;
char componentID;

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = '\0';
    value = (const char *)&data[2];
    componentID = data[0];

    if (componentCallbacks.find(componentID) != componentCallbacks.end()) {
      componentCallbacks[componentID](value);
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
      break;
    case WS_EVT_ERROR:
      break;
  }
  vTaskDelay(3);
}

void tryConnectToWiFi(void *parameter) {
  Serial.println("Trying to connect to wifi");
  const char *STA_SSID = ssidstring.c_str();
  const char *STA_PASS = passwordstring.c_str();

  WiFi.begin(STA_SSID, STA_PASS);
  unsigned long startMillis = millis();

  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startMillis >= 5000) {
      Serial.println("Could not connect to wifi");
      break;
    }
    vTaskDelay(3);
    delay(100);
  }
  if (WiFi.status() == WL_CONNECTED) {
    preferences.putString("ssid", STA_SSID);
    preferences.putString("password", STA_PASS);
    preferences.end();
    Serial.println("Connectionn successful");
    Serial.println(WiFi.localIP());
    Serial.println(ws.count());
    if (ws.count() > 0) {
      String message = "W:1";
      ws.textAll(message);
    }
    // WiFi.softAPdisconnect(true);
  } else {
    if (ws.count() > 0) {
      String message = "W:0";
      ws.textAll(message);
    }
  }
  vTaskDelete(Task2);
}

void createWifiTask() {
  xTaskCreatePinnedToCore(
    tryConnectToWiFi,
    "WifiTask",
    10000,
    NULL,
    2,
    &Task2,
    0);
}

void setPassword(const char *value) {
  passwordstring = String(value);
  createWifiTask();
}

void setSSID(const char *value) {
  ssidstring = String(value);
}

void addComponentCallback(char componentID, ComponentCallback callback) {
  componentCallbacks[componentID] = callback;
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
  server.begin();
}



void wifiInit() {
  WiFi.mode(WIFI_MODE_APSTA);

  preferences.begin("my-app", false);
  String usern = preferences.getString("ssid", "Foot");
  String passw = preferences.getString("password", "Foot");

  ssidstring = usern;
  passwordstring = passw;

  WiFi.softAP(AP_SSID, AP_PASS);
  IPAddress IP = WiFi.softAPIP();

  createWifiTask();

  initWebSocket();
}
