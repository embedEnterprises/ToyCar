#ifndef __LIGHTING_H__
#define __LIGHTING_H__
#include <Arduino.h>


#define r1 27
#define r2 12
#define r3 14
#define l1 15
#define l2 13
#define l3 32
#define b 25

#define ON HIGH
#define OFF LOW

void setupLights();
void updateLedMode(uint8_t c);

#endif
