#include "steering.h"

uint8_t steerAngle = 65;
uint8_t steerValue = 0;
bool steerDirection = true;  //true for clockwise and vice versa

Servo steer;

void setupSteering() {
  ESP32PWM::allocateTimer(3);
  steer.setPeriodHertz(50);  // standard 50 hz servo
  steer.attach(servoPin, 500, 2500);
}

void updateSteering() {
  if (steerDirection) steerAngle = map(steerValue, 0, 100, centerAngle, leftAngle); 
  else steerAngle = map(steerValue, 100, 0, rightAngle, centerAngle);
  steer.write(steerAngle);
}

void setClockwiseSteering(const char * value) {
  uint8_t val = atoi(value);
  steerValue = val <= 100 ? val : 100;
  steerDirection = true;
  updateSteering();
}

void setAnticlockwiseSteering(const char * value) {
  steerValue = atoi(value);
  steerDirection = false;
  updateSteering();
}