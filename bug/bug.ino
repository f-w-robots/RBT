#include "LineSensor.h"
#include "Motor28BYJ.h"
#include "I2C.h"
#include "Config.h"

typedef union
{
  struct
  {
    unsigned char setSensorsCount : 1;
    unsigned char wheels : 1;
    unsigned char leftWheelForward : 1;
    unsigned char leftWheelReverse : 1;
    unsigned char rightWheelForward : 1;
    unsigned char rightWheelReverse : 1;
    unsigned char calibrationLower : 1;
    unsigned char calibrationUpper : 1;
  } bits;
  unsigned char byte;
} PackageHeader;

PackageHeader packageHeader;

boolean newPackage = false;

boolean needResponse = false;

uint8_t *data = new uint8_t[2];
I2C i2c(1, data, &newPackage);

const int speed = 2000;

Motor28BYJ motor2(2, 3, 4, 5);
Motor28BYJ motor1(6, 7, 8, 9);

int8_t rightDirection = 0;
int8_t leftDirection = 0;

uint8_t lineInputs[] = {A0, A1, A2, A3, A4};
LineSensor line(lineInputs, 5);

unsigned long oldTimeValue = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  data[0] = 0;
  data[1] = 0;
}

void loop()
{
  if (!i2c.check()) return;

  packageHeader.byte = data[0];

  if (needResponse)
    responseNextTick();

  if (newPackage) {
    newPackage = false;
    needResponse = true;
    parsePackage();
    i2c.response(5);
  }
  doMove();
}

void parsePackage() {
  if (packageHeader.bits.calibrationLower) {
    line.calibrateDown();
  }
  if (packageHeader.bits.calibrationUpper) {
    line.calibrateUp();
  }

  if (data[1] != 0) {
    Config::sensorCount(data[1]);
    data[1] = 0;
  }

  if (packageHeader.bits.wheels) {
    rightDirection = packageHeader.bits.rightWheelForward ? 1 : (packageHeader.bits.rightWheelReverse ? -1 : 0);
    leftDirection = packageHeader.bits.leftWheelForward ? 1 : (packageHeader.bits.leftWheelReverse ? -1 : 0);
  }
}

void responseNextTick() {
  i2c.response((char)(line.readSensor()));

  if (line.sensorsRead()) {
    needResponse = false;
  }
}

void doMove() {
  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor2.step(leftDirection);
    motor1.step(rightDirection);
  }
}

