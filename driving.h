#ifndef __DRIVING_H__
#define __DRIVING_H__
#include <Arduino.h>

#define in1 18
#define in2 19

#define maxPwm 200
#define minPwm 40
#define maxSpeed 200

// extern int speed;

void setupDriving();
void updateDriving(uint8_t speed);

#endif