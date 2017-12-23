#include "TMCStepper.h"

TMC2660Stepper::TMC2660Stepper(uint8_t pinCS) {
  this->_pinCS = pinCS;

  #include "TMC2660_REGDEFS.h"
  TMCStepper::cfg = &cfg;
  Rsense = 0.1;

  //begin();
}

void TMC2660Stepper::write(uint32_t config) {
  uint32_t response = 0UL;
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000/8, MSBFIRST, SPI_MODE3));
  digitalWrite(_pinCS, LOW);
  //switchCSpin(LOW);

  //DEBUG_PRINT("write", config);
  //response |= SPI.transfer((config >> 24) & 0xFF);
  //response <<= 8;
  
  response |= SPI.transfer((config >> 16) & 0xFF);
  response <<= 8;
  response |= SPI.transfer((config >>  8) & 0xFF);
  response <<= 8;
  response |= SPI.transfer(config & 0xFF);
  
  digitalWrite(_pinCS, HIGH);
  //switchCSpin(HIGH);
  SPI.endTransaction();

  SPI_response = response;
}

bool TMC2660Stepper::isEnabled() { return toff() > 0; }
