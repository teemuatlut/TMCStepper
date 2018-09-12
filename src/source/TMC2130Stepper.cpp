#include "TMCStepper.h"
#include "TMC_DECL.h"

TT uint32_t TMC2130StepperBase<T>::spi_speed = 16000000 / 8;

TT TMC2130StepperBase<T>::TMC2130StepperBase(uint16_t pinCS, float RS) :
  TMCStepper<T>(RS),
  _pinCS(pinCS)
  {}

TT TMC2130StepperBase<T>::TMC2130StepperBase(uint16_t pinCS, float RS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK) :
  TMCStepper<T>(RS),
  _pinCS(pinCS)
  {
    SW_SPIClass *SW_SPI_Obj = new SW_SPIClass(pinMOSI, pinMISO, pinSCK);
    TMC_SW_SPI = SW_SPI_Obj;
  }

TT void TMC2130StepperBase<T>::setSPISpeed(uint32_t speed) {
  spi_speed = speed;
}

TT void TMC2130StepperBase<T>::switchCSpin(bool state) {
  // Allows for overriding in child class to make use of fast io
  digitalWrite(_pinCS, state);
}

TT uint32_t TMC2130StepperBase<T>::read(uint8_t addressByte) {
  uint32_t out = 0UL;
  if (TMC_SW_SPI != NULL) {
    switchCSpin(LOW);
    TMC_SW_SPI->transfer(addressByte & 0xFF);
    TMC_SW_SPI->transfer16(0x0000); // Clear SPI
    TMC_SW_SPI->transfer16(0x0000);

    switchCSpin(HIGH);
    switchCSpin(LOW);

    status_response = TMC_SW_SPI->transfer(addressByte & 0xFF); // Send the address byte again
    out  = TMC_SW_SPI->transfer(0x00);
    out <<= 8;
    out |= TMC_SW_SPI->transfer(0x00);
    out <<= 8;
    out |= TMC_SW_SPI->transfer(0x00);
    out <<= 8;
    out |= TMC_SW_SPI->transfer(0x00);

  } else {
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

TT void TMC2130StepperBase<T>::write(uint8_t addressByte, uint32_t config) {
  addressByte |= this->TMC_WRITE;
  if (TMC_SW_SPI != NULL) {
    switchCSpin(LOW);
    status_response = TMC_SW_SPI->transfer(addressByte & 0xFF);
    TMC_SW_SPI->transfer16((config>>16) & 0xFFFF);
    TMC_SW_SPI->transfer16(config & 0xFFFF);
  } else {
    SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
    switchCSpin(LOW);
    status_response = SPI.transfer(addressByte & 0xFF);
    SPI.transfer16((config>>16) & 0xFFFF);
    SPI.transfer16(config & 0xFFFF);
    SPI.endTransaction();
  }
  switchCSpin(HIGH);
}

TT void TMC2130StepperBase<T>::begin() {
  //set pins
  pinMode(_pinCS, OUTPUT);
  switchCSpin(HIGH);

  if (TMC_SW_SPI != NULL) TMC_SW_SPI->init();

  GCONF(REG(GCONF).sr);
  CHOPCONF(REG(CHOPCONF).sr);
  COOLCONF(REG(COOLCONF).sr);
  PWMCONF(REG(PWMCONF).sr);
  this->IHOLD_IRUN(REG(IHOLD_IRUN).sr);

  toff(8); //off_time(8);
  SELF.tbl(1); //blank_time(24);
}

/**
 *  Helper functions
 */

TT bool TMC2130StepperBase<T>::isEnabled() { return !drv_enn_cfg6() && toff(); }

TT void TMC2130StepperBase<T>::push() {
  this->GCONF(REG(GCONF).sr);
  this->IHOLD_IRUN(REG(IHOLD_IRUN).sr);
  this->TPOWERDOWN(REG(TPOWERDOWN).sr);
  this->TPWMTHRS(REG(TPWMTHRS).sr);
  this->TCOOLTHRS(REG(TCOOLTHRS).sr);
  this->THIGH(REG(THIGH).sr);
  this->XDIRECT(REG(XDIRECT).sr);
  this->VDCMIN(REG(VDCMIN).sr);
  this->CHOPCONF(REG(CHOPCONF).sr);
  this->COOLCONF(REG(COOLCONF).sr);
  this->PWMCONF(REG(PWMCONF).sr);
  this->ENCM_CTRL(REG(ENCM_CTRL).sr);
}

///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
TT uint32_t  TMC2130StepperBase<T>::IOIN()    { return SELF.read(ADR(IOIN)); }
TT bool TMC2130StepperBase<T>::step()         { IOIN_t r{0}; r.sr = IOIN(); return r.step; }
TT bool TMC2130StepperBase<T>::dir()          { IOIN_t r{0}; r.sr = IOIN(); return r.dir; }
TT bool TMC2130StepperBase<T>::dcen_cfg4()    { IOIN_t r{0}; r.sr = IOIN(); return r.dcen_cfg4; }
TT bool TMC2130StepperBase<T>::dcin_cfg5()    { IOIN_t r{0}; r.sr = IOIN(); return r.dcin_cfg5; }
TT bool TMC2130StepperBase<T>::drv_enn_cfg6() { IOIN_t r{0}; r.sr = IOIN(); return r.drv_enn_cfg6; }
TT bool TMC2130StepperBase<T>::dco()          { IOIN_t r{0}; r.sr = IOIN(); return r.dco; }
TT uint8_t TMC2130StepperBase<T>::version()   { IOIN_t r{0}; r.sr = IOIN(); return r.version; }
///////////////////////////////////////////////////////////////////////////////////////
// W: TCOOLTHRS
TT uint32_t TMC2130StepperBase<T>::TCOOLTHRS() { return REG(TCOOLTHRS).sr; }
TT void TMC2130StepperBase<T>::TCOOLTHRS(uint32_t input) {
  REG(TCOOLTHRS).sr = input;
  SELF.write(ADR(TCOOLTHRS), REG(TCOOLTHRS).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: THIGH
TT uint32_t TMC2130StepperBase<T>::THIGH() { return REG(THIGH).sr; }
TT void TMC2130StepperBase<T>::THIGH(uint32_t input) {
  REG(THIGH).sr = input;
  SELF.write(ADR(THIGH), REG(THIGH).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XDIRECT
TT uint32_t TMC2130StepperBase<T>::XDIRECT() {
  REG(XDIRECT).sr = SELF.read(ADR(XDIRECT));
  return REG(XDIRECT).sr;
}
TT void TMC2130StepperBase<T>::XDIRECT(uint32_t input) {
  REG(XDIRECT).sr = input;
  SELF.write(ADR(XDIRECT), REG(XDIRECT).sr);
}
TT void TMC2130StepperBase<T>::coil_A(int16_t B)  { REG(XDIRECT).coil_A = B; SELF.write(ADR(XDIRECT), REG(XDIRECT).sr); }
TT void TMC2130StepperBase<T>::coil_B(int16_t B)  { REG(XDIRECT).coil_B = B; SELF.write(ADR(XDIRECT), REG(XDIRECT).sr); }
TT int16_t TMC2130StepperBase<T>::coil_A()        { XDIRECT(); return REG(XDIRECT).coil_A; }
TT int16_t TMC2130StepperBase<T>::coil_B()        { XDIRECT(); return REG(XDIRECT).coil_B; }
///////////////////////////////////////////////////////////////////////////////////////
// W: VDCMIN
TT uint32_t TMC2130StepperBase<T>::VDCMIN() { return REG(VDCMIN).sr; }
TT void TMC2130StepperBase<T>::VDCMIN(uint32_t input) {
  REG(VDCMIN).sr = input;
  SELF.write(ADR(VDCMIN), REG(VDCMIN).sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: PWM_SCALE
TT uint8_t TMC2130StepperBase<T>::PWM_SCALE() { return SELF.read(ADR(PWM_SCALE)); }
///////////////////////////////////////////////////////////////////////////////////////
// W: ENCM_CTRL
TT uint8_t TMC2130StepperBase<T>::ENCM_CTRL() { return REG(ENCM_CTRL).sr; }
TT void TMC2130StepperBase<T>::ENCM_CTRL(uint8_t input) {
  REG(ENCM_CTRL).sr = input;
  SELF.write(ADR(ENCM_CTRL), REG(ENCM_CTRL).sr);
}
TT void TMC2130StepperBase<T>::inv(bool B)      { REG(ENCM_CTRL).inv = B;       SELF.write(ADR(ENCM_CTRL), REG(ENCM_CTRL).sr); }
TT void TMC2130StepperBase<T>::maxspeed(bool B) { REG(ENCM_CTRL).maxspeed  = B; SELF.write(ADR(ENCM_CTRL), REG(ENCM_CTRL).sr); }
TT bool TMC2130StepperBase<T>::inv()            { return REG(ENCM_CTRL).inv; }
TT bool TMC2130StepperBase<T>::maxspeed()       { return REG(ENCM_CTRL).maxspeed; }
///////////////////////////////////////////////////////////////////////////////////////
// R: LOST_STEPS
TT uint32_t TMC2130StepperBase<T>::LOST_STEPS() { return SELF.read(ADR(LOST_STEPS)); }

TT void TMC2130StepperBase<T>::sg_current_decrease(uint8_t value) {
  switch(value) {
    case 32: sedn(0b00); break;
    case  8: sedn(0b01); break;
    case  2: sedn(0b10); break;
    case  1: sedn(0b11); break;
  }
}
TT uint8_t TMC2130StepperBase<T>::sg_current_decrease() {
  switch(sedn()) {
    case 0b00: return 32;
    case 0b01: return  8;
    case 0b10: return  2;
    case 0b11: return  1;
  }
  return 0;
}
