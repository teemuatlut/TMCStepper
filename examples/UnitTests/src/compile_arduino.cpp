
#if defined(ARDUINO) && !(defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAM) || defined(TARGET_LPC1768))

#include <Arduino.h>
#include <TMCStepper.h>

constexpr uint8_t CS_PIN = 53;
constexpr float R_SENSE = 0.11f;
auto SERIAL_PORT = Serial2;
constexpr uint8_t DRIVER_ADDRESS = 1;

SW_SPIClass SW_SPI(1, 2, 3);

TMC2130Stepper driver (   SPI, CS_PIN, R_SENSE);
TMC2130Stepper driver1(SW_SPI, CS_PIN, R_SENSE);
TMC2160Stepper driver2(   SPI, CS_PIN, R_SENSE);
TMC2160Stepper driver3(SW_SPI, CS_PIN, R_SENSE);
TMC2660Stepper driver4(   SPI, CS_PIN, R_SENSE);
TMC2660Stepper driver5(SW_SPI, CS_PIN, R_SENSE);
TMC5130Stepper driver6(   SPI, CS_PIN, R_SENSE);
TMC5130Stepper driver7(SW_SPI, CS_PIN, R_SENSE);
TMC5160Stepper driver8(   SPI, CS_PIN, R_SENSE);
TMC5160Stepper driver9(SW_SPI, CS_PIN, R_SENSE);

TMC2208Stepper driver10(SERIAL_PORT, R_SENSE);
TMC2209Stepper driver12(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
TMC2300Stepper driver14(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

void setup() {
    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);
}

void loop() {}

#endif
