#include "speakers.h"
#include "sounds/horn.h";

XT_DAC_Audio_Class DacAudio(26,0);

XT_Wav_Class Horn(hornData);

void setupSpeakers() {
  Horn.RepeatForever = true;
}

void playHorn(){
  DacAudio.Play(&Horn);
}
void stopHorn () {
  DacAudio.StopAllSounds();
}
void updateSpeakers(){
  DacAudio.FillBuffer(); 
}

void setHorn(const char * value) {
  uint8_t val = atoi(value);
  if(val == 1) playHorn();
  if(val == 0) stopHorn();
}