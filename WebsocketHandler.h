#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "lighting.h"
#include "speakers.h"

extern AsyncWebSocket ws;

void assignValues(uint8_t *data, size_t len);
void initWebSocket();
void wifiInit();

// Declare global variables
extern int steering;
extern int speed;
extern int ledMode;

#endif // WEBSOCKETHANDLER_H
