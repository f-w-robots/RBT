#include "LineSensor.h"
#include "Motor28BYJ.h"

Motor28BYJ motor1(2, 3, 4, 5);
Motor28BYJ motor2(6, 7, 8, 9);

// S0, S1, S2, Z
LineSensor line(A3, A4, A5, A2);

boolean move = false;
int8_t right = 0;
int8_t left = 0;

unsigned long oldTimeValue = 0;
unsigned long newTimeValue = 0;

int speed = 1200;

int stepCount = 0;

char request = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (move)  {
    newTimeValue = micros() / speed;

    if (newTimeValue != oldTimeValue) {
      oldTimeValue = newTimeValue ;
      motor1.step(right);
      motor2.step(left);
      stepCount++;
      if (stepCount > 2500) {
        move = false;
        Serial.write('w');
      }
    }
  } else {
    if (Serial.available() > 0) {
      request = Serial.read();
      if (request == 'f' || request == 'r' || request == 'l') {
        move = true;
        stepCount = 0;
        if (request == 'f') {
          left = 1;
          right = -1;
        }
        if (request == 'l') {
          left = -1;
          right = -1;
        }
        if (request == 'r') {
          left = 1;
          right = 1;
        }
      }
    }
  }
}
