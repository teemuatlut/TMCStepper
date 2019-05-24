#include "SW_SPI.h"

SW_SPIClass::SW_SPIClass(uint16_t mosi, uint16_t miso, uint16_t sck) :
  mosi_pin(mosi),
  miso_pin(miso),
  sck_pin(sck)
  {}

void SW_SPIClass::init() {
  pinMode(mosi_pin, OUTPUT);
  pinMode(sck_pin, OUTPUT);
  pinMode(miso_pin, INPUT_PULLUP);
  #if defined(ARDUINO_ARCH_AVR)
    mosi_register = portOutputRegister(getPort(mosi_pin));
    miso_register = portInputRegister(getPort(miso_pin));
    sck_register = portOutputRegister(getPort(sck_pin));
    mosi_bm = digitalPinToBitMask(mosi_pin);
    miso_bm = digitalPinToBitMask(miso_pin);
    sck_bm = digitalPinToBitMask(sck_pin);
  #endif
}

//Combined shiftOut and shiftIn from Arduino wiring_shift.c
byte SW_SPIClass::transfer(uint8_t ulVal, uint8_t ulBitOrder) {
  uint8_t value = 0;

  for (uint8_t i=0 ; i<8 ; ++i) {
    // Write bit
    if ( ulBitOrder == LSBFIRST ) {
      !!(ulVal & (1 << i)) ? writeMOSI_H : writeMOSI_L;
    } else {
      !!(ulVal & (1 << (7 - i))) ? writeMOSI_H : writeMOSI_L;
    }

    // Start clock pulse
    writeSCK_H;

    // Read bit
    if ( ulBitOrder == LSBFIRST ) {
      value |= ( readMISO ? 1 : 0) << i ;
    } else {
      value |= ( readMISO ? 1 : 0) << (7 - i) ;
    }

    // Stop clock pulse
    writeSCK_L;
  }

  return value;
}

uint16_t SW_SPIClass::transfer16(uint16_t data) {
  uint16_t returnVal = 0x0000;
  returnVal |= transfer((data>>8)&0xFF) << 8;
  returnVal |= transfer(data&0xFF) & 0xFF;
  return returnVal;
}
