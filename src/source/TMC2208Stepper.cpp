#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC2208Stepper::TMC2208Stepper(Stream * SerialPort, float RS, bool has_rx) :
	TMCStepper(RS),
	write_only(!has_rx)
	{ HWSerial = SerialPort; }

#if SW_CAPABLE_PLATFORM
	TMC2208Stepper::TMC2208Stepper(uint16_t SW_RX_pin, uint16_t SW_TX_pin, float RS, bool has_rx) :
		TMCStepper(RS),
		write_only(!has_rx)
		{
			SoftwareSerial *SWSerialObj = new SoftwareSerial(SW_RX_pin, SW_TX_pin);
			SWSerial = SWSerialObj;
		}

	void TMC2208Stepper::beginSerial(uint32_t baudrate) {
		if (SWSerial != NULL) SWSerial->begin(baudrate);
	}
#endif

void TMC2208Stepper::begin() {
	#if SW_CAPABLE_PLATFORM
		beginSerial(115200);
	#endif
}

void TMC2208Stepper::push() {
	GCONF(GCONF_register.sr);
	IHOLD_IRUN(IHOLD_IRUN_register.sr);
	SLAVECONF(SLAVECONF_register.sr);
	FACTORY_CONF(FACTORY_CONF_register.sr);
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

void TMC2208Stepper::write(uint8_t addr, uint32_t regVal) {
	uint8_t len = 7;
	addr |= TMC_WRITE;
	uint8_t datagram[] = {TMC2208_SYNC, TMC2208_SLAVE_ADDR, addr, (uint8_t)(regVal>>24), (uint8_t)(regVal>>16), (uint8_t)(regVal>>8), (uint8_t)(regVal>>0), 0x00};

	datagram[len] = calcCRC(datagram, len);

	#if SW_CAPABLE_PLATFORM
		if (SWSerial != NULL) {
				for(int i=0; i<=len; i++){
					bytesWritten += SWSerial->write(datagram[i]);
				}
		} else
	#endif
		{
			for(int i=0; i<=len; i++){
				bytesWritten += HWSerial->write(datagram[i]);
		}
	}
	delay(replyDelay);
}

template<typename SERIAL_TYPE>
uint64_t _sendDatagram(SERIAL_TYPE &serPtr, uint8_t datagram[], const uint8_t len, uint16_t timeout) {
	while (serPtr.available() > 0) serPtr.read(); // Flush
	for(int i=0; i<=len; i++) serPtr.write(datagram[i]);
	delay(TMC2208Stepper::replyDelay);

	// scan for the rx frame and read it
	uint32_t ms = millis();
	uint32_t sync_target = ((uint32_t)datagram[0]<<16) | 0xFF00 | datagram[2];
	uint32_t sync = 0;

	do {
		uint32_t ms2 = millis();
		if (ms2 != ms) {
			// 1ms tick
			ms = ms2;
			timeout--;
		}
		if (!timeout) return 0;

		int16_t res = serPtr.read();
		if (res < 0) continue;

		sync <<= 8;
		sync |= res & 0xFF;
		sync &= 0xFFFFFF;

	} while (sync != sync_target);

	uint64_t out = sync;
	ms = millis();
	timeout = TMC2208Stepper::abort_window;

	for(uint8_t i=0; i<5;) {
		uint32_t ms2 = millis();
		if (ms2 != ms) {
			// 1ms tick
			ms = ms2;
			timeout--;
		}
		if (!timeout) return 0;

		int16_t res = serPtr.read();
		if (res < 0) continue;

		out <<= 8;
		out |= res & 0xFF;

		i++;
	}

	while (serPtr.available() > 0) serPtr.read(); // Flush
	return out;
}

uint32_t TMC2208Stepper::read(uint8_t addr) {
	constexpr uint8_t len = 3;
	addr |= TMC_READ;
	uint8_t datagram[] = {TMC2208_SYNC, TMC2208_SLAVE_ADDR, addr, 0x00};
	datagram[len] = calcCRC(datagram, len);
	uint64_t out = 0x00000000UL;

	for (uint8_t i = 0; i < max_retries; i++) {
		#if SW_CAPABLE_PLATFORM
			if (SWSerial != NULL) {
					SWSerial->listen();
					out = _sendDatagram(*SWSerial, datagram, len, abort_window);
					SWSerial->stopListening();
			} else
		#endif
			{
				out = _sendDatagram(*HWSerial, datagram, len, abort_window);
			}

		delay(replyDelay);

		CRCerror = false;
		uint8_t out_datagram[] = {(uint8_t)(out>>56), (uint8_t)(out>>48), (uint8_t)(out>>40), (uint8_t)(out>>32), (uint8_t)(out>>24), (uint8_t)(out>>16), (uint8_t)(out>>8), (uint8_t)(out>>0)};
		uint8_t crc = calcCRC(out_datagram, 7);
		if ((crc != (uint8_t)out) || crc == 0 ) {
			CRCerror = true;
			out = 0;
		} else {
			break;
		}
	}

	return out>>8;
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
	IOIN_register.sr = read(IOIN_register.address);
	return IOIN_register.sr;
}
bool TMC2208Stepper::enn()			{ IOIN(); return IOIN_register.enn;		}
bool TMC2208Stepper::ms1()			{ IOIN(); return IOIN_register.ms1;		}
bool TMC2208Stepper::ms2()			{ IOIN(); return IOIN_register.ms2;		}
bool TMC2208Stepper::diag()			{ IOIN(); return IOIN_register.diag;	}
bool TMC2208Stepper::pdn_uart()		{ IOIN(); return IOIN_register.pdn_uart;}
bool TMC2208Stepper::step()			{ IOIN(); return IOIN_register.step;	}
bool TMC2208Stepper::sel_a()		{ IOIN(); return IOIN_register.sel_a;	}
bool TMC2208Stepper::dir()			{ IOIN(); return IOIN_register.dir;		}
uint8_t TMC2208Stepper::version() 	{ IOIN(); return IOIN_register.version;	}

uint32_t TMC2224Stepper::IOIN() {
	IOIN_register.sr = read(IOIN_register.address);
	return IOIN_register.sr;
}
bool TMC2224Stepper::enn()			{ IOIN(); return IOIN_register.enn;		}
bool TMC2224Stepper::ms1()			{ IOIN(); return IOIN_register.ms1;		}
bool TMC2224Stepper::ms2()			{ IOIN(); return IOIN_register.ms2;		}
bool TMC2224Stepper::pdn_uart()		{ IOIN(); return IOIN_register.pdn_uart;}
bool TMC2224Stepper::spread()		{ IOIN(); return IOIN_register.spread;	}
bool TMC2224Stepper::step()			{ IOIN(); return IOIN_register.step;	}
bool TMC2224Stepper::sel_a()		{ IOIN(); return IOIN_register.sel_a;	}
bool TMC2224Stepper::dir()			{ IOIN(); return IOIN_register.dir;		}
uint8_t TMC2224Stepper::version() 	{ IOIN(); return IOIN_register.version;	}

uint16_t TMC2208Stepper::FACTORY_CONF() {
	if (write_only) return FACTORY_CONF_register.sr;
	FACTORY_CONF_register.sr = read(FACTORY_CONF_register.address);
	return FACTORY_CONF_register.sr;
}
void TMC2208Stepper::FACTORY_CONF(uint16_t input) {
	FACTORY_CONF_register.sr = input;
	write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr);
}
void TMC2208Stepper::fclktrim(uint8_t B){ FACTORY_CONF_register.fclktrim = B; write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr); }
void TMC2208Stepper::ottrim(uint8_t B)	{ FACTORY_CONF_register.ottrim = B; write(FACTORY_CONF_register.address, FACTORY_CONF_register.sr); }
uint8_t TMC2208Stepper::fclktrim()		{ read(FACTORY_CONF_register.address); return FACTORY_CONF_register.fclktrim; }
uint8_t TMC2208Stepper::ottrim()		{ read(FACTORY_CONF_register.address); return FACTORY_CONF_register.ottrim; }

void TMC2208Stepper::VACTUAL(uint32_t input) {
	VACTUAL_register.sr = input;
	write(VACTUAL_register.address, VACTUAL_register.sr);
}
uint32_t TMC2208Stepper::VACTUAL() {
	return VACTUAL_register.sr;
}

uint32_t TMC2208Stepper::PWM_SCALE() {
	PWM_SCALE_register.sr = read(PWM_SCALE_register.address);
	return PWM_SCALE_register.sr;
}
uint8_t TMC2208Stepper::pwm_scale_sum() { PWM_SCALE(); return PWM_SCALE_register.pwm_scale_sum; }
int16_t TMC2208Stepper::pwm_scale_auto() {
	PWM_SCALE();
	return PWM_SCALE_register.pwm_scale_auto;
	// Not two's complement? 9nth bit determines sign
	/*
	uint32_t d = PWM_SCALE();
	int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
	if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
	else return response;
	*/
}
