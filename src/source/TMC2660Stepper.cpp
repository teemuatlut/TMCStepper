#include "TMCStepper.h"

TMC2660Stepper::TMC2660Stepper(uint8_t pinCS) {
  this->_pinCS = pinCS;

  #include "TMC2660_REGDEFS.h"
  TMCStepper::cfg = &cfg;
  Rsense = 0.1;

  //begin();
}
