#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC2130Stepper::TMC2130Stepper(uint16_t pinCS, float RS) {
  this->_pinCS = pinCS;
  Rsense = RS;
}

TMC2130Stepper::TMC2130Stepper(uint16_t pinCS, float RS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK) {
  this->_pinCS = pinCS;
  Rsense = RS;
  uses_sw_spi = true;
  TMC_SW_SPI.setPins(pinMOSI, pinMISO, pinSCK);
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
  if (uses_sw_spi) {
    switchCSpin(LOW);
    TMC_SW_SPI.transfer(addressByte & 0xFF);
    TMC_SW_SPI.transfer16(0x0000); // Clear SPI
    TMC_SW_SPI.transfer16(0x0000);

    switchCSpin(HIGH);
    switchCSpin(LOW);

    status_response = TMC_SW_SPI.transfer(addressByte & 0xFF); // Send the address byte again
    out  = TMC_SW_SPI.transfer(0x00);
    out <<= 8;
    out |= TMC_SW_SPI.transfer(0x00);
    out <<= 8;
    out |= TMC_SW_SPI.transfer(0x00);
    out <<= 8;
    out |= TMC_SW_SPI.transfer(0x00);

  } else {
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

    SPI.endTransaction();
  }
  switchCSpin(HIGH);
  return out;
}

void TMC2130Stepper::write(uint8_t addressByte, uint32_t config) {
  //Serial.print("\naddressByte="); Serial.print(addressByte, HEX);
  //Serial.print(" - config="); print_HEX(config);
  addressByte |= TMC_WRITE;
  if (uses_sw_spi) {
    switchCSpin(LOW);
    status_response = TMC_SW_SPI.transfer(addressByte & 0xFF);
    TMC_SW_SPI.transfer16((config>>16) & 0xFFFF);
    TMC_SW_SPI.transfer16(config & 0xFFFF);
  } else {
    SPI.begin();
    SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    switchCSpin(LOW);
    status_response = SPI.transfer(addressByte & 0xFF);
    SPI.transfer16((config>>16) & 0xFFFF);
    SPI.transfer16(config & 0xFFFF);
    SPI.endTransaction();
  }
  switchCSpin(HIGH);
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
