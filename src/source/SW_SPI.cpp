#include "SW_SPI.h"

SW_SPIClass::SW_SPIClass(uint16_t mosi, uint16_t miso, uint16_t sck, uint16_t delay_us) : mosi_pin(mosi),
                                                                                              miso_pin(miso),
                                                                                              sck_pin(sck),
                                                                                              delay_us(delay_us)
{
}

void SW_SPIClass::init()
{
    pinMode(mosi_pin, OUTPUT);
    pinMode(sck_pin, OUTPUT);
    pinMode(miso_pin, INPUT_PULLUP);
#ifdef ARDUINO_ARCH_AVR
    mosi_register = portOutputRegister(getPort(mosi_pin));
    miso_register = portInputRegister(getPort(miso_pin));
    sck_register = portOutputRegister(getPort(sck_pin));
    mosi_bm = digitalPinToBitMask(mosi_pin);
    miso_bm = digitalPinToBitMask(miso_pin);
    sck_bm = digitalPinToBitMask(sck_pin);
#endif
    writeSCK_H;
}

uint8_t SW_SPIClass::transfer(uint8_t ulVal)
{
    uint8_t value = 0;
    writeSCK_L;
    delayMicroseconds(delay_us);

    for (uint8_t i = 7; i >= 1; i--)
    {
        // Write bit
        !!(ulVal & (1 << i)) ? writeMOSI_H : writeMOSI_L;
        delayMicroseconds(delay_us);
        // Start clock pulse
        writeSCK_H;
        delayMicroseconds(delay_us);
        // Read bit
        value |= (readMISO ? 1 : 0) << i;
        delayMicroseconds(delay_us);
        // Stop clock pulse
        writeSCK_L;
        delayMicroseconds(delay_us);
    }

    !!(ulVal & (1 << 0)) ? writeMOSI_H : writeMOSI_L;
    delayMicroseconds(delay_us);
    writeSCK_H;
    delayMicroseconds(delay_us);
    value |= (readMISO ? 1 : 0) << 0;
    delayMicroseconds(delay_us);

    return value;
}

uint16_t SW_SPIClass::transfer16(uint16_t data)
{
    uint16_t returnVal = 0x0000;
    returnVal |= transfer((data >> 8) & 0xFF) << 8;
    returnVal |= transfer(data & 0xFF) & 0xFF;
    return returnVal;
}
