#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2300_n;

TMC2300Stepper::TMC2300Stepper(HardwareSerial &SerialPort, float RS, uint8_t addr) :
	TMC_UART(&SerialPort, addr),
	TMC_RMS(RS)
	{
		resetLibCache();
	}

#if SW_CAPABLE_PLATFORM
	TMC2300Stepper::TMC2300Stepper(SoftwareSerial &SWSerial, float RS, uint8_t addr) :
		TMC_UART(&SWSerial, addr),
		TMC_RMS(RS)
		{
			resetLibCache();
		}
#endif

void TMC2300Stepper::begin() {
	#if SW_CAPABLE_PLATFORM
		beginSerial(115200);
	#endif
}

void TMC2300Stepper::defaults() {
	GCONF(1 << 6);
	GSTAT(0);
	SLAVECONF(0);
	IHOLD_IRUN((8) | (31<<8) | (1ul<<16));
	TPOWERDOWN(20);
	VACTUAL(0);
	TCOOLTHRS(0);
	SGTHRS(0);
	COOLCONF(0);
	CHOPCONF(0x13008001u);
	PWMCONF(0xC40D1024u);
}

void TMC2300Stepper::resetLibCache() {
	SLAVECONF_i::r.sr = 0;
	IHOLD_IRUN_i::r.sr = (8) | (31<<8) | (1ul<<16);
	TPOWERDOWN_i::r.sr = 20;
	VACTUAL_i::r.sr = 0;
	TCOOLTHRS_i::r.sr = 0;
	SGTHRS_i::r.sr = 0;
	COOLCONF_i::r.sr = 0;
}

void TMC2300Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
}
