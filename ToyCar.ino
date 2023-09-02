#include <Arduino.h>
#include "WebSocketHandler.h"
#include "driving.h"
#include "steering.h"
#include "lighting.h"
#include "speakers.h"

void setup() {
  Serial.begin(115200);
  wifiInit();
  setupDriving();
  setupSteering();
  ledInit();
  setupSpeakers();
}

void loop() {
  updateDriving(speed);
  updateSteering(steering);
  updateSpeakers();
}