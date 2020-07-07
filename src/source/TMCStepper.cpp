#include "TMCStepper.h"

template class TMCStepper<TMC2130Stepper>;
template class TMCStepper<TMC2208Stepper>;

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
template<typename TYPE>
uint16_t TMCStepper<TYPE>::cs2rms(uint8_t CS) {
  return (float)(CS+1)/32.0 * (static_cast<TYPE*>(this)->vsense() ? 0.180 : 0.325)/(Rsense+0.02) / 1.41421 * 1000;
}

template<typename TYPE>
void TMCStepper<TYPE>::rms_current(uint16_t mA) {
  uint8_t CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.325 - 1;
  // If Current Scale is too low, turn on high sensitivity R_sense and calculate again
  if (CS < 16) {
    static_cast<TYPE*>(this)->vsense(true);
    CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.180 - 1;
  } else { // If CS >= 16, turn off high_sense_r
    static_cast<TYPE*>(this)->vsense(false);
  }

  if (CS > 31)
    CS = 31;

  static_cast<TYPE*>(this)->irun(CS);
  static_cast<TYPE*>(this)->ihold(CS*holdMultiplier);
  //val_mA = mA;
}

template<typename TYPE>
void TMCStepper<TYPE>::rms_current(uint16_t mA, float mult) {
  holdMultiplier = mult;
  rms_current(mA);
}

template<typename TYPE>
uint16_t TMCStepper<TYPE>::rms_current() {
  return cs2rms(static_cast<TYPE*>(this)->irun());
}

template<typename TYPE>
uint8_t TMCStepper<TYPE>::test_connection() {
  uint32_t drv_status = static_cast<TYPE*>(this)->DRV_STATUS();
  switch (drv_status) {
      case 0xFFFFFFFF: return 1;
      case 0: return 2;
      default: return 0;
  }
}

template<typename TYPE> void TMCStepper<TYPE>::hysteresis_end(int8_t value) { static_cast<TYPE*>(this)->hend(value+3); }
template<typename TYPE> int8_t TMCStepper<TYPE>::hysteresis_end() { return static_cast<TYPE*>(this)->hend()-3; };

template<typename TYPE> void TMCStepper<TYPE>::hysteresis_start(uint8_t value) { static_cast<TYPE*>(this)->hstrt(value-1); }
template<typename TYPE> uint8_t TMCStepper<TYPE>::hysteresis_start() { return static_cast<TYPE*>(this)->hstrt()+1; }

template<typename TYPE>
void TMCStepper<TYPE>::microsteps(uint16_t ms) {
  uint16_t mresValue{};
  switch(ms) {
    case 256: mresValue = 0; break;
    case 128: mresValue = 1; break;
    case  64: mresValue = 2; break;
    case  32: mresValue = 3; break;
    case  16: mresValue = 4; break;
    case   8: mresValue = 5; break;
    case   4: mresValue = 6; break;
    case   2: mresValue = 7; break;
    case   0: mresValue = 8; break;
    default: return;
  }

  static_cast<TYPE*>(this)->mres(mresValue);
}

template<typename TYPE>
uint16_t TMCStepper<TYPE>::microsteps() {
  switch(static_cast<TYPE*>(this)->mres()) {
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

template<typename TYPE>
void TMCStepper<TYPE>::blank_time(uint8_t value) {
  switch (value) {
    case 16: static_cast<TYPE*>(this)->tbl(0b00); break;
    case 24: static_cast<TYPE*>(this)->tbl(0b01); break;
    case 36: static_cast<TYPE*>(this)->tbl(0b10); break;
    case 54: static_cast<TYPE*>(this)->tbl(0b11); break;
  }
}

template<typename TYPE>
uint8_t TMCStepper<TYPE>::blank_time() {
  switch (static_cast<TYPE*>(this)->tbl()) {
    case 0b00: return 16;
    case 0b01: return 24;
    case 0b10: return 36;
    case 0b11: return 54;
  }
  return 0;
}
