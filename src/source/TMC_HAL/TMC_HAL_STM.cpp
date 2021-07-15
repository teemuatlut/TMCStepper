
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
    #if defined(STM32F4xx)
        pin.port->BSRR = pin.bm << 16U;
    #else
        pin.port->BRR = pin.bm;
    #endif
}

__attribute__((weak))
void TMC_SPI::initPeripheral() {
    if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {}

#if defined(STM_HAS_LL_SPI)

    __attribute__((weak))
    void TMC_SPI::transfer(void *buf, const uint8_t count) {
        if(TMC_HW_SPI != nullptr) {
            uint8_t *data = (uint8_t*)buf;
            uint8_t bytes = count;
            while(bytes --> 0) {
                transfer(*data);
                LL_SPI_TransmitData8(TMC_HW_SPI, *data);
                *data = LL_SPI_ReceiveData8(TMC_HW_SPI);
                data++;
            }
        }
        else if(TMC_SW_SPI != nullptr) {
            TMC_SW_SPI->transfer((uint8_t*)buf, count);
        }
    }

#elif defined(HAL_SPI_MODULE_ENABLED)

    __attribute__((weak))
    void TMC_SPI::transfer(void *buf, const uint8_t count) {
        if(TMC_HW_SPI != nullptr) {
            HAL_SPI_TransmitReceive(TMC_HW_SPI, (uint8_t*)buf, (uint8_t*)buf, count, timeout);
        }
        else if(TMC_SW_SPI != nullptr) {
            TMC_SW_SPI->transfer((uint8_t*)buf, count);
        }
    }

#endif

__attribute__((weak))
void TMC_SPI::endTransaction() {}

__attribute__((weak))
void TMC_UART::begin(uint32_t) {}

#if defined(STM_HAS_LL_UART)

    int TMC_UART::available() {
        return LL_USART_IsActiveFlag_RXNE(HWSerial);
    }

    size_t TMC_UART::serial_write(const void *buf, int8_t length) {
        uint8_t *data = (uint8_t*)buf;
        while (length --> 0) {
            LL_USART_TransmitData8(HWSerial, *(const uint8_t *)data);
            data++;
        }
        return length;
    }

    size_t TMC_UART::serial_read(void *buf, int8_t length) {
        uint8_t *data = (uint8_t*)buf;
        while (length --> 0) {
            *data = LL_USART_ReceiveData8(HWSerial);
            data++;
        }
        return length;
    }

    void delay(uint32_t ms) { LL_mDelay(ms); }

#elif defined(HAL_UART_MODULE_ENABLED)

    __attribute__((weak))
    uint32_t TMC_UART::getTime() const { return HAL_GetTick(); }

    __attribute__((weak))
    int TMC_UART::available() {
        return __HAL_UART_GET_FLAG(HWSerial, UART_FLAG_RXNE);
    }

    size_t TMC_UART::serial_write(const void *data, int8_t length) {
        HAL_UART_Transmit(HWSerial, (uint8_t*)data, length, timeout);
        return length;
    }

    size_t TMC_UART::serial_read(void *buf, int8_t length) {
        HAL_UART_Receive(HWSerial, (uint8_t*)buf, length, timeout);
        return length;
    }

    void delay(uint32_t ms) { HAL_Delay(ms); }

    #endif

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
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {}

#endif
#endif // !defined(__MBED__)
