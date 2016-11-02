#include <Arduino.h>
#include "IRRawRead.h"

IRRawRead::IRRawRead(uint8_t pin, uint16_t maxSignalSize, InterruptCallback interruptCallback)
  : RawRead(pin, maxSignalSize, interruptCallback)  { }

int8_t IRRawRead::getState() {
  if (state == 2 || state == -1) {
    return state;
  }
  long d = micros() - lastTime;
  if (state == 1 && d > 1000000) {
    state = 2;
  }
  return this->state;
}

void IRRawRead::handleInterrupt() {
  if (state == 2 || state == -1) {
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
    if (delta > 20000) {
      state = 2;
      return;
    }
    timings[tindex] = delta;
    lastTime = currentTime;
    tindex++;
  }
}

