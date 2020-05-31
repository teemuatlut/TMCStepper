
#if !(defined(__MBED__) || defined(ARDUINO))

#if (defined(USE_FULL_LL_DRIVER) || defined(USE_HAL_DRIVER))

#include <TMCStepper.h>

using namespace TMCStepper_n;

TMCPin::TMCPin(GPIO_TypeDef* const _port, uint32_t const _pin) : port(_port), pin(_pin) {}

#if defined(HAL_GPIO_MODULE_ENABLED)
    void TMCPin::mode(const uint8_t mode) const {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        switch(mode) {
            case OUTPUT:
                GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
                break;
            case INPUT:
                GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
                break;
            default: break;
        }

        GPIO_InitStruct.Pin = pin;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(port, &GPIO_InitStruct);
    }
#else
    void TMCPin::mode(const uint8_t mode) const {
        switch(mode) {
            case OUTPUT:
                LL_GPIO_SetPinMode(port, pin, LL_GPIO_MODE_OUTPUT);
                break;
            case INPUT:
                LL_GPIO_SetPinMode(port, pin, LL_GPIO_MODE_INPUT);
                break;
            default: break;
        }
    }
#endif

InputPin::InputPin(const TMCPin &_pin) : TMCPin(_pin.port, _pin.pin) {}
InputPin::InputPin(GPIO_TypeDef* const _port, uint32_t const _pin) : TMCPin(_port, _pin) {}

#if defined(HAL_GPIO_MODULE_ENABLED)
    bool InputPin::read() const {
        return HAL_GPIO_ReadPin(port, pin);
    }
#else
    bool InputPin::read() const {
        return LL_GPIO_ReadInputPort(port) & pin;
    }
#endif

OutputPin::OutputPin(const TMCPin &_pin) : TMCPin(_pin.port, _pin.pin) {}
OutputPin::OutputPin(GPIO_TypeDef* const _port, uint32_t const _pin) : TMCPin(_port, _pin) {}

#if defined(HAL_GPIO_MODULE_ENABLED)
    bool OutputPin::read() const {
        return port->ODR & pin;
    }

    void OutputPin::write(const bool state) const {
        HAL_GPIO_WritePin(port, pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void OutputPin::toggle() const {
        HAL_GPIO_TogglePin(port, pin);
    }
#else
    bool OutputPin::read() const {
        return LL_GPIO_ReadOutputPort(port) & pin;
    }

    void OutputPin::write(const bool state) const {
        if (state)
            LL_GPIO_SetOutputPin(port, pin);
        else
            LL_GPIO_ResetOutputPin(port, pin);
    }

    void OutputPin::toggle() const {
        LL_GPIO_TogglePin(port, pin);
    }
#endif

#if defined(HAL_SPI_MODULE_ENABLED)
    SPIClass::SPIClass(SPI_HandleTypeDef * spi) : hspi(spi) {}

    void SPIClass::transfer(char *buf, uint8_t count) const {
        HAL_SPI_TransmitReceive(hspi, (uint8_t*)buf, (uint8_t*)buf, count, timeout);
    }

    void delay(uint32_t ms) { HAL_Delay(ms); }
#elif defined(USE_FULL_LL_DRIVER)
    SPIClass::SPIClass(SPI_TypeDef * spi) : hspi(spi) {}

    uint8_t SPIClass::transfer(const char data) const {
        LL_SPI_TransmitData8(hspi, data);
        return LL_SPI_ReceiveData8(hspi);
    }
    void SPIClass::transfer(char *buf, uint8_t count) const {
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
size_t TMC2208Stepper::getTime() const { return millis(); }

__attribute__((weak))
void TMC2130Stepper::beginTransaction() {
    if (TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    }
}

__attribute__((weak))
void TMC2130Stepper::transfer(char *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {
        TMC_HW_SPI->transfer(buf, count);
    }
}

__attribute__((weak))
void TMC2130Stepper::endTransaction() {
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
int TMC2208Stepper::available() {
    int out = 0;

    if (HWSerial != nullptr) {
        out = HWSerial->available();
    }

    return out;
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
    if (HWSerial != nullptr) {
        if (sswitch != nullptr)
            sswitch->active();
    }
}

__attribute__((weak))
void TMC2208Stepper::serial_read(uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        HWSerial->read(data, length);
    }
}

__attribute__((weak))
void TMC2208Stepper::serial_write(const uint8_t *data, int8_t length) {
    if (HWSerial != nullptr) {
        HWSerial->write(data, length);
    }
}

__attribute__((weak))
void TMC2208Stepper::postWriteCommunication() {}

__attribute__((weak))
void TMC2208Stepper::postReadCommunication() {}

#endif
#endif // !defined(__MBED__)
