#include "Motor28BYJ.h"
#include "RobatzModule.h"

#ifndef RobatzDCMotor_h
#define RobatzDCMotor_h

class RobatzDCMotor : public RobatzModule {
  public:
    RobatzDCMotor(uint8_t pinA, uint8_t pin1, uint8_t pin2);
    void update(byte data);
    boolean loop();
    byte outData();
  private:
    byte data = 0;
    boolean updated = false;
    uint8_t pinA;
    uint8_t pin1;
    uint8_t pin2;
};

#endif
