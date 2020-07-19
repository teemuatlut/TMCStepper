#include "TMCStepper.h"
#include "SERIAL_SWITCH.h"

using namespace TMCStepper_n;

// Protected
// addr needed for TMC2209
TMC2208Stepper::TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr) :
	TMCStepper(RS),
	slaveAddress(addr)
	{
		HWSerial = SerialPort;
		defaults();
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
		TMCStepper(RS),
		RXTX_pin(SW_RX_pin == SW_TX_pin ? SW_RX_pin : 0),
		slaveAddress(addr)
		{
			SoftwareSerial *SWSerialObj = new SoftwareSerial(SW_RX_pin, SW_TX_pin);
			SWSerial = SWSerialObj;
			defaults();
		}

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
	GCONF_register.i_scale_analog = 1;
	GCONF_register.internal_rsense = 0; // OTP
	GCONF_register.en_spreadcycle = 0; // OTP
	GCONF_register.multistep_filt = 1; // OTP
	IHOLD_IRUN_register.iholddelay = 1; // OTP
	TPOWERDOWN_register.sr = 20;
	CHOPCONF_register.sr = 0x10000053;
	PWMCONF_register.sr = 0xC10D0024;
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
	GCONF(GCONF_register.sr);
	IHOLD_IRUN(IHOLD_IRUN_register.sr);
	SLAVECONF(SLAVECONF_register.sr);
	TPOWERDOWN(TPOWERDOWN_register.sr);
	TPWMTHRS(TPWMTHRS_register.sr);
	VACTUAL(VACTUAL_register.sr);
	CHOPCONF(CHOPCONF_register.sr);
	PWMCONF(PWMCONF_register.sr);
}

bool TMC2208Stepper::isEnabled() { return !enn() && toff(); }

uint8_t TMC2208Stepper::calcCRC(uint8_t datagram[], uint8_t len) {
	uint8_t crc = 0;
	for (uint8_t i = 0; i < len; i++) {
		uint8_t currentByte = datagram[i];
		for (uint8_t j = 0; j < 8; j++) {
			if ((crc >> 7) ^ (currentByte & 0x01)) {
				crc = (crc << 1) ^ 0x07;
			} else {
				crc = (crc << 1);
			}
			crc &= 0xff;
			currentByte = currentByte >> 1;
		}
	}
	return crc;
}

__attribute__((weak))
void TMC2208Stepper::write(uint8_t addr, uint32_t regVal) {
    WriteDatagram datagram;
    datagram.driverAddress = slaveAddress;
    datagram.registerAddress = addr | TMC_WRITE;
    datagram.data = regVal;

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);

	preWriteCommunication();
	serial_write((uint8_t*)&datagram, datagram.length);
	postWriteCommunication();

	delay(replyDelay);
}

TMC2208Stepper::ReadResponse TMC2208Stepper::sendReadRequest(ReadRequest &datagram) {
    serial_write((uint8_t*)&datagram, datagram.length);

    //delay(this->replyDelay);
    const uint32_t timeout = this->getTime() + this->abort_window;

    // scan for the rx frame and read it
    const uint32_t sync_target = static_cast<uint32_t>(datagram.sync)<<16 | 0xFF00 | datagram.registerAddress;
    uint32_t sync = 0;

    do {
        sync <<= 8;
        serial_read((uint8_t*)&sync, 1);

        if (this->getTime() > timeout) {
            return ReadResponse{};
        }
    } while (sync != sync_target);

    ReadResponse response;
    response.driverAddress = 0xFF;
    response.registerAddress = static_cast<uint8_t>(sync);

    serial_read((uint8_t*)&response.data, 5);

    return response;
}

uint32_t TMC2208Stepper::read(uint8_t addr) {
    ReadResponse response;
    ReadRequest datagram;
    datagram.driverAddress = slaveAddress;
    datagram.registerAddress = addr | TMC_READ;

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);
    CRCerror = true;

    for (uint8_t i = 0; i < max_retries; i++) {
        preReadCommunication();
        response = sendReadRequest(datagram);
        postReadCommunication();

        uint8_t crc = calcCRC((uint8_t*)&response, response.length);

        if (crc == response.crc || crc != 0) {
            CRCerror = false;
            break;
        }

        response.data = 0;
    }

    return response.data;
}

uint8_t TMC2208Stepper::IFCNT() {
	return read(IFCNT_t::address);
}

void TMC2208Stepper::SLAVECONF(uint16_t input) {
	SLAVECONF_register.sr = input&0xF00;
	write(SLAVECONF_register.address, SLAVECONF_register.sr);
}
uint16_t TMC2208Stepper::SLAVECONF() {
	return SLAVECONF_register.sr;
}
void TMC2208Stepper::senddelay(uint8_t B) 	{ SLAVECONF_register.senddelay = B; write(SLAVECONF_register.address, SLAVECONF_register.sr); }
uint8_t TMC2208Stepper::senddelay() 		{ return SLAVECONF_register.senddelay; }

