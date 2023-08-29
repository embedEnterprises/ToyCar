#include <Arduino.h>
#include "WebSocketHandler.h"

void setup() {
  Serial.begin(115200);
  wifiInit();
}

void loop() {
  Serial.printf("Steering: %d, Speed: %d, LED Mode: %d\n", steering, speed, ledMode);
  delay(400);
}