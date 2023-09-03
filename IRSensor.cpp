#include "IRSensor.h"

uint16_t rawData[10] = { 9000, 4500, 650, 550, 650, 1650, 600, 550, 650, 550 };
decode_results results;


class IRUnit {

public:
  IRUnit(int transmitterPin, int receiverPin) {
    irReceiver = new IRrecv(receiverPin);
    irTransmitter = new IRsend(transmitterPin);
    // Serial.println(a);
  }

  void begin() {
    irReceiver->enableIRIn();
    irTransmitter->begin();
  }

  int checkObstacle() {
    int b = 0;
    // Serial.println("i am in the function");
    irTransmitter->sendRaw(rawData, 10, 38);
    b++;
    if (irReceiver->decode(&results)) {
      serialPrintUint64(results.value, HEX);
      Serial.println("");
      irReceiver->resume();  // Receive the next value
      b = 10;
      return b;
    }
    return b;
  }

private:
  IRrecv *irReceiver;
  IRsend *irTransmitter;
};


IRUnit irPair1(16, 34);
TaskHandle_t irTask1;
unsigned long int prevMillisIR = 0;

void irTask1code( void * parameter) {
  for(;;){
  prevMillisIR = millis();
  while (true) {
    int val = irPair1.checkObstacle();
    delay(50);
  }
    //  vTaskSuspend(NULL);
    vTaskSuspend(NULL);
  }
}

void createIRTask() {
  xTaskCreatePinnedToCore(
    irTask1code, /* Function to implement the task */
    "LedTask", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    2,  /* Priority of the task */
    &irTask1,  /* Task handle. */
    1); /* Core where the task should run */
}


int count = 0;
void setupIRSensors() {
  irPair1.begin();
  createIRTask();
  vTaskResume(irTask1);
}