void TMC2208Stepper::OTP_PROG(uint16_t input) {
	write(OTP_PROG_t::address, input);
}

uint32_t TMC2208Stepper::OTP_READ() {
	return read(OTP_READ_t::address);
}

uint32_t TMC2208Stepper::IOIN() {
	return read(TMC2208_n::IOIN_t::address);
}
bool TMC2208Stepper::enn()			{ return TMC2208_n::IOIN_t{ IOIN() }.enn;		}
bool TMC2208Stepper::ms1()			{ return TMC2208_n::IOIN_t{ IOIN() }.ms1;		}
bool TMC2208Stepper::ms2()			{ return TMC2208_n::IOIN_t{ IOIN() }.ms2;		}
bool TMC2208Stepper::diag()			{ return TMC2208_n::IOIN_t{ IOIN() }.diag;		}
bool TMC2208Stepper::pdn_uart()		{ return TMC2208_n::IOIN_t{ IOIN() }.pdn_uart;	}
bool TMC2208Stepper::step()			{ return TMC2208_n::IOIN_t{ IOIN() }.step;		}
bool TMC2208Stepper::sel_a()		{ return TMC2208_n::IOIN_t{ IOIN() }.sel_a;		}
bool TMC2208Stepper::dir()			{ return TMC2208_n::IOIN_t{ IOIN() }.dir;		}
uint8_t TMC2208Stepper::version() 	{ return TMC2208_n::IOIN_t{ IOIN() }.version;	}

uint32_t TMC2224Stepper::IOIN() {
	return read(TMC2224_n::IOIN_t::address);
}
bool TMC2224Stepper::enn()			{ return TMC2224_n::IOIN_t{ IOIN() }.enn;		}
bool TMC2224Stepper::ms1()			{ return TMC2224_n::IOIN_t{ IOIN() }.ms1;		}
bool TMC2224Stepper::ms2()			{ return TMC2224_n::IOIN_t{ IOIN() }.ms2;		}
bool TMC2224Stepper::pdn_uart()		{ return TMC2224_n::IOIN_t{ IOIN() }.pdn_uart;	}
bool TMC2224Stepper::spread()		{ return TMC2224_n::IOIN_t{ IOIN() }.spread;	}
bool TMC2224Stepper::step()			{ return TMC2224_n::IOIN_t{ IOIN() }.step;		}
bool TMC2224Stepper::sel_a()		{ return TMC2224_n::IOIN_t{ IOIN() }.sel_a;		}
bool TMC2224Stepper::dir()			{ return TMC2224_n::IOIN_t{ IOIN() }.dir;		}
uint8_t TMC2224Stepper::version() 	{ return TMC2224_n::IOIN_t{ IOIN() }.version;	}

uint16_t TMC2208Stepper::FACTORY_CONF() {
	return read(FACTORY_CONF_register.address);
}
void TMC2208Stepper::FACTORY_CONF(uint16_t input) {
	FACTORY_CONF_register.sr = input;
	write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr);
}
void TMC2208Stepper::fclktrim(uint8_t B){ FACTORY_CONF_register.fclktrim = B; write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr); }
void TMC2208Stepper::ottrim(uint8_t B)	{ FACTORY_CONF_register.ottrim = B; write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr); }
uint8_t TMC2208Stepper::fclktrim()		{ return FACTORY_CONF_t{ FACTORY_CONF() }.fclktrim; }
uint8_t TMC2208Stepper::ottrim()		{ return FACTORY_CONF_t{ FACTORY_CONF() }.ottrim; }

void TMC2208Stepper::VACTUAL(uint32_t input) {
	VACTUAL_register.sr = input;
	write(VACTUAL_register.address, VACTUAL_register.sr);
}
uint32_t TMC2208Stepper::VACTUAL() {
	return VACTUAL_register.sr;
}

uint32_t TMC2208Stepper::PWM_SCALE() {
	return read(TMC2208_n::PWM_SCALE_t::address);
}
uint8_t TMC2208Stepper::pwm_scale_sum() {
	TMC2208_n::PWM_SCALE_t r{0};
	r.sr = PWM_SCALE();
	return r.pwm_scale_sum;
}

int16_t TMC2208Stepper::pwm_scale_auto() {
	TMC2208_n::PWM_SCALE_t r{0};
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
uint32_t TMC2208Stepper::PWM_AUTO() {
	return read(PWM_AUTO_t::address);
}
uint8_t TMC2208Stepper::pwm_ofs_auto()  { return PWM_AUTO_t{ PWM_AUTO() }.pwm_ofs_auto; }
uint8_t TMC2208Stepper::pwm_grad_auto() { return PWM_AUTO_t{ PWM_AUTO() }.pwm_grad_auto; }
