#include "RawRead.h"
#ifndef IRReadRaw_h
#define IRReadRaw_h

class IRRawRead : public RawRead {
  public:
    IRRawRead(uint8_t pin, uint16_t maxSignalSize, InterruptCallback interruptCallback);
    ~IRRawRead();
    int8_t getState();
    void handleInterrupt();
};

#endif

