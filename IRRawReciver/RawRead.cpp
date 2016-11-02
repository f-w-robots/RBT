#include <Arduino.h>
#include "RawRead.h"

RawRead::RawRead(uint8_t pin, uint16_t maxSignalSize, InterruptCallback interruptCallback) {
  this->pin = pin;
  this->maxSignalSize = maxSignalSize;
  timings = new uint16_t[maxSignalSize];
  this->interruptCallback = interruptCallback;
  clear();
}

RawRead::~RawRead() {
  delete timings;
}

void RawRead::beginLisning() {
  clear();
  attachInterrupt(pin, interruptCallback, CHANGE);
}

void RawRead::stopLisning() {
  detachInterrupt(pin);
}

void RawRead::clear() {
  for (int i = 0; i < maxSignalSize; i++) {
    timings[i] = 0;
  }
}

int8_t RawRead::getState() {
  return -100;
}

void RawRead::handleInterrupt() {}

void RawRead::print() {
  Serial.print("Size: ");
  Serial.println(tindex);
  for (int i = 0; i < tindex; i++) {
    Serial.println(timings[i]);
  }
}

