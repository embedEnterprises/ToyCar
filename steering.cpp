#include "steering.h"

uint8_t steerAngle = 65;
Servo steer;

void setupSteering() {
  ESP32PWM::allocateTimer(3);
  steer.setPeriodHertz(50);  // standard 50 hz servo
  steer.attach(servoPin, 500, 2500);
}

void updateSteering(int value) {
  if (value > 100) value = 100;
  if (value < -100) value = -100;
  steerAngle = map(value, -100, 100, rightAngle, leftAngle);
  steer.write(steerAngle);
}