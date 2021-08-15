
#if defined(PICO_BOARD) && !defined(ARDUINO)

#include <hardware/spi.h>
#include <hardware/timer.h>
#include "../../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
    gpio_set_dir(pin, false);
}

bool InputPin::read() const {
    return gpio_get(pin);
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    gpio_set_dir(pin, true);
}

void OutputPin::set() const {
    gpio_put(pin, HIGH);
}

void OutputPin::reset() const {
    gpio_put(pin, LOW);
}

__attribute__((weak))
void TMC_SPI::initPeripheral() {
    if (TMC_HW_SPI != nullptr)
        spi_init(*TMC_HW_SPI, spi_speed);
    else if (TMC_SW_SPI != nullptr)
        TMC_SW_SPI->init();
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        spi_set_format(*TMC_HW_SPI, 8, SPI_CPOL_1, SPI_CPHA_1, SPI_MSB_FIRST);
    }
}

__attribute__((weak))
void TMC_SPI::transfer(void *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        spi_write_read_blocking(*TMC_HW_SPI, static_cast<uint8_t*>(buf), static_cast<uint8_t*>(buf), count);
    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer((uint8_t*)buf, count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {
    if (TMC_HW_SPI != nullptr) {
    }
}

__attribute__((weak))
void TMC_UART::begin(uint32_t baudrate) {
	if (HWSerial != nullptr) {
        uart_init(*HWSerial, baudrate);
	}
}

__attribute__((weak))
int TMC_UART::available() {
    int out = 0;
    if (HWSerial != nullptr) {
        out = uart_is_readable(*HWSerial);
    }

    return out;
}

__attribute__((weak))
uint32_t TMC_UART::getTime() const {
    return time_us_32();
}

__attribute__((weak))
void TMC_UART::preWriteCommunication() {
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active(slaveAddress);
    }
}

__attribute__((weak))
void TMC_UART::preReadCommunication() {
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active(slaveAddress);
    }
}

__attribute__((weak))
size_t TMC_UART::serial_read(void *data, int8_t length) {
    if (HWSerial != nullptr && available() > 0) {
        uart_read_blocking(*HWSerial, static_cast<uint8_t*>(data), length);
        return length;
    }

    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const void *data, int8_t length) {
    if (HWSerial != nullptr) {
        uart_write_blocking(*HWSerial, static_cast<const uint8_t*>(data), length);
        return length;
    }
    return 0;
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {}

#endif
