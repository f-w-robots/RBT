#ifndef I2C_h
#define I2C_h

class I2C
{
  public:
    I2C(char deviceId, uint8_t *data, boolean *newPackage);
    boolean check();
    void response(char c);

  private:
    boolean acceptPackage();
    void dbgMsg(char msg[]);
    void switchLed13();

    boolean led13State = false;
    byte initByte = 29;
    boolean init = false;
    uint8_t *package;
    uint8_t deviceId = 0;
    uint8_t packageSize = 0;
    uint8_t packageI = 0;
    uint8_t packageId = 0;
    boolean packageRead = false;
    boolean *newPackage;
};

#endif

