
#pragma once

#if defined(ARDUINO_ARCH_AVR)

    #include <Arduino.h>
	#include <SoftwareSerial.h>
    #include <SPI.h>

    #define SW_CAPABLE_PLATFORM true

    namespace TMC_HAL {
        using PinDef = uint8_t;

        struct PinCache {
            PinCache(const uint8_t p, const uint8_t bm, volatile uint8_t* const ptr);
            const uint8_t port;
            const uint8_t bitMask;
            volatile uint8_t* const pPort = nullptr;
        };

        class SWSerial : public SoftwareSerial {
            public:
                SWSerial(uint8_t receivePin, uint8_t transmitPin, bool inverse_logic = false) :
                    SoftwareSerial(receivePin, transmitPin, inverse_logic),
                    RXTX_pin(receivePin == transmitPin ? receivePin : 0)
                    {}

                virtual size_t write(const uint8_t *buffer, size_t size) {
                    if (RXTX_pin > 0) {
                        digitalWrite(RXTX_pin, HIGH);
                        pinMode(RXTX_pin, OUTPUT);
                    }

                    const size_t bytesOut = SoftwareSerial::write(buffer, size);

                    if (RXTX_pin > 0) {
                        pinMode(RXTX_pin, INPUT_PULLUP);
                    }

                    return bytesOut;
                }

            private:
                const PinDef RXTX_pin; // Half duplex
        };
    }

#elif defined(ARDUINO_ARCH_SAM)

    #include <Arduino.h>
	#include <HardwareSerial.h>
	#include <SPI.h>

    #define SW_CAPABLE_PLATFORM false

    namespace TMC_HAL {
        using PinDef = uint32_t;

        struct PinCache {
            explicit PinCache(const PinDef _pin) :
                pin(_pin) {}
            const PinDef pin;
        };
    }

#elif defined(TARGET_LPC1768)

    #include <Arduino.h>
	#include <HardwareSerial.h>
	#include <SoftwareSerial.h>
	
    #define SW_CAPABLE_PLATFORM true

    namespace TMC_HAL {
        using PinDef = uint16_t;

        struct PinCache {
            explicit PinCache(const PinDef _pin) :
                pin(_pin)
                {}
            uint16_t const pin;
            static constexpr uint_fast8_t pinDelay = 60;
        };
    }

    #define HardwareSerial HardwareSerial<>

    #ifndef __MARLIN_FIRMWARE__
        #include <SoftwareSPI.h>

        struct SPIClass { // Should be removed when LPC core gets full SPI class implementation
            SPIClass(const uint8_t spi_speed, const pin_t sck_pin, const pin_t miso_pin, const pin_t mosi_pin) :
                mosi(mosi_pin), miso(miso_pin), sck(sck_pin), speed(spi_speed) {
                    swSpiInit(spi_speed, sck_pin, mosi_pin);
                }

            void beginTransaction() const {
                swSpiBegin(sck, miso, mosi);
            }

            uint8_t transfer(uint8_t data) const {
                return swSpiTransfer(data, speed, sck, miso, mosi);
            }

            private:
                const pin_t mosi, miso, sck;
                const uint8_t speed;
        };
    #endif

#elif defined(ARDUINO)

    #include <Arduino.h>
    #include <SPI.h>
    #include <HardwareSerial.h>

    #define SW_CAPABLE_PLATFORM false

    namespace TMC_HAL {
        using PinDef = uint8_t;

        struct PinCache {
            explicit PinCache(const PinDef _pin) :
                pin(_pin)
                {}
            const PinDef pin;
        };
    }

#elif defined(__MBED__)

    #include <mbed.h>

    namespace TMC_HAL {
        using PinDef = PinName;

        struct PinCache {
            explicit PinCache(const PinDef _pin) :
                pin(_pin)
                {}

            /// All other HALs can treat the object as const
            mutable DigitalInOut pin;
        };
    }

    using SPIClass = SPI;
    using HardwareSerial = BufferedSerial;

    inline void delay(size_t ms) { wait_us(1000*ms); }

