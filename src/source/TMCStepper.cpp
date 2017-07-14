#include <SPI.h>
#include "TMCStepper.h"
#include "TMCStepper_MACROS.h"
/*
TMCStepper::TMCStepper(uint8_t pinEN, uint8_t pinCS) {
	_started = false;

	this->_pinEN = pinEN;
	this->_pinCS = pinCS;

	//begin();
}
*/
TMC5130Stepper::TMC5130Stepper(uint8_t pinEN, uint8_t pinCS) {
	_started = false;

	this->_pinEN = pinEN;
	this->_pinCS = pinCS;

	//begin();
}

inline void TMCStepper::switchCSpin(bool state) {
	// Allows for overriding in child class to make use of fast io
	digitalWrite(_pinCS, state);
}

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
	//deactivate driver (LOW active)
	digitalWrite(_pinEN, HIGH);
	//digitalWrite(_pinCS, HIGH);
	switchCSpin(HIGH);
/*
	pinMode(MOSI, OUTPUT);
	pinMode(MISO, INPUT);
	pinMode(SCK, OUTPUT);
	digitalWrite(MOSI, LOW);
	digitalWrite(MISO, HIGH);
	digitalWrite(SCK, LOW);

	SPI.begin();
*/
	GCONF(GCONF_sr);
	CHOPCONF(CHOPCONF_sr);
	COOLCONF(COOLCONF_sr);
	PWMCONF(PWMCONF_sr);
	IHOLD_IRUN(IHOLD_IRUN_sr);

	toff(8); //off_time(8);
	tbl(1); //blank_time(24);

	_started = true;
}

void TMC5130Stepper::begin() {
	TMCStepper::begin();
	XACTUAL(XACTUAL_sr);
}

void TMCStepper::setSPISpeed(uint32_t speed) {
	spi_speed = speed;
}

void TMCStepper::write(uint8_t addressByte, uint32_t config) {
	//uint8_t s;
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000/8, MSBFIRST, SPI_MODE3));
	//digitalWrite(_pinCS, LOW);
	switchCSpin(LOW);

	SPI.transfer(addressByte & 0xFF); // s = 
	#ifdef TMCDEBUG
		Serial.print("WRITE");
		Serial.print("\t| A=");
		Serial.print(addressByte&0x7F, HEX);
		Serial.print("\t| ");
		Serial.print(config, HEX);
		Serial.print("\t| s=");
		Serial.print(status_response, HEX);
	#endif

	//*config &= ~mask; // Clear bits being set
	//*config |= (value & mask); // Set new values
	SPI.transfer((config >> 24) & 0xFF);
	SPI.transfer((config >> 16) & 0xFF);
	SPI.transfer((config >>  8) & 0xFF);
	SPI.transfer(config & 0xFF);

	#ifdef TMCDEBUG
		Serial.println();
	#endif

	//digitalWrite(_pinCS, HIGH);
	switchCSpin(HIGH);
	SPI.endTransaction();

	//return s;
}
void TMCStepper::write(uint8_t addressByte, int32_t config) {
	//uint8_t s;
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000/8, MSBFIRST, SPI_MODE3));
	//digitalWrite(_pinCS, LOW);
	switchCSpin(LOW);

	SPI.transfer(addressByte & 0xFF); // s = 
	#ifdef TMCDEBUG
		Serial.print("WRITE");
		Serial.print("\t| A=");
		Serial.print(addressByte&0x7F, HEX);
		Serial.print("\t| ");
		Serial.print(config, HEX);
		Serial.print("\t| s=");
		Serial.print(status_response, HEX);
	#endif

	//*config &= ~mask; // Clear bits being set
	//*config |= (value & mask); // Set new values
	SPI.transfer((config >> 24) & 0xFF);
	SPI.transfer((config >> 16) & 0xFF);
	SPI.transfer((config >>  8) & 0xFF);
	SPI.transfer(config & 0xFF);

	#ifdef TMCDEBUG
		Serial.println();
	#endif

	//digitalWrite(_pinCS, HIGH);
	switchCSpin(HIGH);
	SPI.endTransaction();

	//return s;
}

