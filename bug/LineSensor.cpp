#include "Arduino.h"
#include "Config.h"
#include "LineSensor.h"

LineSensor::LineSensor(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t analogIn) {
  pins[0] = pin0;
  pinMode(pin0, OUTPUT);
  pins[1] = pin1;
  pinMode(pin1, OUTPUT);
  pins[2] = pin2;
  pinMode(pin2, OUTPUT);

  this->analogIn = analogIn;

  cd4051 = new CD4051(pin0, pin1, pin2);

  int sensorsCount = Config::sensorCount();

  sensorValues = new int16_t[sensorsCount];
  sensorsColibrationDown = new int16_t[sensorsCount];
  sensorsColibrationUp = new int16_t[sensorsCount];
  if (sensorsCount > 9)
    return;
  for (int8_t i = 0;  i < sensorsCount; i++) {
    sensorsColibrationDown[i] = Config::readDownSensor(i);
    sensorsColibrationUp[i] = Config::readUpSensor(i);
  }
}

boolean LineSensor::sensorsRead() {
  return sensorsReadFinish;
}

uint16_t LineSensor::readSensor() {
  sensorsReadFinish = false;
  cd4051->switchInput(currentSensor);
  delayMicroseconds(100);
  uint16_t value = maps(calibrate(analogRead(analogIn), currentSensor));
  sensorValues[currentSensor] = value;
  currentSensor++;
  if (currentSensor >= Config::sensorCount()) {
    currentSensor = 0;
    sensorsReadFinish = true;
  }
  return value;
}


uint16_t LineSensor::readRawSensor(uint8_t sensor) {
  cd4051->switchInput(sensor);
  delayMicroseconds(300);
  return analogRead(analogIn);
}

int LineSensor::calibrate(int value, int sensor) {
  return (value - sensorsColibrationDown[sensor]) * (1023.0 / (sensorsColibrationUp[sensor] - sensorsColibrationDown[sensor]));
}

int LineSensor::maps(int value) {
  int v = value / 100;
  if (v < 0)
    v = 0;
  if (v > 9)
    v = 9;
  return v;
}

void LineSensor::calibrateDown() {
  for (uint8_t i = 0; i < Config::sensorCount(); i++) {
    Config::writeUpSensor(i, readRawSensor(i));
  }
}

void LineSensor::calibrateUp() {
  for (uint8_t i = 0; i < Config::sensorCount(); i++) {
    Config::writeDownSensor(i, readRawSensor(i));
  }
}


