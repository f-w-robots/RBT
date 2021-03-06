#define DC_MOTOR
//#define STEPPER_MOTOR
//#define SENSORS

#include <SPI.h>
#include "RobatzModule.h"
#include "RobatzMotor28BYJ.h"
#include "RobatzDCMotor.h"
#include "RobatzSR04.h"
#include "RobatzSensor.h"
#include "RobatzIRREC.h"
#include "RobatzIRSend.h"

RobatzModule **modules;
uint8_t modulesSize = 0;

int16_t packageSize = 0;
int inPackagePos = 0;
int inPackageSize = 0;
int outSize = 0;
byte* outPackage = NULL;

uint8_t outPackageSize = 0;
uint8_t *outPackagePositions = NULL;

void setupSPI()
{
  SPCR |= bit (SPE);
  pinMode(MISO, OUTPUT);
  SPI.attachInterrupt();
}

void setup()
{
  Serial.begin(115200);

  // INITIALIZE MODULES --- BEGIN

//#ifdef DC_MOTOR
//  modulesSize = 2;
//  modules = new RobatzModule*[modulesSize];
//  modules[0] = new RobatzDCMotor(3, 2, 4);
//  modules[1] = new RobatzDCMotor(9, 8, 5);
//#endif
//
//#ifdef STEPPER_MOTOR
//  modulesSize = 2;
//  modules = new RobatzModule*[modulesSize];
//  modules[0] = new RobatzMotor28BYJ(2, 3, 4, 5);
//  modules[1] = new RobatzMotor28BYJ(6, 7, 8, 9);
//#endif
//
//#ifdef SENSORS
//  modulesSize = 6;
//  modules = new RobatzModule*[modulesSize];
//  modules[0] = new RobatzSensor(A3);
//  modules[1] = new RobatzSensor(A2);
//  modules[2] = new RobatzSensor(A1);
//  modules[3] = new RobatzSensor(A0);
//  modules[4] = new RobatzSensor(A4);
//  modules[5] = new RobatzSR04(9, 8);
//  //  modules[6] = new RobatzIRREC(5);
//  //  modules[7] = new RobatzIRSend(3);
//#endif

#ifdef SENSORS
  modulesSize = 1;
  modules = new RobatzModule*[modulesSize];
  modules[0] = new RobatzIRSend(3);
#endif

  outPackagePositions = new uint8_t[modulesSize];

  for (int i = 0; i < modulesSize; i++) {
    outPackagePositions[i] = outPackageSize;

    outPackageSize += modules[i]->answerSize();
  }

  outPackage = new byte[outPackageSize];

  int outPackagePosition = 0;
  for (int i = 0; i < outPackageSize; i++) {
    outPackage[i] = 0;
  }

  // INITIALIZE MODULES --- END

  setupSPI();
}

void parseRequest(uint8_t moduleId, byte data) {
  if (moduleId >= modulesSize)
    return;
  modules[moduleId]->update(data);
}

ISR (SPI_STC_vect)
{
  byte b = SPDR;

  if (packageSize == 0) {
    inPackagePos = 0;
    if (b > 0) {
      SPDR = outSize;
      packageSize = max(b, outSize);
      outSize = 0;
      inPackageSize = b - 1;
      inPackagePos = -2;
    }
    return;
  }

  if (packageSize > 0) {
    packageSize--;
    inPackagePos++;
    if (inPackagePos < inPackageSize && inPackagePos > -1) {
      parseRequest(inPackagePos, SPDR);
    }

    int outPackagePos = inPackagePos - 1 + 2;
    if (outPackagePos < outPackageSize && outPackagePos > -1) {
      SPDR = outPackage[outPackagePos];
    }
  }
}

uint32_t lastSendTime = 0;

void loop() {
  for (int i = 0; i < modulesSize; i++) {
    if (modules[i]->loop()) {

      int32_t value = modules[i]->outData();

      for (int g = 0; g < modules[i]->answerSize(); g++) {
        byte one = ((value >> (g * 8)) & 0xFF);
        outPackage[outPackagePositions[i] + g] = one;
      }

      if (millis() - lastSendTime > 10) {
        outSize = outPackageSize;
        lastSendTime = millis();
      }
    }
  }
}

