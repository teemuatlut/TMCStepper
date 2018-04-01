#include "TMCStepper.h"
#include "TMC_MACROS.h"
#include "TMCStepper_UTILITY.h"

TMC2130Stepper::TMC2130Stepper(uint8_t pinCS) {
  this->_pinCS = pinCS;
  Rsense = 0.15;
}

void TMC2130Stepper::setSPISpeed(uint32_t speed) {
  spi_speed = speed;
}

void TMC2130Stepper::switchCSpin(bool state) {
  // Allows for overriding in child class to make use of fast io
  digitalWrite(_pinCS, state);
}

uint32_t TMC2130Stepper::read(uint8_t addressByte) {
  uint32_t out = 0UL;
  SPI.begin();
  SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
  switchCSpin(LOW);

  SPI.transfer(addressByte & 0xFF);
  SPI.transfer16(0x0000); // Clear SPI
  SPI.transfer16(0x0000);

  switchCSpin(HIGH);
  switchCSpin(LOW);

  status_response = SPI.transfer(addressByte & 0xFF); // Send the address byte again
  out  = SPI.transfer(0x00);
  out <<= 8;
  out |= SPI.transfer(0x00);
  out <<= 8;
  out |= SPI.transfer(0x00);
  out <<= 8;
  out |= SPI.transfer(0x00);

  switchCSpin(HIGH);
  SPI.endTransaction();
  return out;
}

void TMC2130Stepper::write(uint8_t addressByte, uint32_t config) {
  Serial.print("\naddressByte="); Serial.print(addressByte, HEX);
  Serial.print(" - config="); print_HEX(config);
  SPI.begin();
  SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
  switchCSpin(LOW);
  status_response = SPI.transfer(addressByte & 0xFF);
  SPI.transfer16((config>>16) & 0xFFFF);
  SPI.transfer16(config & 0xFFFF);
  switchCSpin(HIGH);
  SPI.endTransaction();
}

void TMC2130Stepper::begin() {
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

  _started = true;
}

/**
 *  Helper functions
 */

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
void TMC2130Stepper::rms_current(uint16_t mA) {
  uint8_t CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.325 - 1;
  // If Current Scale is too low, turn on high sensitivity R_sense and calculate again
  if (CS < 16) {
    vsense(true);
    CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.180 - 1;
  } else { // If CS >= 16, turn off high_sense_r
    vsense(false);
  }
  irun(CS);
  ihold(CS*holdMultiplier);
  val_mA = mA;
}

uint16_t TMC2130Stepper::rms_current() {
  return (float)(irun()+1)/32.0 * (vsense()?0.180:0.325)/(Rsense+0.02) / 1.41421 * 1000;
}

bool TMC2130Stepper::checkOT() {
  if (otpw()) {
    flag_otpw = 1;
    return true; // bit 26 for overtemperature warning flag
  }
  return false;
}

bool TMC2130Stepper::getOTPW() { return flag_otpw; }

void TMC2130Stepper::clear_otpw() { flag_otpw = 0; }

bool TMC2130Stepper::isEnabled() { return !drv_enn_cfg6() && toff(); }

void TMC2130Stepper::push() {
  GCONF(GCONF_register.cfg.sr);
  IHOLD_IRUN(IHOLD_IRUN_register.cfg.sr);
  TPOWERDOWN(TPOWERDOWN_register.sr);
  TPWMTHRS(TPWMTHRS_register.sr);
  TCOOLTHRS(TCOOLTHRS_register.sr);
  THIGH(THIGH_register.sr);
  XDIRECT(XDIRECT_register.cfg.sr);
  VDCMIN(VDCMIN_register.sr);
  CHOPCONF(CHOPCONF_register.cfg.sr);
  COOLCONF(COOLCONF_register.cfg.sr);
  PWMCONF(PWMCONF_register.cfg.sr);
  ENCM_CTRL(ENCM_CTRL_register.cfg.sr);
}

