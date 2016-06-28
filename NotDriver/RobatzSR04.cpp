#include <Arduino.h>
#include "RobatzSR04.h"

RobatzSR04::RobatzSR04(uint8_t trig, uint8_t echo) {
  sr04 = new SR04(trig, echo);
  sr04->setMaxDistance(255);
}

void RobatzSR04::update(byte data) {
  this->data = data;
  this->updated = true;
}

byte RobatzSR04::outData() {
  return output;
}

boolean RobatzSR04::loop() {
  if (updated) {
   
    updated = false;
  }

  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    output = sr04->readNow();
    return true;
  }

  return false;
}
