
#if defined(ARDUINO_ARCH_SAM)

#include <Arduino.h>
#include <SPI.h>
#include "../TMC_HAL.h"
#include "TMCStepper.h"

using namespace TMCStepper_n;

TMCPin::TMCPin(const uint32_t _pin) : pin(_pin) {}

void TMCPin::mode(const uint8_t mode) const {
    switch(mode) {
        case OUTPUT:
            pinMode(pin, OUTPUT);
            break;
        case INPUT:
            pinMode(pin, INPUT);
            break;
        default: break;
    }
}

bool TMCPin::read() const {
    return PIO_Get( g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin );
}

OutputPin::OutputPin(const uint32_t _pin) : TMCPin(_pin) {}

void OutputPin::write(const bool state) const {
    if (state)
        g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
    else
        g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    }
}

__attribute__((weak))
void TMC_SPI::transfer(char *buf, const uint8_t count) {
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
void TMC2660Stepper::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    }
}

__attribute__((weak))
void TMC2660Stepper::transfer(char *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->transfer(buf, count);
    }
}

__attribute__((weak))
void TMC2660Stepper::endTransaction() {
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
size_t TMC_UART::getTime() const {
    return millis();
}

__attribute__((weak))
void TMC_UART::preWriteCommunication() {
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC_UART::preReadCommunication() {
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC_UART::serial_read(uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        HWSerial->readBytes(data, length);
    }
}

__attribute__((weak))
void TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        HWSerial->write(data, length);
    }
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {}

#endif
