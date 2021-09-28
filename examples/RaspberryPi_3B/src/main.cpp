
#include <TMCStepper.h>

constexpr int
    en_pin = 23,
    cs_pin = 25,
    step_pin = 24;

int main() {
    char chip_id = 0;
    auto cs = ::gpiod::chip(&chip_id).get_line(cs_pin);
    auto step = TMC_HAL::OutputPin(
        ::gpiod::chip(&chip_id).get_line(step_pin)
    );
    auto enable = TMC_HAL::OutputPin(
        ::gpiod::chip(&chip_id).get_line(en_pin)
    );

    TMC_HAL::HW_port spi("/dev/spidev0.0");
    TMC_HAL::HW_port uart("dev/serial1");

    TMC2130Stepper spi_driver(spi, cs, 0.11);

    spi_driver.begin();
    spi_driver.rms_current(600);
    spi_driver.microsteps(16);

    std::cout << "TMCStepper\nDriver_version = " << spi_driver.version() << std::endl;

    enable.reset();

    while(true) {
        step.set();
        usleep(160);
        step.reset();
        usleep(160);
    }
}
