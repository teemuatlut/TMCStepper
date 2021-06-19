#include "../TMCStepper.h"

TMC2209Stepper::TMC2209Stepper(HardwareSerial &SerialPort, float RS, uint8_t addr) :
	TMC_UART(&SerialPort, addr),
	TMC_RMS(RS)
	{
		resetLibCache();
	}

#if SW_CAPABLE_PLATFORM
	TMC2209Stepper::TMC2209Stepper(SoftwareSerial &SWSerial, float RS, uint8_t addr) :
		TMC_UART(&SWSerial, addr),
		TMC_RMS(RS)
		{
			resetLibCache();
		}
#endif

void TMC2209Stepper::begin(const uint32_t baud) {
	#if SW_CAPABLE_PLATFORM
		beginSerial(baud);
	#endif
	pdn_disable(true);
	mstep_reg_select(true);
}

void TMC2209Stepper::defaults() {
	GCONF(1 | (1<<8));
	SLAVECONF(0);
	OTP_PROG(0);
	FACTORY_CONF(0);
	IHOLD_IRUN(31 << 8);
	TPOWERDOWN(20);
	TPWMTHRS(0);
	TCOOLTHRS(0);
	VACTUAL(0);
	SGTHRS(0);
	COOLCONF(0);
	CHOPCONF(0x10000053u);
	PWMCONF(0xC10D0024u);
}

void TMC2209Stepper::resetLibCache() {
	SLAVECONF_i::r.sr = 0;
	IHOLD_IRUN_i::r.sr = 31 << 8;
	TPOWERDOWN_i::r.sr = 20;
	TPWMTHRS_i::r.sr = 0;
	TCOOLTHRS_i::r.sr = 0;
	VACTUAL_i::r.sr = 0;
	SGTHRS_i::r.sr = 0;
	COOLCONF_i::r.sr = 0;
}

void TMC2209Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	TPWMTHRS(TPWMTHRS_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
	SGTHRS(SGTHRS_i::r.sr);
	COOLCONF(COOLCONF_i::r.sr);
}
