#include <SPI.h>
#include "SR04.h"

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

boolean skip = false;

ISR (SPI_STC_vect)
{
  byte b = SPDR;

  if (packageSize == 0) {
    if (b > 0) {
      SPDR = outSize;
      outSize = 0;
      skip = true;
      packageSize = max(b, outSize);
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
    }
      
    SPDR = outPackage[0];
    return;
  }
}

SR04 sr04(6, 7);

void setup() {
  setupSPI();
  sr04.setMaxDistance(255);
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  //  digitalWrite(3, HIGH);
  //  digitalWrite(4, HIGH);
  //  digitalWrite(5, HIGH);
}

long time = 0;

void loop() {
  if (millis() - time > 2000) {
    outPackage[0] = sr04.readNow();
    outSize = 1;
    time = millis();
  }
  if(inPackage[0] > 10) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  if(inPackage[1] > 10) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(4, LOW);
  }
  if(inPackage[2] > 10) {
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);
  }
}
