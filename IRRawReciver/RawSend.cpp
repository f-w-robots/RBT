#include <Arduino.h>
#include "RawSend.h"

void RawSend::send(uint8_t pin, uint16_t *timings, uint16_t length, boolean firstValue) {
  pinMode(pin, OUTPUT);
  int i=0;
  boolean sign = firstValue;
  while(i < length) {
    digitalWrite(pin, sign);
    delayMicroseconds(timings[i]);
    sign = !sign;
    i++;    
  }
}

