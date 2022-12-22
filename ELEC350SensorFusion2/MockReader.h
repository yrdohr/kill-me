#ifndef MockReader_H
#define MockReader_H

#include "mbed.h"
#include "SensorReaderBase.h"
#include "x_nucleo_iks01a1.h"


// Defines for chosing which sensors to read
#define READ_ACC_MASK   1<<0
#define READ_GYRO_MASK  1<<1
#define READ_MAG_MASK   1<<2
#define READ_TEMP_MASK  1<<3
#define READ_PRESS_MASK 1<<4
#define READ_HUM_MASK   1<<5
#define READ_GYRO_ACC_MASK  (READ_ACC_MASK | READ_GYRO_MASK);
#define READ_ALL_MASK   0X3F

// Some shorthand notations
#define X_AXIS  0
#define Y_AXIS  1
#define Z_AXIS  2
#define XYZ     3

class MockReader : public SensorReaderBase {

private:
    Timer timothy;

protected:
    uint32_t _mask;
    imuOffsets_t _offsets;

    // Returns a sensorDataInt_t containing int32_t
    // virtual sensorDataInt_t mockSensorsInt();

public:
    MockReader(uint32_t mask = READ_ALL_MASK, float accelerometer_coeff = 0.18f);

    virtual void displayAddresses();

    virtual void calculateOffsets(int reps = 200);

    virtual sensorData_t readSensors();
};


#endif