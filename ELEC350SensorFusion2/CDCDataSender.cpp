#include "CDCDataSender.h"

// Private method which is added to the EventQueue
void CDCDataSender::sendDataCDC(const SensorReader::imuAngles_t* angles){
    //Convert angles to 32-bit signed this makes it easier to interpret by the java apps
    int32_t ax = (int32_t) angles->ax;
    int32_t ay = (int32_t) angles->ay;
    int32_t az = (int32_t) angles->az;
    int32_t gx = (int32_t) angles->gx;
    int32_t gy = (int32_t) angles->gy;
    int32_t gz = (int32_t) angles->gz;
    int32_t filtered_x = (int32_t) angles->x;
    int32_t filtered_y = (int32_t) angles->y;
    int32_t filtered_z = (int32_t) angles->z;

    int32_t d [9] = {ax,ay,az,gx,gy,gz,filtered_x,filtered_y,filtered_z};
    // Send the data to the host
    cdc->send((uint8_t*)d,sizeof(d));
}

//  Instantiates the USBCDC object - called from constructor
void CDCDataSender::initCDC(){
    cdc=new USBCDC;    
}

// Constructor - Starts thread and links to EventQueue then instantiates USBCDC object
CDCDataSender::CDCDataSender(){
    cdcThread.start((callback(&this->q, &EventQueue::dispatch_forever)));
    q.call(callback(this,&CDCDataSender::initCDC));
}

// Clean up on destruction
CDCDataSender::~CDCDataSender(){
    delete cdc;
}

// public API to send data via CDC
void CDCDataSender::sendData(const SensorReader::imuAngles_t* angles){
    q.call(callback(this,&CDCDataSender::sendDataCDC),angles);
}


      
