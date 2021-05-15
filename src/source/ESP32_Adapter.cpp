#include "ESP32_Adapter.h"

#if defined(ESP_PLATFORM)
    void pinMode( uint16_t num, gpio_dir_t mode ) {
        switch( mode ) {
            case OUTPUT:
                gpio_set_direction( (gpio_num_t)num, GPIO_MODE_OUTPUT );
                break;
            case INPUT:
                gpio_set_direction( (gpio_num_t)num, GPIO_MODE_INPUT );
                gpio_set_pull_mode( (gpio_num_t)num, GPIO_FLOATING );
                break;
            case INPUT_PULLUP:
                gpio_set_direction( (gpio_num_t)num, GPIO_MODE_INPUT );
                gpio_set_pull_mode( (gpio_num_t)num, GPIO_PULLUP_ONLY );
                break;
        }
    }
    void digitalWrite( uint16_t num, uint32_t level ) {
        gpio_set_level( (gpio_num_t)num, level );
    }
    int digitalRead( uint16_t num ) {
        return gpio_get_level( (gpio_num_t)num );
    }
#endif
