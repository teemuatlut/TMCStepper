#include <SPI.h>
#include "TMCStepper.h"
#include "TMC5130_MACROS.h"
/*
TMCStepper::TMCStepper(uint8_t pinEN, uint8_t pinCS) {
	_started = false;

	this->_pinEN = pinEN;
	this->_pinCS = pinCS;

	//begin();
}
*/
TMC5130Stepper::TMC5130Stepper(uint8_t pinCS) {
	this->_pinCS = pinCS;

	#include "TMC5130_REGDEFS.h"
	TMCStepper::cfg = &cfg;
	Rsense = 0.15;

	//begin();
}

bool TMC5130Stepper::isEnabled() { return !digitalRead(_pinEN) && toff(); }

/*
void TMCStepper::begin() {
#ifdef TMCDEBUG
	Serial.println("TMC Stepper driver library");
	Serial.print("Enable pin: ");
	Serial.println(_pinEN);
	Serial.print("Chip select pin: ");
	Serial.println(_pinCS);
#endif
	//set pins
	pinMode(_pinEN, OUTPUT);
	pinMode(_pinCS, OUTPUT);
	//activate driver (LOW active)
	digitalWrite(_pinEN, LOW);
	//digitalWrite(_pinCS, HIGH);
	switchCSpin(HIGH);

	GCONF(GCONF_sr);
	CHOPCONF(CHOPCONF_sr);
	COOLCONF(COOLCONF_sr);
	PWMCONF(PWMCONF_sr);
	IHOLD_IRUN(IHOLD_IRUN_sr);

	toff(8); //off_time(8);
	tbl(1); //blank_time(24);

	_started = true;
}
*/
/*
void TMC5130Stepper::begin() {
	TMCStepper::begin();

	XTARGET(0);
	XACTUAL(0);
	while (( RAMP_STAT() & VZERO_bm) != VZERO_bm) {}
}
*/

