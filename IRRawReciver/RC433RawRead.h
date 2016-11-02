#include "RawRead.h"
#ifndef RC433ReadRaw_h
#define RC433ReadRaw_h

class RC433RawRead : public RawRead {
  public:
    RC433RawRead(uint8_t pin, uint16_t maxSignalSize, InterruptCallback interruptCallback);
    ~RC433RawRead();
    int8_t getState();
    void handleInterrupt();
  private:
    boolean start = false;
    long const MIN_DELTA = 200;
    long const MAX_DELTA = 100000;
    int longCount = 0;
    int veryLongCount = 0;
};

#endif

