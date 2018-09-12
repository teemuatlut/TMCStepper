#include "TMCStepper.h"
#include "TMC_DECL.h"

TT TMC2208StepperBase<T>::TMC2208StepperBase(Stream * SerialPort, float RS, bool has_rx) :
	TMCStepper<T>(RS),
	write_only(!has_rx)
	{ HWSerial = SerialPort; }

#if SW_CAPABLE_PLATFORM
	TT TMC2208StepperBase<T>::TMC2208StepperBase(uint16_t SW_RX_pin, uint16_t SW_TX_pin, float RS, bool has_rx) :
		TMCStepper<T>(RS),
		write_only(!has_rx)
		{
			SoftwareSerial *SWSerialObj = new SoftwareSerial(SW_RX_pin, SW_TX_pin);
			SWSerial = SWSerialObj;
		}

	TT void TMC2208StepperBase<T>::beginSerial(uint32_t baudrate) {
		if (SWSerial != NULL) SWSerial->begin(baudrate);
	}
#endif

TT void TMC2208StepperBase<T>::push() {
	this->GCONF(REG(GCONF).sr);
	this->IHOLD_IRUN(REG(IHOLD_IRUN).sr);
	this->SLAVECONF(REG(SLAVECONF).sr);
	this->FACTORY_CONF(REG(FACTORY_CONF).sr);
	this->TPOWERDOWN(REG(TPOWERDOWN).sr);
	this->TPWMTHRS(REG(TPWMTHRS).sr);
	this->VACTUAL(REG(VACTUAL).sr);
	this->CHOPCONF(REG(CHOPCONF).sr);
	this->PWMCONF(REG(PWMCONF).sr);
}

TT bool TMC2208StepperBase<T>::isEnabled() { return !enn() && toff(); }

