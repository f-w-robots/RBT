#include <SPI.h>
#include "RobatzSR04.h"

void setupSPI()
{
  SPCR |= bit (SPE);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
}

int16_t packageSize = 0;

uint16_t distance = 0;

int outSize = 0;
byte* inPackage = new byte[10];
int inPackagePos = 0;
int inPackageSize = 0;
byte* outPackage = new byte[1];

ISR (SPI_STC_vect)
{
  byte b = SPDR;

  if (packageSize == 0) {
    if (b > 0) {
      SPDR = outSize;
      outSize = 0;
      packageSize = max(b, outSize);
      if(b > 1) {
        inPackageSize = b - 1;
        inPackagePos = -2;
      }
    }
    return;
  }

  if (packageSize > 0) {
    packageSize--;
    inPackagePos++;
    if (inPackagePos < inPackageSize && inPackagePos > -1) {
      inPackage[inPackagePos] = SPDR;
    }
      
    SPDR = outPackage[0];
    return;
  }
}

RobatzModule *sr04;

void setup() {
  Serial.begin(115200);
    
  sr04 = new RobatzSR04(9, 8);
  
  setupSPI();

//  pinMode(3, OUTPUT);
//  pinMode(4, OUTPUT);
//  pinMode(5, OUTPUT);
}

long time = 0;

void loop() {
  if (millis() - time > 2000) {
    outPackage[0] = sr04->outData();
    outSize = 1;
    time = millis();
  }
  sr04->loop();
//  if(inPackage[0] > 10) {
//    digitalWrite(3, HIGH);
//  } else {
//    digitalWrite(3, LOW);
//  }
//  if(inPackage[1] > 10) {
//    digitalWrite(4, HIGH);
//  } else {
//    digitalWrite(4, LOW);
//  }
//  if(inPackage[2] > 10) {
//    digitalWrite(5, HIGH);
//  } else {
//    digitalWrite(5, LOW);
//  }
}
