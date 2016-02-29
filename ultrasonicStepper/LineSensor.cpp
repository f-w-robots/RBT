#include "Arduino.h"

#include "LineSensor.h"

LineSensor::LineSensor(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t analog) {
  _pins[0] = pin0;
  pinMode(pin0, OUTPUT);
  _pins[1] = pin1;
  pinMode(pin1, OUTPUT);
  _pins[2] = pin2;
  pinMode(pin2, OUTPUT);

  _analog = analog;

  _cd4051 = new CD4051(pin0, pin1, pin2);
}


String LineSensor::printSensors() {
  String req = "";
  for (int i = 0; i < 6; i++) {
    req += _sensors[i];
    req += " ";
  }
  return req;
}

String LineSensor::printSensorsBool() {
  String req = "";
  for (int i = 0; i < 6; i++) {
    req += (_sensors[i] < 300);
    req += " ";
  }
  return req;
}

boolean LineSensor::sensorsRead() {
  return _sensorsRead;
}

void LineSensor::readSensor() {
  _sensorsRead = false;
  _cd4051->switchInput(_currentSensor);
  delayMicroseconds(100);
  _sensors[_currentSensor] = (analogRead(_analog) - _sensorsColibration[_currentSensor]) * (1023.0 / _sensorsColibrationUp[_currentSensor]);
  _currentSensor++;
  if(_currentSensor >= 6) {
    _currentSensor = 0;
    _sensorsRead = true;
  }
}

void LineSensor::readSensors() {
  for (int i = 0; i < 6; i++) {
    _cd4051->switchInput(i);
    delayMicroseconds(100);
    _sensors[i] = (analogRead(_analog) - _sensorsColibration[i]) * (1023.0 / _sensorsColibrationUp[i]);
  }
}

void LineSensor::assignValues(int8_t &v0, int8_t &vc, int8_t &vr, int8_t &vl, int8_t &vrr, int8_t &vll) {
  v0 = constrain(map(_sensors[5], 200, 800, 0, 10), 0, 10);
  vc = constrain(map(_sensors[2], 200, 800, 0, 10), 0, 10);
  vr = constrain(map(_sensors[3], 200, 800, 0, 10), 0, 10);
  vl = constrain(map(_sensors[1], 200, 800, 0, 10), 0, 10);
  vrr = constrain(map(_sensors[4], 200, 800, 0, 10), 0, 10);
  vll = constrain(map(_sensors[0], 200, 800, 0, 10), 0, 10);
}

