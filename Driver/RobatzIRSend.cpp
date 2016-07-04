#include <Arduino.h>
#include "RobatzIRSend.h"

RobatzIRSend::RobatzIRSend(uint8_t pin) {
  this-> pin = pin;
  irsend = new IRsend();
}

void RobatzIRSend::update(byte data) {
  this->data = data;
  this->updated = true;
}

int32_t RobatzIRSend::outData() {
  return 0;
}

byte RobatzIRSend::answerSize() {
  return 0;
}

boolean RobatzIRSend::loop() {
  if(updated) {
    updated = false;
    irsend->sendSony(0x90, 12);
  }
  return false;
}

