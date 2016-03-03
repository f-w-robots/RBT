#include "Arduino.h"

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
}

boolean LineSensor::sensorsRead() {
  return sensorsReadFinish;
}

void LineSensor::readSensor() {
  sensorsReadFinish = false;
  cd4051->switchInput(currentSensor);
  delayMicroseconds(100);
  Serial.println(analogRead(A2));
  sensorValues[currentSensor] = maps(calibrate(analogRead(analogIn)));
  currentSensor++;
  if (currentSensor >= 6) {
    currentSensor = 0;
    sensorsReadFinish = true;
  }
}

int LineSensor::calibrate(int value) {
  return (value - sensorsColibrationDonw[currentSensor]) * (1023.0 / sensorsColibrationUp[currentSensor]);
}

int LineSensor::maps(int value) {
  return constrain(map(value, 200, 800, 0, 10), 0, 10);
}

uint8_t LineSensor::getSensor(uint8_t i) {
  return sensorValues[i];
}

