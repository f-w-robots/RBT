#include "StepperMotor.h"

StepperMotor motor(A0,A1,2,3,4,5,6,7);

void setup(){
//  Serial.begin(9600);
}

void loop(){
  motor.step(1000, 1, 1);
}

