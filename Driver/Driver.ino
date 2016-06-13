#include <SPI.h>
#include "Motor28BYJ.h"

int8_t rightDirection = 0;
int8_t leftDirection = 0;

unsigned long oldTimeValue = 0;
uint16_t speed = 3000;

Motor28BYJ motor2(2, 3, 4, 5);
Motor28BYJ motor1(6, 7, 8, 9);

void setup()
{
  Serial.begin(115200);
  SPCR |= bit (SPE);

  pinMode(MISO, OUTPUT);
  pinMode(10, OUTPUT);

  SPI.attachInterrupt();
}

void parseRequest(byte b) {
  int t = b % 4;
  if (t == 1)
    rightDirection = 1;
  else if (t == 2)
    rightDirection = -1;
  else
    rightDirection = 0;
  b = b / 4;
  t = b % 4;
  if (t == 1)
    leftDirection = 1;
  else if (t == 2)
    leftDirection = -1;
  else
    leftDirection = 0;
}

uint16_t packageSize = 0;

ISR (SPI_STC_vect)
{
  byte b = SPDR;
  if (b != 0 && packageSize == 0) {
    packageSize = b;
//    Serial.println(b);
  } else {
    if (packageSize > 0) {
      parseRequest(b);
      packageSize--;
    }
  }
}

void loop ()
{
  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor1.step(rightDirection);
    motor2.step(leftDirection);
  }
}
