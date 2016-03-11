#ifndef Config_h
#define Config_h

class Config {
  public:
    static uint8_t sensorCount();
    static void sensorCount(int8_t count);
    static void writeDonwSensor(uint8_t number, uint16_t value);
    static uint16_t readDonwSensor(uint8_t number);
    static void writeUpSensor(uint8_t number, uint16_t value);
    static uint16_t readUpSensor(uint8_t number);
  private:
    static int8_t _sensorCount;
};

#endif
