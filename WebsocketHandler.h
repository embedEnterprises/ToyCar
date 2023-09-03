#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <map>


extern AsyncWebSocket ws;

typedef void (*ComponentCallback)(uint8_t value);

void assignValues(uint8_t *data, size_t len);
void initWebSocket();
void wifiInit();
void addComponentCallback(char componentID, ComponentCallback callback);

// Declare global variables
extern int steering;
extern int ledMode;

#endif // WEBSOCKETHANDLER_H