uint8_t TMC2130Stepper::test_connection() {
  uint32_t drv_status = DRV_STATUS();
  switch (drv_status) {
      case 0xFFFFFFFF: return 1;
      case 0: return 2;
      default: return 0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////
// R+C: GSTAT
uint8_t TMC2130Stepper::GSTAT()  {
  GSTAT_register.cfg.sr = READ_REG(GSTAT);
  return GSTAT_register.cfg.sr;
}
void  TMC2130Stepper::GSTAT(uint8_t input){
  (void)(input);
  write(GSTAT_register.address, 0b111);
}
bool  TMC2130Stepper::reset()    { GSTAT(); return GSTAT_register.cfg.opt.reset; }
bool  TMC2130Stepper::drv_err()  { GSTAT(); return GSTAT_register.cfg.opt.drv_err; }
bool  TMC2130Stepper::uv_cp()    { GSTAT(); return GSTAT_register.cfg.opt.uv_cp; }
///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
uint32_t  TMC2130Stepper::IOIN() {
  IOIN_register.cfg.sr = READ_REG(IOIN);
  return IOIN_register.cfg.sr;
}
bool TMC2130Stepper::step()         { IOIN(); return IOIN_register.cfg.opt.step; }
bool TMC2130Stepper::dir()          { IOIN(); return IOIN_register.cfg.opt.dir; }
bool TMC2130Stepper::dcen_cfg4()    { IOIN(); return IOIN_register.cfg.opt.dcen_cfg4; }
bool TMC2130Stepper::dcin_cfg5()    { IOIN(); return IOIN_register.cfg.opt.dcin_cfg5; }
bool TMC2130Stepper::drv_enn_cfg6() { IOIN(); return IOIN_register.cfg.opt.drv_enn_cfg6; }
bool TMC2130Stepper::dco()          { IOIN(); return IOIN_register.cfg.opt.dco; }
uint8_t TMC2130Stepper::version()   { IOIN(); return IOIN_register.cfg.opt.version; }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPOWERDOWN
uint8_t TMC2130Stepper::TPOWERDOWN() { return TPOWERDOWN_register.sr; }
void TMC2130Stepper::TPOWERDOWN(uint8_t input) {
  TPOWERDOWN_register.sr = input;
  write(TPOWERDOWN_register.address, TPOWERDOWN_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: TSTEP
uint32_t TMC2130Stepper::TSTEP() { return READ_REG(TSTEP); }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPWMTHRS
uint32_t TMC2130Stepper::TPWMTHRS() { return TPWMTHRS_register.sr; }
void TMC2130Stepper::TPWMTHRS(uint32_t input) {
  TPWMTHRS_register.sr = input;
  write(TPWMTHRS_register.address, TPWMTHRS_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TCOOLTHRS
uint32_t TMC2130Stepper::TCOOLTHRS() { return TCOOLTHRS_register.sr; }
void TMC2130Stepper::TCOOLTHRS(uint32_t input) {
  TCOOLTHRS_register.sr = input;
  write(TCOOLTHRS_register.address, TCOOLTHRS_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: THIGH
uint32_t TMC2130Stepper::THIGH() { return THIGH_register.sr; }
void TMC2130Stepper::THIGH(uint32_t input) {
  THIGH_register.sr = input;
  write(THIGH_register.address, THIGH_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XDIRECT
uint32_t TMC2130Stepper::XDIRECT() {
  XDIRECT_register.cfg.sr = READ_REG(XDIRECT);
  return XDIRECT_register.cfg.sr;
}
void TMC2130Stepper::XDIRECT(uint32_t input) {
  XDIRECT_register.cfg.sr = input;
  WRITE_REG(XDIRECT);
}
void TMC2130Stepper::coil_A(int16_t B)  { XDIRECT_register.cfg.opt.coil_A = B; WRITE_REG(XDIRECT); }
void TMC2130Stepper::coil_B(int16_t B)  { XDIRECT_register.cfg.opt.coil_A = B; WRITE_REG(XDIRECT); }
int16_t TMC2130Stepper::coil_A()        { XDIRECT(); return XDIRECT_register.cfg.opt.coil_A; }
int16_t TMC2130Stepper::coil_B()        { XDIRECT(); return XDIRECT_register.cfg.opt.coil_B; }
///////////////////////////////////////////////////////////////////////////////////////
// W: VDCMIN
uint32_t TMC2130Stepper::VDCMIN() { return VDCMIN_register.sr; }
void TMC2130Stepper::VDCMIN(uint32_t input) {
  VDCMIN_register.sr = input;
  write(VDCMIN_register.address, VDCMIN_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: PWM_SCALE
uint8_t TMC2130Stepper::PWM_SCALE() { return READ_REG(PWM_SCALE); }
///////////////////////////////////////////////////////////////////////////////////////
// W: ENCM_CTRL
uint8_t TMC2130Stepper::ENCM_CTRL() { return ENCM_CTRL_register.cfg.sr; }
void TMC2130Stepper::ENCM_CTRL(uint8_t input) {
  ENCM_CTRL_register.cfg.sr = input;
  WRITE_REG(ENCM_CTRL);
}
void TMC2130Stepper::inv(bool B)      { ENCM_CTRL_register.cfg.opt.inv = B; WRITE_REG(ENCM_CTRL); }
void TMC2130Stepper::maxspeed(bool B) { ENCM_CTRL_register.cfg.opt.maxspeed  = B; WRITE_REG(ENCM_CTRL); }
bool TMC2130Stepper::inv()            { return ENCM_CTRL_register.cfg.opt.inv; }
bool TMC2130Stepper::maxspeed()       { return ENCM_CTRL_register.cfg.opt.maxspeed; }
///////////////////////////////////////////////////////////////////////////////////////
// R: LOST_STEPS
uint32_t TMC2130Stepper::LOST_STEPS() { return READ_REG(LOST_STEPS); }

void TMC2130Stepper::hysteresis_end(int8_t value) { hend(value+3); }
int8_t TMC2130Stepper::hysteresis_end() { return hend()-3; };

void TMC2130Stepper::hysteresis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMC2130Stepper::hysteresis_start() { return hstrt()+1; }

void TMC2130Stepper::sg_current_decrease(uint8_t value) {
  switch(value) {
    case 32: sedn(0b00); break;
    case  8: sedn(0b01); break;
    case  2: sedn(0b10); break;
    case  1: sedn(0b11); break;
  }
}
uint8_t TMC2130Stepper::sg_current_decrease() {
  switch(sedn()) {
    case 0b00: return 32;
    case 0b01: return  8;
    case 0b10: return  2;
    case 0b11: return  1;
  }
  return 0;
}

void TMC2130Stepper::microsteps(uint16_t ms) {
  switch(ms) {
    case 256: mres(0); break;
    case 128: mres(1); break;
    case  64: mres(2); break;
    case  32: mres(3); break;
    case  16: mres(4); break;
    case   8: mres(5); break;
    case   4: mres(6); break;
    case   2: mres(7); break;
    case   0: mres(8); break;
    default: break;
  }
}

uint16_t TMC2130Stepper::microsteps() {
  switch(mres()) {
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

void TMC2130Stepper::blank_time(uint8_t value) {
  switch (value) {
    case 16: tbl(0b00); break;
    case 24: tbl(0b01); break;
    case 36: tbl(0b10); break;
    case 54: tbl(0b11); break;
  }
}

uint8_t TMC2130Stepper::blank_time() {
  switch (tbl()) {
    case 0b00: return 16;
    case 0b01: return 24;
    case 0b10: return 36;
    case 0b11: return 54;
  }
  return 0;
}
