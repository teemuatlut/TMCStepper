#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2160_n;

TMC2160Stepper::TMC2160Stepper(SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC2160Stepper>(RS)
  { resetLibCache(); }
TMC2160Stepper::TMC2160Stepper(SW_SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC2160Stepper>(RS)
  { resetLibCache(); }

void TMC2160Stepper::begin() {
  //set pins
  OutputPin cs(pinCS);
  cs.mode(OUTPUT);
  cs.write(HIGH);

  if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();

  TMC2160_n::PWMCONF_i<TMC2160Stepper>::PWMCONF(TMC2160_n::PWMCONF_i<TMC2160Stepper>::r.sr);
  IHOLD_IRUN(IHOLD_IRUN_i::r.sr);

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);
}

void TMC2160Stepper::defaults() {
  GCONF(1u<<3);
  GSTAT(0);
  IHOLD_IRUN(0);
  TPOWERDOWN(10);
  TPWMTHRS(0);
  TCOOLTHRS(0);
  THIGH(0);
  XDIRECT(0);
  MSLUTSEL(0);
  MSLUTSTART(247ul << 16);
  VDCMIN(0);
  CHOPCONF(0x10410150);
  COOLCONF(0);
  DCCTRL(0);
  PWMCONF(0xC40C001E);
  ENCM_CTRL(0);
  SHORT_CONF(0);
  DRV_CONF(0);
  GLOBAL_SCALER(0);
}

void TMC2160Stepper::resetLibCache() {
  IHOLD_IRUN_i::r.sr = 0;
  TPOWERDOWN_i::r.sr = 10;
  TPWMTHRS_i::r.sr = 0;
  TCOOLTHRS_i::r.sr = 0;
  THIGH_i::r.sr = 0;
  VDCMIN_i::r.sr = 0;
  MSLUTSEL_i::r.sr = 0;
  MSLUTSTART_i::r.sr = 247ul << 16;
  COOLCONF_i::r.sr = 0;
  DCCTRL_i::r.sr = 0;
  PWMCONF_i::r.sr = 0;
  ENCM_CTRL_i::r.sr = 0;
  SHORT_CONF_i::r.sr = 0;
  DRV_CONF_i::r.sr = 0;
  GLOBAL_SCALER_i::r.sr = 0;
}

void TMC2160Stepper::push() {
  IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
  TPOWERDOWN(TPOWERDOWN_i::r.sr);
  TPWMTHRS(TPWMTHRS_i::r.sr);
  TCOOLTHRS(TCOOLTHRS_i::r.sr);
  THIGH(THIGH_i::r.sr);
  VDCMIN(VDCMIN_i::r.sr);
  COOLCONF(COOLCONF_i::r.sr);
  DCCTRL(DCCTRL_i::r.sr);
  TMC2160_n::PWMCONF_i<TMC2160Stepper>::PWMCONF(TMC2160_n::PWMCONF_i<TMC2160Stepper>::r.sr);
  SHORT_CONF(SHORT_CONF_i::r.sr);
  DRV_CONF(DRV_CONF_i::r.sr);
  GLOBAL_SCALER(GLOBAL_SCALER_i::r.sr);
}

