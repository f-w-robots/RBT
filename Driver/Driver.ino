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
byte* inPackage = new byte[10];
int inPackagePos = 0;
int inPackageSize = 0;
byte* outPackage = new byte[1];

ISR (SPI_STC_vect)
{
  byte b = SPDR;

  if (packageSize == 0) {
    if (b > 0) {
      SPDR = 0;
      packageSize = max(b, 0);
      if(b > 1) {
        inPackageSize = b - 1;
        inPackagePos = -2;
//        inPackage = new byte[inPackageSize];
      }
    }
    return;
  }

  if (packageSize > 0) {
    packageSize--;
    inPackagePos++;
    if (inPackagePos < inPackageSize && inPackagePos > -1) {
      inPackage[inPackagePos] = SPDR;
      parseRequest(inPackage[inPackagePos]);
      
    }
      
    SPDR = outPackage[0];
    return;
  }
}

//ISR (SPI_STC_vect)
//{
//  byte b = SPDR;
//  if (b != 0 && packageSize == 0) {
//    packageSize = b;
////    Serial.println(b);
//  } else {
//    if (packageSize > 0) {
//      parseRequest(b);
//      packageSize--;
//    }
//  }
//}

void loop ()
{
  unsigned long newTimeValue = micros() / speed;

  if (newTimeValue != oldTimeValue) {
    oldTimeValue = newTimeValue;
    motor1.step(rightDirection);
    motor2.step(leftDirection);
  }
}
