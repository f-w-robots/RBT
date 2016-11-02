#ifndef RawSend_h
#define RawSend_h

class RawSend {
  public:
    static void send(uint8_t pin, uint16_t  *timings, uint16_t length, boolean firstValue = 1);
};

#endif

