/**
 * TMCStepper library by @teemuatlut
 * TMC2240Stepper.cpp
 */
#include "TMCStepper.h"
#include "TMC_MACROS.h"

int8_t TMC2240Stepper::chain_length = 0;
uint32_t TMC2240Stepper::spi_speed = 16000000/8;

TMC2240Stepper::TMC2240Stepper(uint16_t pinCS, int8_t link) :
	_pinCS(pinCS),
	link_index(link)
	{
		defaults();

		if (link > chain_length)
			chain_length = link;
	}

TMC2240Stepper::TMC2240Stepper(uint16_t pinCS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK, int8_t link) :
	_pinCS(pinCS),
	link_index(link)
	{
		SW_SPIClass *SW_SPI_Obj = new SW_SPIClass(pinMOSI, pinMISO, pinSCK);
		TMC_SW_SPI = SW_SPI_Obj;
		defaults();

		if (link > chain_length)
			chain_length = link;
	}

void TMC2240Stepper::defaults() {
	//GCONF_register.en_spreadcycle = 0;
	GCONF_register.multistep_filt = 1;

	IHOLD_IRUN_register.iholddelay = 1;
	TPOWERDOWN_register.sr = 20;

	CHOPCONF_register.sr = 0x10000053; 	// 1/16 x 256 single-edge
	PWMCONF_register.sr = 0xC10D0024; 	// autoscale=1, freq=01, grad & amp, freewheel=00
}

__attribute__((weak))
void TMC2240Stepper::setSPISpeed(uint32_t speed) {
	spi_speed = speed;
}

__attribute__((weak))
void TMC2240Stepper::switchCSpin(bool state) {
	digitalWrite(_pinCS, state);
}

__attribute__((weak))
void TMC2240Stepper::beginTransaction() {
	if (TMC_SW_SPI == nullptr) {
		SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
	}
}
__attribute__((weak))
void TMC2240Stepper::endTransaction() {
	if (TMC_SW_SPI == nullptr) {
		SPI.endTransaction();
	}
}

__attribute__((weak))
uint8_t TMC2240Stepper::transfer(const uint8_t data) {
	uint8_t out = 0;
	if (TMC_SW_SPI != nullptr) {
		out = TMC_SW_SPI->transfer(data);
	}
	else {
		out = SPI.transfer(data);
	}
	return out;
}

void TMC2240Stepper::transferEmptyBytes(const uint8_t n) {
	for (uint8_t i = 0; i < n; i++) {
		transfer(0x00);
	}
}

__attribute__((weak))
uint32_t TMC2240Stepper::read(uint8_t addressByte) {
	uint32_t out = 0UL;
	int8_t i = 1;

	beginTransaction();
	switchCSpin(LOW);
	transfer(addressByte);
	// Clear SPI
	transferEmptyBytes(4);

	// Shift the written data to the correct driver in chain
	// Default link_index = -1 and no shifting happens
	while(i < link_index) {
		transferEmptyBytes(5);
		i++;
	}

	switchCSpin(HIGH);
	switchCSpin(LOW);

	// Shift data from target link into the last one...
	while(i < chain_length) {
		transferEmptyBytes(5);
		i++;
	}

	// ...and once more to MCU
	status_response = transfer(addressByte); // Send the address byte again
	out  = transfer(0x00);
	out <<= 8;
	out |= transfer(0x00);
	out <<= 8;
	out |= transfer(0x00);
	out <<= 8;
	out |= transfer(0x00);

	endTransaction();
	switchCSpin(HIGH);
	return out;
}

__attribute__((weak))
void TMC2240Stepper::write(uint8_t addressByte, uint32_t config) {
	addressByte |= TMC_WRITE;
	int8_t i = 1;

	beginTransaction();
	switchCSpin(LOW);
	status_response = transfer(addressByte);
	transfer(config>>24);
	transfer(config>>16);
	transfer(config>>8);
	transfer(config);

	// Shift the written data to the correct driver in chain
	// Default link_index = -1 and no shifting happens
	while (i < link_index) {
		transferEmptyBytes(5);
		i++;
	}

	endTransaction();
	switchCSpin(HIGH);
}

void TMC2240Stepper::begin() {
	// set pins
	pinMode(_pinCS, OUTPUT);
	switchCSpin(HIGH);

	if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();

	//GCONF(GCONF_register.sr);
	//CHOPCONF(CHOPCONF_register.sr);
	//PWMCONF(PWMCONF_register.sr);
	//IHOLD_IRUN(IHOLD_IRUN_register.sr);

	//toff(8); //off_time(8);
	//tbl(1); //blank_time(24);
}

void TMC2240Stepper::push() {
	TPOWERDOWN(TPOWERDOWN_register.sr);
	TPWMTHRS(TPWMTHRS_register.sr);
	GCONF(GCONF_register.sr);
	SLAVECONF(SLAVECONF_register.sr);
	DRV_CONF(DRV_CONF_register.sr);
	IHOLD_IRUN(IHOLD_IRUN_register.sr);
	CHOPCONF(CHOPCONF_register.sr);
	PWMCONF(PWMCONF_register.sr);
}

bool TMC2240Stepper::isEnabled() { return !drv_enn() && toff(); }

uint8_t TMC2240Stepper::IFCNT() {
	return read(IFCNT_t::address);
}

uint32_t TMC2240Stepper::PWM_SCALE() {
	return read(TMC2240_n::PWM_SCALE_t::address);
}
uint8_t TMC2240Stepper::pwm_scale_sum() {
	TMC2240_n::PWM_SCALE_t r{0};
	r.sr = PWM_SCALE();
	return r.pwm_scale_sum;
}

