#include "driving.h"

const int freq = 5000;
const int resolution = 8;

void setupDriving() {
  //Motor setup
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  ledcSetup(0, freq, resolution);
  ledcSetup(1, freq, resolution);
  ledcAttachPin(in1, 0);
  ledcAttachPin(in2, 1);
}

void updateDriving(uint8_t speed) {
  ledcWrite(0, abs(speed));
  ledcWrite(1, 0);
}