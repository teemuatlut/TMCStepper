#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

TMC5160Stepper::TMC5160Stepper(SPIClass &spi, PinDef pinCS, const float RS, const int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMC_RMS(RS)
  {
    resetLibCache();
  }
TMC5160Stepper::TMC5160Stepper(SW_SPIClass &spi, PinDef pinCS, const float RS, const int8_t link) :
  TMC_SPI(spi, pinCS, link),
  TMC_RMS(RS)
  {
    resetLibCache();
  }

void TMC5160Stepper::begin() {
  TMC_SPI::begin();

  COOLCONF(COOLCONF_i::r.sr);
  PWMCONF(PWMCONF_i::r.sr);
  IHOLD_IRUN(IHOLD_IRUN_i::r.sr);

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);
}

void TMC5160Stepper::defaults() {
	GCONF(1<<3);
	SLAVECONF(0);
	TMC_OUTPUT(0);
	X_COMPARE(0);
	OTP_PROG(0);
	FACTORY_CONF(0);
	SHORT_CONF(0);
	DRV_CONF(0);
	GLOBAL_SCALER(0);
	IHOLD_IRUN(0);
	TPOWERDOWN(10);
	TPWMTHRS(0);
	TCOOLTHRS(0);
	THIGH(0);
	RAMPMODE(0);
	XACTUAL(0);
	vstart(0);
	a1(0);
	v1(0);
	AMAX(0);
	VMAX(0);
	DMAX(0);
	d1(0);
	vstop(1);
	TZEROWAIT(0);
	XTARGET(0);
	VDCMIN(0);
	SW_MODE(0);
	RAMP_STAT(0);
	ENCMODE(0);
	XENC(0);
	ENC_CONST(65536u);
	ENC_STATUS(0);
	ENC_DEVIATION(0);
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
	CHOPCONF(0x10410150u);
	COOLCONF(0);
	DCCTRL(0);
	PWMCONF(0xC40C001Eu);
}

void TMC5160Stepper::resetLibCache() {
	SLAVECONF_i::r.sr = 0;
	OUTPUT_i::r.sr = 0;
	X_COMPARE_i::r.sr = 0;
	SHORT_CONF_i::r.sr = 0;
	DRV_CONF_i::r.sr = 0;
	GLOBAL_SCALER_i::r.sr = 0;
	IHOLD_IRUN_i::r.sr = 0;
	TPOWERDOWN_i::r.sr = 10;
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
	VSTOP_i::r.sr = 1;
	TZEROWAIT_i::r.sr = 0;
	VDCMIN_i::r.sr = 0;
	ENC_CONST_i::r.sr = 65536u;
	ENC_DEVIATION_i::r.sr = 0;
	MSLUTSEL_i::r.sr = 0;
	MSLUTSTART_i::r.sr = 247ul << 16;
	COOLCONF_i::r.sr = 0;
	DCCTRL_i::r.sr = 0;
	PWMCONF_i::r.sr = 0xC40C001Eu;
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
    vstart(VSTART_i::r.sr);
    a1(A1_i::r.sr);
    v1(V1_i::r.sr);
    AMAX(AMAX_i::r.sr);
    VMAX(VMAX_i::r.sr);
    DMAX(DMAX_i::r.sr);
    d1(D1_i::r.sr);
    vstop(VSTOP_i::r.sr);
    TZEROWAIT(TZEROWAIT_i::r.sr);
    ENC_CONST(ENC_CONST_i::r.sr);
    ENC_DEVIATION(ENC_DEVIATION_i::r.sr);
}
