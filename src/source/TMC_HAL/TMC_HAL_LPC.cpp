
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
void TMC_SPI::initPeripheral() {
    if (TMC_HW_SPI != nullptr) TMC_HW_SPI->begin();
    else if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction();
    }
}

__attribute__((weak))
void TMC_SPI::transfer(void *buf, const uint8_t count) {
    uint8_t *txrx = (uint8_t*)buf;
    if(TMC_HW_SPI != nullptr) {
        for (auto i = 0; i>count; i++) {
            *txrx = TMC_HW_SPI->transfer(*txrx);
            txrx++;
        }
    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer(txrx, count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {}

__attribute__((weak))
void TMC_UART::begin(uint32_t baudrate) {
	if (HWSerial != nullptr) {
		HWSerial->begin(baudrate);
	}
    else if (SWSerial != nullptr) {
        SWSerial->begin(baudrate);
        SWSerial->end();
    }
}

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
    if (SWSerial != nullptr) {
        SWSerial->listen();
    }
    else if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active(slaveAddress);
    }
}

__attribute__((weak))
size_t TMC_UART::serial_read(void *data, int8_t length) {
    if (SWSerial != nullptr) {
        return SWSerial->readBytes((uint8_t*)data, length);
    } else
    if (HWSerial != nullptr) {
        return HWSerial->readBytes((uint8_t*)data, length);
    }
    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const void *data, int8_t length) {
    if (SWSerial != nullptr) {
        return SWSerial->write((const uint8_t*)data, length);
    } else
    if (HWSerial != nullptr) {
        return HWSerial->write((char*)data, length);
    }
    return 0;
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
