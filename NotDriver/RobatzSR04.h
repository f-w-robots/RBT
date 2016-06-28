#include "SR04.h"
#include "RobatzModule.h"

#ifndef RobatzSR04_h
#define RobatzSR04_h

class RobatzSR04 : public RobatzModule {
  public:
    RobatzSR04(uint8_t trig, uint8_t echo);
    void update(byte data);
    boolean loop();
    byte outData();
  private:
    byte data = 0;
    boolean updated = false;
    byte output = 0;

    SR04 *sr04;
    unsigned long oldTimeValue = 0;
    uint16_t speed = 1000;
};

#endif
