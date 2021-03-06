#ifndef LineSensor_h
#define LineSensor_h

class LineSensor
{
  public:
    LineSensor(uint8_t inputs[], uint8_t inputs_size);
    uint16_t readSensor();
    boolean sensorsRead();
    void calibrateDown();
    void calibrateUp();
  private:
    uint16_t readRawSensor(uint8_t sensor);
    int calibrate(int value, int sensor);
    int maps(int value);

    uint8_t* sensorInputs;
    int16_t* sensorValues;
    int16_t* sensorsColibrationDown;
    int16_t* sensorsColibrationUp;
    int8_t currentSensor;
    boolean sensorsReadFinish = false;
};

#endif

