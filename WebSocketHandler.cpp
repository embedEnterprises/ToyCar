#include "WebSocketHandler.h"

const char *ssid = "Onkar";
const char *password = "Onkar@link";

IPAddress local_IP(192, 168, 0, 106);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

std::map<char, ComponentCallback> componentCallbacks;

int steering = 0;
// int speed = 0;
int ledMode = 0;
uint8_t horn = 0;
uint8_t value;
char componentID;

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo *)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = '_';
    value = atoi((const char *)&data[2]);
    componentID = data[0];

    // Check if the component ID exists in the map
    if (componentCallbacks.find(componentID) != componentCallbacks.end()) {
      // Call the associated callback function
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
      // Handle PONG event if needed
      break;
    case WS_EVT_ERROR:
      // Handle ERROR event if needed
      break;
  }
  vTaskDelay(3);  // You may want to adjust this delay
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
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println(WiFi.localIP());

  initWebSocket();
}
