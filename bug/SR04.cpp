#include "Arduino.h"
#include "SR04.h"

SR04::SR04(uint8_t trig, uint8_t echo)
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  _trig = trig;
  _echo = echo;
  time = 0;
}

void SR04::pulse()
{
  digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);
  time = micros();
}

int16_t SR04::calibrate(int16_t val) {
  value = (val - 500) / 51;
  return value;
}

int16_t SR04::read()
{
  long now = micros();
  if (now - time < 500) {
    return -1;
  } else {
    if (now - time > 3000) {
      return calibrate(3000);
    } else {
      if (digitalRead(_echo) == 0) {
        return calibrate(now - time);
      } else {
        return -1;
      }
    }
  }
}

int16_t SR04::getValue() {
  return value;
}

