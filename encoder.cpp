#include "encoder.h"

volatile unsigned long int encoder_counts = 0;
volatile unsigned long int prev_encoder_counts = 0;
unsigned long int prev_int = 0;

void IRAM_ATTR encoder_isr() {
  if (micros() - prev_int > 100) {
    encoder_counts++;
    prev_int = micros();
  }
}

void setupEncoder() {
  pinMode(encoder_pin, INPUT_PULLUP);
  attachInterrupt(encoder_pin, encoder_isr, FALLING);
}

void encoderLoop() {
    if(prev_encoder_counts != encoder_counts) {
    Serial.println(encoder_counts);
    prev_encoder_counts = encoder_counts;
  }
}