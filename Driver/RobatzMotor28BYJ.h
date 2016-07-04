#include "Motor28BYJ.h"
#include "RobatzModule.h"

#ifndef RobatzMotor28BYJ_h
#define RobatzMotor28BYJ_h

class RobatzMotor28BYJ : public RobatzModule {
  public:
    RobatzMotor28BYJ(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    void update(byte data);
    boolean loop();
    int32_t outData();
    byte answerSize();
  private:
    byte data = 0;
    boolean updated = false;

    Motor28BYJ *motor;
    int8_t direction = 0;
    unsigned long oldTimeValue = 0;
    uint16_t speed = 3000;
};

#endif
