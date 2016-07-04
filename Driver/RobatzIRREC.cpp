#include <Arduino.h>
#include "RobatzIRREC.h"

RobatzIRREC::RobatzIRREC(uint8_t pin) {
  this-> pin = pin;
  irrecv = new IRrecv(pin);
  irrecv->enableIRIn();
}

void RobatzIRREC::update(byte data) {
}

int32_t RobatzIRREC::outData() {
  return out;
}

byte RobatzIRREC::answerSize() {
  return 4;
}

boolean RobatzIRREC::loop() {
  unsigned long newTimeValue = micros() / speed;
  
  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    if (irrecv->decode(&results)) {
      out = results.value;
      irrecv->resume(); // Receive the next value
      return true;
    }
  }
  return false;
}

