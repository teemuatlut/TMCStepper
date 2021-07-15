
#if defined(USE_FULL_LL_DRIVER) && !defined(__MBED__)


#if defined(STM32F0xx)
    #include <stm32f0xx_ll_gpio.h>
    #include <stm32f0xx_ll_spi.h>
    #include <stm32f0xx_ll_usart.h>
    #include <stm32f0xx_ll_utils.h>
#elif defined(STM32F1xx)
    #include <stm32f1xx_ll_gpio.h>
    #include <stm32f1xx_ll_spi.h>
    #include <stm32f1xx_ll_usart.h>
    #include <stm32f1xx_ll_utils.h>
#elif defined(STM32F3xx)
    #include <stm32f3xx_ll_gpio.h>
    #include <stm32f3xx_ll_spi.h>
    #include <stm32f3xx_ll_usart.h>
    #include <stm32f3xx_ll_utils.h>
#elif defined(STM32F4xx)
    #include <stm32f4xx_ll_gpio.h>
    #include <stm32f4xx_ll_spi.h>
    #include <stm32f4xx_ll_usart.h>
    #include <stm32f4xx_ll_utils.h>
#elif defined(STM32F7xx)
    #include <stm32f7xx_ll_gpio.h>
    #include <stm32f7xx_ll_spi.h>
    #include <stm32f7xx_ll_usart.h>
    #include <stm32f7xx_ll_utils.h>
#endif

#endif