int16_t TMC2240Stepper::pwm_scale_auto() {
	TMC2240_n::PWM_SCALE_t r{0};
	r.sr = PWM_SCALE();
	return r.pwm_scale_auto;
	// Not two's complement? 9nth bit determines sign
	/*
	uint32_t d = PWM_SCALE();
	int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
	if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
	else return response;
	*/
}

// R: PWM_AUTO
uint32_t TMC2240Stepper::PWM_AUTO() {
	return read(PWM_AUTO_t::address);
}
uint8_t TMC2240Stepper::pwm_ofs_auto()  { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_ofs_auto; }
uint8_t TMC2240Stepper::pwm_grad_auto() { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_grad_auto; }

/**
 * 0:1A  1:2A  2:3A  3:3A
 */
//#define TMC2240_CURRENT_RANGE   2

/**
 * ('rref', 12000, minval=12000, maxval=60000)
 */
//#define TMC2240_Rref            12000

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = (CS+1)/32 * V_fs/R_sense * 1/sqrt(2)
  Solve for CS ->
  CS = 32*sqrt(2)*I_rms*R_sense/V_fs - 1

  Example:
  vsense = 0b0 -> V_fs = 0.310V //Typical
  mA = 1650mA = I_rms/1000 = 1.65A
  R_sense = 0.100 Ohm
  ->
  CS = 32*sqrt(2)*1.65*0.100/0.310 - 1 = 24,09
  CS = 24
*/

uint16_t TMC2240Stepper::cs2rms(uint8_t CS) {
	float IFS_current_RMS	= calc_IFS_current_RMS();
	uint32_t globalscaler	= GLOBAL_SCALER();
	return (float)(CS+0.5)*(globalscaler * IFS_current_RMS)/256/32*1000;
}


float TMC2240Stepper::calc_IFS_current_RMS() {
	uint32_t Kifs_values[] = {11750,24000,36000,36000};
	uint32_t Kifs = Kifs_values[DRV_CONF_register.current_range];
	return ((float)Kifs /Rref) /1.414;
}

uint32_t TMC2240Stepper::set_globalscaler(float current, float IFS_current_RMS) {
	uint32_t globalscaler = ((current * 256) / IFS_current_RMS) + 0.5;

	if (globalscaler < 32) globalscaler = 32;
	if (globalscaler >= 256) globalscaler = 0;
	GLOBAL_SCALER(globalscaler);
	return globalscaler;
}

void TMC2240Stepper::rms_current(uint16_t mA) {
	float IFS_current_RMS	= calc_IFS_current_RMS();
	float mA_float = (float)mA / 1000;
	uint32_t globalscaler	= set_globalscaler(mA_float, IFS_current_RMS);
	int32_t CS = mA_float * globalscaler/256.0 * IFS_current_RMS * 32 - 1 + 0.5;
	if (CS > 31) CS = 31;
	if (CS < 0) CS = 0;
	irun(CS);
	ihold(CS*holdMultiplier);
}

void TMC2240Stepper::rms_current(uint16_t mA, float mult) {
	holdMultiplier = mult;
	rms_current(mA);
}

uint16_t TMC2240Stepper::rms_current() {
	return cs2rms(irun());
}

void TMC2240Stepper::microsteps(uint16_t ms) {
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

uint16_t TMC2240Stepper::microsteps() {
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

// R+C: GSTAT
uint8_t TMC2240Stepper::GSTAT()			{ return read(TMC2240_n::GSTAT_t::address); }
void  TMC2240Stepper::GSTAT(uint8_t)	{ write(TMC2240_n::GSTAT_t::address, 0b111); }
bool  TMC2240Stepper::reset()			{ TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.reset; }
bool  TMC2240Stepper::drv_err()			{ TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.drv_err; }
bool  TMC2240Stepper::uv_cp()			{ TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.uv_cp; }
bool  TMC2240Stepper::register_reset()	{ TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.register_reset; }
bool  TMC2240Stepper::vm_uvlo()			{ TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.vm_uvlo; }


uint8_t TMC2240Stepper::test_connection() {
  	uint32_t drv_status = DRV_STATUS();
  	switch (drv_status) {
		case 0xFFFFFFFF: return 1;
		case 0: return 2;
		default: return 0;
	}
}

// W: TPOWERDOWN
uint8_t TMC2240Stepper::TPOWERDOWN() { return TPOWERDOWN_register.sr; }
void TMC2240Stepper::TPOWERDOWN(uint8_t input) {
	TPOWERDOWN_register.sr = input;
	write(TPOWERDOWN_register.address, TPOWERDOWN_register.sr);
}

// W: TPWMTHRS
uint32_t TMC2240Stepper::TPWMTHRS() { return TPWMTHRS_register.sr; }
void TMC2240Stepper::TPWMTHRS(uint32_t input) {
  TPWMTHRS_register.sr = input;
  write(TPWMTHRS_register.address, TPWMTHRS_register.sr);
}

void TMC2240Stepper::hysteresis_end(int8_t value) { hend(value+3); }
int8_t TMC2240Stepper::hysteresis_end() { return hend() - 3; };

void TMC2240Stepper::hysteresis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMC2240Stepper::hysteresis_start() { return hstrt() + 1; }

// W: TCOOLTHRS
uint32_t TMC2240Stepper::TCOOLTHRS() { return TCOOLTHRS_register.sr; }
void TMC2240Stepper::TCOOLTHRS(uint32_t input) {
	TCOOLTHRS_register.sr = input;
	write(TCOOLTHRS_register.address, TCOOLTHRS_register.sr);
}
///////////////////////////////////////////////////////////////////////////////////////
// W: THIGH
uint32_t TMC2240Stepper::THIGH() { return THIGH_register.sr; }
void TMC2240Stepper::THIGH(uint32_t input) {
	THIGH_register.sr = input;
	write(THIGH_register.address, THIGH_register.sr);
}
