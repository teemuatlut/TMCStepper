#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC2160Stepper::TMC2160Stepper(uint16_t pinCS, float RS) : TMC2130Stepper(pinCS, RS) {}
TMC2160Stepper::TMC2160Stepper(uint16_t pinCS) : TMC2130Stepper(pinCS, 0.15) {}

void TMC2160Stepper::begin() {
  //set pins
  pinMode(_pinCS, OUTPUT);
  switchCSpin(HIGH);

  if (TMC_SW_SPI != NULL) TMC_SW_SPI->init();

  GCONF(GCONF_register.sr);
  CHOPCONF(CHOPCONF_register.sr);
  COOLCONF(COOLCONF_register.sr);
  PWMCONF(PWMCONF_register.sr);
  IHOLD_IRUN(IHOLD_IRUN_register.sr);

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);
}

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = GLOBALSCALER/256 * (CS+1)/32 * V_fs/R_sense * 1/sqrt(2)
  Solve for CS ->
       32 * 256 * sqrt(2) * I_rms * R_sense      |
  CS = ------------------------------------ -1   |
                GLOBALSCALER * V_fs              | V_fs = 0.325
*/
void TMC2160Stepper::rms_current(uint16_t mA) {
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
void TMC2160Stepper::rms_current(uint16_t mA, float mult) {
  holdMultiplier = mult;
  rms_current(mA);
}
uint16_t TMC2160Stepper::rms_current() {
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

///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
uint32_t  TMC2160Stepper::IOIN() {
  IOIN_register.sr = read(IOIN_register.address);
  return IOIN_register.sr;
}
bool    TMC2160Stepper::refl_step()      { IOIN(); return IOIN_register.refl_step; }
bool    TMC2160Stepper::refr_dir()       { IOIN(); return IOIN_register.refr_dir; }
bool    TMC2160Stepper::encb_dcen_cfg4() { IOIN(); return IOIN_register.encb_dcen_cfg4; }
bool    TMC2160Stepper::enca_dcin_cfg5() { IOIN(); return IOIN_register.enca_dcin_cfg5; }
bool    TMC2160Stepper::drv_enn()        { IOIN(); return IOIN_register.drv_enn; }
bool    TMC2160Stepper::dco_cfg6()       { IOIN(); return IOIN_register.dco_cfg6; }
uint8_t TMC2160Stepper::version()        { IOIN(); return IOIN_register.version; }

// W: GLOBAL_SCALER
uint8_t TMC2160Stepper::GLOBAL_SCALER() { return GLOBAL_SCALER_register.sr; }
void TMC2160Stepper::GLOBAL_SCALER(uint8_t input) {
  GLOBAL_SCALER_register.sr = input;
  write(GLOBAL_SCALER_register.address, GLOBAL_SCALER_register.sr);
}

// R: OFFSET_READ
uint16_t TMC2160Stepper::OFFSET_READ() { return read(OFFSET_READ_register.address); }
