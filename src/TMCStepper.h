#pragma once

//#define TMCDEBUG

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#endif

#include <SPI.h>
#include "source/SW_SPI.h"
#include "source/TMC2130_bitfields.h"
#include "source/TMC5130_bitfields.h"
#include "source/TMC2660_bitfields.h"

#define INIT_REGISTER(REG) reg_##REG REG##_register = reg_##REG
#define SET_ALIAS(TYPE, DRIVER, NEW, ARG, OLD) TYPE (DRIVER::*NEW)(ARG) = &DRIVER::OLD

const uint32_t TMCStepper_version = 0x10100; // v1.1.0

class TMC2130Stepper {
	public:
	TMC2130Stepper(uint8_t pinCS);
	TMC2130Stepper(uint16_t pinCS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK);
	void begin();
	void setSPISpeed(uint32_t speed);
	void switchCSpin(bool state);
	void checkStatus();
	virtual void rms_current(uint16_t mA);
	virtual uint16_t rms_current();
	bool checkOT();
	bool getOTPW();
	void clear_otpw();
	bool isEnabled();
	uint16_t getMilliAmps() {return val_mA;}
	void push();
	uint8_t test_connection();

	// Helper functions
	void microsteps(uint16_t ms);
	uint16_t microsteps();
	void blank_time(uint8_t value);
	uint8_t blank_time();
	void hysteresis_end(int8_t value);
	int8_t hysteresis_end();
	void hysteresis_start(uint8_t value);
	uint8_t hysteresis_start();
	void sg_current_decrease(uint8_t value);
	uint8_t sg_current_decrease();

	// GCONF
	uint32_t GCONF();
	void GCONF(								uint32_t value);
	void I_scale_analog(			bool B);
	void internal_Rsense(			bool B);
	void en_pwm_mode(					bool B);
	void enc_commutation(			bool B);
	void shaft(								bool B);
	void diag0_error(					bool B);
	void diag0_otpw(					bool B);
	void diag0_stall(					bool B);
	void diag1_stall(					bool B);
	void diag1_index(					bool B);
	void diag1_onstate(				bool B);
	void diag1_steps_skipped(	bool B);
	void diag0_int_pushpull(	bool B);
	void diag1_pushpull(			bool B);
	void small_hysterisis(		bool B);
	void stop_enable(					bool B);
	void direct_mode(					bool B);
	bool I_scale_analog();
	bool internal_Rsense();
	bool en_pwm_mode();
	bool enc_commutation();
	bool shaft();
	bool diag0_error();
	bool diag0_otpw();
	bool diag0_stall();
	bool diag1_stall();
	bool diag1_index();
	bool diag1_onstate();
	bool diag1_steps_skipped();
	bool diag0_int_pushpull();
	bool diag1_pushpull();
	bool small_hysterisis();
	bool stop_enable();
	bool direct_mode();

	// GSTAT
	void 	GSTAT(							uint8_t input);
	uint8_t GSTAT();
	bool 	reset();
	bool 	drv_err();
	bool 	uv_cp();

	// IOIN
	uint32_t IOIN();
	bool step();
	bool dir();
	bool dcen_cfg4();
	bool dcin_cfg5();
	bool drv_enn_cfg6();
	bool dco();
	uint8_t version();

	// IHOLD_IRUN
	void IHOLD_IRUN(					uint32_t input);
	uint32_t IHOLD_IRUN();
	void 	ihold(							uint8_t B);
	void 	irun(								uint8_t B);
	void 	iholddelay(					uint8_t B);
	uint8_t ihold();
	uint8_t irun();
	uint8_t iholddelay();

	// TPOWERDOWN
	uint8_t TPOWERDOWN();
	void TPOWERDOWN(					uint8_t input);

	// TSTEP
	uint32_t TSTEP();

	// TPWMTHRS
	uint32_t TPWMTHRS();
	void TPWMTHRS(						uint32_t input);

	// TCOOLTHRS
	uint32_t TCOOLTHRS();
	void TCOOLTHRS(						uint32_t input);

	// THIGH
	uint32_t THIGH();
	void THIGH(								uint32_t input);

	// XDRIRECT
	uint32_t XDIRECT();
	void XDIRECT(							uint32_t input);
	void coil_A(							int16_t 	B);
	void coil_B(							int16_t 	B);
	int16_t coil_A();
	int16_t coil_B();

