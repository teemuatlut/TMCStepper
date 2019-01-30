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

// R: PWM_SCALE
uint32_t TMC5160Stepper::PWM_SCALE() {
	PWM_SCALE_register.sr = read(PWM_SCALE_register.address);
	return PWM_SCALE_register.sr;
}
uint8_t TMC5160Stepper::pwm_scale_sum() { PWM_SCALE(); return PWM_SCALE_register.pwm_scale_sum; }
uint16_t TMC5160Stepper::pwm_scale_auto() { PWM_SCALE(); return PWM_SCALE_register.pwm_scale_auto; }

// R: PWM_AUTO
uint32_t TMC5160Stepper::PWM_AUTO() {
	PWM_AUTO_register.sr = read(PWM_AUTO_register.address);
	return PWM_AUTO_register.sr;
}
uint8_t TMC5160Stepper::pwm_ofs_auto() { PWM_AUTO(); return PWM_AUTO_register.pwm_ofs_auto; }
uint8_t TMC5160Stepper::pwm_grad_auto() { PWM_AUTO(); return PWM_AUTO_register.pwm_grad_auto; }
