#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2208_n;

TMC2208Stepper::TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr, TMCStepper_n::SSwitch *sswitch) :
	TMC_UART(SerialPort, addr),
	TMCStepper(RS)
	{
		HWSerial = SerialPort;
		resetLibCache();
	}

#if SW_CAPABLE_PLATFORM
	// Protected
	// addr needed for TMC2209
	TMC2208Stepper::TMC2208Stepper(SoftwareSerial *ser, float RS) :
		TMC_UART(SWSerial, TMC2208_SLAVE_ADDR),
		TMCStepper(RS)
		{
			resetLibCache();
		}
#endif

void TMC2208Stepper::begin() {
	#if SW_CAPABLE_PLATFORM
		beginSerial(115200);
	#endif
	pdn_disable(true);
	mstep_reg_select(true);

}

void TMC2208Stepper::defaults() {
	GCONF_t gconf{0};
	gconf.i_scale_analog = 1;
	gconf.internal_rsense = 0; // OTP
	gconf.en_spreadcycle = 0; // OTP
	gconf.multistep_filt = 1; // OTP
	GCONF(gconf.sr);

	IHOLD_IRUN_i::r.iholddelay = 1; // OTP
	TPOWERDOWN_i::r.sr = 20;
	CHOPCONF(0x10000053);
	PWMCONF(0xC10D0024);
  //MSLUT0_register.sr = ???;
  //MSLUT1_register.sr = ???;
  //MSLUT2_register.sr = ???;
  //MSLUT3_register.sr = ???;
  //MSLUT4_register.sr = ???;
  //MSLUT5_register.sr = ???;
  //MSLUT6_register.sr = ???;
  //MSLUT7_register.sr = ???;
  //MSLUTSTART_register.start_sin90 = 247;
}

void TMC2208Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	TPWMTHRS(TPWMTHRS_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
}

bool TMC2208Stepper::isEnabled() { return !enn() && toff(); }
