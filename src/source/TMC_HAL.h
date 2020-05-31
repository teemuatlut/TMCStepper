
#pragma once

#if defined(ARDUINO_ARCH_AVR)

    namespace TMCStepper_n {
        typedef uint8_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint8_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const {
                return read();
            }

        protected:
            volatile uint8_t* const port = nullptr;
            uint8_t const bitMask;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint8_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
    }

#elif defined(ARDUINO_ARCH_SAM)

    namespace TMCStepper_n {

        typedef uint32_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint32_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const { return read(); }
            operator uint32_t() const { return pin; }
        protected:
            uint32_t const pin;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint32_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
    }

#elif defined(TARGET_LPC1768)

    namespace TMCStepper_n {

        typedef uint16_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint16_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const { return read(); }
            operator uint16_t() const { return pin; }
        protected:
            uint16_t const pin;
            static constexpr uint8_t pinDelay = 60;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint16_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
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

    namespace TMCStepper_n {

        typedef uint8_t PinDef;

        class TMCPin {
        public:
            explicit TMCPin(const uint8_t _pin);
            void mode(const uint8_t mode) const;
            bool read() const;
            operator bool() const {
                return read();
            }

        protected:
            uint8_t const pin;
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const uint8_t _pin);
            void write(const bool state) const;
        };

        typedef TMCPin InputPin;
    }

#elif defined(__MBED__)

    #include <mbed.h>

    namespace TMCStepper_n {
        typedef PinName PinDef;

        struct OutputPin : public DigitalOut {
            OutputPin(PinName pin);
            void mode(uint8_t);
        };

        struct InputPin : public DigitalIn {
            InputPin(PinName pin);
            void mode(const uint8_t inputType);
        };

    }

    typedef SPI SPIClass;
    typedef Serial HardwareSerial;

    inline void delay(size_t ms) { wait_us(1000*ms); }

#elif (defined(USE_FULL_LL_DRIVER) || defined(USE_HAL_DRIVER))

    #include <cstddef>
    #include "main.h"
    #if defined(USE_FULL_LL_DRIVER)
        #include <stm32f4xx_ll_gpio.h>
    #endif

    #include <stdint.h>
    #include <spi.h>
    #include <usart.h>

    #include "TMC_HAL.h"

    namespace TMCStepper_n {

        struct TMCPin {
            TMCPin(GPIO_TypeDef* const _port, uint32_t const _pin);
            void mode(const uint8_t mode) const;
            bool operator ==(const TMCPin &p2) {
                return (p2.port == port) && (p2.pin == pin);
            }

            GPIO_TypeDef* const port = nullptr;
            uint32_t const pin;
        };

        class InputPin : public TMCPin {
        public:
            InputPin(const TMCPin &_pin);
            InputPin(GPIO_TypeDef* const _port, uint32_t const _pin);

            bool read() const;

            operator bool() const { return read(); }
        };

        class OutputPin : public TMCPin {
        public:
            OutputPin(const TMCPin &_pin);
            OutputPin(GPIO_TypeDef* const _port, uint32_t const _pin);

            bool read() const;
            void write(const bool state) const;
            void toggle() const;
            void operator =(bool state) { write(state); }
        };

        typedef TMCPin PinDef;

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
    }

#endif

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
