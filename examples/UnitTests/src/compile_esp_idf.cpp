
#if defined(IDF_VER)

#include <TMCStepper.h>

const gpio_num_t
    CS_PIN     = GPIO_NUM_NC,
    SW_MOSI    = GPIO_NUM_NC,
    SW_MISO    = GPIO_NUM_NC,
    SW_SCK     = GPIO_NUM_NC,
    SW_RX      = GPIO_NUM_NC,
    SW_TX      = GPIO_NUM_NC;

constexpr uint8_t DRIVER_ADDRESS = 0b00; // TMC2209 Driver address according to MS1 and MS2
constexpr float R_SENSE = 0.11; // Current shunt resistor

spi_device_handle_t SPI{};
uart_port_t SERIAL_PORT = 1;

SW_SPIClass SW_SPI(GPIO_NUM_NC, GPIO_NUM_NC, GPIO_NUM_NC);

TMC2130Stepper driver (   SPI, CS_PIN, R_SENSE); // Hardware SPI
TMC2130Stepper driver1(SW_SPI, CS_PIN, R_SENSE); // Software SPI
TMC2160Stepper driver2(   SPI, CS_PIN, R_SENSE); // Hardware SPI
TMC2160Stepper driver3(SW_SPI, CS_PIN, R_SENSE); // Software SPI
TMC2660Stepper driver4(   SPI, CS_PIN, R_SENSE);
TMC2660Stepper driver5(SW_SPI, CS_PIN, R_SENSE);
TMC5130Stepper driver6(   SPI, CS_PIN, R_SENSE);
TMC5130Stepper driver7(SW_SPI, CS_PIN, R_SENSE);
TMC5160Stepper driver8(   SPI, CS_PIN, R_SENSE);
TMC5160Stepper driver9(SW_SPI, CS_PIN, R_SENSE);

TMC2208Stepper driver10(SERIAL_PORT, R_SENSE);    // Hardware Serial
TMC2209Stepper driver12(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
TMC2300Stepper driver14(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

extern "C"
void app_main() {
    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);
}

#endif
