//#define DC_MOTOR
#define STEPPER_MOTOR

#include <SPI.h>
#include "RobatzModule.h"
#include "RobatzMotor28BYJ.h"
#include "RobatzDCMotor.h"

RobatzModule **modules;
uint8_t modulesSize = 0;

void setup()
{
  // INITIALIZE MODULES --- BEGIN

#ifdef DC_MOTOR
  modulesSize = 2;
  modules = new RobatzModule*[modulesSize];
  modules[0] = new RobatzDCMotor(3, 2, 4);
  modules[1] = new RobatzDCMotor(9, 8, 5);
#endif

#ifdef STEPPER_MOTOR
  modulesSize = 2;
  modules = new RobatzModule*[modulesSize];
  modules[0] = new RobatzMotor28BYJ(2, 3, 4, 5);
  modules[1] = new RobatzMotor28BYJ(6, 7, 8, 9);
#endif

  // INITIALIZE MODULES --- END

  Serial.begin(115200);
  SPCR |= bit (SPE);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
}

void parseRequest(uint8_t moduleId, byte data) {
  if (moduleId >= modulesSize)
    return;
  modules[moduleId]->update(data);
}

uint16_t packageSize = 0;
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


void loop ()
{
  for (int i = 0; i < modulesSize; i++)
    modules[i]->loop();
}

