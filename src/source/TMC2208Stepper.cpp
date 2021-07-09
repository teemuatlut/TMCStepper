#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2208_n;

TMC2208Stepper::TMC2208Stepper(HardwareSerial &SerialPort, float RS, uint8_t addr, TMC_HAL::SSwitch &sswitch) :
	TMC_UART(&SerialPort, addr),
	TMC_RMS(RS)
	{
		resetLibCache();
	}

TMC2208Stepper::TMC2208Stepper(HardwareSerial &SerialPort, float RS) :
	TMC_UART(&SerialPort, TMC2208_SLAVE_ADDR, nullptr),
	TMC_RMS(RS)
	{
		resetLibCache();
	}

#if SW_CAPABLE_PLATFORM
	// Protected
	// addr needed for TMC2209
	TMC2208Stepper::TMC2208Stepper(SoftwareSerial &ser, float RS) :
		TMC_UART(&ser, TMC2208_SLAVE_ADDR),
		TMC_RMS(RS)
		{
			resetLibCache();
		}
#endif

void TMC2208Stepper::begin(const uint32_t baudrate) {
	TMC_UART::begin(baudrate);
	pdn_disable(true);
	mstep_reg_select(true);
}

void TMC2208Stepper::defaults() {
	GCONF(1 | (1<<8));
	SLAVECONF(0);
	OTP_PROG(0);
	FACTORY_CONF(0);
	IHOLD_IRUN(31<<8);
	TPOWERDOWN(20);
	TPWMTHRS(0);
	VACTUAL(0);
	CHOPCONF(0x10000053u);
	PWMCONF(0xC10D0024u);
}

void TMC2208Stepper::resetLibCache() {
	SLAVECONF_i::r.sr = 0;
	IHOLD_IRUN_i::r.sr = 31<<8;
	TPOWERDOWN_i::r.sr = 20;
	TPWMTHRS_i::r.sr = 0;
	VACTUAL_i::r.sr = 0;
}

void TMC2208Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	TPWMTHRS(TPWMTHRS_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
}
