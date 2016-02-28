#ifndef StepperMotor_h
#define StepperMotor_h

class StepperMotor {
  public:
    StepperMotor(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t pin1a, uint8_t pin2a, uint8_t pin3a, uint8_t pin4a);
    void step(int duration, int8_t directionA, int8_t directionB);
  private:
  int _pins[8];
  int _speed = 1000;
  const boolean _sequence[8][4] = {
      {LOW, LOW, LOW, HIGH },
      {LOW, LOW, HIGH, HIGH},
      {LOW, LOW, HIGH, LOW },
      {LOW, HIGH, HIGH, LOW},
      {LOW, HIGH, LOW, LOW },
      {HIGH, HIGH, LOW, LOW},
      {HIGH, LOW, LOW, LOW },
      {HIGH, LOW, LOW, HIGH}
    };
};

#endif
