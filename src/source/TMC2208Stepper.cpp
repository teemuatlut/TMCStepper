#include "TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC2208_n;

// Protected
// addr needed for TMC2209
TMC2208Stepper::TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr) :
	TMC_UART(SerialPort, addr),
	TMCStepper(RS)
	{
		HWSerial = SerialPort;
	}

TMC2208Stepper::TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr, PinDef mul_pin1, PinDef mul_pin2) :
	TMC2208Stepper(SerialPort, RS)
	{
		SSwitch *SMulObj = new SSwitch(mul_pin1, mul_pin2, addr);
		sswitch = SMulObj;
	}

#if SW_CAPABLE_PLATFORM
	// Protected
	// addr needed for TMC2209
	TMC2208Stepper::TMC2208Stepper(PinDef SW_RX_pin, PinDef SW_TX_pin, float RS, uint8_t addr) :
		TMC_UART(SW_RX_pin, SW_TX_pin, addr),
		TMCStepper(RS)
		{}

	void TMC2208Stepper::beginSerial(uint32_t baudrate) {
		if (SWSerial != nullptr)
		{
			SWSerial->begin(baudrate);
			SWSerial->end();
		}
		#if defined(ARDUINO_ARCH_AVR)
			if (RXTX_pin > 0) {
				digitalWrite(RXTX_pin, HIGH);
				pinMode(RXTX_pin, OUTPUT);
			}
		#endif
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
