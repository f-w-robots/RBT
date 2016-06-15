#include "I2C.h"

I2C i2c(1, data, &newPackage);

unsigned long oldTimeValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  data[0] = 0;
  data[1] = 0;

}

void loop()
{
  if (!i2c.check()) return;

  if (newPackage) {
    newPackage = false;
    parsePackage();
    i2c.response(5);
  }
  doMove();
}

void parsePackage() {
  rightDirection = packageHeader.bits.rightWheelForward ? 1 : (packageHeader.bits.rightWheelReverse ? -1 : 0);
  leftDirection = packageHeader.bits.leftWheelForward ? 1 : (packageHeader.bits.leftWheelReverse ? -1 : 0);
}

void doMove() {
  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor2.step(leftDirection);
    motor1.step(rightDirection);
  }
}

