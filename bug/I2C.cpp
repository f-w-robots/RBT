#include "Arduino.h"

#include "I2C.h"

I2C::I2C(char deviceId, uint8_t *data, boolean *newPackage) {
  this->deviceId = deviceId;
  this->package = data;
  this->newPackage = newPackage;
}

boolean I2C::check() {
  if (Serial.available() < 1)
    return init;

  char c = Serial.read();

  if (!init && (c == initByte)) {
    init = true;
    switchLed13();
    return init;
  }

  if(!init)
    return init;

  if (!packageRead) {
    dbgMsg("beginReadPakcage");
    packageSize = 0;
    packageRead = true;
    packageId = c;
    return init;
  }

  if (packageSize == 0) {
    dbgMsg("setPackageSize");
    packageSize = c;
    packageI = 0;
    return init;
  }

  if (acceptPackage()) {
    package[packageI] = c;
    dbgMsg("readPackage");
  }
  packageI ++;
  dbgMsg("packageI++");

  if (packageI == packageSize) {
    dbgMsg("packageEnd");
    packageRead = false;
    if (acceptPackage())
      *newPackage = true;
  }
}

boolean I2C::acceptPackage() {
  return packageId == deviceId;
}

void I2C::response(char c) {
  Serial.write(c);
}

void I2C::dbgMsg(char msg[]) {
//  Serial.println(msg);
}

void I2C::switchLed13() {
  led13State = !led13State;
  digitalWrite(13, led13State);
}

