
#if defined(ARDUINO_ARCH_AVR)

#include "../../TMCStepper.h"

using namespace TMC_HAL;
using namespace TMCStepper_n;

PinCache::PinCache(const uint8_t p, const uint8_t bm, volatile uint8_t* const ptr) :
    port(p), bitMask(bm), pPort(ptr) {}

InputPin::InputPin(const PinDef _pin) :
    PinCache(
        digitalPinToPort(_pin),
        digitalPinToBitMask(_pin),
        portInputRegister(digitalPinToPort(_pin))
    ) {}

void InputPin::setMode() const {
    volatile uint8_t *reg = portModeRegister(port);
    volatile uint8_t *out = portOutputRegister(port);

    // INPUT_PULLUP
    uint8_t oldSREG = SREG;
    cli();
    *reg &= ~bitMask;
    *out |= bitMask;
    SREG = oldSREG;
}

bool InputPin::read() const {
    return *pPort & bitMask;
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(
        digitalPinToPort(_pin),
        digitalPinToBitMask(_pin),
        portOutputRegister(digitalPinToPort(_pin))
    ) {}

void OutputPin::setMode() const {
    volatile uint8_t *reg = portModeRegister(port);

    // OUTPUT
    uint8_t oldSREG = SREG;
    cli();
    *reg |= bitMask;
    SREG = oldSREG;
}

void OutputPin::set() const {
    *pPort |= bitMask;
}

void OutputPin::reset() const {
    *pPort &= ~bitMask;
}

__attribute__((weak))
void TMC_SPI::initPeripheral() {
    if (TMC_HW_SPI != nullptr) TMC_HW_SPI->begin();
    else if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    }
}

__attribute__((weak))
void TMC_SPI::transfer(void *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->transfer((uint8_t*)buf, count);
    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer((uint8_t*)buf, count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->endTransaction();
    }
}

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
    } else if (HWSerial != nullptr) {
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
    } else
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active(slaveAddress);
    }
}

__attribute__((weak))
size_t TMC_UART::serial_read(void *data, int8_t length) {
    if (SWSerial != nullptr && SWSerial->available() > 0) {
        return SWSerial->readBytes((uint8_t*)data, length);
    } else if (HWSerial != nullptr && HWSerial->available() > 0) {
        return HWSerial->readBytes((uint8_t*)data, length);
    }
    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const void *data, int8_t length) {
    if (SWSerial != nullptr) {
        return SWSerial->write((const uint8_t*)data, length);
    }
    else if (HWSerial != nullptr) {
        return HWSerial->write((const uint8_t*)data, length);
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
