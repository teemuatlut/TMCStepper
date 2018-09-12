#include "TMCStepper.h"
#include "TMC_DECL.h"

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = (CS+1)/32 * V_fs/(R_sense+0.02ohm) * 1/sqrt(2)
  Solve for CS ->
  CS = 32*sqrt(2)*I_rms*(R_sense+0.02)/V_fs - 1

  Example:
  vsense = 0b0 -> V_fs = 0.325V
  mA = 1640mA = I_rms/1000 = 1.64A
  R_sense = 0.10 Ohm
  ->
  CS = 32*sqrt(2)*1.64*(0.10+0.02)/0.325 - 1 = 26.4
  CS = 26
*/
TT void TMCStepper<T>::rms_current(uint16_t mA) {
  uint8_t CS = 32.0 * 1.41421 * mA / 1000.0 * (Rsense + 0.02) / 0.325 - 1;
  // If Current Scale is too low, turn on high sensitivity R_sense and calculate again
  const bool vsen = CS < 16;
  SELF.vsense(vsen);
  if (vsen) CS = (CS + 1) * 0.325 / 0.180 - 1;
  irun(CS);
  ihold(CS * holdMultiplier);
  //val_mA = mA;
}
TT void TMCStepper<T>::rms_current(uint16_t mA, float mult) {
  holdMultiplier = mult;
  SELF.rms_current(mA);
}

TT uint16_t TMCStepper<T>::rms_current() {
  return (float)(irun() + 1) / 32.0 * (SELF.vsense() ? 0.180 : 0.325) / (Rsense + 0.02) / 1.41421 * 1000;
}

TT uint8_t TMCStepper<T>::test_connection() {
  uint32_t drv_status = SELF.DRV_STATUS();
  switch (drv_status) {
      case 0xFFFFFFFF: return 1;
      case 0: return 2;
      default: return 0;
  }
}

TT void TMCStepper<T>::hysteresis_end(int8_t value) { SELF.hend(value+3); }
TT int8_t TMCStepper<T>::hysteresis_end() { return SELF.hend()-3; };

TT void TMCStepper<T>::hysteresis_start(uint8_t value) { SELF.hstrt(value-1); }
TT uint8_t TMCStepper<T>::hysteresis_start() { return SELF.hstrt()+1; }

TT void TMCStepper<T>::microsteps(uint16_t ms) {
  switch(ms) {
    case 256: SELF.mres(0); break;
    case 128: SELF.mres(1); break;
    case  64: SELF.mres(2); break;
    case  32: SELF.mres(3); break;
    case  16: SELF.mres(4); break;
    case   8: SELF.mres(5); break;
    case   4: SELF.mres(6); break;
    case   2: SELF.mres(7); break;
    case   0: SELF.mres(8); break;
    default: break;
  }
}

TT uint16_t TMCStepper<T>::microsteps() {
  switch(SELF.mres()) {
    case 0: return 256;
    case 1: return 128;
    case 2: return  64;
    case 3: return  32;
    case 4: return  16;
    case 5: return   8;
    case 6: return   4;
    case 7: return   2;
    case 8: return   0;
  }
  return 0;
}

TT void TMCStepper<T>::blank_time(uint8_t value) {
  switch (value) {
    case 16: SELF.tbl(0b00); break;
    case 24: SELF.tbl(0b01); break;
    case 36: SELF.tbl(0b10); break;
    case 54: SELF.tbl(0b11); break;
  }
}

TT uint8_t TMCStepper<T>::blank_time() {
  switch (SELF.tbl()) {
    case 0b00: return 16;
    case 0b01: return 24;
    case 0b10: return 36;
    case 0b11: return 54;
  }
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// R+C: GSTAT
TT uint8_t TMCStepper<T>::GSTAT()  { return SELF.read(ADR(GSTAT)); }
TT void  TMCStepper<T>::GSTAT(uint8_t){ SELF.write(ADR(GSTAT), 0b111); }
TT bool  TMCStepper<T>::reset()    { GSTAT_t r{0}; r.sr = GSTAT(); return r.reset; }
TT bool  TMCStepper<T>::drv_err()  { GSTAT_t r{0}; r.sr = GSTAT(); return r.drv_err; }
TT bool  TMCStepper<T>::uv_cp()    { GSTAT_t r{0}; r.sr = GSTAT(); return r.uv_cp; }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPOWERDOWN
TT uint8_t TMCStepper<T>::TPOWERDOWN() { return REG(TPOWERDOWN).sr; }
TT void TMCStepper<T>::TPOWERDOWN(uint8_t input) {
  REG(TPOWERDOWN).sr = input;
  SELF.write(ADR(TPOWERDOWN), REG(TPOWERDOWN).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: TSTEP
TT uint32_t TMCStepper<T>::TSTEP() { return SELF.read(ADR(TSTEP)); }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPWMTHRS
TT uint32_t TMCStepper<T>::TPWMTHRS() { return REG(TPWMTHRS).sr; }
TT void TMCStepper<T>::TPWMTHRS(uint32_t input) {
  REG(TPWMTHRS).sr = input;
  SELF.write(ADR(TPWMTHRS), REG(TPWMTHRS).sr);
}

TT uint16_t TMCStepper<T>::MSCNT() {
  return SELF.read(ADR(MSCNT));
}

TT uint32_t TMCStepper<T>::MSCURACT() { return SELF.read(ADR(MSCURACT)); }
TT int16_t TMCStepper<T>::cur_a() {
  MSCURACT_t r{0};
  r.sr = MSCURACT();
  int16_t value = r.cur_a;
  if (value > 255) value -= 512;
  return value;
}
TT int16_t TMCStepper<T>::cur_b() {
  MSCURACT_t r{0};
  r.sr = MSCURACT();
  int16_t value = r.cur_b;
  if (value > 255) value -= 512;
  return value;
}
