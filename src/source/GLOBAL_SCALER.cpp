/**
 * TMCStepper library by @teemuatlut
 * GLOBAL_SCALER.cpp
 * TMC2160, TMC2240
 */
#include "TMCStepper.h"
#include "TMC_MACROS.h"

//
// TMC2160
//

uint8_t TMC2160Stepper::GLOBAL_SCALER() { return GLOBAL_SCALER_register.sr; }
void TMC2160Stepper::GLOBAL_SCALER(uint8_t input) {
  GLOBAL_SCALER_register.sr = input;
  write(GLOBAL_SCALER_register.address, GLOBAL_SCALER_register.sr);
}

//
// TMC2240
//

uint8_t TMC2240Stepper::GLOBAL_SCALER() { return GLOBAL_SCALER_register.sr; }
void TMC2240Stepper::GLOBAL_SCALER(uint8_t input) {
  GLOBAL_SCALER_register.sr = input;
  write(GLOBAL_SCALER_register.address, GLOBAL_SCALER_register.sr);
}
