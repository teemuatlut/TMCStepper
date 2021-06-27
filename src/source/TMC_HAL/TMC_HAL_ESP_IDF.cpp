
#if defined(IDF_VER)

#include <esp_log.h>
#include "../../TMCStepper.h"

#define TAG_EPS32_SERIAL "ESP32_UART"

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
    gpio_set_direction( pin, GPIO_MODE_INPUT );
    gpio_set_pull_mode( pin, GPIO_FLOATING );
}

bool InputPin::read() const {
    return gpio_get_level( pin );
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    gpio_set_direction( pin, GPIO_MODE_OUTPUT );
}

void OutputPin::set() const {
    gpio_set_level( pin, HIGH );
}

void OutputPin::reset() const {
    gpio_set_level( pin, LOW );
}

__attribute__((weak))
void TMC_SPI::beginTransaction() {
    spi_device_acquire_bus(*TMC_HW_SPI, 100);
}

__attribute__((weak))
void TMC_SPI::transfer(uint8_t *buf, const uint8_t count) {
    spi_transaction_t t{};
    t.length = count * 8u;
    t.rxlength = count * 8u;
    t.tx_buffer = buf;
    t.rx_buffer = buf;

    spi_device_polling_transmit(*TMC_HW_SPI, &t);
}

__attribute__((weak))
void TMC_SPI::endTransaction() {
    spi_device_release_bus(*TMC_HW_SPI);
}

__attribute__((weak))
int TMC_UART::available() {
    size_t len = 0;
    if (ESP_OK != uart_get_buffered_data_len(*HWSerial, &len)) {
        ESP_LOGE(TAG_EPS32_SERIAL, "Error getting available bytes.");
        return 0;
    }
    ESP_LOGD(TAG_EPS32_SERIAL, "Number of bytes available: %d", len);
    return len;
}

__attribute__((weak))
size_t TMC_UART::getTime() const {
    return esp_timer_get_time() / 1000;
}

__attribute__((weak))
void TMC_UART::preWriteCommunication() {}

__attribute__((weak))
void TMC_UART::preReadCommunication() {}

__attribute__((weak))
size_t TMC_UART::serial_read(uint8_t *data, int8_t length) {
    int len = uart_read_bytes(*HWSerial, data, 1, 0);
    ESP_LOGD( TAG_EPS32_SERIAL, "Read data: %X (length %d)", *data, len);
    return len;
}

__attribute__((weak))
size_t TMC_UART::serial_write(const uint8_t *data, int8_t length) {
    ESP_LOGD( TAG_EPS32_SERIAL, "Write data: %X", *data );
    const int len = uart_write_bytes(*HWSerial, (const char*)data, 1);
    ESP_LOGD( TAG_EPS32_SERIAL, "Number of bytes written: %d", len );
    return len;
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {}

#endif
