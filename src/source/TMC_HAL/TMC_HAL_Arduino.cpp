
#if defined(ARDUINO) && !(defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAM) || defined(TARGET_LPC1768))

#include <Arduino.h>
#include <SPI.h>
#include "../TMC_HAL.h"
#include "TMCStepper.h"

using namespace TMCStepper_n;

TMCPin::TMCPin(const uint8_t _pin) : pin(_pin) {}

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
    return digitalRead(pin);
}

OutputPin::OutputPin(const uint8_t _pin) : TMCPin(_pin) {}

void OutputPin::write(const bool state) const {
    digitalWrite(pin, state);
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
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer(buf, count);
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
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr) {
            out = SWSerial->available();
        }
    #endif

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
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr) {
            SWSerial->listen();
        }
    #endif
}

__attribute__((weak))
void TMC_UART::serial_read(uint8_t *data, int8_t length) {
    #if SW_CAPABLE_PLATFORM
        if (RXTX_pin > 0) {
            pinMode(RXTX_pin, INPUT_PULLUP);
        }
    #endif

    if (HWSerial != nullptr && HWSerial->available() > 0) {
        HWSerial->readBytes(data, length);
    }
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr && SWSerial->available() > 0) {
            SWSerial->readBytes(data, length);
        };
    #endif
}

__attribute__((weak))
void TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    #if SW_CAPABLE_PLATFORM
        if (RXTX_pin > 0) {
            digitalWrite(RXTX_pin, HIGH);
            pinMode(RXTX_pin, OUTPUT);
        }
    #endif

    if (HWSerial != nullptr) {
        HWSerial->write(data, length);
    }
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr) {
            SWSerial->write(data, length);
        }
    #endif
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {
    #if SW_CAPABLE_PLATFORM
        if (SWSerial != nullptr) {
            SWSerial->end();
        }
    #endif
}

#endif
