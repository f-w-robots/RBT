#include "Arduino.h"

#include "I2C.h"

I2C::I2C(char deviceId, InCallback inCallback, OutCallback outCallback) {
  this->deviceId = deviceId;
  this->inCallback = inCallback;
  this->outCallback = outCallback;
}

boolean I2C::check() {
  if (Serial.available() < 1)
    return init;

  char c = Serial.read();

  if (readPackage) {
    if (!pinId) {
      pinId = c;
    } else {
      dbgMsg("write Value");
      if (pinId != ' ')
        inCallback(pinId - 32, c);
      pinId = 0;
    }
  }

  if (dataCount > 0) {
    dataCount --;
    if (dataCount == 0) {
      readPackage = false;
      outCallback();
      dbgMsg("endPackage");
    }
    return init;
  }

  if (!init) {
    _checkInit(c);
  } else {
    if (c != deviceId) {
      _nextPackage();
    } else {
      _nextPackage();
      readPackage = true;
      dbgMsg("OK");
    }
  }
  return init;
}

void I2C::_checkInit(char c) {
  if (!initArr[initI] &&  c == initMask[initI]) {
    initI ++;
    if (initI >= initPackageSize) {
      init = true;
      dbgMsg("init");
    }
  } else {
    initI = 0;
  }
}

void I2C::_nextPackage() {
  dataCount = 8;
}

void I2C::responseStart(uint8_t size) {
  Serial.write((char)(size + 48));
}

void I2C::response(char c) {
  Serial.write(c);
}

void I2C::dbgMsg(char msg[]) {
  //  Serial.println(msg);
}

