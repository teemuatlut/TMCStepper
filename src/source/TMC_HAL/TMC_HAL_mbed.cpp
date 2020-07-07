
#if defined(__MBED__)

#include "TMC_HAL.h"
#include "TMCStepper.h"

using namespace TMCStepper_n;

OutputPin::OutputPin(PinName pin) : DigitalOut(pin) {}

void OutputPin::mode(uint8_t) {}

InputPin::InputPin(PinName pin) : DigitalIn(pin) {}

void InputPin::mode(const uint8_t inputType) {
    switch(inputType) {
        case INPUT: mode(PullDefault); break;
        case INPUT_PULLUP: mode(PullUp); break;
        default: break;
    }
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->frequency(spi_speed);
        constexpr int bitsPerFrame = 8;
        constexpr int mode = 3;
        TMC_HW_SPI->format(bitsPerFrame, mode);
        TMC_HW_SPI->lock();
    }
}

__attribute__((weak))
void TMC_SPI::transfer(char *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->write(buf, count, buf, count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->unlock();
    }
}

__attribute__((weak))
void TMC2660Stepper::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->frequency(spi_speed);
        constexpr int bitsPerFrame = 8;
        constexpr int mode = 3;
        TMC_HW_SPI->format(bitsPerFrame, mode);
        TMC_HW_SPI->lock();
    }
}

__attribute__((weak))
void TMC2660Stepper::transfer(char *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->write(buf, count, buf, count);
    }
}

__attribute__((weak))
void TMC2660Stepper::endTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->unlock();
    }
}

static Timer serialTimeout;

__attribute__((weak))
size_t TMC_UART::getTime() const {
    return serialTimeout.read_ms();
}

__attribute__((weak))
void TMC_UART::preWriteCommunication() {
    if (HWSerial != nullptr) {
        serialTimeout.start();

        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC_UART::preReadCommunication() {
    if (HWSerial != nullptr) {
        serialTimeout.start();

        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC_UART::serial_read(uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        HWSerial->read(data, length, nullptr);
    }
}

__attribute__((weak))
void TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        bytesWritten += HWSerial->write(data, length, nullptr);
    }
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {
    serialTimeout.reset();
}

__attribute__((weak))
void TMC_UART::postReadCommunication() {
    serialTimeout.reset();
}

#endif
