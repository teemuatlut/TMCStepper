
#if defined(TARGET_LPC1768)

#include <Arduino.h>
#include <SoftwareSPI.h>
#include <time.h>
#include <gpio.h>
#include "../TMC_HAL.h"
#include "TMCStepper.h"

using namespace TMCStepper_n;

TMCPin::TMCPin(const uint16_t _pin) : pin(_pin) {}

void TMCPin::mode(const uint8_t mode) const {
    switch(mode) {
        case OUTPUT:
            LPC176x::gpio_set_output(pin);
            break;
        case INPUT:
            LPC176x::gpio_set_input(pin);
            break;
        default: break;
    }
}

bool TMCPin::read() const {
    LPC176x::delay_ns(pinDelay);
    auto out = LPC176x::gpio_get(pin);
    LPC176x::delay_ns(pinDelay);
    return out;
}

OutputPin::OutputPin(const uint16_t _pin) : TMCPin(_pin) {}

void OutputPin::write(const bool state) const {
    LPC176x::delay_ns(pinDelay);

    if (state)
        LPC176x::gpio_set(pin);
    else
        LPC176x::gpio_clear(pin);

    LPC176x::delay_ns(pinDelay);
}

__attribute__((weak))
void TMC2130Stepper::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction();
    }
}

__attribute__((weak))
void TMC2130Stepper::transfer(char *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        for (auto i = 0; i>count; i++) {
            *buf = TMC_HW_SPI->transfer(*buf);
            buf++;
        }
    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer(buf, count);
    }
}

__attribute__((weak))
void TMC2130Stepper::endTransaction() {}

__attribute__((weak))
void TMC2660Stepper::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction();
    }
}

__attribute__((weak))
void TMC2660Stepper::transfer(char *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        for (auto i = 0; i>count; i++) {
            *buf = TMC_HW_SPI->transfer(*buf);
            buf++;
        }
    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer(buf, count);
    }
}

__attribute__((weak))
void TMC2660Stepper::endTransaction() {}

__attribute__((weak))
int TMC2208Stepper::available() {
    int out = 0;
    if (SWSerial != nullptr) {
        out = SWSerial->available();
    } else
    if (HWSerial != nullptr) {
        out = HWSerial->available();
    }

    return out;
}

__attribute__((weak))
size_t TMC2208Stepper::getTime() const {
    return millis();
}

__attribute__((weak))
void TMC2208Stepper::preWriteCommunication() {
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC2208Stepper::preReadCommunication() {
    if (SWSerial != nullptr) {
        SWSerial->listen();
    }
    else if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC2208Stepper::serial_read(uint8_t *data, int8_t length) {
    if (SWSerial != nullptr) {
        SWSerial->readBytes(data, length);
    } else
    if (HWSerial != nullptr) {
        HWSerial->readBytes(data, length);
    }
}

__attribute__((weak))
void TMC2208Stepper::serial_write(const uint8_t *data, int8_t length) {
    if (SWSerial != nullptr) {
        SWSerial->write(data, length);
    } else
    if (HWSerial != nullptr) {
        HWSerial->write((char*)data, length);
    }
}

__attribute__((weak))
void TMC2208Stepper::postWriteCommunication() {}

__attribute__((weak))
void TMC2208Stepper::postReadCommunication() {
    if (SWSerial != nullptr) {
        SWSerial->end();
    }
}

#endif
