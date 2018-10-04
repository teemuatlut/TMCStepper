#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC5160Stepper::TMC5160Stepper(uint16_t pinCS, float RS) : TMC5130Stepper(pinCS, RS) {}

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = GLOBALSCALER/256 * (CS+1)/32 * V_fs/R_sense * 1/sqrt(2)
  Solve for CS ->
       32 * 256 * sqrt(2) * I_rms * R_sense      |
  CS = ------------------------------------ -1   |
                GLOBALSCALER * V_fs              | V_fs = 0.325
*/
void TMC5160Stepper::rms_current(uint16_t mA) {
  uint32_t V_fs = 325; // x1000
  uint16_t scaler = GLOBAL_SCALER();
  if (!scaler) scaler = 256;

  uint32_t numerator = 1414UL * mA;
  numerator *= Rsense*1000UL;
  uint32_t CS = numerator / scaler;
  CS /= V_fs;
  CS <<= (5+8); // Multiply by 32 and 256
  CS /= 1000UL;
  CS /= 1000UL;
  CS -= 1.0;
  irun(CS);
  ihold(CS*holdMultiplier);
  //val_mA = mA;
}
void TMC5160Stepper::rms_current(uint16_t mA, float mult) {
  holdMultiplier = mult;
  rms_current(mA);
}
uint16_t TMC5160Stepper::rms_current() {
    uint16_t scaler = GLOBAL_SCALER();
    if (!scaler) scaler = 256;
    uint32_t numerator = scaler * (irun()+1);
    numerator *= 325;
    numerator >>= (8+5); // Divide by 256 and 32
    numerator *= 1000000;
    uint32_t denominator = Rsense*1000;
    denominator *= 1414;

    return numerator / denominator;
}

// W: GLOBAL_SCALER
uint8_t TMC5160Stepper::GLOBAL_SCALER() { return GLOBAL_SCALER_register.sr; }
void TMC5160Stepper::GLOBAL_SCALER(uint8_t input) {
  GLOBAL_SCALER_register.sr = input;
  write(GLOBAL_SCALER_register.address, GLOBAL_SCALER_register.sr);
}

// R: OFFSET_READ
uint16_t TMC5160Stepper::OFFSET_READ() { return read(OFFSET_READ_register.address); }

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
