#ifndef Led_h
#define Led_h

class Led {
  public:
    Led(uint8_t wifiPin, uint8_t socketPin);
    void set(boolean wifiPinValue, boolean socketPinValue);
    void blink(boolean mode, int16_t timeout);
  private:
    uint8_t socketPin;
    uint8_t wifiPin;
};

#endif

