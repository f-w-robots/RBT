#ifndef ReadRaw_h
#define ReadRaw_h

typedef void (*InterruptCallback)();

class RawRead {
  public:
    RawRead(uint8_t pin, uint16_t maxSignalSize, InterruptCallback interruptCallback);
    ~RawRead();
    void beginLisning();
    void stopLisning();
    virtual int8_t getState();
    virtual void handleInterrupt();
    void print();
    void clear();
  protected:
    uint8_t pin;
    uint16_t maxSignalSize;
    uint16_t *timings;
    int8_t state;
    uint16_t tindex;
    long lastTime;
    InterruptCallback interruptCallback;
};

#endif

