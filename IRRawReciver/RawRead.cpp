#include <Arduino.h>
#include "RawRead.h"

RawRead::RawRead(uint16_t _maxSignalSize) {
  this->maxSignalSize = _maxSignalSize;
  timings = new uint16_t[maxSignalSize];
  for (int i = 0; i < maxSignalSize; i++) {
    timings[i] = 0;
  }
}

int8_t RawRead::getStateIR() {
  if(state == 2 || state == -1) {
    return state;
  }
  long d = micros() - lastTime;
  if (state == 1 && d > 1000000) {
    state = 2;
  }
  return this->state;
}

void RawRead::handleInterruptIR() {
  if(state == 2 || state == -1) {
    return;
  }
  if (state == 0) {
    timings[0] = 0;
    lastTime = micros();
    tindex = 1;
    state = 1;
    return;
  } else {
    if (tindex >= maxSignalSize) {
      state = -1;
      return;
    }
    long currentTime = micros();
    long delta = currentTime - lastTime;
    if(delta > 20000) {
      state = 2;
      return;
    }
    timings[tindex] = delta;
    lastTime = currentTime;
    tindex++;
  }
}

void RawRead::print() {
  Serial.print("Size: ");
  Serial.println(tindex);
  for(int i=0; i < tindex; i++) {
    Serial.println(timings[i]);
  }
}

