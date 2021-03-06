#include "LineSensor.h"
#include "Motor28BYJ.h"
#include "I2C.h"
#include "Config.h"
#include "SR04.h"

boolean pins[4] = {false, false, false, false};
boolean needResponse = false;
int8_t calibrationMode = 0;

void inCallback(uint8_t pin, char c) {
  if (pin == 6) {
    Config::sensorCount(c - 48);
  }
  if (pin == 5)
    calibrationMode = c - 48;
  if (pin <= 4)
    pins[pin - 1] = (c == '1');
}

I2C i2c('1', inCallback, outCallback);

void outCallback() {
  needResponse = true;
  i2c.responseStart(Config::sensorCount() + 1);
}

const int speed = 2000;

Motor28BYJ motor2(2, 3, 4, 5);
Motor28BYJ motor1(6, 7, 8, 9);
SR04 sr04(12, 11);

uint8_t lineInputs[] = {A0, A1, A2, A3, A4};
LineSensor line(lineInputs, 5);

unsigned long oldTimeValue = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop()
{
  if (!i2c.check()) return;

  if (calibrationMode != 0) {
    if (calibrationMode == 1) {
      line.calibrateDown();
      calibrationMode = 0;
    }
    if (calibrationMode == 2) {
      line.calibrateUp();
      calibrationMode = 0;
    }
    return;
  }

  if (needResponse) {
    responseNextTick();
  }

  doMove();
}

void responseNextTick() {
  i2c.response((char)(line.readSensor() + 48));

  if (line.sensorsRead()) {
    int v = sr04.getValue();

    i2c.response((char)(v + 48));
    needResponse = false;
  }
}

int8_t rightDirection() {
  return (pins[0] == pins[1] ? 0 : (pins[0] > pins[1] ? 1 : -1));
}

int8_t leftDirection() {
  return (pins[2] == pins[3] ? 0 : (pins[2] > pins[3] ? 1 : -1));
}

void doMove() {
  unsigned long newTimeValue = micros() / speed;

  sr04.read();

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor2.step(leftDirection());
    motor1.step(rightDirection());
  }
}

