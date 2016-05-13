#ifndef SR04_h
#define SR04_h

#include "Arduino.h"

class SR04
{
  public:
    SR04(uint8_t trig, uint8_t echo);
    void pulse();
    void read();
    int16_t getValue();
    int16_t calibrate(int16_t val);

  private:
    uint8_t _trig;
    uint8_t _echo;
    long time;
    long value;
    long pulseTime = 0;
    boolean pulsed = false;

};

#endif
