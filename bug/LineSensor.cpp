#include "Arduino.h"
#include "Config.h"
#include "LineSensor.h"

LineSensor::LineSensor(uint8_t inputs[], uint8_t inputs_size) {
  this->currentSensor = 0;

  int sensorsCount = Config::sensorCount();
  if (inputs_size < sensorsCount || sensorsCount > 9)
    return;

  sensorInputs = new uint8_t[sensorsCount];
  sensorValues = new int16_t[sensorsCount];
  sensorsColibrationDown = new int16_t[sensorsCount];
  sensorsColibrationUp = new int16_t[sensorsCount];

  for (int8_t i = 0;  i < sensorsCount; i++) {
    sensorInputs[i] = inputs[i];
    sensorsColibrationDown[i] = Config::readDownSensor(i);
    sensorsColibrationUp[i] = Config::readUpSensor(i);
  }
}

boolean LineSensor::sensorsRead() {
  return sensorsReadFinish;
}

uint16_t LineSensor::readSensor() {
  sensorsReadFinish = false;
  uint16_t value = maps(calibrate(analogRead(sensorInputs[currentSensor]), currentSensor));
  sensorValues[currentSensor] = value;
  currentSensor++;
  if (currentSensor >= Config::sensorCount()) {
    currentSensor = 0;
    sensorsReadFinish = true;
  }
  return value;
}


uint16_t LineSensor::readRawSensor(uint8_t sensor) {
  return analogRead(sensorInputs[sensor]);
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
    Config::writeDownSensor(i, readRawSensor(i));
  }
}

void LineSensor::calibrateUp() {
  for (uint8_t i = 0; i < Config::sensorCount(); i++) {
    Config::writeUpSensor(i, readRawSensor(i));
  }
}


