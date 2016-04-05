#include <Arduino.h>
#include "Motor28BYJ.h"

Motor28BYJ::Motor28BYJ(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
  _pins[0] = pin1;
  _pins[1] = pin2;
  _pins[2] = pin3;
  _pins[3] = pin4;

  for (int i = 0; i < 4; i++) {
    pinMode(this->_pins[i], OUTPUT);
  }
}

void Motor28BYJ::step(int direction) {
  if (direction == 0) {
    for (int pin = 0; pin < 4; pin++) {
      digitalWrite(_pins[pin], LOW);
    }
    return;
  }
  for (int pin = 0; pin < 4; pin++) {
    digitalWrite(_pins[pin], _sequence[(int)(3.5 - (3.5 * direction) + (direction * position))][pin]);
  }
  position ++;
  if (position > 7)
    position = 0;
}
