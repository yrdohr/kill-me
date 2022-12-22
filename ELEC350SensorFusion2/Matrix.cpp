#include "uop_msb.h"
using namespace uop_msb;

#include <iostream>
using namespace std;

#include "Matrix.h"


void Matrix::SetMatrix(void)
{
    // matrix_spi_cs=0;
    // matrix_spi.write(0x01);//COL LHS
    // matrix_spi.write(0x00);//COL RHS
    // matrix_spi.write(0x03);//ROX RHS
    // matrix_spi_cs=1;
    // wait_us(1000000);

    while(1){
        //Smiley
        
        matrix_spi_cs=0;
        matrix_spi.write(0x06);//COL LHS
        matrix_spi.write(0x60);//COL RHS
        matrix_spi.write(0x01);//ROX RHS
        matrix_spi_cs=1;
        ThisThread::sleep_for(1ms);
        matrix_spi_cs=0;
        matrix_spi.write(0x06);//COL LHS
        matrix_spi.write(0x60);//COL RHS
        matrix_spi.write(0x02);//ROX RHS
        matrix_spi_cs=1;
        ThisThread::sleep_for(1ms);
        matrix_spi_cs=0;
        matrix_spi.write(0x06);//COL LHS
        matrix_spi.write(0x60);//COL RHS
        matrix_spi.write(0x03);//ROX RHS
        matrix_spi_cs=1;
        ThisThread::sleep_for(1ms);

        matrix_spi_cs=0;
        matrix_spi.write(0x10);//COL LHS
        matrix_spi.write(0x08);//COL RHS
        matrix_spi.write(0x05);//ROX RHS
        matrix_spi_cs=1;
        ThisThread::sleep_for(1ms);
        matrix_spi_cs=0;
        matrix_spi.write(0x08);//COL LHS
        matrix_spi.write(0x10);//COL RHS
        matrix_spi.write(0x06);//ROX RHS
        matrix_spi_cs=1;
        ThisThread::sleep_for(1ms);
        matrix_spi_cs=0;
        matrix_spi.write(0x07);//COL LHS
        matrix_spi.write(0xE0);//COL RHS
        matrix_spi.write(0x07);//ROX RHS
        matrix_spi_cs=1;
        ThisThread::sleep_for(1ms);
    }

}