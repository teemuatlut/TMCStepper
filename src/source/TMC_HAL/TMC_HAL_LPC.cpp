
#if defined(TARGET_LPC1768)

#include <Arduino.h>
#include <time.h>
#include <gpio.h>
#include "../TMC_HAL.h"
#include "../../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
    LPC176x::gpio_set_input(pin);

}

bool InputPin::read() const {
    LPC176x::delay_ns(pinDelay);
    auto out = LPC176x::gpio_get(pin);
    LPC176x::delay_ns(pinDelay);
    return out;
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    LPC176x::gpio_set_output(pin);

}

void OutputPin::set() const {
    LPC176x::delay_ns(pinDelay);
    LPC176x::gpio_set(pin);
    LPC176x::delay_ns(pinDelay);
}

void OutputPin::reset() const {
    LPC176x::delay_ns(pinDelay);
    LPC176x::gpio_clear(pin);
    LPC176x::delay_ns(pinDelay);
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction();
    }
}

__attribute__((weak))
void TMC_SPI::transfer(char *buf, const uint8_t count) {
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
void TMC_SPI::endTransaction() {}

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
int TMC_UART::available() {
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
    if (SWSerial != nullptr) {
        SWSerial->listen();
    }
    else if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC_UART::serial_read(uint8_t *data, int8_t length) {
    if (SWSerial != nullptr) {
        SWSerial->readBytes(data, length);
    } else
    if (HWSerial != nullptr) {
        HWSerial->readBytes(data, length);
    }
}

__attribute__((weak))
void TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    if (SWSerial != nullptr) {
        SWSerial->write(data, length);
    } else
    if (HWSerial != nullptr) {
        HWSerial->write((char*)data, length);
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
