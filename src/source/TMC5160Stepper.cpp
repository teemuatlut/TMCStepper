#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC5160Stepper::TMC5160Stepper(uint16_t pinCS, float RS) : TMC5130Stepper(pinCS, RS) {}
TMC5160Stepper::TMC5160Stepper(uint16_t pinCS, float RS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK) :
  TMC5130Stepper(pinCS, RS, pinMOSI, pinMISO, pinSCK) {}
TMC5160Stepper::TMC5160Stepper(uint16_t pinCS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK) :
  TMC5130Stepper(pinCS, default_RS, pinMOSI, pinMISO, pinSCK) {}

// R+WC: ENC_STATUS
uint8_t TMC5160Stepper::ENC_STATUS() { return read(ENC_STATUS_t::address); }
void TMC5160Stepper::ENC_STATUS(uint8_t input) {
	write(ENC_STATUS_t::address, input & 0x3);
}

// W: ENC_DEVIATION
uint32_t TMC5160Stepper::ENC_DEVIATION() { return ENC_DEVIATION_register.sr; }
void TMC5160Stepper::ENC_DEVIATION(uint32_t input) {
	ENC_DEVIATION_register.sr = input;
	write(ENC_DEVIATION_register.address, ENC_DEVIATION_register.sr);
}

// R: PWM_AUTO
uint32_t TMC5160Stepper::PWM_AUTO() {
	return read(PWM_AUTO_t::address);
}
uint8_t TMC5160Stepper::pwm_ofs_auto()  { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_ofs_auto; }
uint8_t TMC5160Stepper::pwm_grad_auto() { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_grad_auto; }