TT uint8_t TMC2208StepperBase<T>::calcCRC(uint8_t datagram[], uint8_t len) {
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

TT void TMC2208StepperBase<T>::write(uint8_t addr, uint32_t regVal) {
	uint8_t len = 7;
	addr |= this->TMC_WRITE;
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

TT uint64_t _sendDatagram(T &serPtr, uint8_t datagram[], uint8_t len, uint16_t replyDelay) {
	uint64_t out = 0x00000000UL;

	while (serPtr.available() > 0) serPtr.read(); // Flush

	for(int i=0; i<=len; i++) serPtr.write(datagram[i]);
	for(int byte=0; byte<4; byte++) serPtr.read(); // Flush bytes written
	delay(replyDelay);

	while(serPtr.available() > 0) {
		uint8_t res = serPtr.read();
		out <<= 8;
		out |= res&0xFF;
	}
	return out;
}

TT uint32_t TMC2208StepperBase<T>::read(uint8_t addr) {
	uint8_t len = 3;
	addr |= this->TMC_READ;
	uint8_t datagram[] = {TMC2208_SYNC, TMC2208_SLAVE_ADDR, addr, 0x00};
	datagram[len] = calcCRC(datagram, len);
	uint64_t out = 0x00000000UL;

	#if SW_CAPABLE_PLATFORM
		if (SWSerial != NULL) {
				SWSerial->listen();
				out = _sendDatagram(*SWSerial, datagram, len, replyDelay);
		} else
	#endif
		{
			out = _sendDatagram(*HWSerial, datagram, len, replyDelay);
		}

	uint8_t out_datagram[] = {(uint8_t)(out>>56), (uint8_t)(out>>48), (uint8_t)(out>>40), (uint8_t)(out>>32), (uint8_t)(out>>24), (uint8_t)(out>>16), (uint8_t)(out>>8), (uint8_t)(out>>0)};
	if (calcCRC(out_datagram, 7) == (uint8_t)(out&0xFF)) {
		CRCerror = false;
	} else {
		CRCerror = true;
	}
	return out>>8;
}

TT uint8_t TMC2208StepperBase<T>::IFCNT() {
	return SELF.read(ADR(IFCNT));
}

TT void TMC2208StepperBase<T>::SLAVECONF(uint16_t input) {
	REG(SLAVECONF).sr = input&0xF00;
	SELF.write(ADR(SLAVECONF), REG(SLAVECONF).sr);
}
TT uint16_t TMC2208StepperBase<T>::SLAVECONF() {
	return REG(SLAVECONF).sr;
}
TT void TMC2208StepperBase<T>::senddelay(uint8_t B) 	{ REG(SLAVECONF).senddelay = B; SELF.write(ADR(SLAVECONF), REG(SLAVECONF).sr); }
TT uint8_t TMC2208StepperBase<T>::senddelay() 		{ return REG(SLAVECONF).senddelay; }

TT void TMC2208StepperBase<T>::OTP_PROG(uint16_t input) {
	SELF.write(ADR(OTP_PROG), input);
}

TT uint32_t TMC2208StepperBase<T>::OTP_READ() {
	return read(ADR(OTP_READ));
}

TT uint32_t TMC2208StepperBase<T>::IOIN() {
	REG(IOIN).sr = read(ADR(IOIN));
	return REG(IOIN).sr;
}
TT bool TMC2208StepperBase<T>::enn()			{ IOIN(); return REG(IOIN).enn;		}
TT bool TMC2208StepperBase<T>::ms1()			{ IOIN(); return REG(IOIN).ms1;		}
TT bool TMC2208StepperBase<T>::ms2()			{ IOIN(); return REG(IOIN).ms2;		}
TT bool TMC2208StepperBase<T>::diag()			{ IOIN(); return REG(IOIN).diag;	}
TT bool TMC2208StepperBase<T>::pdn_uart()		{ IOIN(); return REG(IOIN).pdn_uart;}
TT bool TMC2208StepperBase<T>::step()			{ IOIN(); return REG(IOIN).step;	}
TT bool TMC2208StepperBase<T>::sel_a()			{ IOIN(); return REG(IOIN).sel_a;	}
TT bool TMC2208StepperBase<T>::dir()			{ IOIN(); return REG(IOIN).dir;		}
TT uint8_t TMC2208StepperBase<T>::version() 	{ IOIN(); return REG(IOIN).version;	}

uint32_t TMC2224Stepper::IOIN() {
	REG(IOIN).sr = read(ADR(IOIN));
	return REG(IOIN).sr;
}
bool TMC2224Stepper::enn()			{ IOIN(); return REG(IOIN).enn;		}
bool TMC2224Stepper::ms1()			{ IOIN(); return REG(IOIN).ms1;		}
bool TMC2224Stepper::ms2()			{ IOIN(); return REG(IOIN).ms2;		}
bool TMC2224Stepper::pdn_uart()		{ IOIN(); return REG(IOIN).pdn_uart;}
bool TMC2224Stepper::spread()		{ IOIN(); return REG(IOIN).spread;	}
bool TMC2224Stepper::step()			{ IOIN(); return REG(IOIN).step;	}
bool TMC2224Stepper::sel_a()		{ IOIN(); return REG(IOIN).sel_a;	}
bool TMC2224Stepper::dir()			{ IOIN(); return REG(IOIN).dir;		}
uint8_t TMC2224Stepper::version() 	{ IOIN(); return REG(IOIN).version;	}

TT uint16_t TMC2208StepperBase<T>::FACTORY_CONF() {
	if (write_only) return REG(FACTORY_CONF).sr;
	REG(FACTORY_CONF).sr = read(ADR(FACTORY_CONF));
	return REG(FACTORY_CONF).sr;
}
TT void TMC2208StepperBase<T>::FACTORY_CONF(uint16_t input) {
	REG(FACTORY_CONF).sr = input;
	SELF.write(ADR(FACTORY_CONF), REG(FACTORY_CONF).sr);
}
TT void TMC2208StepperBase<T>::fclktrim(uint8_t B){ REG(FACTORY_CONF).fclktrim = B; SELF.write(ADR(FACTORY_CONF), REG(FACTORY_CONF).sr); }
TT void TMC2208StepperBase<T>::ottrim(uint8_t B)	{ REG(FACTORY_CONF).ottrim = B; SELF.write(ADR(FACTORY_CONF), REG(FACTORY_CONF).sr); }
TT uint8_t TMC2208StepperBase<T>::fclktrim()		{ SELF.read(ADR(FACTORY_CONF)); return REG(FACTORY_CONF).fclktrim; }
TT uint8_t TMC2208StepperBase<T>::ottrim()		{ SELF.read(ADR(FACTORY_CONF)); return REG(FACTORY_CONF).ottrim; }

TT void TMC2208StepperBase<T>::VACTUAL(uint32_t input) {
	REG(VACTUAL).sr = input;
	SELF.write(ADR(VACTUAL), REG(VACTUAL).sr);
}
TT uint32_t TMC2208StepperBase<T>::VACTUAL() {
	return REG(VACTUAL).sr;
}

TT uint32_t TMC2208StepperBase<T>::PWM_SCALE() {
	REG(PWM_SCALE).sr = SELF.read(ADR(PWM_SCALE));
	return REG(PWM_SCALE).sr;
}
TT uint8_t TMC2208StepperBase<T>::pwm_scale_sum() { PWM_SCALE(); return REG(PWM_SCALE).pwm_scale_sum; }
TT int16_t TMC2208StepperBase<T>::pwm_scale_auto() {
	PWM_SCALE();
	return REG(PWM_SCALE).pwm_scale_auto;
	// Not two's complement? 9nth bit determines sign
	/*
	uint32_t d = PWM_SCALE();
	int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
	if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
	else return response;
	*/
}
