#include "IRRawRead.h"
#include "RC433RawRead.h"
const uint8_t INPUT_PIN = 5;

RawRead *reader = NULL;
boolean read = false;

void callInterrupt() {
  reader->handleInterrupt();
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  //  reader = new IRRawRead(INPUT_PIN, 2014 * 3, callInterrupt);
  reader = new RC433RawRead(INPUT_PIN, 2014 * 3, callInterrupt);
  reader->beginLisning();
}

void loop() {
  if (!read && (reader->getState() == 2 || reader->getState() == -1)) {
    read = true;
    reader->stopLisning();
    if (reader->getState() == -1) {
      Serial.println("signal very long");
    } else {
      Serial.println("signal is complete recived");
    }
    reader->print();
  }
}

