#include "TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2160_n;

TMC2160Stepper::TMC2160Stepper(SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC2160Stepper>(RS)
  { defaults(); }
TMC2160Stepper::TMC2160Stepper(SW_SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC2160Stepper>(RS)
  { defaults(); }

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
  SHORT_CONF_t short_conf{};
  short_conf.s2vs_level = 6;
  short_conf.s2g_level = 6;
  short_conf.shortfilter = 0b01;
  short_conf.shortdelay = 0;
  SHORT_CONF(short_conf.sr);

  DRV_CONF_t drv_conf{};
  drv_conf.bbmtime = 0;
  drv_conf.bbmclks = 4;
  drv_conf.otselect = 0b00;
  drv_conf.drvstrength = 0b10;
  drv_conf.filt_isense = 0b00;
  DRV_CONF(drv_conf.sr);

  TPOWERDOWN(10);
  //MSLUT0_register.sr = ???;
  //MSLUT1_register.sr = ???;
  //MSLUT2_register.sr = ???;
  //MSLUT3_register.sr = ???;
  //MSLUT4_register.sr = ???;
  //MSLUT5_register.sr = ???;
  //MSLUT6_register.sr = ???;
  //MSLUT7_register.sr = ???;
  //MSLUTSEL_register.sr = ???;
  //MSLUTSTART_register.start_sin = 0;
  //MSLUTSTART_register.start_sin90 = 247;
  CHOPCONF(0x10410150);
  TMC2160_n::PWMCONF_i<TMC2160Stepper>::PWMCONF(0xC40C001E);
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

