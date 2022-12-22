#include "uop_msb.h"
#include "SensorReader.h"
#include "MockReader.h"
#include "CDCDataSender.h"
#include <iostream>
#include "mbed.h"
#include "DFT.h"

#include "Matrix.h"
#include "SD_Card.h"

using namespace std;
/*
Library: (c) ST Microelectronics
http://os.mbed.com/teams/ST/code/X_NUCLEO_IKS01A1/

Demo Code:
Lead: Andrew Norris
(c) 2022 University of Plymouth 

Rev     DATE            AUTHOR          BRANCH      COMMENTS
Rev.    0.1 02/11/22    Andrew Norris   MASTER      Initial Commit with working demo        
Rev.    0.2 02/11/22    Nicholas Outram NJO-CHANGES Added Module Support Board + Z Angle from the Accelerometer
Rev.    0.3 04/11/22    Nicholas Outram NJO-CHANGES Squashed warnings; decoupled serial from sensor data; added virtual base class; 
Rev.    0.4 08/11/22    Andrew Norris   AN          Added Z plane + Integrate USB OTG for 2D/3D demo output + Fixed Debug 2D and 3D demo issue (AN); relocate driver to GitHub (NJO)     
Rev.    0.5 09/11/22    Nicholas Outram NJO         Moved calcAngles and setFilterCoeffs to base class; renamed getAngles to calcAngles; baseclass constructor updated
*/

/*
TODO:
Add defaults and constructor parameters for mask and filter weight
Review and implement Policy for thread and ISR safety 
Review baseclass - convert some PVF to VF
*/


//Use demo mode to send data via the USB OTG connector - run the 2D/2D visualtion program to see the output
//#define DEMO_MODE

//Use real sensor (comment out for mocked)
//#define IKS01A1_CONNECTED

// SensorReaderBase* _sensors;
#ifdef IKS01A1_CONNECTED
SensorReader sensors;
#else
//Created mocked object here
MockReader sensors;
#endif

#ifdef DEMO_MODE
CDCDataSender sender;
#endif

//Blue button - used to start / recalibrate
DigitalIn button(USER_BUTTON);

Thread setup(osPriorityHigh);
Thread sampleSensors(osPriorityHigh);
Thread writeSD(osPriorityNormal);
Thread readSD(osPriorityNormal);
Thread serialInterface(osPriorityNormal);
Thread computeSpectrum(osPriorityNormal);
Thread displayLED(osPriorityAboveNormal);

EventQueue sampling;

Matrix mat;

void LEDMatrix() {
    mat.SetMatrix();
}


void setupSensors() {
    sensors.displayAddresses();     // Call this to print the I2C addresses of the sensors


    //  Calculate the gyro offsets (board should be level and stationary)
    printf("Calculating offsets...");
    ThisThread::sleep_for(500ms);
    sensors.calculateOffsets();
    printf("complete\r\n");

    // Set the coefficients for the complementary filter 
    sensors.setFilterCoeffs(0.18f);

    // Print the csv header
    cout << "ax,ay,az,gx,gy,gz,cfx,cfy,cfz" << endl;
}
void sample() {
    int counter = 0;
    //Read the sensor data as floats
        SensorReader::sensorData_t data;
        data = sensors.readSensors();

        //Calculate the angles and apply filtering
        SensorReaderBase::imuAngles_t angles;
        angles = sensors.calcAngles(data);

        //Log to terminal - copy into data.csv and read into excel
        cout << "accelerometer: X: " << angles.ax << ", Y: " << angles.ay << ", Z: " << angles.az << "\n";
        cout << "gyroscope: X: " << angles.gx << ", Y: " << angles.gy << ", Z: " << angles.gz << "\n";
        cout << "angle: X: " << angles.x << ", Y: " << angles.y << ", Z: " << angles.z << "\n" << endl;


        float accelData[3][1000];
        float gyroData[3][1000];
        float angleData[3][1000];

        for (unsigned int i = 998; i == 0; i--) {
            accelData[0][i+1] = accelData[2][i];
            accelData[1][i+1] = accelData[2][i];
            accelData[2][i+1] = accelData[2][i];

            gyroData[0][i+1] = gyroData[0][i];
            gyroData[1][i+1] = gyroData[1][i];
            gyroData[2][i+1] = gyroData[2][i];

            angleData[0][i+1] = angleData[0][i];
            angleData[1][i+1] = angleData[1][i];;
            angleData[2][i+1] = angleData[2][i];
        }
        accelData[0][0] = angles.ax;
        accelData[1][0] = angles.ay;
        accelData[2][0] = angles.az;

        gyroData[0][0] = angles.gx;
        gyroData[1][0] = angles.gy;
        gyroData[2][0] = angles.gz;

        angleData[0][0] = angles.x;
        angleData[1][0] = angles.y;
        angleData[2][0] = angles.z;

        // cout << accelData[0][1] << "\n\n" << endl;

        // float dataFromSensors[3][3] = {{ANGLEAX, ANGLEAY, ANGLEAZ}, {ANGLEGX, ANGLEGY, ANGLEGZ}, {ANGLEX, ANGLEY, ANGLEZ}};
        // return dataFromSensors[1][2];




        #ifdef DEMO_MODE
        //Send the angles via CDC
        sender.sendData(&angles);
        #endif

        //Option to recalibrate
        if (button == 1) {
            ThisThread::sleep_for(500ms);
            sensors.calculateOffsets();
        }

}



int main() {
    
    // if (button) {
    //     _sensors = new SensorReader();
    // }
    // else {
    //     _sensors = new MockReader();
    // }
    // SensorReaderBase& sensors = *_sensors;

    cout << "Press the blue button to start" << endl;

    //Wait for blue button
    while (button ==  0);
    
    setup.start(setupSensors);
    wait_us(10000);
    displayLED.start(LEDMatrix);
    // mat.SetMatrix();
    sampling.call_every(10ms, sample); // 100Hz
    sampling.dispatch_forever();
    // writeSD.start(write_sdcard);
    // float array[] = {1, 2, 3, 4};
    // unsigned int n = sizeof(array);
    // DFT(array, n);
    
    while(1) {
        
        
        //A terrible waste of time
        wait_us(100000);
        //cout<<sample();
    }
}
