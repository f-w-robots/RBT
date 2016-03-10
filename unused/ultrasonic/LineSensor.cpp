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

int LineSensor::sensorsPosition() {
  readSensors();
  return correctPath(
           _sensors[5] < 300,
           _sensors[2] < 300,
           _sensors[3] < 300,
           _sensors[1] < 300,
           _sensors[4] < 300,
           _sensors[0] < 300
         );
//  return correctPath(
//           constrain(map(_sensors[5], 200, 800, 0, 10), 0, 10),
//           constrain(map(_sensors[2], 200, 800, 0, 10), 0, 10),
//           constrain(map(_sensors[3], 200, 800, 0, 10), 0, 10),
//           constrain(map(_sensors[1], 200, 800, 0, 10), 0, 10),
//           constrain(map(_sensors[4], 200, 800, 0, 10), 0, 10),
//           constrain(map(_sensors[0], 200, 800, 0, 10), 0, 10)
//         );
}

// 1 - stop
// 2 - right
// 3 - left
// 4 - right*2
// 5 - left*2
int LineSensor::correctPath(boolean v0, boolean vc, boolean vr, boolean vl, boolean vr2, boolean vl2) {
  if (!vc && !vr && !vl) {
    return 1;
  }
  if (!vr && !vc) {
    return 4;
  }
  if (!vl && !vc) {
    return 5;
  }
  if (!vr) {
    return 2;
  }
  if (!vl) {
    return 3;
  }  
}

//int LineSensor::correctPath(int v0, int vc, int vr, int vl, int vr2, int vl2) {
////  if (!vc && !vr && !vl) {
////    return 1;
////  }
////  if (!vr && !vc) {
////    return 4;
////  }
////  if (!vl && !vc) {
////    return 5;
////  }
////  if (!vr) {
////    return 2;
////  }
////  if (!vl) {
////    return 3;
////  }
//  int x = 10 - vc;
//  if(vr - vl < 0) {
//    return vr - vl - x;
//  }
//  if(vr - vl > 0) {
//    return vr - vl + x;
//  }
//  return 0;
//}

