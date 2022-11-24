#pragma once

#define TMCSPI_BITORDER_LSB 0
#define TMCSPI_BITORDER_MSB 1

#define TMCSPI_CLKMODE_0    0
#define TMCSPI_CLKMODE_1    1
#define TMCSPI_CLKMODE_2    2
#define TMCSPI_CLKMODE_3    3

struct TMCSPIInterface {
    virtual void begin(uint32_t maxClockFreq, int bitOrder, int clkMode) = 0;
    virtual void end() = 0;
    virtual uint8_t transfer(uint8_t txval) = 0;
    virtual void sendRepeat(uint8_t val, uint16_t repcnt) = 0;
};