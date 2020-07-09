#include "TMCStepper.h"
#if 0
using namespace TMCStepper_n;

TMC5160Stepper::TMC5160Stepper(SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC5130Stepper(spi, pinCS, RS, link)
  { defaults(); }
TMC5160Stepper::TMC5160Stepper(SW_SPIClass &spi, PinDef pinCS, float RS, int8_t link) :
  TMC5130Stepper(spi, pinCS, RS, link)
  { defaults(); }

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
  VSTOP_register.sr = 1;
  ENC_CONST_register.sr = 65536;
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
    PWMCONF(TMC2160_n::PWMCONF_i<TMC2160Stepper>::r.sr);
    SHORT_CONF(SHORT_CONF_i::r.sr);
    DRV_CONF(DRV_CONF_i::r.sr);
    GLOBAL_SCALER(GLOBAL_SCALER_i::r.sr);
    SLAVECONF(SLAVECONF_register.sr);
    TMC_OUTPUT(OUTPUT_register.sr);
    X_COMPARE(X_COMPARE_register.sr);
    RAMPMODE(RAMPMODE_register.sr);
    XACTUAL(XACTUAL_register.sr);
    VSTART(VSTART_register.sr);
    a1(A1_register.sr);
    v1(V1_register.sr);
    AMAX(AMAX_register.sr);
    VMAX(VMAX_register.sr);
    DMAX(DMAX_register.sr);
    d1(D1_register.sr);
    VSTOP(VSTOP_register.sr);
    TZEROWAIT(TZEROWAIT_register.sr);
    SW_MODE(SW_MODE_register.sr);
    ENCMODE(ENCMODE_register.sr);
    ENC_CONST(ENC_CONST_register.sr);
	ENC_DEVIATION(ENC_DEVIATION_register.sr);
}

// R+WC: ENC_STATUS
uint8_t TMC5160Stepper::ENC_STATUS() { return read(ENC_STATUS_t::address); }
void TMC5160Stepper::ENC_STATUS(uint8_t input) {
	write(ENC_STATUS_t::address, input & 0x3);
}

// W: ENC_DEVIATION
uint32_t TMC5160Stepper::ENC_DEVIATION() { return ENC_DEVIATION_register.sr; }
void TMC5160Stepper::ENC_DEVIATION(uint32_t input) {
	ENC_DEVIATION_register.sr = input;
	write(ENC_DEVIATION_register.address, ENC_DEVIATION_register.sr);
}

// R: PWM_AUTO
uint32_t TMC5160Stepper::PWM_AUTO() {
	return read(PWM_AUTO_t::address);
}
uint8_t TMC5160Stepper::pwm_ofs_auto()  { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_ofs_auto; }
uint8_t TMC5160Stepper::pwm_grad_auto() { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_grad_auto; }

#endif
