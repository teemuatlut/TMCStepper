
#include <TMCStepper.h>
#include <pico/config_autogen.h>

uint CS_pin = PICO_DEFAULT_SPI_CSN_PIN;
uint STEP_pin = 22;

TMC2130Stepper driver(spi0, CS_pin, 0.11);
// TMC2208Stepper driver(uart0, 0.11);

int main() {
    gpio_set_dir(STEP_pin, true);

    driver.begin();
    driver.rms_current(600);
    driver.microsteps(16);

    while(1) {
        gpio_put(STEP_pin, 1);
        sleep_us(160);
        gpio_put(STEP_pin, 0);
        sleep_us(160);
    }
}
