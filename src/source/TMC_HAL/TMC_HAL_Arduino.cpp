
#if defined(ARDUINO) && !(defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_SAM) || defined(TARGET_LPC1768))

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
    return digitalRead(pin);
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    pinMode(pin, OUTPUT);
}

void OutputPin::set() const {
    digitalWrite(pin, HIGH);
}

void OutputPin::reset() const {
    digitalWrite(pin, LOW);
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
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr) {
            SWSerial->begin(baudrate);
        }
    #endif
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
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr) {
            SWSerial->listen();
        }
    #endif
}

__attribute__((weak))
size_t TMC_UART::serial_read(void *data, int8_t length) {
    if (HWSerial != nullptr && HWSerial->available() > 0) {
        return HWSerial->readBytes((uint8_t*)data, length);
    }
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr && SWSerial->available() > 0) {
            return SWSerial->readBytes((uint8_t*)data, length);
        };
    #endif
    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const void *data, int8_t length) {
    if (HWSerial != nullptr) {
        return HWSerial->write((const uint8_t*)data, length);
    }
    #if SW_CAPABLE_PLATFORM
        else if (SWSerial != nullptr) {
            return SWSerial->write((const uint8_t*)data, length);
        }
    #endif
    return 0;
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
