#pragma once

#include <cstdint>
#include <cstddef>
#include <deque>
#include <array>

#include <unity.h>

#include <iostream>

#define SW_CAPABLE_PLATFORM false

namespace TMC_HAL {
    using PinDef = uint8_t;

    struct PinCache {
        explicit PinCache(const PinDef _pin) :
            pin(_pin)
            {}
        const PinDef pin;
    };

    inline void delay_ns(...) {}
}

#include <cstdio>

struct SPIClass {
    struct Payload {
        Payload(const uint_least8_t a, const uint_least32_t d) : address(a), data(d) {}
        uint_fast8_t address;
        uint_fast32_t data;

        bool operator ==(const Payload rhs) const {
            if (rhs.address == address && rhs.data == data) {
                return true;
            }
            else {
                return false;
            }
        }
    };

    friend std::ostream& operator<< (std::ostream &out, const SPIClass &cmd);

    operator const char*() {
        int_least16_t n = 0;

        for (auto cmd : sentCommands) {
            n += snprintf(&printout[n], sizeof(printout)-n, "{0x%02X,0x%08X} ", cmd.address, cmd.data);
        }

        return printout;
    }

    void begin() {}
    std::deque<Payload> sentCommands;
    std::deque<uint32_t> responses{};
    bool active = false;
    int transferCalls = 0;

    char printout[256] = {0};
};

struct HardwareSerial {
    HardwareSerial(void *const handle) {}

    void begin(...) {}
    void write(const uint8_t *data, uint8_t length) {}
    void read(uint8_t *buf, uint8_t length) {}
    uint8_t available() { return 0; }
};

inline void delay(int) {}

template<class TMC, typename INTERFACE>
struct MockInterface : TMC {
    using TMC::TMC;

    void set_register(const uint32_t new_value) {
        INTERFACE::r.sr = new_value;
    }
};