void TMCStepper::read(uint8_t addressByte, uint32_t *config) {
	//uint8_t s;
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000/8, MSBFIRST, SPI_MODE3));
	//digitalWrite(_pinCS, LOW);
	switchCSpin(LOW);

	SPI.transfer(addressByte & 0xFF); // s = 
	#ifdef TMCDEBUG
		Serial.print("READ");
		Serial.print("\t| A=");
		Serial.print(addressByte&0x7F, HEX);
		Serial.print("\t| ");
		Serial.print(*config, HEX);
		Serial.print("\t| s=");
		Serial.print(status_response, HEX);
	#endif

	SPI.transfer16(0x0000); // Clear SPI
	SPI.transfer16(0x0000);
	//digitalWrite(_pinCS, HIGH);
	//digitalWrite(_pinCS, LOW);
	switchCSpin(HIGH);
	switchCSpin(LOW);

	SPI.transfer(addressByte & 0xFF); // Send the address byte again
	*config  = SPI.transfer(0x00);
	*config <<= 8;
	*config |= SPI.transfer(0x00);
	*config <<= 8;
	*config |= SPI.transfer(0x00);
	*config <<= 8;
	*config |= SPI.transfer(0x00);
	#ifdef TMCDEBUG
		Serial.print("\t| R=");
		Serial.print(*config, HEX);
		Serial.println();
	#endif

	//digitalWrite(_pinCS, HIGH);
	switchCSpin(HIGH);
	SPI.endTransaction();

	//return s;
}
void TMCStepper::read(uint8_t addressByte, int32_t *config) {
	//uint8_t s;
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000/8, MSBFIRST, SPI_MODE3));
	//digitalWrite(_pinCS, LOW);
	switchCSpin(LOW);

	SPI.transfer(addressByte & 0xFF); // s = 
	#ifdef TMCDEBUG
		Serial.print("READ");
		Serial.print("\t| A=");
		Serial.print(addressByte&0x7F, HEX);
		Serial.print("\t| ");
		Serial.print(*config, HEX);
		Serial.print("\t| s=");
		Serial.print(status_response, HEX);
	#endif

	SPI.transfer16(0x0000); // Clear SPI
	SPI.transfer16(0x0000);
	//digitalWrite(_pinCS, HIGH);
	//digitalWrite(_pinCS, LOW);
	switchCSpin(HIGH);
	switchCSpin(LOW);

	SPI.transfer(addressByte & 0xFF); // Send the address byte again
	*config  = SPI.transfer(0x00);
	*config <<= 8;
	*config |= SPI.transfer(0x00);
	*config <<= 8;
	*config |= SPI.transfer(0x00);
	*config <<= 8;
	*config |= SPI.transfer(0x00);
	#ifdef TMCDEBUG
		Serial.print("\t| R=");
		Serial.print(*config, HEX);
		Serial.println();
	#endif

	//digitalWrite(_pinCS, HIGH);
	switchCSpin(HIGH);
	SPI.endTransaction();

	//return s;
}

bool TMCStepper::checkOT() {
	uint32_t response = DRV_STATUS();
	if (response & OTPW_bm) {
		flag_otpw = 1;
		return true; // bit 26 for overtemperature warning flag
	}
	return false;
}

bool TMCStepper::getOTPW() { return flag_otpw; }

void TMCStepper::clear_otpw() {	flag_otpw = 0; }

bool TMCStepper::isEnabled() { return !digitalRead(_pinEN) && toff(); }

