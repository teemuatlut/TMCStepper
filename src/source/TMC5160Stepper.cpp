#include "TMCStepper.h"
#include "TMC_DECL.h"

TT TMC5160StepperBase<T>::TMC5160StepperBase(uint16_t pinCS, float RS) : TMC5130StepperBase<T>(pinCS, RS) {}

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = GLOBALSCALER/256 * (CS+1)/32 * V_fs/R_sense * 1/sqrt(2)
  Solve for CS ->
       32 * 256 * sqrt(2) * I_rms * R_sense      |
  CS = ------------------------------------ -1   |
                GLOBALSCALER * V_fs              | V_fs = 0.325
*/
TT void TMC5160StepperBase<T>::rms_current(uint16_t mA) {
  uint32_t V_fs = 325; // x1000
  uint16_t scaler = GLOBAL_SCALER();
  if (!scaler) scaler = 256;

  uint32_t numerator = 1414UL * mA;
  numerator *= this->Rsense * 1000UL;
  uint32_t CS = numerator / scaler;
  CS /= V_fs;
  CS <<= (5+8); // Multiply by 32 and 256
  CS /= 1000UL;
  CS /= 1000UL;
  CS -= 1.0;
  this->irun(CS);
  this->ihold(CS * this->holdMultiplier);
  //val_mA = mA;
}
TT void TMC5160StepperBase<T>::rms_current(uint16_t mA, float mult) {
  this->holdMultiplier = mult;
  rms_current(mA);
}
TT uint16_t TMC5160StepperBase<T>::rms_current() {
    uint16_t scaler = GLOBAL_SCALER();
    if (!scaler) scaler = 256;
    uint32_t numerator = scaler * (this->irun()+1);
    numerator *= 325;
    numerator >>= (8+5); // Divide by 256 and 32
    numerator *= 1000000;
    uint32_t denominator = this->Rsense * 1000;
    denominator *= 1414;

    return numerator / denominator;
}

// W: GLOBAL_SCALER
TT uint8_t TMC5160StepperBase<T>::GLOBAL_SCALER() { return REG(GLOBAL_SCALER).sr; }
TT void TMC5160StepperBase<T>::GLOBAL_SCALER(uint8_t input) {
  REG(GLOBAL_SCALER).sr = input;
  SELF.write(ADR(GLOBAL_SCALER), REG(GLOBAL_SCALER).sr);
}

// R: OFFSET_READ
TT uint16_t TMC5160StepperBase<T>::OFFSET_READ() { return SELF.read(ADR(OFFSET_READ)); }

// R+WC: ENC_STATUS
TT uint8_t TMC5160StepperBase<T>::ENC_STATUS() { return SELF.read(ADR(ENC_STATUS)); }
TT void TMC5160StepperBase<T>::ENC_STATUS(uint8_t input) {
	SELF.write(ADR(ENC_STATUS), input & 0x3);
}

// W: ENC_DEVIATION
TT uint32_t TMC5160StepperBase<T>::ENC_DEVIATION() { return REG(ENC_DEVIATION).sr; }
TT void TMC5160StepperBase<T>::ENC_DEVIATION(uint32_t input) {
	REG(ENC_DEVIATION).sr = input;
	SELF.write(ADR(ENC_DEVIATION), REG(ENC_DEVIATION).sr);
}

// R: PWM_SCALE
TT uint32_t TMC5160StepperBase<T>::PWM_SCALE() {
	REG(PWM_SCALE).sr = SELF.read(ADR(PWM_SCALE));
	return REG(PWM_SCALE).sr;
}
TT uint8_t TMC5160StepperBase<T>::pwm_scale_sum() { PWM_SCALE(); return REG(PWM_SCALE).pwm_scale_sum; }
TT uint16_t TMC5160StepperBase<T>::pwm_scale_auto() { PWM_SCALE(); return REG(PWM_SCALE).pwm_scale_auto; }

// R: PWM_AUTO
TT uint32_t TMC5160StepperBase<T>::PWM_AUTO() {
	REG(PWM_AUTO).sr = SELF.read(ADR(PWM_AUTO));
	return REG(PWM_AUTO).sr;
}
TT uint8_t TMC5160StepperBase<T>::pwm_ofs_auto() { PWM_AUTO(); return REG(PWM_AUTO).pwm_ofs_auto; }
TT uint8_t TMC5160StepperBase<T>::pwm_grad_auto() { PWM_AUTO(); return REG(PWM_AUTO).pwm_grad_auto; }
