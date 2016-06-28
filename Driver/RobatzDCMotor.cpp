#include <Arduino.h>
#include "RobatzDCMotor.h"

RobatzDCMotor::RobatzDCMotor(uint8_t pinA, uint8_t pin1, uint8_t pin2) {
  this->pinA = pinA;
  this->pin1 = pin1;
  this->pin2 = pin2;
}

boolean RobatzDCMotor::update(byte data) {
  this->data = data;
  this->updated = true;
  return false;
}

void RobatzDCMotor::loop() {
  
  if (updated) {
    Serial.println("updated");
    digitalWrite(pin1, data % 2);
    data = data / 2;
    digitalWrite(pin2, data % 2);
    data = data / 2;
    digitalWrite(pinA, data * 4);
    updated = false;
  }
}
