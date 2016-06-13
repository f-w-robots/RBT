#ifndef Motor28BYJ_h
#define Motor28BYJ_h

class Motor28BYJ {
  public:
    Motor28BYJ(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);
    void step(int direction);
  private:
    int _pins[4];
    int _speed = 1000;
    uint8_t position = 0;
    const boolean _sequence[8][4] = {
      {HIGH, LOW,  LOW,  LOW},
      {LOW, HIGH,  LOW,  LOW},
      {LOW,  LOW, HIGH,  LOW},
      {LOW,  LOW,  LOW, HIGH},
    };
};

#endif