	// VDCMIN
	uint32_t VDCMIN();
	void VDCMIN(							uint32_t input);

	// CHOPCONF
	uint32_t CHOPCONF();
	void CHOPCONF(						uint32_t value);
	void toff(								uint8_t B);
	void hstrt(								uint8_t B);
	void hend(								int8_t  B);
	//void fd(									uint8_t B);
	void disfdcc(							bool 		B);
	void rndtf(								bool 		B);
	void chm(									bool 		B);
	void tbl(									uint8_t B);
	void vsense(							bool 		B);
	void vhighfs(							bool 		B);
	void vhighchm(						bool 		B);
	void sync(								uint8_t B);
	void mres(								uint8_t B);
	void intpol(							bool 		B);
	void dedge(								bool 		B);
	void diss2g(							bool 		B);
	uint8_t toff();
	uint8_t hstrt();
	int8_t  hend();
	//uint8_t fd();
	bool 	disfdcc();
	bool 	rndtf();
	bool 	chm();
	uint8_t tbl();
	bool 	vsense();
	bool 	vhighfs();
	bool 	vhighchm();
	uint8_t sync();
	uint8_t mres();
	bool 	intpol();
	bool 	dedge();
	bool 	diss2g();

	// COOLCONF
	void COOLCONF(uint32_t value);
	uint32_t COOLCONF();
	void semin(								uint8_t B);
	void seup(								uint8_t B);
	void semax(								uint8_t B);
	void sedn(								uint8_t B);
	void seimin(							bool 		B);
	void sgt(									int8_t  B);
	void sfilt(								bool 		B);
	uint8_t semin();
	uint8_t seup();
	uint8_t semax();
	uint8_t sedn();
	bool seimin();
	int8_t sgt();
	bool sfilt();

	// DRV_STATUS
	uint32_t DRV_STATUS();
	uint16_t sg_result();
	bool fsactive();
	uint8_t cs_actual();
	bool stallguard();
	bool ot();
	bool otpw();
	bool s2ga();
	bool s2gb();
	bool ola();
	bool olb();
	bool stst();

	// PWMCONF
	void PWMCONF(							uint32_t value);
	uint32_t PWMCONF();
	void pwm_ampl(						uint8_t B);
	void pwm_grad(						uint8_t B);
	void pwm_freq(						uint8_t B);
	void pwm_autoscale(				bool		B);
	void pwm_symmetric(				bool		B);
	void freewheel(						uint8_t B);
	uint8_t pwm_ampl();
	uint8_t pwm_grad();
	uint8_t pwm_freq();
	bool 	pwm_autoscale();
	bool 	pwm_symmetric();
	uint8_t freewheel();

	// PWM_SCALE
	uint8_t PWM_SCALE();
	
	// ENCM_CTRL
	uint8_t ENCM_CTRL();
	void ENCM_CTRL(						uint8_t input);
	void inv(									bool B);
	void maxspeed(						bool B);
	bool inv();
	bool maxspeed();
	
	// LOST_STEPS
	uint32_t LOST_STEPS();

	// Function aliases

	//protected:

	static constexpr uint8_t TMC_READ = 0x00,
													TMC_WRITE = 0x80;
	virtual void write(uint8_t addressByte, uint32_t config);
	virtual uint32_t read(uint8_t addressByte);

