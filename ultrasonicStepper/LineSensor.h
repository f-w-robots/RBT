#include "CD4051.h"

#ifndef LineSensor_h
#define LineSensor_h

class LineSensor
{
  public:
    LineSensor(uint8_t pin0, uint8_t pin1, uint8_t pin2, uint8_t analog);
    void readSensors();
    void readSensor();
    boolean sensorsRead();
    String printSensors();
    String printSensorsBool();
    void assignValues(int8_t &v0, int8_t &vc, int8_t &vr, int8_t &vl, int8_t &vrr, int8_t &vll);
  private:
    uint8_t _pins[3];
    uint8_t _analog;
    int _sensors[6];
    CD4051* _cd4051;
    int _sensorsColibration[6] = {0,0,0,0,0,0};
    int _sensorsColibrationUp[6] = {1023, 1023, 1023, 1023, 1023, 1023};
    int8_t _currentSensor;
    boolean _sensorsRead = false;
};

#endif

