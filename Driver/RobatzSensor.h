#include "SR04.h"
#include "RobatzModule.h"

#ifndef RobatzSensor_h
#define RobatzSensor_h

class RobatzSensor : public RobatzModule {
  public:
    RobatzSensor(uint8_t pin);
    void update(byte data);
    boolean loop();
    int32_t outData();
    byte answerSize();
  private:
    uint16_t output = 0;
    uint8_t pin = 0;
    unsigned long oldTimeValue = 0;
    uint16_t latency = 2000;
};

#endif
