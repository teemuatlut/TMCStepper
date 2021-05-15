#pragma once

#if defined(ESP_PLATFORM)
    #include <cstdint>

    #include <driver/uart.h>

    class ESP32_Serial {
        public:
            ESP32_Serial( int baud_rate, int rx_pin = 16, int tx_pin = 17, uart_port_t uart_num_new = UART_NUM_2 );

            int16_t read();
            uint8_t write( const uint8_t data );
            size_t available();

        private:
            bool ready;
            uart_port_t uart_num;
    };
#endif
