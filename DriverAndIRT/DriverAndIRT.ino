#include "Motor28BYJ.h"
#include "I2C.h"

typedef union
{
  struct
  {
    unsigned char leftWheelForward : 1;
    unsigned char leftWheelReverse : 1;
    unsigned char rightWheelForward : 1;
    unsigned char rightWheelReverse : 1;
    unsigned char shoot : 1;
    unsigned char empty1 : 1;
    unsigned char empty2 : 1;
    unsigned char empty3 : 1;
  } bits;
  unsigned char byte;
} PackageHeader;

PackageHeader packageHeader;
uint8_t *data = new uint8_t[1];
boolean newPackage = false;
I2C i2c(1, data, &newPackage);

const int speed = 2000;

Motor28BYJ motor2(2, 3, 4, 5);
Motor28BYJ motor1(6, 7, 8, 9);

int8_t rightDirection = 0;
int8_t leftDirection = 0;

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

  packageHeader.byte = data[0];

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

