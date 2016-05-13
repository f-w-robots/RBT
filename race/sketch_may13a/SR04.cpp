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

  pulsed = true;
  pulseTime = millis();
}

int16_t SR04::calibrate(int16_t val) {
  value = (val - 500) / 51;
  pulsed = false;
  return value;
}

void SR04::read()
{
  if (millis() - pulseTime > 50) {
    pulse();
    return;
  }
  if (!pulsed) {
    return;
  }
  long now = micros();
  if (now - time < 500) {
    return;
  } else {
    if (now - time > 30000) {
      calibrate(30000);
      return;
    } else {
      if (digitalRead(_echo) == 0) {
        calibrate(now - time);
        return;
      } else {
        return;
      }
    }
  }
}

int16_t SR04::getValue() {
  return value;
}

