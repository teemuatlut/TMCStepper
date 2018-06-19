#include "SW_SPI.h"

SW_SPIClass TMC_SW_SPI;

#if defined(ARDUINO_ARCH_AVR)
  #define getPort(P) digitalPinToPort(P)
  #define writeMOSI_H *mosi_register |= mosi_bm
  #define writeMOSI_L *mosi_register &= ~mosi_bm
  #define writeSCK_H *sck_register |= sck_bm
  #define writeSCK_L *sck_register &= ~sck_bm
  #define readMISO *miso_register & miso_bm
#elif defined(ARDUINO_ARCH_SAM) // DUE:1.2MHz
  // by stimmer https://forum.arduino.cc/index.php?topic=129868.msg980466#msg980466
  #define writeMOSI_H g_APinDescription[mosi_pin].pPort -> PIO_SODR = g_APinDescription[mosi_pin].ulPin
  #define writeMOSI_L g_APinDescription[mosi_pin].pPort -> PIO_CODR = g_APinDescription[mosi_pin].ulPin
  #define writeSCK_H g_APinDescription[sck_pin].pPort -> PIO_SODR = g_APinDescription[sck_pin].ulPin
  #define writeSCK_L g_APinDescription[sck_pin].pPort -> PIO_CODR = g_APinDescription[sck_pin].ulPin
  #define readMISO !!(g_APinDescription[miso_pin].pPort -> PIO_PDSR & g_APinDescription[miso_pin].ulPin)
#else // DUE:116kHz
  #define writeMOSI_H digitalWrite(mosi_pin, HIGH)
  #define writeMOSI_L digitalWrite(mosi_pin, LOW)
  #define writeSCK_H digitalWrite(sck_pin, HIGH)
  #define writeSCK_L digitalWrite(sck_pin, LOW)
  #define readMISO digitalRead(miso_pin)
#endif

void SW_SPIClass::setPins(uint16_t sw_mosi_pin, uint16_t sw_miso_pin, uint16_t sw_sck_pin) {
  mosi_pin = sw_mosi_pin;
  miso_pin = sw_miso_pin;
  sck_pin = sw_sck_pin;
}

void SW_SPIClass::init() {
  pinMode(mosi_pin, OUTPUT);
  pinMode(sck_pin, OUTPUT);
  pinMode(miso_pin, INPUT_PULLUP);
  #ifndef TARGET_LPC1768
    mosi_bm = digitalPinToBitMask(mosi_pin);
    miso_bm = digitalPinToBitMask(miso_pin);
    sck_bm = digitalPinToBitMask(sck_pin);
    #ifdef ARDUINO_ARCH_AVR
      mosi_register = portOutputRegister(getPort(mosi_pin));
      miso_register = portInputRegister(getPort(miso_pin));
      sck_register = portOutputRegister(getPort(sck_pin));
    #endif
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
