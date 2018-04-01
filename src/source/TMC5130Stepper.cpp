#include "TMCStepper.h"
#include "TMC_MACROS.h"

/*
TMCStepper::TMCStepper(uint8_t pinEN, uint8_t pinCS) {
  _started = false;

  this->_pinEN = pinEN;
  this->_pinCS = pinCS;

  //begin();
}
*/
TMC5130Stepper::TMC5130Stepper(uint8_t pinCS) : TMC2130Stepper(pinCS, 0.15) {}

/*
uint32_t TMC5130Stepper::setBits(uint32_t sr, uint32_t bitmask, uint8_t bitpos, uint8_t B) {
  
  Serial.print("setBits(0b");
  Serial.print(sr, BIN);
  Serial.print(", 0x");
  Serial.print(bitmask, HEX);
  Serial.print(", ");
  Serial.print(bitpos);
  Serial.print(", 0b");
  Serial.print(B, BIN);
  Serial.println(')');
  ^
  sr &= ~bitmask; // Clear config area
  
  Serial.print("sr=");
  Serial.println(sr);
  
  sr |= ((uint32_t)B<<bitpos)&bitmask; // Set bits
  
  Serial.print("sr=");
  Serial.println(sr);
  
  return sr;
}

uint32_t TMC5130Stepper::getBits(uint32_t sr, uint32_t bitmask, uint8_t bitpos) {
  return (sr&bitmask) >> bitpos;
}
*/
void TMC5130Stepper::begin() {
  //set pins
  pinMode(_pinCS, OUTPUT);
  switchCSpin(HIGH);

  GCONF(GCONF_register.cfg.sr);
  CHOPCONF(CHOPCONF_register.cfg.sr);
  COOLCONF(COOLCONF_register.cfg.sr);
  PWMCONF(PWMCONF_register.cfg.sr);
  IHOLD_IRUN(IHOLD_IRUN_register.cfg.sr);

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);

  XTARGET(0);
  XACTUAL(0);
  //while (( RAMP_STAT() & cfg.VZERO_bm) != cfg.VZERO_bm) {}

  _started = true;
}

///////////////////////////////////////////////////////////////////////////////////////
// R: IFCNT
uint8_t TMC5130Stepper::IFCNT() { return READ_REG(IFCNT); }
///////////////////////////////////////////////////////////////////////////////////////
// W: SLAVECONF
uint16_t TMC5130Stepper::SLAVECONF() { return SLAVECONF_register.cfg.sr; }
void TMC5130Stepper::SLAVECONF(uint16_t input) {
  SLAVECONF_register.cfg.sr = input;
  WRITE_REG(SLAVECONF);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
uint32_t  TMC5130Stepper::IOIN() {
  IOIN_register.cfg.sr = READ_REG(IOIN);
  return IOIN_register.cfg.sr;
}
bool    TMC5130Stepper::refl_step()      { IOIN(); return IOIN_register.cfg.opt.refl_step; }
bool    TMC5130Stepper::refr_dir()       { IOIN(); return IOIN_register.cfg.opt.refr_dir; }
bool    TMC5130Stepper::encb_dcen_cfg4() { IOIN(); return IOIN_register.cfg.opt.encb_dcen_cfg4; }
bool    TMC5130Stepper::enca_dcin_cfg5() { IOIN(); return IOIN_register.cfg.opt.enca_dcin_cfg5; }
bool    TMC5130Stepper::drv_enn_cfg6()   { IOIN(); return IOIN_register.cfg.opt.drv_enn_cfg6; }
bool    TMC5130Stepper::enc_n_dco()      { IOIN(); return IOIN_register.cfg.opt.enc_n_dco; }
bool    TMC5130Stepper::sd_mode()        { IOIN(); return IOIN_register.cfg.opt.sd_mode; }
bool    TMC5130Stepper::swcomp_in()      { IOIN(); return IOIN_register.cfg.opt.swcomp_in; }
uint8_t   TMC5130Stepper::version()      { IOIN(); return IOIN_register.cfg.opt.version; }
///////////////////////////////////////////////////////////////////////////////////////
// W: OUTPUT
bool TMC5130Stepper::TMC_OUTPUT() { return OUTPUT_register.sr; }
void TMC5130Stepper::TMC_OUTPUT(bool input) {
  OUTPUT_register.sr = input;
  write(OUTPUT_register.address, OUTPUT_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: X_COMPARE
uint32_t TMC5130Stepper::X_COMPARE() { return X_COMPARE_register.sr; }
void TMC5130Stepper::X_COMPARE(uint32_t input) {
  X_COMPARE_register.sr = input;
  write(X_COMPARE_register.address, X_COMPARE_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: RAMPMODE
uint8_t TMC5130Stepper::RAMPMODE() { return READ_REG(RAMPMODE); }
void TMC5130Stepper::RAMPMODE(uint8_t input) {
  RAMPMODE_register.sr = input;
  write(THIGH_register.address, THIGH_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XACTUAL
int32_t TMC5130Stepper::XACTUAL() { return READ_REG(XACTUAL); }
void TMC5130Stepper::XACTUAL(int32_t input) {
  write(XACTUAL_register.address, input);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: VACTUAL
int32_t TMC5130Stepper::VACTUAL() { return READ_REG(VACTUAL); }
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTART
uint32_t TMC5130Stepper::VSTART() { return VSTART_register.sr; }
void TMC5130Stepper::VSTART(uint32_t input) {
  VSTART_register.sr = input;
  write(VSTART_register.address, VSTART_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: A1
uint16_t TMC5130Stepper::A1() { return A1_register.sr; }
void TMC5130Stepper::A1(uint16_t input) {
  A1_register.sr = input;
  write(A1_register.address, A1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: V1
uint32_t TMC5130Stepper::V1() { return V1_register.sr; }
void TMC5130Stepper::V1(uint32_t input) {
  V1_register.sr = input;
  write(V1_register.address, V1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: AMAX
uint16_t TMC5130Stepper::AMAX() { return AMAX_register.sr; }
void TMC5130Stepper::AMAX(uint16_t input) {
  AMAX_register.sr = input;
  write(AMAX_register.address, AMAX_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VMAX
uint32_t TMC5130Stepper::VMAX() { return VMAX_register.sr; }
void TMC5130Stepper::VMAX(uint32_t input) {
  VMAX_register.sr = input;
  write(VMAX_register.address, VMAX_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: DMAX
uint16_t TMC5130Stepper::DMAX() { return DMAX_register.sr; }
void TMC5130Stepper::DMAX(uint16_t input) {
  DMAX_register.sr = input;
  write(DMAX_register.address, DMAX_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: D1
uint16_t TMC5130Stepper::D1() { return D1_register.sr; }
void TMC5130Stepper::D1(uint16_t input) {
  D1_register.sr = input;
  write(D1_register.address, D1_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTOP
uint32_t TMC5130Stepper::VSTOP() { return VSTOP_register.sr; }
void TMC5130Stepper::VSTOP(uint32_t input) {
  if (input == 0 && RAMPMODE() == 0) return;
  VSTOP_register.sr = input;
  write(VSTOP_register.address, VSTOP_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TZEROWAIT
uint16_t TMC5130Stepper::TZEROWAIT() { return TZEROWAIT_register.sr; }
void TMC5130Stepper::TZEROWAIT(uint16_t input) {
  TZEROWAIT_register.sr = input;
  write(TZEROWAIT_register.address, TZEROWAIT_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XTARGET
int32_t TMC5130Stepper::XTARGET() { return READ_REG(XTARGET); }
void TMC5130Stepper::XTARGET(int32_t input) {
  write(XTARGET_register.address, input);
}
