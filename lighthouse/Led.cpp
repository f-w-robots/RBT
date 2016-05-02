#include <Arduino.h>
#include "Led.h"

Led::Led(uint8_t wifiPin, uint8_t socketPin) {
  this->wifiPin = wifiPin;
  this->socketPin = socketPin;

  pinMode(wifiPin, OUTPUT);
  pinMode(socketPin, OUTPUT);
  digitalWrite(wifiPin, LOW);
  digitalWrite(socketPin, LOW);
}

void Led::set(boolean wifiPinValue, boolean socketPinValue) {
  digitalWrite(this->wifiPin, wifiPinValue);
  digitalWrite(this->socketPin, socketPinValue);
}

void Led::blink(boolean mode, int16_t timeout) {
  delay(timeout);
  if (mode)
    digitalWrite(socketPin, LOW);
  else
    digitalWrite(wifiPin, LOW);
  delay(timeout);
  if (mode)
    digitalWrite(socketPin, HIGH);
  else
    digitalWrite(wifiPin, HIGH);
}

void Led::setBlue(boolean wifiPinValue) {
  digitalWrite(this->wifiPin, wifiPinValue);
}

void Led::setRed(boolean socketPinValue) {
  digitalWrite(this->socketPin, socketPinValue);
}

