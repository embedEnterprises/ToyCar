#ifndef __STEERING_H__
#define __STEERING_H__

#include <Arduino.h>
#include <ESP32Servo.h>
#include <math.h>

#define servoPin 17
#define leftAngle 89
#define rightAngle 165
#define centerAngle 127
#define maxSteering 180

void setupSteering();

void updateSteering(int value);

#endif