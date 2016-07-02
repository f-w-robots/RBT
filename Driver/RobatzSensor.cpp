#include <Arduino.h>
#include "RobatzSR04.h"
#include "RobatzSensor.h"

RobatzSensor::RobatzSensor(uint8_t pin) {
  this->pin = pin;
  
}

void RobatzSensor::update(byte data) {
  
}

byte RobatzSensor::outData() {
  return output;
}

boolean RobatzSensor::loop() {
//  unsigned long newTimeValue = millis() / latency;
//
//  if (newTimeValue != oldTimeValue) {
//    oldTimeValue = newTimeValue;
//    output = analogRead(pin) / 4;
//    return true;
//  }
//
//  return false;
  uint16_t newOutput = analogRead(pin) / 4;
  if(newOutput != output) {
    output = newOutput;
    return true;
  } else {
    return false;
  }
  
}
