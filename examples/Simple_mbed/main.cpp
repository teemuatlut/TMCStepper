#include "mbed.h"

#include <TMCStepper.h>

SPI spi(SPI_MOSI, SPI_MISO, SPI_SCK);
TMC2130Stepper driver(spi, SPI_CS, 0.11);

Serial hwSerial(USBTX, USBRX);
TMC2208Stepper driver3(&hwSerial, 0.11);

// main() runs in its own thread in the OS
int main()
{
    while (true) {

    }
}


