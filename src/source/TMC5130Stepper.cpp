#include "TMCStepper.h"

using namespace TMCStepper_n;

TMC5130Stepper::TMC5130Stepper(SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC5130Stepper>(RS)
  {
    defaults();
  }
TMC5130Stepper::TMC5130Stepper(SW_SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMCStepper<TMC5130Stepper>(RS)
  {
    defaults();
  }

void TMC5130Stepper::begin() {
  XTARGET(0);
  XACTUAL(0);
  //while (( RAMP_STAT() & cfg.VZERO_bm) != cfg.VZERO_bm) {}
}

void TMC5130Stepper::defaults() {
  TMC_OUTPUT(1);
  ENC_CONST(65536);
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
  PWMCONF(0x00050480);
}

void TMC5130Stepper::push() {
    IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
    TPOWERDOWN(TPOWERDOWN_i::r.sr);
    TPWMTHRS(TPWMTHRS_i::r.sr);
    TCOOLTHRS(TCOOLTHRS_i::r.sr);
    THIGH(THIGH_i::r.sr);
    VDCMIN(VDCMIN_i::r.sr);
    COOLCONF(COOLCONF_i::r.sr);
    DCCTRL(DCCTRL_i::r.sr);
    ENCM_CTRL(ENCM_CTRL_i::r.sr);
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
}
