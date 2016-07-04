#include "RobatzModule.h"
#include <IRremote.h>

#ifndef RobatzIRSend_h
#define RobatzIRSend_h

class RobatzIRSend : public RobatzModule {
  public:
    RobatzIRSend(uint8_t pin);
    void update(byte data);
    boolean loop();
    int32_t outData();
    byte answerSize();
  private:
    int8_t pin = 0;
    byte data = 0;
    boolean updated = false;
    IRsend *irsend;
};

#endif
