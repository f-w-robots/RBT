#include "RobatzModule.h"
#include <IRremote.h>

#ifndef RobatzIRREC_h
#define RobatzIRREC_h

class RobatzIRREC : public RobatzModule {
  public:
    RobatzIRREC(uint8_t pin);
    void update(byte data);
    boolean loop();
    int32_t outData();
    byte answerSize();
  private:
    int8_t pin = 0;
    int8_t out = 0;
    IRrecv *irrecv;
    decode_results results;
    unsigned long oldTimeValue = 0;
    uint16_t speed = 200;
};

#endif
