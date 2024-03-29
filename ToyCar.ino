#include <Arduino.h>
#include "WebSocketHandler.h"
#include "driving.h"
#include "steering.h"
#include "lighting.h"
#include "speakers.h"
#include "IRSensor.h"
// #include "IMUUnit.h"
#include "encoder.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Hello There");
  wifiInit();
  setupDriving();
  setupSteering();
  setupLights();
  setupSpeakers();
  setupIRSensors();
  setupEncoder();
  // setupIMU();

  addComponentCallback('L', updateLedMode);
  addComponentCallback('A', setAnticlockwiseSteering);
  addComponentCallback('C', setClockwiseSteering);
  addComponentCallback('H', setHorn);
  addComponentCallback('F', setForwardSpeed);
  addComponentCallback('R', setReverseSpeed);
  addComponentCallback('P', setPassword);
  addComponentCallback('S', setSSID);
}

void loop() {
  // updateSpeakers();
}