#include "TMCStepper.h"

using namespace TMCStepper_n;

TMC5160Stepper::TMC5160Stepper(SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC5160Stepper>(RS)
  {
    defaults();
  }
TMC5160Stepper::TMC5160Stepper(SW_SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC5160Stepper>(RS)
  {
    defaults();
  }

void TMC5160Stepper::defaults() {
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

  TPOWERDOWN_i::r.sr = 10;
  VSTOP_i::r.sr = 1;
  ENC_CONST_i::r.sr = 65536;
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
  PWMCONF(0xC40C001E);
}

void TMC5160Stepper::push() {
    IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
    TPOWERDOWN(TPOWERDOWN_i::r.sr);
    TPWMTHRS(TPWMTHRS_i::r.sr);
    TCOOLTHRS(TCOOLTHRS_i::r.sr);
    THIGH(THIGH_i::r.sr);
    VDCMIN(VDCMIN_i::r.sr);
    COOLCONF(COOLCONF_i::r.sr);
    DCCTRL(DCCTRL_i::r.sr);
    PWMCONF(PWMCONF_i::r.sr);
    SHORT_CONF(SHORT_CONF_i::r.sr);
    DRV_CONF(DRV_CONF_i::r.sr);
    GLOBAL_SCALER(GLOBAL_SCALER_i::r.sr);
    SLAVECONF(SLAVECONF_i::r.sr);
    TMC_OUTPUT(OUTPUT_i::r.sr);
    X_COMPARE(X_COMPARE_i::r.sr);
    VSTART(VSTART_i::r.sr);
    A1(A1_i::r.sr);
    V1(V1_i::r.sr);
    AMAX(AMAX_i::r.sr);
    VMAX(VMAX_i::r.sr);
    DMAX(DMAX_i::r.sr);
    D1(D1_i::r.sr);
    VSTOP(VSTOP_i::r.sr);
    TZEROWAIT(TZEROWAIT_i::r.sr);
    ENC_CONST(ENC_CONST_i::r.sr);
    ENC_DEVIATION(ENC_DEVIATION_i::r.sr);
}
