
#if defined(__MBED__)

#include <TMCStepper.h>

constexpr float r_sense = 0.11f;
constexpr uint8_t driver_address = 2;

SPI spi(SPI_MOSI, SPI_MISO, SPI_SCK);
SW_SPIClass sw_spi(PA_3, PA_4, PA_5);
BufferedSerial serial_port(USBTX, USBRX);

TMC2130Stepper driver (   spi, SPI_CS, r_sense);
TMC2130Stepper driver1(sw_spi, SPI_CS, r_sense);
TMC2160Stepper driver2(   spi, SPI_CS, r_sense);
TMC2160Stepper driver3(sw_spi, SPI_CS, r_sense);
TMC2660Stepper driver4(   spi, SPI_CS, r_sense);
TMC2660Stepper driver5(sw_spi, SPI_CS, r_sense);
TMC5130Stepper driver6(   spi, SPI_CS, r_sense);
TMC5130Stepper driver7(sw_spi, SPI_CS, r_sense);
TMC5160Stepper driver8(   spi, SPI_CS, r_sense);
TMC5160Stepper driver9(sw_spi, SPI_CS, r_sense);

TMC2208Stepper driver10(serial_port, r_sense);
TMC2209Stepper driver12(serial_port, r_sense, driver_address);
TMC2300Stepper driver14(serial_port, r_sense, driver_address);

int main() {
    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);
}

#endif