///////////////////////////////////////////////////////////////////////////////////////
// R+C: GSTAT
void 	TMCStepper::GSTAT(uint8_t input){
	GSTAT_sr = input;
	WRITE_REG(GSTAT);
}
uint8_t TMCStepper::GSTAT()			 	{ READ_REG_R(GSTAT); 		}
bool 	TMCStepper::reset()				{ GET_BYTE(GSTAT, RESET);	}
bool 	TMCStepper::drv_err()			{ GET_BYTE(GSTAT, DRV_ERR);	}
bool 	TMCStepper::uv_cp()				{ GET_BYTE(GSTAT, UV_CP);	}
///////////////////////////////////////////////////////////////////////////////////////
// R: IFCNT
uint8_t TMCStepper::IFCNT() { READ_REG_R(IFCNT); }
///////////////////////////////////////////////////////////////////////////////////////
// W: SLAVECONF
uint16_t TMCStepper::SLAVECONF() { return SLAVECONF_sr; }
void TMCStepper::SLAVECONF(uint16_t input) {
	SLAVECONF_sr = input;
	WRITE_REG(SLAVECONF);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: IOIN
uint32_t 	TMCStepper::IOIN() 			{ READ_REG_R(IOIN); 					}
bool 		TMCStepper::refl_step()		{ GET_BYTE_R(IOIN, REFL_STEP);			}
bool 		TMCStepper::refr_dir()		{ GET_BYTE_R(IOIN, REFR_DIR);			}
bool 		TMCStepper::encb_dcen_cfg4(){ GET_BYTE_R(IOIN, ENCB_DCEN_CFG4);		}
bool 		TMCStepper::enca_dcin_cfg5(){ GET_BYTE_R(IOIN, ENCA_DCIN_CFG5);		}
bool 		TMCStepper::drv_enn_cfg6()	{ GET_BYTE_R(IOIN, DRV_ENN_CFG6);		}
bool 		TMCStepper::enc_n_dco()		{ GET_BYTE_R(IOIN, ENC_N_DCO);			}
bool 		TMCStepper::sd_mode()		{ GET_BYTE_R(IOIN, SD_MODE);			}
bool 		TMCStepper::swcomp_in()		{ GET_BYTE_R(IOIN, SWCOMP_IN);			}
uint8_t 	TMCStepper::version() 		{ GET_BYTE_R(IOIN, VERSION);			}
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
uint32_t TMCStepper::TPOWERDOWN() { return TPOWERDOWN_sr; }
void TMCStepper::TPOWERDOWN(uint32_t input) {
	TPOWERDOWN_sr = input;
	WRITE_REG(TPOWERDOWN);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: TSTEP
uint32_t TMCStepper::TSTEP() { READ_REG_R(TSTEP); }
///////////////////////////////////////////////////////////////////////////////////////
// W: TPWMTHRS
uint32_t TMCStepper::TPWMTHRS() { return TPWMTHRS_sr; }
void TMCStepper::TPWMTHRS(uint32_t input) {
	TPWMTHRS_sr = input;
	WRITE_REG(TPWMTHRS);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: TCOOLTHRS
uint32_t TMCStepper::TCOOLTHRS() { return TCOOLTHRS_sr; }
void TMCStepper::TCOOLTHRS(uint32_t input) {
	TCOOLTHRS_sr = input;
	WRITE_REG(TCOOLTHRS);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: THIGH
uint32_t TMCStepper::THIGH() { return THIGH_sr; }
void TMCStepper::THIGH(uint32_t input) {
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
uint32_t TMCStepper::VDCMIN() { return VDCMIN_sr; }
void TMCStepper::VDCMIN(uint32_t input) {
	VDCMIN_sr = input;
	WRITE_REG(VDCMIN);
}
///////////////////////////////////////////////////////////////////////////////////////
// R: PWM_SCALE
uint8_t TMCStepper::PWM_SCALE() { READ_REG_R(PWM_SCALE); }
///////////////////////////////////////////////////////////////////////////////////////
// W: ENCM_CTRL
uint8_t TMCStepper::ENCM_CTRL() { return ENCM_CTRL_sr; }
void TMCStepper::ENCM_CTRL(uint8_t input) {
	ENCM_CTRL_sr = input;
	WRITE_REG(ENCM_CTRL);
}
void TMCStepper::inv(bool B)		{ MOD_REG(ENCM_CTRL, INV);		}
void TMCStepper::maxspeed(bool B)	{ MOD_REG(ENCM_CTRL, MAXSPEED); }
bool TMCStepper::inv() 				{ GET_BYTE(ENCM_CTRL, INV); 	}
bool TMCStepper::maxspeed() 		{ GET_BYTE(ENCM_CTRL, MAXSPEED);}
///////////////////////////////////////////////////////////////////////////////////////
// R: LOST_STEPS
uint32_t TMCStepper::LOST_STEPS() { READ_REG_R(LOST_STEPS); }


/**
 *	Helper functions
 */


/*	
	Requested current = mA = I_rms/1000
	Equation for current:
	I_rms = (CS+1)/32 * V_fs/(R_sense+0.02ohm) * 1/sqrt(2)
	Solve for CS ->
	CS = 32*sqrt(2)*I_rms*(R_sense+0.02)/V_fs - 1
	
	Example:
	vsense = 0b0 -> V_fs = 0.325V
	mA = 1640mA = I_rms/1000 = 1.64A
	R_sense = 0.10 Ohm
	->
	CS = 32*sqrt(2)*1.64*(0.10+0.02)/0.325 - 1 = 26.4
	CS = 26
*/	
void TMCStepper::rms_current(uint16_t mA, float multiplier, float RS) {
	Rsense = RS;
	uint8_t CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.325 - 1;
	// If Current Scale is too low, turn on high sensitivity R_sense and calculate again
	if (CS < 16) {
		vsense(true);
		CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.180 - 1;
	} else if(vsense()) { // If CS >= 16, turn off high_sense_r if it's currently ON
		vsense(false);
	}
	irun(CS);
	ihold(CS*multiplier);
	val_mA = mA;
}

uint16_t TMCStepper::rms_current() {
	return (float)(irun()+1)/32.0 * (vsense()?0.180:0.325)/(Rsense+0.02) / 1.41421 * 1000;
}

void TMCStepper::setCurrent(uint16_t mA, float R, float multiplier) { rms_current(mA, multiplier, R); }
uint16_t TMCStepper::getCurrent() {	return val_mA; }

void TMCStepper::SilentStepStick(uint16_t current) { rms_current(current); }

void TMCStepper::microsteps(uint16_t ms) {
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

uint16_t TMCStepper::microsteps() {
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

void TMCStepper::blank_time(uint8_t value) {
	switch (value) {
		case 16: tbl(0b00); break;
		case 24: tbl(0b01); break;
		case 36: tbl(0b10); break;
		case 54: tbl(0b11); break;
	}
}

uint8_t TMCStepper::blank_time() {
	switch (tbl()) {
		case 0b00: return 16;
		case 0b01: return 24;
		case 0b10: return 36;
		case 0b11: return 54;
	}
	return 0;
}

void TMCStepper::hysterisis_low(int8_t value) { hend(value+3); }
int8_t TMCStepper::hysterisis_low() { return hend()-3; };

void TMCStepper::hysterisis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMCStepper::hysterisis_start() { return hstrt()+1; }

void TMCStepper::sg_current_decrease(uint8_t value) {
	switch(value) {
		case 32: sedn(0b00); break;
		case  8: sedn(0b01); break;
		case  2: sedn(0b10); break;
		case  1: sedn(0b11); break;
	}
}
uint8_t TMCStepper::sg_current_decrease() {
	switch(sedn()) {
		case 0b00: return 32;
		case 0b01: return  8;
		case 0b10: return  2;
		case 0b11: return  1;
	}
	return 0;
}
