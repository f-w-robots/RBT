#include <Arduino.h>
#include "RobatzDCMotor.h"

RobatzDCMotor::RobatzDCMotor(uint8_t pinA, uint8_t pin1, uint8_t pin2) {
  this->pinA = pinA;
  this->pin1 = pin1;
  this->pin2 = pin2;
}

void RobatzDCMotor::update(byte data) {
  Serial.println(data);
  this->data = data;
  this->updated = true;
}

int32_t RobatzDCMotor::outData() {
  return 0;
}

byte RobatzDCMotor::answerSize() {
  return 0;
}

boolean RobatzDCMotor::loop() {

  if (updated) {
    digitalWrite(pin1, data % 2);
    data = data / 2;
    digitalWrite(pin2, data % 2);
    data = data / 2;
    analogWrite(pinA, 255);
    updated = false;
  }

  return false;
}
