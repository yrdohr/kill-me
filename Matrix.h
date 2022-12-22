#include "uop_msb.h"
#include "mbed.h"


// MATRIX
#define MATRIX_LATCH_PIN PB_6
#define MATRIX_OE_PIN    PB_12
#define SPI3_SCK_PIN     PC_10
#define SPI3_MISO_PIN    PC_11
#define SPI3_MOSI_PIN    PC_12

class Matrix{
private:
        SPI matrix_spi;
        DigitalOut matrix_spi_cs;
        DigitalOut matrix_spi_oe;
        
public:
    Matrix() : matrix_spi(SPI3_MOSI_PIN, SPI3_MISO_PIN, SPI3_SCK_PIN),
        matrix_spi_cs(MATRIX_LATCH_PIN),
        matrix_spi_oe(MATRIX_OE_PIN)        
    {
    
    }
    void SetMatrix(void);
};