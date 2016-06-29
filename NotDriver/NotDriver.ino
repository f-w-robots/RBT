#define SENSORS


#include <SPI.h>
#include "RobatzModule.h"
#include "RobatzSR04.h"


RobatzModule **modules;
uint8_t modulesSize = 0;

int16_t packageSize = 0;
int inPackagePos = 0;
int inPackageSize = 0;
byte* outPackage = NULL;

void setupSPI()
{
  SPCR |= bit (SPE);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
}

void setup() {
  Serial.begin(115200);

#ifdef SENSORS
  modulesSize = 1;
  modules = new RobatzModule*[modulesSize];
  modules[0] = new RobatzSR04(9, 8);
  outPackage = new byte[modulesSize];
#endif








  setupSPI();
}


int outSize = 0;
uint16_t distance = 0;

void parseRequest(uint8_t moduleId, byte data) {
  if (moduleId >= modulesSize)
    return;
  modules[moduleId]->update(data);
}





ISR (SPI_STC_vect)
{
  byte b = SPDR;

  if (packageSize == 0) {
    if (b > 0) {
      SPDR = outSize;
      packageSize = max(b, outSize);
      outSize = 0;
      if (b > 1) {
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
      parseRequest(inPackagePos, SPDR);
    }

    SPDR = outPackage[0];
    return;
  }
}


long time = 0;

void loop() {
  for (int i = 0; i < modulesSize; i++) {
    if (modules[i]->loop()) {
      outPackage[i] = modules[i]->outData();
      outSize = modulesSize;
    }
  }
}

