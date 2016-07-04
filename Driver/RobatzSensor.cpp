#include <Arduino.h>
#include "RobatzSR04.h"
#include "RobatzSensor.h"

RobatzSensor::RobatzSensor(uint8_t pin) {
  this->pin = pin;
  
}

void RobatzSensor::update(byte data) {
  
}

int32_t RobatzSensor::outData() {
  return output;
}

byte RobatzSensor::answerSize() {
  return 2;
}

boolean RobatzSensor::loop() {
  uint16_t newOutput = analogRead(pin);
  if(newOutput != output) {
    output = newOutput;
    return true;
  } else {
    return false;
  }
  
}