///////////////////////////////////////////////////////////////////////////////////////
// R+C: GSTAT
void 	TMC5130Stepper::GSTAT(uint8_t input){
	GSTAT_sr = input;
	WRITE_REG(GSTAT);
}
uint8_t TMC5130Stepper::GSTAT()			 	{ READ_REG_R(GSTAT); 		}
bool 	TMC5130Stepper::reset()				{ GET_BYTE(GSTAT, RESET);	}
bool 	TMC5130Stepper::drv_err()			{ GET_BYTE(GSTAT, DRV_ERR);	}
bool 	TMC5130Stepper::uv_cp()				{ GET_BYTE(GSTAT, UV_CP);	}
///////////////////////////////////////////////////////////////////////////////////////
// R: IFCNT
uint8_t TMC5130Stepper::IFCNT() { READ_REG_R(IFCNT); }
///////////////////////////////////////////////////////////////////////////////////////
// W: SLAVECONF
uint16_t TMC5130Stepper::SLAVECONF() { return SLAVECONF_sr; }
void TMC5130Stepper::SLAVECONF(uint16_t input) {
	SLAVECONF_sr = input;
	WRITE_REG(SLAVECONF);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
uint32_t 	TMC5130Stepper::IOIN() 			{ READ_REG_R(IOIN); 					}
bool 		TMC5130Stepper::refl_step()		{ GET_BYTE_R(IOIN, REFL_STEP);			}
bool 		TMC5130Stepper::refr_dir()		{ GET_BYTE_R(IOIN, REFR_DIR);			}
bool 		TMC5130Stepper::encb_dcen_cfg4(){ GET_BYTE_R(IOIN, ENCB_DCEN_CFG4);		}
bool 		TMC5130Stepper::enca_dcin_cfg5(){ GET_BYTE_R(IOIN, ENCA_DCIN_CFG5);		}
bool 		TMC5130Stepper::drv_enn_cfg6()	{ GET_BYTE_R(IOIN, DRV_ENN_CFG6);		}
bool 		TMC5130Stepper::enc_n_dco()		{ GET_BYTE_R(IOIN, ENC_N_DCO);			}
bool 		TMC5130Stepper::sd_mode()		{ GET_BYTE_R(IOIN, SD_MODE);			}
bool 		TMC5130Stepper::swcomp_in()		{ GET_BYTE_R(IOIN, SWCOMP_IN);			}
uint8_t 	TMC5130Stepper::version() 		{ GET_BYTE_R(IOIN, VERSION);			}
///////////////////////////////////////////////////////////////////////////////////////
// W: OUTPUT
uint8_t TMC5130Stepper::TMC_OUTPUT() { return OUTPUT_sr; }
void TMC5130Stepper::TMC_OUTPUT(uint8_t input) {
	OUTPUT_sr = input;
	WRITE_REG(OUTPUT);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: X_COMPARE
uint32_t TMC5130Stepper::X_COMPARE() { return X_COMPARE_sr; }
void TMC5130Stepper::X_COMPARE(uint32_t input) {
	X_COMPARE_sr = input;
	WRITE_REG(X_COMPARE);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TPOWERDOWN
uint32_t TMC5130Stepper::TPOWERDOWN() { return TPOWERDOWN_sr; }
void TMC5130Stepper::TPOWERDOWN(uint32_t input) {
	TPOWERDOWN_sr = input;
	WRITE_REG(TPOWERDOWN);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: TSTEP
uint32_t TMC5130Stepper::TSTEP() { READ_REG_R(TSTEP); }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPWMTHRS
uint32_t TMC5130Stepper::TPWMTHRS() { return TPWMTHRS_sr; }
void TMC5130Stepper::TPWMTHRS(uint32_t input) {
	TPWMTHRS_sr = input;
	WRITE_REG(TPWMTHRS);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TCOOLTHRS
uint32_t TMC5130Stepper::TCOOLTHRS() { return TCOOLTHRS_sr; }
void TMC5130Stepper::TCOOLTHRS(uint32_t input) {
	TCOOLTHRS_sr = input;
	WRITE_REG(TCOOLTHRS);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: THIGH
uint32_t TMC5130Stepper::THIGH() { return THIGH_sr; }
void TMC5130Stepper::THIGH(uint32_t input) {
	THIGH_sr = input;
	WRITE_REG(THIGH);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: RAMPMODE
uint8_t TMC5130Stepper::RAMPMODE() { READ_REG(RAMPMODE); }
void TMC5130Stepper::RAMPMODE(uint8_t input) {
	RAMPMODE_sr = input;
	WRITE_REG(RAMPMODE);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XACTUAL
int32_t TMC5130Stepper::XACTUAL() { READ_REG(XACTUAL); }
void TMC5130Stepper::XACTUAL(int32_t input) {
	XACTUAL_sr = input;
	WRITE_REG(XACTUAL);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: VACTUAL
int32_t TMC5130Stepper::VACTUAL() { READ_REG_R(VACTUAL); }
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTART
uint32_t TMC5130Stepper::VSTART() { return VSTART_sr; }
void TMC5130Stepper::VSTART(uint32_t input) {
	VSTART_sr = input;
	WRITE_REG(VSTART);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: A1
uint16_t TMC5130Stepper::A1() { return A1_sr; }
void TMC5130Stepper::A1(uint16_t input) {
	A1_sr = input;
	WRITE_REG(A1);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: V1
uint32_t TMC5130Stepper::V1() { return V1_sr; }
void TMC5130Stepper::V1(uint32_t input) {
	V1_sr = input;
	WRITE_REG(V1);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: AMAX
uint16_t TMC5130Stepper::AMAX() { return AMAX_sr; }
void TMC5130Stepper::AMAX(uint16_t input) {
	AMAX_sr = input;
	WRITE_REG(AMAX);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VMAX
uint32_t TMC5130Stepper::VMAX() { return VMAX_sr; }
void TMC5130Stepper::VMAX(uint32_t input) {
	VMAX_sr = input;
	WRITE_REG(VMAX);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: DMAX
uint16_t TMC5130Stepper::DMAX() { return DMAX_sr; }
void TMC5130Stepper::DMAX(uint16_t input) {
	DMAX_sr = input;
	WRITE_REG(DMAX);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: D1
uint16_t TMC5130Stepper::D1() { return D1_sr; }
void TMC5130Stepper::D1(uint16_t input) {
	D1_sr = input;
	WRITE_REG(D1);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VSTOP
uint32_t TMC5130Stepper::VSTOP() { return VSTOP_sr; }
void TMC5130Stepper::VSTOP(uint32_t input) {
	if (input == 0 && RAMPMODE() == 0) return;
	VSTOP_sr = input;
	WRITE_REG(VSTOP);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TZEROWAIT
uint16_t TMC5130Stepper::TZEROWAIT() { return TZEROWAIT_sr; }
void TMC5130Stepper::TZEROWAIT(uint16_t input) {
	TZEROWAIT_sr = input;
	WRITE_REG(TZEROWAIT);
}
///////////////////////////////////////////////////////////////////////////////////////
// RW: XTARGET
int32_t TMC5130Stepper::XTARGET() { READ_REG(XTARGET); }
void TMC5130Stepper::XTARGET(int32_t input) {
	XTARGET_sr = input;
	WRITE_REG(XTARGET);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: VDCMIN
uint32_t TMC5130Stepper::VDCMIN() { return VDCMIN_sr; }
void TMC5130Stepper::VDCMIN(uint32_t input) {
	VDCMIN_sr = input;
	WRITE_REG(VDCMIN);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: PWM_SCALE
uint8_t TMC5130Stepper::PWM_SCALE() { READ_REG_R(PWM_SCALE); }
///////////////////////////////////////////////////////////////////////////////////////
// W: ENCM_CTRL
uint8_t TMC5130Stepper::ENCM_CTRL() { return ENCM_CTRL_sr; }
void TMC5130Stepper::ENCM_CTRL(uint8_t input) {
	ENCM_CTRL_sr = input;
	WRITE_REG(ENCM_CTRL);
}
void TMC5130Stepper::inv(bool B)		{ MOD_REG(ENCM_CTRL, INV);		}
void TMC5130Stepper::maxspeed(bool B)	{ MOD_REG(ENCM_CTRL, MAXSPEED); }
bool TMC5130Stepper::inv() 				{ GET_BYTE(ENCM_CTRL, INV); 	}
bool TMC5130Stepper::maxspeed() 		{ GET_BYTE(ENCM_CTRL, MAXSPEED);}
///////////////////////////////////////////////////////////////////////////////////////
// R: LOST_STEPS
uint32_t TMC5130Stepper::LOST_STEPS() { READ_REG_R(LOST_STEPS); }


/**
 *	Helper functions
 */

void TMC5130Stepper::microsteps(uint16_t ms) {
	switch(ms) {
		case 256: mres(0); break;
		case 128: mres(1); break;
		case  64: mres(2); break;
		case  32: mres(3); break;
		case  16: mres(4); break;
		case   8: mres(5); break;
		case   4: mres(6); break;
		case   2: mres(7); break;
		case   0: mres(8); break;
		default: break;
	}
}

uint16_t TMC5130Stepper::microsteps() {
	switch(mres()) {
		case 0: return 256;
		case 1: return 128;
		case 2: return  64;
		case 3: return  32;
		case 4: return  16;
		case 5: return   8;
		case 6: return   4;
		case 7: return   2;
		case 8: return   0;
	}
	return 0;
}

void TMC5130Stepper::blank_time(uint8_t value) {
	switch (value) {
		case 16: tbl(0b00); break;
		case 24: tbl(0b01); break;
		case 36: tbl(0b10); break;
		case 54: tbl(0b11); break;
	}
}

uint8_t TMC5130Stepper::blank_time() {
	switch (tbl()) {
		case 0b00: return 16;
		case 0b01: return 24;
		case 0b10: return 36;
		case 0b11: return 54;
	}
	return 0;
}

void TMC5130Stepper::hysterisis_low(int8_t value) { hend(value+3); }
int8_t TMC5130Stepper::hysterisis_low() { return hend()-3; };

void TMC5130Stepper::hysterisis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMC5130Stepper::hysterisis_start() { return hstrt()+1; }

void TMC5130Stepper::sg_current_decrease(uint8_t value) {
	switch(value) {
		case 32: sedn(0b00); break;
		case  8: sedn(0b01); break;
		case  2: sedn(0b10); break;
		case  1: sedn(0b11); break;
	}
}
uint8_t TMC5130Stepper::sg_current_decrease() {
	switch(sedn()) {
		case 0b00: return 32;
		case 0b01: return  8;
		case 0b10: return  2;
		case 0b11: return  1;
	}
	return 0;
}
