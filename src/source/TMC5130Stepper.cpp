#include "TMCStepper.h"
#include "TMC_DECL.h"

TT TMC5130StepperBase<T>::TMC5130StepperBase(uint16_t pinCS, float RS) : TMC2130StepperBase<T>(pinCS, RS) {}
TT TMC5130StepperBase<T>::TMC5130StepperBase(uint16_t pinCS) : TMC2130StepperBase<T>(pinCS, 0.15) {}

TT void TMC5130StepperBase<T>::begin() {
  //set pins
  pinMode(this->_pinCS, OUTPUT);
  this->switchCSpin(HIGH);

  if (this->TMC_SW_SPI != NULL) this->TMC_SW_SPI->init();

  this->GCONF(REG(GCONF).sr);
  this->CHOPCONF(REG(CHOPCONF).sr);
  this->COOLCONF(REG(COOLCONF).sr);
  this->PWMCONF(REG(PWMCONF).sr);
  this->IHOLD_IRUN(REG(IHOLD_IRUN).sr);

  this->toff(8); //off_time(8);
  SELF.tbl(1); //blank_time(24);

  XTARGET(0);
  XACTUAL(0);
  //while (( RAMP_STAT() & cfg.VZERO_bm) != cfg.VZERO_bm) {}
}

///////////////////////////////////////////////////////////////////////////////////////
// R: IFCNT
TT uint8_t TMC5130StepperBase<T>::IFCNT() { return SELF.read(ADR(IFCNT)); }
///////////////////////////////////////////////////////////////////////////////////////
// W: SLAVECONF
TT uint16_t TMC5130StepperBase<T>::SLAVECONF() { return REG(SLAVECONF).sr; }
TT void TMC5130StepperBase<T>::SLAVECONF(uint16_t input) {
  REG(SLAVECONF).sr = input;
  SELF.write(ADR(SLAVECONF), REG(SLAVECONF).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
TT uint32_t  TMC5130StepperBase<T>::IOIN() {
  REG(IOIN).sr = SELF.read(ADR(IOIN));
  return REG(IOIN).sr;
}
TT bool    TMC5130StepperBase<T>::refl_step()      { IOIN(); return REG(IOIN).refl_step; }
TT bool    TMC5130StepperBase<T>::refr_dir()       { IOIN(); return REG(IOIN).refr_dir; }
TT bool    TMC5130StepperBase<T>::encb_dcen_cfg4() { IOIN(); return REG(IOIN).encb_dcen_cfg4; }
TT bool    TMC5130StepperBase<T>::enca_dcin_cfg5() { IOIN(); return REG(IOIN).enca_dcin_cfg5; }
TT bool    TMC5130StepperBase<T>::drv_enn_cfg6()   { IOIN(); return REG(IOIN).drv_enn_cfg6; }
TT bool    TMC5130StepperBase<T>::enc_n_dco()      { IOIN(); return REG(IOIN).enc_n_dco; }
TT bool    TMC5130StepperBase<T>::sd_mode()        { IOIN(); return REG(IOIN).sd_mode; }
TT bool    TMC5130StepperBase<T>::swcomp_in()      { IOIN(); return REG(IOIN).swcomp_in; }
TT uint8_t   TMC5130StepperBase<T>::version()      { IOIN(); return REG(IOIN).version; }
///////////////////////////////////////////////////////////////////////////////////////
// W: OUTPUT
TT bool TMC5130StepperBase<T>::TMC_OUTPUT() { return REG(OUTPUT).sr; }
TT void TMC5130StepperBase<T>::TMC_OUTPUT(bool input) {
  REG(OUTPUT).sr = input;
  SELF.write(ADR(OUTPUT), REG(OUTPUT).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: X_COMPARE
TT uint32_t TMC5130StepperBase<T>::X_COMPARE() { return REG(X_COMPARE).sr; }
TT void TMC5130StepperBase<T>::X_COMPARE(uint32_t input) {
  REG(X_COMPARE).sr = input;
  SELF.write(ADR(X_COMPARE), REG(X_COMPARE).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: RAMPMODE
TT uint8_t TMC5130StepperBase<T>::RAMPMODE() { return SELF.read(ADR(RAMPMODE)); }
TT void TMC5130StepperBase<T>::RAMPMODE(uint8_t input) {
  REG(RAMPMODE).sr = input;
  SELF.write(ADR(THIGH), REG(THIGH).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XACTUAL
TT int32_t TMC5130StepperBase<T>::XACTUAL() { return SELF.read(ADR(XACTUAL)); }
TT void TMC5130StepperBase<T>::XACTUAL(int32_t input) {
  SELF.write(ADR(XACTUAL), input);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: VACTUAL
TT int32_t TMC5130StepperBase<T>::VACTUAL() { return SELF.read(ADR(VACTUAL)); }
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTART
TT uint32_t TMC5130StepperBase<T>::VSTART() { return REG(VSTART).sr; }
TT void TMC5130StepperBase<T>::VSTART(uint32_t input) {
  REG(VSTART).sr = input;
  SELF.write(ADR(VSTART), REG(VSTART).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: A1
TT uint16_t TMC5130StepperBase<T>::A1() { return A1_register.sr; }
TT void TMC5130StepperBase<T>::A1(uint16_t input) {
  A1_register.sr = input;
  SELF.write(A1_address, A1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: V1
TT uint32_t TMC5130StepperBase<T>::V1() { return V1_register.sr; }
TT void TMC5130StepperBase<T>::V1(uint32_t input) {
  V1_register.sr = input;
  SELF.write(V1_address, V1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: AMAX
TT uint16_t TMC5130StepperBase<T>::AMAX() { return REG(AMAX).sr; }
TT void TMC5130StepperBase<T>::AMAX(uint16_t input) {
  REG(AMAX).sr = input;
  SELF.write(ADR(AMAX), REG(AMAX).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VMAX
TT uint32_t TMC5130StepperBase<T>::VMAX() { return REG(VMAX).sr; }
TT void TMC5130StepperBase<T>::VMAX(uint32_t input) {
  REG(VMAX).sr = input;
  SELF.write(ADR(VMAX), REG(VMAX).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: DMAX
TT uint16_t TMC5130StepperBase<T>::DMAX() { return REG(DMAX).sr; }
TT void TMC5130StepperBase<T>::DMAX(uint16_t input) {
  REG(DMAX).sr = input;
  SELF.write(ADR(DMAX), REG(DMAX).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: D1
TT uint16_t TMC5130StepperBase<T>::D1() { return D1_register.sr; }
TT void TMC5130StepperBase<T>::D1(uint16_t input) {
  D1_register.sr = input;
  SELF.write(D1_address, D1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTOP
TT uint32_t TMC5130StepperBase<T>::VSTOP() { return REG(VSTOP).sr; }
TT void TMC5130StepperBase<T>::VSTOP(uint32_t input) {
  if (input == 0 && RAMPMODE() == 0) return;
  REG(VSTOP).sr = input;
  SELF.write(ADR(VSTOP), REG(VSTOP).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TZEROWAIT
TT uint16_t TMC5130StepperBase<T>::TZEROWAIT() { return REG(TZEROWAIT).sr; }
TT void TMC5130StepperBase<T>::TZEROWAIT(uint16_t input) {
  REG(TZEROWAIT).sr = input;
  SELF.write(ADR(TZEROWAIT), REG(TZEROWAIT).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XTARGET
TT int32_t TMC5130StepperBase<T>::XTARGET() { return SELF.read(ADR(XTARGET)); }
TT void TMC5130StepperBase<T>::XTARGET(int32_t input) {
  SELF.write(ADR(XTARGET), input);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: XLATCH
TT uint32_t TMC5130StepperBase<T>::XLATCH() { return SELF.read(ADR(XLATCH)); }
///////////////////////////////////////////////////////////////////////////////////////
// RW: X_ENC
TT int32_t TMC5130StepperBase<T>::X_ENC() { return SELF.read(ADR(X_ENC)); }
TT void TMC5130StepperBase<T>::X_ENC(int32_t input) {
  SELF.write(ADR(X_ENC), input);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: ENC_CONST
TT uint16_t TMC5130StepperBase<T>::ENC_CONST() { return REG(ENC_CONST).sr; }
TT void TMC5130StepperBase<T>::ENC_CONST(uint16_t input) {
  REG(ENC_CONST).sr = input;
  SELF.write(ADR(ENC_CONST), REG(ENC_CONST).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: ENC_STATUS
TT bool TMC5130StepperBase<T>::ENC_STATUS() { return SELF.read(ADR(ENC_STATUS)); }
///////////////////////////////////////////////////////////////////////////////////////
// R: ENC_LATCH
TT uint32_t TMC5130StepperBase<T>::ENC_LATCH() { return SELF.read(ADR(ENC_LATCH)); }
