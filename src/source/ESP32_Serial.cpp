#include "ESP32_Serial.h"

#if defined(ESP_PLATFORM)
    #define LOG_LOCAL_LEVEL ESP_LOG_INFO
    #define TAG_EPS32_SERIAL "ESP32_UART"
    #include <esp_log.h>
    #include <hal/gpio_types.h>

    ESP32_Serial::ESP32_Serial( int baud_rate, int rx_pin, int tx_pin, uart_port_t uart_num_new ) {
        uart_num = uart_num_new;
        ready = false;
        uart_config_t uart_config = {
            .baud_rate = baud_rate,
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .rx_flow_ctrl_thresh = 0,
            .source_clk = UART_SCLK_APB,
        };
        if( ESP_OK == uart_driver_install( uart_num, 2048, 0, 0, NULL, 0 ) ) {
            if( ESP_OK == uart_param_config( uart_num, &uart_config ) ) {
                if( ESP_OK == uart_set_pin( uart_num, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE ) ) {
                    ready = true;
                }
                else {
                    ESP_LOGE( TAG_EPS32_SERIAL, "Unable to set UART pins." );
                }
            }
            else {
                ESP_LOGE( TAG_EPS32_SERIAL, "Unable to configure UART." );
            }
        }
        else {
            ESP_LOGE( TAG_EPS32_SERIAL, "Unable to install UART driver." );
        }
    }

    int16_t ESP32_Serial::read() {
        if( !ready ) {
            ESP_LOGE( TAG_EPS32_SERIAL, "Trying to read from not ready UART." );
            return -1;
        }
        uint8_t data = 0;
        int len = uart_read_bytes( uart_num, &data, 1, 0 );
        ESP_LOGD( TAG_EPS32_SERIAL, "Read data: %X (length %d)", data, len );
        if( len < 1 ) return -1;
        else return data;
    }

    uint8_t ESP32_Serial::write( const uint8_t data ) {
        if( !ready ) {
            ESP_LOGE( TAG_EPS32_SERIAL, "Trying to write to not ready UART." );
            return 0;
        }
        ESP_LOGD( TAG_EPS32_SERIAL, "Write data: %X", data );
        int len = uart_write_bytes( uart_num, (const char*)&data, 1);
        ESP_LOGD( TAG_EPS32_SERIAL, "Number of bytes written: %d", len );
        if( len < 1 ) return 0;
        else return len;
    }

    size_t ESP32_Serial::available() {
        if( !ready ) {
            ESP_LOGE( TAG_EPS32_SERIAL, "Trying to get available bytes from not ready UART." );
            return 0;
        }
        size_t len = 0;
        if( ESP_OK == uart_get_buffered_data_len( uart_num, &len ) ) {
            ESP_LOGD( TAG_EPS32_SERIAL, "Number of bytes available: %d", len );
            return len;
        }
        else {
            ESP_LOGE( TAG_EPS32_SERIAL, "Error getting available bytes." );
            return 0;
        }
    }
#endif
