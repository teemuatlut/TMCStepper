
#if !(defined(__MBED__) || defined(ARDUINO))

#if (defined(USE_FULL_LL_DRIVER) || defined(USE_HAL_DRIVER))

#include "../../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

#if defined(USE_FULL_LL_DRIVER)
    void InputPin::setMode() const {
        LL_GPIO_SetPinMode(pin.port, pin.bm, LL_GPIO_MODE_INPUT);
    }

    void OutputPin::setMode() const {
        LL_GPIO_SetPinMode(pin.port, pin.bm, LL_GPIO_MODE_OUTPUT);
    }
#elif defined(HAL_GPIO_MODULE_ENABLED)
    void InputPin::setMode() const {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pin = pin.bm;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(pin.port, &GPIO_InitStruct);
    }

    void OutputPin::setMode() const {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pin = pin.bm;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(pin.port, &GPIO_InitStruct);
    }
#endif

bool InputPin::read() const {
    return pin.port->IDR & pin.bm;
}

void OutputPin::set() const {
    pin.port->BSRR = pin.bm;
}

void OutputPin::reset() const {
    pin.port->BRR = pin.bm;
}

#if defined(HAL_SPI_MODULE_ENABLED)
    SPIClass::SPIClass(SPI_HandleTypeDef * spi) : hspi(spi) {}

    void SPIClass::transfer(uint8_t *buf, uint8_t count) const {
        HAL_SPI_TransmitReceive(hspi, buf, buf, count, timeout);
    }

    void delay(uint32_t ms) { HAL_Delay(ms); }
#elif defined(USE_FULL_LL_DRIVER)
    SPIClass::SPIClass(SPI_TypeDef * spi) : hspi(spi) {}

    uint8_t SPIClass::transfer(const uint8_t data) const {
        LL_SPI_TransmitData8(hspi, data);
        return LL_SPI_ReceiveData8(hspi);
    }
    void SPIClass::transfer(uint8_t *buf, uint8_t count) const {
        while(count --> 0) {
            transfer(*buf);
        }
    }

#endif

#if defined(HAL_UART_MODULE_ENABLED)

    HardwareSerial::HardwareSerial(UART_HandleTypeDef *const handle) : huart(handle) {}

    void HardwareSerial::write(const uint8_t *data, uint8_t length) {
        HAL_UART_Transmit(huart, const_cast<uint8_t*>(data), length, timeout);
    }
    void HardwareSerial::read(uint8_t *buf, uint8_t length) {
        HAL_UART_Receive(huart, buf, length, timeout);
    }
    uint8_t HardwareSerial::available() {
        return __HAL_UART_GET_FLAG(huart, UART_FLAG_RXNE);
    }

#elif defined(USE_FULL_LL_DRIVER)

    HardwareSerial::HardwareSerial(USART_TypeDef *const handle) : huart(handle) {}

    void HardwareSerial::write(const uint8_t *data, uint8_t length) {
        while (length --> 0) {
            LL_USART_TransmitData8(huart, *data);
            data++;
        }
    }
    void HardwareSerial::read(uint8_t *buf, uint8_t length) {
        while (length --> 0) {
            *buf = LL_USART_ReceiveData8(huart);
            buf++;
        }
    }
    uint8_t HardwareSerial::available() {
        return LL_USART_IsActiveFlag_RXNE(huart);
    }

#endif

__attribute__((weak))
uint32_t TMC_UART::getTime() const { return millis(); }

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
void TMC2660Stepper::transfer(uint8_t *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->transfer(buf, count);
    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer(buf, count);
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
void TMC_UART::serial_read(uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        HWSerial->read(data, length);
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
#endif // !defined(__MBED__)
