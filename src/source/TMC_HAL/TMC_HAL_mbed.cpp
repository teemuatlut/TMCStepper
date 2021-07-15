
#if defined(__MBED__)

#include "../TMC_HAL.h"
#include "../../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
    pin.input();
    pin.mode(PullUp);
}

bool InputPin::read() const {
    return pin.read();
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    pin.output();
}

void OutputPin::set() const {
    pin.write(1);
}

void OutputPin::reset() const {
    pin.write(0);
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
void TMC_SPI::transfer(void *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->write(static_cast<char*>(buf), count, static_cast<char*>(buf), count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->unlock();
    }
}

__attribute__((weak))
int TMC_UART::available() {
    int out = 0;
    if (HWSerial != nullptr) {
        out = HWSerial->readable();
    }

    return out;
}

static Timer serialTimeout;

__attribute__((weak))
uint32_t TMC_UART::getTime() const {
    using namespace std::chrono;
    return duration_cast<milliseconds>(serialTimeout.elapsed_time()).count();
}

__attribute__((weak))
void TMC_UART::preWriteCommunication() {
    if (HWSerial != nullptr) {
        serialTimeout.start();

        if (sswitch != nullptr)
            sswitch->active(slaveAddress);
    }
}

__attribute__((weak))
void TMC_UART::preReadCommunication() {
    if (HWSerial != nullptr) {
        serialTimeout.start();

        if (sswitch != nullptr)
            sswitch->active(slaveAddress);
    }
}

__attribute__((weak))
size_t TMC_UART::serial_read(void *data, int8_t length) {
    if (HWSerial != nullptr) {
        return HWSerial->read((uint8_t*)data, length);
    }
    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const void *data, int8_t length) {
    if (HWSerial != nullptr) {
        return HWSerial->write((const uint8_t*)data, length);
    }
    return 0;
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
