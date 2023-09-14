#ifndef __SPEAKERS_H__
#define __SPEAKERS_H__

#include <Arduino.h>
#include "XT_DAC_Audio.h";



void setupSpeakers();

void playHorn();
void stopHorn();
void updateSpeakers();
void setHorn(const char * value);

#endif