	INIT_REGISTER(GCONF){0x00, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(IHOLD_IRUN){0x10, {0,0,0}};
	INIT_REGISTER(GSTAT){0x01, {0,0,0}};
	INIT_REGISTER(IOIN){0x04, {0,0,0,0,0,0,0}};
	INIT_REGISTER(TPOWERDOWN){0x11, 0};
	INIT_REGISTER(TSTEP){0x12};
	INIT_REGISTER(TPWMTHRS){0x13, 0};
	INIT_REGISTER(TCOOLTHRS){0x14, 0};
	INIT_REGISTER(THIGH){0x15, 0};
	INIT_REGISTER(XDIRECT){0x2D, {0,0}};
	INIT_REGISTER(VDCMIN){0x33, 0};
	INIT_REGISTER(CHOPCONF){0x6C, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(COOLCONF){0x6D, {0,0,0,0,0,0,0}};
	INIT_REGISTER(DRV_STATUS){0x6F, {0,0,0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(PWMCONF){0x70, {0,0,0,0,0,0}};
	INIT_REGISTER(PWM_SCALE){0x71};
	INIT_REGISTER(ENCM_CTRL){0x72, {0,0}};
	INIT_REGISTER(LOST_STEPS){0x73};

	uint8_t _pinCS;
	float Rsense;
	bool _started;
	uint8_t status_response;
	bool flag_otpw = false;
	uint16_t val_mA           = 0;
	float holdMultiplier = 0.5;
	uint32_t spi_speed = 16000000/8; // Default 2MHz
	bool uses_sw_spi = false;
};

class TMC5130Stepper : public TMC2130Stepper {
	public:
	TMC5130Stepper(uint8_t pinCS);
	//uint32_t setBits(uint32_t reg, uint32_t bitmask, uint8_t bitpos, uint8_t B);
	//uint32_t getBits(uint32_t sr, uint32_t bitmask, uint8_t bitpos);
	void begin();

	// R: IFCNT
	uint8_t IFCNT();
	// W: SLAVECONF
	uint16_t SLAVECONF();
	void SLAVECONF(uint16_t input);
	// IOIN
	uint32_t 	IOIN();
	bool 			refl_step();
	bool 			refr_dir();
	bool 			encb_dcen_cfg4();
	bool 			enca_dcin_cfg5();
	bool 			drv_enn_cfg6();
	bool 			enc_n_dco();
	bool 			sd_mode();
	bool 			swcomp_in();
	uint8_t 	version();

	// GCONF
	void diag1_poscomp_pushpull(bool B) { diag1_pushpull(B); }
	bool diag1_poscomp_pushpull() { return diag1_pushpull(); }

	// SW_MODE
	uint32_t SW_MODE();
	void SW_MODE(uint32_t input);

	void stop_l_enable(bool B);
	void stop_r_enable(bool B);
	void pol_stop_l(bool B);
	void pol_stop_r(bool B);
	void swap_lr(bool B);
	void latch_l_active(bool B);
	void latch_l_inactive(bool B);
	void latch_r_active(bool B);
	void latch_r_inactive(bool B);
	void en_latch_encoder(bool B);
	void sg_stop(bool B);
	void en_softstop(bool B);

	bool stop_r_enable();
	bool pol_stop_l();
	bool pol_stop_r();
	bool swap_lr();
	bool latch_l_active();
	bool latch_l_inactive();
	bool latch_r_active();
	bool latch_r_inactive();
	bool en_latch_encoder();
	bool sg_stop();
	bool en_softstop();

	// RAMP_STAT
	uint32_t RAMP_STAT();
	bool status_stop_l();
	bool status_stop_r();
	bool status_latch_l();
	bool status_latch_r();
	bool event_stop_l();
	bool event_stop_r();
	bool event_stop_sg();
	bool event_pos_reached();
	bool velocity_reached();
	bool position_reached();
	bool vzero();
	bool t_zerowait_active();
	bool second_move();
	bool status_sg();

	// ENCMODE
	uint32_t ENCMODE();
	void ENCMODE(uint32_t input);
	void pol_a(bool B);
	void pol_b(bool B);
	void pol_n(bool B);
	void ignore_ab(bool B);
	void clr_cont(bool B);
	void clr_once(bool B);
	void pos_edge(bool B);
	void neg_edge(bool B);
	void clr_enc_x(bool B);
	void latch_x_act(bool B);
	void enc_sel_decimal(bool B);

	bool pol_a();
	bool pol_b();
	bool pol_n();
	bool ignore_ab();
	bool clr_cont();
	bool clr_once();
	bool pos_edge();
	bool neg_edge();
	bool clr_enc_x();
	bool latch_x_act();
	bool enc_sel_decimal();

	// W: OUTPUT
	bool TMC_OUTPUT();
	void TMC_OUTPUT(bool input);
	// W: X_COMPARE
	uint32_t X_COMPARE();
	void X_COMPARE(uint32_t input);
	// RW: RAMPMODE
	uint8_t RAMPMODE();
	void RAMPMODE(uint8_t input);
	// RW: XACTUAL
	int32_t XACTUAL();
	void XACTUAL(int32_t input);
	// R: VACTUAL
	int32_t VACTUAL();
	// W: VSTART
	uint32_t VSTART();
	void VSTART(uint32_t input);
	// W: A1
	uint16_t A1();
	void A1(uint16_t input);
	// W: V1
	uint32_t V1();
	void V1(uint32_t input);
	// W: AMAX
	uint16_t AMAX();
	void AMAX(uint16_t input);
	// W: VMAX
	uint32_t VMAX();
	void VMAX(uint32_t input);
	// W: DMAX
	uint16_t DMAX();
	void DMAX(uint16_t input);
	// W: D1
	uint16_t D1();
	void D1(uint16_t input);
	// W: VSTOP
	uint32_t VSTOP();
	void VSTOP(uint32_t input);
	// W: TZEROWAIT
	uint16_t TZEROWAIT();
	void TZEROWAIT(uint16_t input);
	// RW: XTARGET
	int32_t XTARGET();
	void XTARGET(int32_t input);

	INIT_REGISTER(IFCNT){0x02};
	INIT_REGISTER(SLAVECONF){0x03, {0,0}};
	reg_IOIN_5130 IOIN_register = reg_IOIN_5130{0x04, {0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(OUTPUT){0x04, 0};
	INIT_REGISTER(X_COMPARE){0x05, 0};
	INIT_REGISTER(RAMPMODE){0x20, 0};
	INIT_REGISTER(XACTUAL){0x21};
	INIT_REGISTER(VACTUAL){0x22};
	INIT_REGISTER(VSTART){0x23, 0};
	INIT_REGISTER(A1){0x24, 0};
	INIT_REGISTER(V1){0x25, 0};
	INIT_REGISTER(AMAX){0x26, 0};
	INIT_REGISTER(VMAX){0x27, 0};
	INIT_REGISTER(DMAX){0x28, 0};
	INIT_REGISTER(D1){0x2A, 0};
	INIT_REGISTER(VSTOP){0x2B, 0};
	INIT_REGISTER(TZEROWAIT){0x2C, 0};
	INIT_REGISTER(XTARGET){0x2D};
	INIT_REGISTER(SW_MODE){0x34, {0,0,0,0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(RAMP_STAT){0x35, {0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(XLATCH){0x36};
	INIT_REGISTER(ENCMODE){0x38, {0,0,0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(X_ENC){0x39};
	INIT_REGISTER(ENC_CONST){0x3A, 0};
	INIT_REGISTER(ENC_STATUS){0x3B};
	INIT_REGISTER(ENC_LATCH){0x3C};
	/*
	INIT_REGISTER(MSLUT0){0x60, 0};
	INIT_REGISTER(MSLUT1){0x61, 0};
	INIT_REGISTER(MSLUT2){0x62, 0};
	INIT_REGISTER(MSLUT3){0x63, 0};
	INIT_REGISTER(MSLUT4){0x64, 0};
	INIT_REGISTER(MSLUT5){0x65, 0};
	INIT_REGISTER(MSLUT6){0x66, 0};
	INIT_REGISTER(MSLUT7){0x67, 0};
	INIT_REGISTER(MSLUTSEL){0x68, {0,0,0,0,0,0,0}};
	INIT_REGISTER(MSLUTSTART){0x69, {0,0}};
	INIT_REGISTER(MSCNT){0x6A};
	INIT_REGISTER(MSCURACT){0x6B, {0,0}};
	INIT_REGISTER(DCCTRL){0x6E, {0,0}};
	*/
};

class TMC2660Stepper {
	public:
	TMC2660Stepper(uint8_t pinCS);
	TMC2660Stepper(uint16_t pinCS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK);
	void write(uint8_t addressByte, uint32_t config);
	uint32_t read();
	void switchCSpin(bool state);
	void begin();
	bool isEnabled();
	uint16_t rms_current();
	void rms_current(uint16_t mA);
	uint16_t getMilliAmps() {return val_mA;}
	void push();

	// Helper functions
	void microsteps(uint16_t ms);
	uint16_t microsteps();
	void blank_time(uint8_t value);
	uint8_t blank_time();

	// W: DRVCONF
	void DRVCONF(uint32_t);
	void tst(bool);
	void slph(uint8_t);
	void slpl(uint8_t);
	void diss2g(bool);
	void ts2g(uint8_t);
	void sdoff(bool);
	void vsense(bool);
	void rdsel(uint8_t);
	uint32_t DRVCONF();
	bool tst();
	uint8_t slph();
	uint8_t slpl();
	bool diss2g();
	uint8_t ts2g();
	bool sdoff();
	bool vsense();
	uint8_t rdsel();

	// W: DRVCTRL
	void DRVCTRL(uint32_t);
	void pha(bool B);
	void ca(uint8_t B);
	void phb(bool B);
	void cb(uint8_t B);
	bool pha();
	uint8_t ca();
	bool phb();
	uint8_t cb();
	void intpol(bool);
	void dedge(bool);
	void mres(uint8_t);
	uint32_t DRVCTRL();
	bool intpol();
	bool dedge();
	uint8_t mres();

	// W: CHOPCONF
	void CHOPCONF(uint32_t);
	void tbl(uint8_t);
	void chm(bool);
	void rndtf(bool);
	void hdec(uint8_t);
	void hend(uint8_t);
	void hstrt(uint8_t);
	void toff(uint8_t);
	uint32_t CHOPCONF();
	uint8_t tbl();
	bool chm();
	bool rndtf();
	uint8_t hdec();
	uint8_t hend();
	uint8_t hstrt();
	uint8_t toff();

	// R: DRVSTATUS
	uint32_t DRVSTATUS();
	uint16_t mstep();
	uint8_t se();
	bool stst();
	bool olb();
	bool ola();
	bool s2gb();
	bool s2ga();
	bool otpw();
	bool ot();
	bool sg();
	uint16_t sg_result();

	// W: SGCSCONF
	uint32_t SGCSCONF();
	void sfilt(bool);
	void sgt(uint8_t);
	void cs(uint8_t);
	void SGCSCONF(uint32_t);
	bool sfilt();
	uint8_t sgt();
	uint8_t cs();

	// W: SMARTEN
	void SMARTEN(uint32_t);
	void seimin(bool B);
	void sedn(uint8_t B);
	void semax(uint8_t B);
	void seup(uint8_t B);
	void semin(uint8_t B);
	uint32_t SMARTEN();
	bool seimin();
	uint8_t sedn();
	uint8_t semax();
	uint8_t seup();
	uint8_t semin();
	/*
	// Alias
	SET_ALIAS(void, polarity_A, bool, pha);
	SET_ALIAS(void, current_A, uint8_t, ca);
	SET_ALIAS(void, polarity_B, bool, phb);
	SET_ALIAS(void, current_b, uint8_t, cb);
	SET_ALIAS(void, interpolate, bool, intpol);
	SET_ALIAS(void, double_edge_step, bool, dedge);
	SET_ALIAS(void, microsteps, uint8_t, mres);
	SET_ALIAS(void, blank_time, uint8_t, tbl);
	SET_ALIAS(void, chopper_mode, bool, chm);
	SET_ALIAS(void, random_off_time, bool, rndtf);
	SET_ALIAS(void, hysteresis_decrement, uint8_t, hdec);
	SET_ALIAS(void, hysteresis_low, uint8_t, hend);
	SET_ALIAS(void, hysteresis_start, uint8_t, hstrt);
	SET_ALIAS(void, off_time, uint8_t, toff);
	*/
	INIT_REGISTER(DRVCTRL_1){0b00, {0,0,0,0}};
	INIT_REGISTER(DRVCTRL_0){0b00, {0,0,0}};
	reg_TMC2660CHOPCONF CHOPCONF_register = reg_TMC2660CHOPCONF{0b100, {0,0,0,0,0,0,0}};
	INIT_REGISTER(SMARTEN){0b101, {0,0,0,0,0}};
	INIT_REGISTER(SGCSCONF){0b110, {0,0,0}};
	INIT_REGISTER(DRVCONF){0b111, {0,0,0,0,0,0,0,0}};
	INIT_REGISTER(READ_RDSEL00){{0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(READ_RDSEL01){{0,0,0,0,0,0,0,0,0}};
	INIT_REGISTER(READ_RDSEL10){{0,0,0,0,0,0,0,0,0,0}};

	uint8_t _pinCS;
	float Rsense;
	bool _started;
	uint8_t status_response;
	bool flag_otpw = false;
	uint16_t val_mA           = 0;
	float holdMultiplier = 0.5;
	uint32_t spi_speed = 16000000/8; // Default 2MHz
	bool uses_sw_spi = false;
};
