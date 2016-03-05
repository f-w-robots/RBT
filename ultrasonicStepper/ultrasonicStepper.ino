#include "LineSensor.h"
#include "Motor28BYJ.h"

const int speed = 1200;

Motor28BYJ motor1(2, 3, 4, 5);
Motor28BYJ motor2(6, 7, 8, 9);

// S0, S1, S2, Z
LineSensor line(A3, A4, A5, A2);

boolean move = false;
boolean turning = false;
int8_t right = 0;
int8_t left = 0;

int skipSensorsStep = 0;

unsigned long oldTimeValue = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (move)
    doMove();
  else
    readCommand();

  processSensors();
}

void doMove() {
  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue ;
    motor1.step(right);
    motor2.step(left);
  }
}

void readCommand() {
  if (Serial.available() > 0) {
    char request = Serial.read();
    if (request == 'f' || request == 'r' || request == 'l' || request  == 'x') {
      move = true;
      skipSensorsStep = 1000;
      if (request == 'f') {
        left = 1;
        right = -1;
      }
      if (request == 'x') {
        Serial.println(line.printSensors());
      }
      if (request == 'l') {
        turning = true;
        left = -1;
        right = -1;
      }
      if (request == 'r') {
        turning = true;
        left = 1;
        right = 1;
      }
    }
  }
}

void endStep() {
  if (move) {
    move = false;
    turning = false;
    Serial.write('w');
  }
}

void processSensors() {
  line.readSensor();
  if (skipSensorsStep > 0) {
    skipSensorsStep --;
    return;
  }
  if (line.sensorsRead()) {
    int8_t sforward, scenter, sright, sleft, sright2, sleft2 ;
    line.assignValues(sforward, scenter, sright, sleft, sright2, sleft2);
    if (sforward == 0 && !turning)
      endStep();
    if (sright2 > 0 && sleft2 > 0)
      endStep();
  }
  Serial.println(line.printSensors());
}
