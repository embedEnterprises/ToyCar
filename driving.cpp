#include "driving.h"

const int freq = 5000;
const uint8_t resolution = 8;
uint8_t speed = 0;
bool drivingDirection = true;

void setupDriving() {
  //Motor setup
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(in1, 0);
  ledcAttachPin(in2, 1);
}

void updateDriving() {
  if (drivingDirection) {
    ledcWrite(0, speed);
    ledcWrite(1, 0);
  } else {
    ledcWrite(0, 0);
    ledcWrite(1, speed);
  }
}

void setForwardSpeed(uint8_t val) {
  speed = val;
  drivingDirection = true;
  updateDriving();
}

void setReverseSpeed(uint8_t val) {
  speed = val;
  drivingDirection = false;
  updateDriving();
}