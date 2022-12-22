#include "MockReader.h"

MockReader::MockReader(uint32_t mask, float accelerometer_coeff) {
    _mask = mask;
    timothy.start();
}



// Returns as float
MockReader::sensorData_t MockReader::readSensors(){
    // Gyro, Acc and Mag values converted to floats arrays

    // ****************************************************************************************************
    // READ FROM SIN WAVE
    float fourHz = sin(2*3.14 * 4 * (timothy.elapsed_time().count())/1000000);
    float fiveHz = sin(2*3.14 * 5 * (timothy.elapsed_time().count())/1000000);
    float sixHz = sin(2*3.14 * 6 * (timothy.elapsed_time().count())/1000000);
    // ****************************************************************************************************

    MockReader::sensorData_t data;
    
    for (int axis = 0; axis<XYZ; axis++) {

        if (_mask & READ_GYRO_MASK) {
            // data.gyro[axis] = sin(2*3.14 * 4 * timothy.elapsed_time().count());
            // data.gyro[1] = 10;
            data.gyro[0] = fourHz;
            data.gyro[1] = fiveHz;
            data.gyro[2] = sixHz;
        }

        if (_mask & READ_ACC_MASK) {
            data.acc[0] = fourHz;
            data.acc[1] = fiveHz;
            data.acc[2] = sixHz;
            // data.acc[axis] = 5;
        }

        if (_mask & READ_MAG_MASK) {
            // data.mag[axis] = 0;
        }
    }


    // data.dt = 0;

    return data;

}


void MockReader::calculateOffsets(int reps){
    float ax=0.0f,ay=0.0f,az=0.0f,gx=0.0f,gy=0.0f,gz=0.0f;
    
    // Reset the offsets to 0
    _offsets.ax = 0.0f;
    _offsets.ay  =0.0f;
    _offsets.az = 0.0f;
    _offsets.gx = 0.0f;
    _offsets.gy = 0.0f;
    _offsets.gz = 0.0f;

    timothy.reset();
}

void MockReader::displayAddresses(){
    uint8_t id;
    printf("Data is in mocky-wocky mode UwU\r\n");

}


// MockReader::sensorDataInt_t MockReader::mockSensorsInt(){
//     MockReader::sensorDataInt_t new_data;
//     float val;
//     int err = 0;
//     if (_mask & READ_ACC_MASK) {
//         //Mock Accelerometer values
//         //err = accelerometer *******************************
//         if (err != 0) {
//             printf("Error Mocking accelerometer\r\n");
//         }
//     }

//     if (_mask & READ_GYRO_MASK) {
//         //Mock magnetommeter values
//         //err = gyroscope ***********************************
//         if(err!=0){
//             printf("Error reading gyroscope\r\n");
//         }
//         // Check timer value in us for dt then reset
//         //new_data.dt = tim.read_us();
//         new_data.dt = tim.elapsed_time().count();
//         tim.reset(); 
//     }

//     if(_mask & READ_MAG_MASK){
//         // Read magnetommeter values in mgauss to int32_t
//         //err = magnetometer *********************************
//         if(err!=0){
//             printf("Error reading magnetometer\r\n");
//         }
//     }

//     if(_mask & READ_TEMP_MASK){
//         // Mock temperature values in Celsius to float
//         //err = temp_sensor2 *********************************
//         if(err!=0){
//             printf("Error reading temperature\r\n");
//         }
//     }

//     if(_mask & READ_PRESS_MASK){
//         // Mock pressure values in mbar to float
//         //err = pressure_sensor ******************************
//         if(err!=0){
//             printf("Error reading pressure\r\n");
//         }  
//     }

//     if(_mask & READ_HUM_MASK){
//         // Mock humidity values in % to float
//         //err = humidity_sensor *****************************
//         if(err!=0){
//             printf("Error reading humidity\r\n");
//         }
//     }

//     return new_data;

// }