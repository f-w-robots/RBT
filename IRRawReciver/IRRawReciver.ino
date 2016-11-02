#include "RawRead.h"

RawRead *reader = NULL;
boolean read = false;

// Work with IR
void callInterruptIR() {
  reader->handleInterruptIR();
}

void setupIR(uint8_t pin, uint16_t maxSize) {
  reader = new RawRead(maxSize);
  attachInterrupt(pin, callInterruptIR, CHANGE);
}

// Work with 433.92 Radio
void callInterruptRadio433() {
//  reader->handleInterruptRadio433();
}

void setupRadio433(uint8_t pin, uint16_t maxSize) {
  reader = new RawRead(maxSize);
  attachInterrupt(pin, callInterruptRadio433, CHANGE);
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  setupIR(5, 1024*3);
}

void loop() {
  if(!read && (reader->getStateIR() == 2 || reader->getStateIR() == -1)) {
    read = true;
    if(reader->getStateIR() == -1)
    Serial.print("state is ");
    Serial.println(reader->getStateIR());
    reader->print();
  }
}

