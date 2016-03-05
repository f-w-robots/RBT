#include "CD4051.h"

#ifndef LineSensor_h
#define LineSensor_h

class LineSensor
{
  public:
    LineSensor(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t analog);
    uint16_t readSensor();
    boolean sensorsRead();
    uint8_t getSensor(uint8_t i);
  private:
    int calibrate(int value);
    int maps(int value);

    uint8_t pins[3];
    uint8_t analogIn;
    int sensorValues[6];
    CD4051* cd4051;
    int sensorsColibrationDonw[6] = {130, 160, 170, 200, 130, 140}; //{90, 97, 134, 155, 75, 73};
    int sensorsColibrationUp[6] = {950, 1023, 1023, 1023, 800, 1023};//{560, 926, 820, 868, 693, 950};//
    int8_t currentSensor;
    boolean sensorsReadFinish = false;
};

#endif

