#include <Arduino.h>
#include "DeviceRC522.h"

DeviceRC522::DeviceRC522(uint8_t ss_pin, uint8_t rst_pin) {
  mfrc522 = new MFRC522(ss_pin, rst_pin);
  SPI.begin();           // Init SPI bus
  mfrc522->PCD_Init();    // Init MFRC522
}

void DeviceRC522::tick() {
  unsigned long newTimeValue = millis() / 300;
  if (newTimeValue == oldTimeValue) {
    return;
  }
  if ( ! mfrc522->PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522->PICC_ReadCardSerial()) {
    return;
  }
  // Show some details of the PICC (that is: the tag/card)
  dump_byte_array(mfrc522->uid.uidByte, mfrc522->uid.size);
}

boolean DeviceRC522::newData() {
  return updated;
}

byte *DeviceRC522::readData() {
  updated = false;
  return buffer;
}

void DeviceRC522::dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize && i < 4; i++) {
    this->buffer[i] = buffer[i];
  }
  buffer[4] = 0;
  updated = true;
}

