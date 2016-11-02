#include <Arduino.h>
#include "RC433RawRead.h"

//TODO
// Опредедение знака начала сигнала, и сдвиг шума сделаны через костыли - переделать

RC433RawRead::RC433RawRead(uint8_t pin, uint16_t maxSignalSize, InterruptCallback interruptCallback)
  : RawRead(pin, maxSignalSize, interruptCallback)  { }

int8_t RC433RawRead::getState() {
  return this->state;
}

void RC433RawRead::handleInterrupt() {
  if (tindex >= maxSignalSize) {
    state = -1;
    stopLisning();
    return;
  }
  long currentTime = micros();
  long delta = currentTime - lastTime;
  timings[tindex] = delta;
  lastTime = currentTime;

  tindex ++;
  if (!start) {
    if (delta > MIN_DELTA) {
      longCount++;
    } else {
      longCount = 0;
    }
    if (longCount > 10 && digitalRead(pin)) {
      start = true;
      state = 1;
    }
    if (!start && tindex > 60) {
      // memcpy()
      for (int i = 35; i < tindex ; i++) {
        timings[i - 35] = timings[i];
      }
      tindex = tindex - 35;
    }
  }

  if (delta > MAX_DELTA) {
    veryLongCount ++;
  }

  if (veryLongCount > 1) {
    state = 2;
    stopLisning();
  }
}

