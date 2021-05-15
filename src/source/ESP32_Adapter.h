#pragma once

#if defined(ESP_PLATFORM)
    #include <cstdint>
    #include <driver/gpio.h>
    #define LOW  0
    #define HIGH 1
    typedef enum {
        OUTPUT,
        INPUT,
        INPUT_PULLUP
    } gpio_dir_t;
    void pinMode( uint16_t num, gpio_dir_t mode );
    void digitalWrite( uint16_t num, uint32_t level );
    int digitalRead( uint16_t num );
#endif
