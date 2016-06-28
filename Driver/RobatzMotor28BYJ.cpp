#include <Arduino.h>
#include "RobatzMotor28BYJ.h"

RobatzMotor28BYJ::RobatzMotor28BYJ(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4) {
  motor = new Motor28BYJ (pin1, pin2, pin3, pin4);
}

boolean RobatzMotor28BYJ::update(byte data) {
  this->data = data;
  this->updated = true;
  return false;
}

void RobatzMotor28BYJ::loop() {
  if (updated) {
    int8_t t = data % 4;
    data = data / 4;
    if (t == 1)
      direction = 1;
    else if (t == 2)
      direction = -1;
    else
      direction = 0;


    if (data == 0)
      speed = 0;
    else
      speed = (-(long)data + 64) * 10000 / 64;

    updated = false;
  }

  if (speed == 0)
    return;

  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor->step(direction);
  }
}
