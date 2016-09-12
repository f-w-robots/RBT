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
  if (irrecv->decode(&results)) {
    out = results.value;
    Serial.println(out);
    irrecv->resume(); // Receive the next value
    return true;
  }
  
  return false;
}

