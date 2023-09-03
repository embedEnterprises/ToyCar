#ifndef __IRSENSOR_H__
#define __IRSENSOR_H__

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRrecv.h>
#include <IRutils.h>


// class IRUnit {
// public:
//   IRUnit(int transmitterPin, int receiverPin);
//   void begin();
//   int checkObstacle();

// private:
//   IRrecv *irReceiver;
//   IRsend *irTransmitter;
// };

void setupIRSensors();
void updateIRSensors();

#endif
