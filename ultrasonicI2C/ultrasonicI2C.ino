#include "LineSensor.h"
#include "Motor28BYJ.h"
#include "I2C.h"

boolean pins[4] = {false, false, false, false};
boolean needResponse = false;
boolean toSendResponse = false;

void inCallback(uint8_t pin, char c) {
  if (pin <= 4)
    pins[pin - 1] = (c == '1');
}

void outCallback() {
  needResponse = true;
//  Serial.write('6');
}

I2C i2c('1', inCallback, outCallback);

const int speed = 1000;

Motor28BYJ motor1(2, 3, 4, 5);
Motor28BYJ motor2(6, 7, 8, 9);

// S0, S1, S2, Z
LineSensor line(A3, A4, A5, A2  );

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

void rgb() {
  if(pins[0])
    digitalWrite(2, HIGH);
  else
    digitalWrite(2, LOW);
    
  if(pins[1])
    digitalWrite(3, HIGH);
  else
    digitalWrite(3, LOW);
    
  if(pins[2])
    digitalWrite(4, HIGH);
  else
    digitalWrite(4, LOW);
}

void loop()
{
  if (!i2c.check()) return;

  if(needResponse) 
    responseNextTick();
  
  rgb();

//  if (move)
//    doMove();
//  else
//    readCommand();
//
//  processSensors();
}

void responseNextTick() {  
  line.readSensor();

//  Serial.write((char)(line.getSensor(0) + 42));

  if (line.sensorsRead()) {
    needResponse = false;
  }  
}

boolean rightDirection() {
  return (pins[0] == pins[1] ? 0 : (pins[0] > pins[1] ? 1 : -1));
}

boolean leftDirection() {
  return (pins[2] == pins[3] ? 0 : (pins[2] > pins[3] ? 1 : -1));
}

void doMove() {
  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor1.step(rightDirection());
    motor2.step(leftDirection());
  }
}

void readCommand() {
  if (Serial.available() > 0) {
    char request = Serial.read();
    if (request == 'f' || request == 'r' || request == 'l') {
      move = true;
      skipSensorsStep = 1000;
      if (request == 'f') {
        left = 1;
        right = -1;
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

