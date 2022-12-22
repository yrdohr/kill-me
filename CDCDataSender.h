#include "USBCDC.h"
#include "mbed.h"
#include "SensorReader.h"

/* (c) 2022 University of Plymouth

Rev     DATE            AUTHOR          BRANCH      COMMENTS
0.1     02/11/22        Andrew Norris   AN          Initial Commit with working demo 

*/
class CDCDataSender{
    private:
        //CDC data is sent using an EventQueue in it's own thread
        EventQueue q;
        Thread cdcThread;
        // Declare USBCDC object to be initialsied in the constructor
        USBCDC* cdc;
        // This method is added to the queue by calling sendData
        void sendDataCDC(const SensorReader::imuAngles_t* angles);
        // Initialised the CDC object in the EventQueue (Dynamic allocation)
        void initCDC();
        // Destroys the dynamically allocated USBCDC object 
        ~CDCDataSender();

    public:
        // Constructor
        CDCDataSender();
        // Public API to send data via CDC
        void sendData(const SensorReader::imuAngles_t* angles); 
};