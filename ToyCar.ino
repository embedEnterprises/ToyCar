#include <Arduino.h>
#include "WebSocketHandler.h"
#include "driving.h"
#include "steering.h"
#include "lighting.h"

void setup() {
  Serial.begin(115200);
  wifiInit();
  setupDriving();
  setupSteering();
  ledInit();
}

void loop() {
  updateDriving(speed);
  updateSteering(steering);
  // updateLedMode(ledMode);
}