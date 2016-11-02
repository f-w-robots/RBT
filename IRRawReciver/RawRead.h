#ifndef ReadRaw_h
#define ReadRaw_h

class RawRead {
  public:
    RawRead(uint16_t maxSignalSize);
    void setAttachIR();
    int8_t getStateIR();
    void handleInterruptIR();
    void print();
  private:
    uint16_t maxSignalSize;
    uint16_t *timings;
    int8_t state;
    uint16_t tindex;
    long lastTime;
};

#endif

