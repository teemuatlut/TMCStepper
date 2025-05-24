/**
 * TMCStepper library by @teemuatlut
 * TMC2209Stepper.cpp
 * Implementing methods for TMC2209 (TMC2224)
 */
#include "TMCStepper.h"

void TMC2209Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_register.sr);
	TPOWERDOWN(TPOWERDOWN_register.sr);
	TPWMTHRS(TPWMTHRS_register.sr);
	GCONF(GCONF_register.sr);
	SLAVECONF(SLAVECONF_register.sr);
	VACTUAL(VACTUAL_register.sr);
	CHOPCONF(CHOPCONF_register.sr);
	PWMCONF(PWMCONF_register.sr);
	TCOOLTHRS(TCOOLTHRS_register.sr);
	SGTHRS(SGTHRS_register.sr);
	COOLCONF(COOLCONF_register.sr);
}

uint8_t TMC2209Stepper::SGTHRS() { return SGTHRS_register.sr; }
void TMC2209Stepper::SGTHRS(uint8_t input) {
	SGTHRS_register.sr = input;
	write(SGTHRS_register.address, SGTHRS_register.sr);
}

// W: TCOOLTHRS
uint32_t TMC2209Stepper::TCOOLTHRS() { return TCOOLTHRS_register.sr; }
void TMC2209Stepper::TCOOLTHRS(uint32_t input) {
  TCOOLTHRS_register.sr = input;
  write(TCOOLTHRS_register.address, TCOOLTHRS_register.sr);
}

uint16_t TMC2209Stepper::SG_RESULT() {
	return read(TMC2209_n::SG_RESULT_t::address);
}
