#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <map>
#include <Preferences.h>


extern AsyncWebSocket ws;

typedef void (*ComponentCallback)(const char * value);

void assignValues(uint8_t *data, size_t len);
void initWebSocket();
void wifiInit();
void addComponentCallback(char componentID, ComponentCallback callback);

void setPassword(const char * value);
void setSSID(const char * value);


// Declare global variables
extern int steering;
extern int ledMode;

#endif // WEBSOCKETHANDLER_H