#elif (defined(USE_FULL_LL_DRIVER) || defined(USE_HAL_DRIVER))

    #include <cstddef>
    #include <stdint.h>

    #if defined(STM32F3xx)
        #include <stm32f3xx_hal_conf.h>
    #elif defined(STM32F4xx)
        #include <stm32f4xx_hal_conf.h>
    #else
        #include "main.h"
    #endif

    namespace TMC_HAL {

        struct PinDef {
            GPIO_TypeDef* const port;
            uint32_t const bm;
        };

        struct PinCache {
            explicit PinCache(const PinDef _pin) :
                pin(_pin)
                {}

            const PinDef pin;

            bool operator ==(const PinDef &p2) {
                return (p2.port == pin.port) && (p2.bm == pin.bm);
            }
        };
    }

        struct SPISettings {
            SPISettings(uint32_t, uint8_t, uint8_t) {}
        };

        #if defined(HAL_SPI_MODULE_ENABLED)
            typedef SPI_HandleTypeDef SPIType;
        #elif defined(USE_FULL_LL_DRIVER)
            typedef SPI_TypeDef SPIType;
        #endif

        struct SPIClass {
            explicit SPIClass(SPIType * spi);

            uint8_t transfer(const char data) const;
            void transfer(char *buf, uint8_t count) const;
            static void beginTransaction(SPISettings) {}
            static void endTransaction() {}

            operator bool() const { return hspi; }

        private:
            SPIType * const hspi;
            static constexpr uint32_t timeout = 1000;
        };

        void delay(uint32_t ms);

        #if defined(HAL_UART_MODULE_ENABLED)
            typedef UART_HandleTypeDef UsartType;
        #elif defined(USE_FULL_LL_DRIVER)
            typedef USART_TypeDef UsartType;
        #endif

        struct HardwareSerial {
            HardwareSerial(UsartType *const handle);

            void write(const uint8_t *data, uint8_t length);
            void read(uint8_t *buf, uint8_t length);
            uint8_t available();
            static constexpr uint32_t timeout = 1000;
        private:
            UsartType * const huart;
        };

#elif defined(bcm2835)

    #include <bcm2835.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <errno.h>
    #include <sys/time.h>

    #define MSBFIRST BCM2835_SPI_BIT_ORDER_MSBFIRST
    #define SPI_MODE0 BCM2835_SPI_MODE0
    #define SPI_MODE1 BCM2835_SPI_MODE1
    #define SPI_MODE2 BCM2835_SPI_MODE2
    #define SPI_MODE3 BCM2835_SPI_MODE3

    namespace TMC_HAL {
        using PinDef = uint8_t;

        struct PinCache {
            explicit PinCache(const PinDef _pin) :
                pin(_pin)
                {}

            bool operator ==(const PinCache &p2) {
                return p2.pin == pin;
            }

            const PinDef pin;
        };
    }

    struct SPISettings;

    class SPIClass
    {
    public:
        void beginTransaction(SPISettings settings);
        void endTransaction() {
            bcm2835_spi_end();
        }
        uint8_t transfer(uint8_t value) {
            return bcm2835_spi_transfer(value);
        }
    };

    struct SPISettings
    {
        friend class SPIClass;
        SPISettings(uint32_t s, bcm2835SPIBitOrder o, bcm2835SPIMode m) :
            speed(s), order(o), mode(m)
            {}

        const uint32_t speed;
        const bcm2835SPIBitOrder order;
        const bcm2835SPIMode mode;
    };

    extern SPIClass SPI;

    uint32_t millis();

    class HardwareSerial
    {
    public:
        HardwareSerial(const char* p) : port(p) {}
        void begin(unsigned long baud) { begin(baud, O_RDWR | O_NOCTTY | O_NDELAY); }
        void begin(unsigned long, int);
        void end() { ::close(port); }
        int available(void);
        uint8_t write(const uint8_t data);
        uint8_t read();
    private:
        int fd;                    /* Filedeskriptor */
        const char* port;
    };

    extern HardwareSerial Serial;
    extern HardwareSerial Serial1;

#endif

namespace TMC_HAL {

    class InputPin : PinCache {
    public:
        InputPin(const PinDef _pin);

        void setMode() const;

        bool read() const;

        operator bool() const {
            return read();
        }
    };

    class OutputPin : PinCache {
    public:
        OutputPin(const PinDef _pin);

        void setMode() const;

        void write(const bool state) const {
            state ? set() : reset();
        }
        void operator =(const bool state) const {
            write(state);
        }

        void set() const;
        void reset() const;
    };
}

#ifndef HIGH
    #define HIGH 1
#endif
#ifndef LOW
    #define LOW 0
#endif
#ifndef INPUT
    #define INPUT  0x00
#endif
#ifndef INPUT_PULLUP
    #define INPUT_PULLUP  0x01
#endif
#ifndef OUTPUT
    #define OUTPUT 0x01
#endif
#if !defined(MSBFIRST) && !(defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD))
    #define MSBFIRST 1
#endif
#ifndef SPI_MODE3
    #define SPI_MODE3 0
#endif
#ifndef SW_CAPABLE_PLATFORM
    #define SW_CAPABLE_PLATFORM false
#endif
