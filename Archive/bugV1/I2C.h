#ifndef I2C_h
#define I2C_h

typedef void (*InCallback)(uint8_t pin, char c);
typedef void (*OutCallback)();

class I2C
{
  public:
    I2C(char deviceId, InCallback inCallback, OutCallback outCallback);
    boolean check();
    void responseStart(uint8_t size);
    void response(char c);

  private:
    void _checkInit(char c);
    void _nextPackage(uint8_t size);
    void dbgMsg(char msg[]);
    void switchLed13();

    boolean led13State = false;
    boolean init = false;
    static const uint8_t initPackageSize = 6;
    boolean initArr[initPackageSize] = {false, false, false, false, false, false};
    char initMask[initPackageSize] = {'0', '4', 'I', 'N', 'I', 'T'};
    uint8_t initI = 0;
    uint16_t dataCount = 0;
    char deviceId = 0;
    int pinId = 0;
    boolean needPackageSize = false;
    boolean readPackage = false;
    boolean packageSize = false;
    InCallback inCallback;
    OutCallback outCallback;
};

#endif

