#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2300_n;

TMC2300Stepper::TMC2300Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr) :
	TMC_UART(SerialPort, addr),
	TMCStepper(RS)
	{
		resetLibCache();
	}

#if SW_CAPABLE_PLATFORM
	TMC2300Stepper::TMC2300Stepper(SoftwareSerial *SWSerial, float RS, uint8_t addr) :
		TMC_UART(SWSerial, addr),
		TMCStepper(RS)
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
	GCONF_t gconf{0};
	gconf.multistep_filt = 1; // OTP
	GCONF(gconf.sr);

	IHOLD_IRUN(0x11F08);
	TPOWERDOWN(20);
	CHOPCONF(0x13008001);
	PWMCONF(0xC40D1024);
}

void TMC2300Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
}

bool TMC2300Stepper::isEnabled() { return !en() && enable_drv(); }
