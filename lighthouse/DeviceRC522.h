#include <MFRC522.h>

#ifndef DeviceRC522_h
#define DeviceRC522_h

class DeviceRC522
{
  public:
    DeviceRC522(uint8_t ss_pin, uint8_t rst_pin);
    void tick();
    boolean newData();
    byte* readData();

  private:
    MFRC522 *mfrc522;
    byte buffer[5];
    boolean updated;
    void dump_byte_array(byte *buffer, byte bufferSize);
    unsigned long oldTimeValue = 0;
};

#endif

