
#if defined(ARDUINO_ARCH_SAM)

#include <Arduino.h>
#include <SPI.h>
#include "../TMC_HAL.h"
#include "../../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
    pinMode(pin, INPUT);
}

bool InputPin::read() const {
    return PIO_Get( g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin );
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    pinMode(pin, OUTPUT);
}

void OutputPin::set() const {
    g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
}

void OutputPin::reset() const {
    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    }
}

__attribute__((weak))
void TMC_SPI::transfer(uint8_t *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->transfer(buf, count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->endTransaction();
    }
}

__attribute__((weak))
int TMC_UART::available() {
    int out = 0;
    if (HWSerial != nullptr) {
        out = HWSerial->available();
    }

    return out;
}

__attribute__((weak))
uint32_t TMC_UART::getTime() const {
    return millis();
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
size_t TMC_UART::serial_read(uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        return HWSerial->readBytes(data, length);
    }
    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        return HWSerial->write(data, length);
    }
    return 0;
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {}

#endif
