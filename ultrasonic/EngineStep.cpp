//#include "Arduino.h"
//#include "EngineStep.h"
//
//// ENA, EN1, EN2, EN3, EN4, ENB
//EngineStep::EngineStep(Motor28BYJ* motor) {
//  _motor= motor;
//}
//
//void EngineStep::command(String command) {
//  if (command == "rf") {
//    right();
//    forward();
//  } else if (command == "lf") {
//    left();
//    forward();
//  } else if (command == "f") {
//    forward();
//  } else if (command == "r") {
//    right();
//  } else if (command == "l") {
//    left();
//  } else if (command == "s") {
//    revert();
//  }
//}
//
//void EngineStep::forward() {
//  _motor->step(5000, 1, 1);
//}
//
//void EngineStep::right() {
//  _motor->step(5000, 1, 0);
//}
//
//void EngineStep::left() {
//  _motor->step(5000, 0, 1);
//}
//
//void EngineStep::revert() {
//  _motor->step(5000, -1, 1);
//}
