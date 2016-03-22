#include "LineSensor.h"
#include "Motor28BYJ.h"
#include "I2C.h"
#include "Config.h"

boolean led13State = HIGH;
uint16_t led13StateDelay = 0;

void switchLed13() {
  led13State = !led13State;
  digitalWrite(13, led13State);
}

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
  i2c.responseStart(Config::sensorCount());
}

const int speed = 1000;

Motor28BYJ motor1(2, 3, 4, 5);
Motor28BYJ motor2(6, 7, 8, 9);

// S0, S1, S2, Z
LineSensor line(A0);

unsigned long oldTimeValue = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
}

void loop()
{
  if (!i2c.check()) return;


  if (needResponse)
    if (calibrationMode == 0) {
      responseNextTick();
    } else {
      if (calibrationMode == 2) {
        line.calibrateDown();
        calibrationMode = 0;
      }
      if (calibrationMode == 1) {
        line.calibrateUp();
        calibrationMode = 0;
      }
    }

  doMove();
}

void responseNextTick() {
  i2c.response((char)(line.readSensor() + 48));

  if (line.sensorsRead()) {
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

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor1.step(rightDirection());
    motor2.step(leftDirection());

    if (leftDirection() != 0 && leftDirection() != 0) {
      led13StateDelay++;
      if (led13StateDelay >= 1000) {

        led13StateDelay = 0;
        switchLed13();
      }
    }
  }
}

