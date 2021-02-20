#include "../TMCStepper.h"

using namespace TMCStepper_n;

TMC5130Stepper::TMC5130Stepper(SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMC_RMS(RS)
  {
    resetLibCache();
  }
TMC5130Stepper::TMC5130Stepper(SW_SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMC_RMS(RS)
  {
    resetLibCache();
  }

void TMC5130Stepper::begin() {
  XTARGET(0);
  XACTUAL(0);
  //while (( RAMP_STAT() & cfg.VZERO_bm) != cfg.VZERO_bm) {}
}

void TMC5130Stepper::defaults() {
	GCONF(0);
	GSTAT(0);
	SLAVECONF(0);
	TMC_OUTPUT(1);
	X_COMPARE(0);
	IHOLD_IRUN(0);
	TPOWERDOWN(0);
	TPWMTHRS(0);
	TCOOLTHRS(0);
	THIGH(0);
	RAMPMODE(0);
	XACTUAL(0);
	VSTART(0);
	A1(0);
	V1(0);
	AMAX(0);
	VMAX(0);
	DMAX(0);
	D1(0);
	VSTOP(0);
	TZEROWAIT(0);
	XTARGET(0);
	VDCMIN(0);
	SW_MODE(0);
	RAMP_STAT(0);
	ENCMODE(0);
	XENC(0);
	ENC_CONST(65536u);
	ENC_STATUS(0);
	MSLUT0(0);
	MSLUT1(0);
	MSLUT2(0);
	MSLUT3(0);
	MSLUT4(0);
	MSLUT5(0);
	MSLUT6(0);
	MSLUT7(0);
	MSLUTSEL(0);
	MSLUTSTART(247ul << 16);
	CHOPCONF(0);
	COOLCONF(0);
	DCCTRL(0);
	PWMCONF(0x00050480u);
	ENCM_CTRL(0);
}

void TMC5130Stepper::resetLibCache() {
	SLAVECONF_i::r.sr = 0;
	OUTPUT_i::r.sr = 1;
	X_COMPARE_i::r.sr = 0;
	IHOLD_IRUN_i::r.sr = 0;
	TPOWERDOWN_i::r.sr = 0;
	TPWMTHRS_i::r.sr = 0;
	TCOOLTHRS_i::r.sr = 0;
	THIGH_i::r.sr = 0;
	VSTART_i::r.sr = 0;
	A1_i::r.sr = 0;
	V1_i::r.sr = 0;
	AMAX_i::r.sr = 0;
	VMAX_i::r.sr = 0;
	DMAX_i::r.sr = 0;
	D1_i::r.sr = 0;
	VSTOP_i::r.sr = 0;
	TZEROWAIT_i::r.sr = 0;
	VDCMIN_i::r.sr = 0;
	ENC_CONST_i::r.sr = 65536u;
	MSLUTSEL_i::r.sr = 0;
	MSLUTSTART_i::r.sr = 247ul << 16;
	COOLCONF_i::r.sr = 0;
	DCCTRL_i::r.sr = 0;
	PWMCONF_i::r.sr = 0;
	ENCM_CTRL_i::r.sr = 0;
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
