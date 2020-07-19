
#if defined(ARDUINO_ARCH_AVR)

#include <Arduino.h>
#include <SPI.h>
#include "../TMC_HAL.h"
#include "TMCStepper.h"

using namespace TMCStepper_n;

TMCPin::TMCPin(const uint8_t _pin) :
    port(digitalPinToPort(_pin)),
    bitMask(digitalPinToBitMask(_pin))
    {}

void TMCPin::mode(const uint8_t mode) const {
    volatile uint8_t *reg, *out;

    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if (mode == INPUT) { 
        uint8_t oldSREG = SREG;
                cli();
        *reg &= ~bitMask;
        *out &= ~bitMask;
        SREG = oldSREG;
    } else if (mode == INPUT_PULLUP) {
        uint8_t oldSREG = SREG;
                cli();
        *reg &= ~bitMask;
        *out |= bitMask;
        SREG = oldSREG;
    } else {
        uint8_t oldSREG = SREG;
                cli();
        *reg |= bitMask;
        SREG = oldSREG;
    }
}

InputPin::InputPin(const uint8_t _pin) :
    TMCPin(_pin),
    inPort(portInputRegister(digitalPinToPort(_pin)))
    {
        pinMode(_pin, INPUT);
    }

bool InputPin::read() const {
    return *inPort & bitMask;
}

OutputPin::OutputPin(const uint8_t _pin) :
    TMCPin(_pin),
    outPort(portOutputRegister(digitalPinToPort(_pin)))
    {
        pinMode(_pin, OUTPUT);
    }

void OutputPin::write(const bool state) const {
    if (state)
        *outPort |= bitMask;
    else
        *outPort &= ~bitMask;
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
    if (SWSerial != nullptr) {
        out = SWSerial->available();
    } else if (HWSerial != nullptr) {
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
    #if SW_CAPABLE_PLATFORM
        if (SWSerial != nullptr) {
            SWSerial->listen();
        } else
    #endif
        if (HWSerial != nullptr) {
            if (sswitch != nullptr)
                sswitch->active();
        }
}

__attribute__((weak))
void TMC_UART::serial_read(uint8_t *data, int8_t length) {
    if (RXTX_pin > 0) {
        pinMode(RXTX_pin, INPUT_PULLUP);
    }

    if (SWSerial != nullptr && SWSerial->available() > 0) {
        SWSerial->readBytes(data, length);
    } else if (HWSerial != nullptr && HWSerial->available() > 0) {
        HWSerial->readBytes(data, length);
    }
}

__attribute__((weak))
void TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    if (RXTX_pin > 0) {
        digitalWrite(RXTX_pin, HIGH);
        pinMode(RXTX_pin, OUTPUT);
    }

    if (SWSerial != nullptr) {
        SWSerial->write(data, length);
    }
    else if (HWSerial != nullptr) {
        HWSerial->write(data, length);
    }
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {
        if (SWSerial != nullptr) {
            SWSerial->end();
        }
}

#endif
