#include <Arduino.h>
#include "StepperMotor.h"

StepperMotor::StepperMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin1a, uint8_t pin2a, uint8_t pin3a, uint8_t pin4a) {
  _pins[0] = pin1;
  _pins[1] = pin2;
  _pins[2] = pin3;
  _pins[3] = pin4;
  _pins[4] = pin1a;
  _pins[5] = pin2a;
  _pins[6] = pin3a;
  _pins[7] = pin4a;

  for (int i = 0; i < 8; i++) {
    pinMode(this->_pins[i], OUTPUT);
  }
}

void StepperMotor::step(int duration, int8_t directionA, int8_t directionB) {
  duration = abs(duration);
  directionB = -directionB;

  for (int sequence = 0;  sequence <= duration / 8; sequence++) {
    for (int position = 0; ( position < 8 ) && ( position < ( duration - sequence * 8 )); position++) {
      delayMicroseconds(_speed);
      for (int pin = 0; pin < 4; pin++) {
        digitalWrite(_pins[pin], _sequence[(int)(3.5 - (3.5 * directionA) + (directionA * position))][pin]);
        digitalWrite(_pins[pin + 4], _sequence[(int)(3.5 - (3.5 * directionB) + (directionB * position))][pin]);
      }
    }
  }
}
