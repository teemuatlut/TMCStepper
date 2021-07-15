
#include <TMCStepper.h>


// main() runs in its own thread in the OS
int main() {

    SPI spi(SPI_MOSI, SPI_MISO, SPI_SCK);
    BufferedSerial hwSerial(SERIAL_TX, SERIAL_RX);

    // Define used pins
    DigitalOut step_pin(NC);

    auto CS_PIN  = NC;
    auto SW_MOSI = NC;
    auto SW_MISO = NC;
    auto SW_SCK  = NC;


    constexpr float R_SENSE = 0.11f; // Match to your driver

    //SW_SPIClass sw_spi(SW_MOSI, SW_MISO, SW_SCK);

    // Select your stepper driver type
    TMC2130Stepper   driver(   spi, CS_PIN, R_SENSE); // Hardware SPI
    //TMC2130Stepper driver(sw_spi, CS_PIN, R_SENSE); // Software SPI
    //TMC2660Stepper driver(   spi, CS_PIN, R_SENSE);
    //TMC2660Stepper driver(sw_spi, CS_PIN, R_SENSE);
    //TMC5160Stepper driver(   spi, CS_PIN, R_SENSE);
    //TMC5160Stepper driver(sw_spi, CS_PIN, R_SENSE);

    //TMC2208Stepper driver(SERIAL_PORT, R_SENSE);   // Hardware Serial
    //TMC2209Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
    //TMC2300Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);

    while(1) {
        step_pin.write(1);
        wait_us(1000);
        step_pin.write(0);
        wait_us(1000);
    }
}
