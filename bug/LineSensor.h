#include "CD4051.h"

#ifndef LineSensor_h
#define LineSensor_h

class LineSensor
{
  public:
    LineSensor(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t analogIn);
    uint16_t readSensor();
    boolean sensorsRead();
    void calibrateDown();
    void calibrateUp();
  private:
    uint16_t readRawSensor(uint8_t sensor);
    int calibrate(int value, int sensor);
    int maps(int value);

    uint8_t pins[3];
    uint8_t analogIn;
    int16_t* sensorValues;
    int16_t* sensorsColibrationDown;
    int16_t* sensorsColibrationUp;
    CD4051* cd4051;
    int8_t currentSensor;
    boolean sensorsReadFinish = false;
};

#endif

