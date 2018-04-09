#include <Stream.h>
#include "TMCStepper.h"
#include <SoftwareSerial.h>
#include "TMC_MACROS.h"

TMC2208Stepper::TMC2208Stepper(Stream * SerialPort, float RS, bool has_rx) {
	this->Rsense = RS;
	write_only = !has_rx;
	uses_sw_serial = false;
	SerialObject = &SerialPort;
}

TMC2208Stepper::TMC2208Stepper(uint16_t SW_RX_pin, uint16_t SW_TX_pin, float RS, bool has_rx) {
	this->Rsense = RS;
	write_only = !has_rx;
	uses_sw_serial = true;
	static SoftwareSerial mySWSerial = SoftwareSerial(SW_RX_pin, SW_TX_pin);
	SerialObject = &mySWSerial;
}

void TMC2208Stepper::beginSerial(uint32_t baudrate) {
	if (uses_sw_serial) static_cast<SoftwareSerial*>(SerialObject)->begin(baudrate);
	else static_cast<HardwareSerial*>(SerialObject)->begin(baudrate);
}

void TMC2208Stepper::push() {
	GCONF(GCONF_register.cfg.sr);
	IHOLD_IRUN(IHOLD_IRUN_register.cfg.sr);
	SLAVECONF(SLAVECONF_register.cfg.sr);
	FACTORY_CONF(FACTORY_CONF_register.cfg.sr);
	TPOWERDOWN(TPOWERDOWN_register.sr);
	TPWMTHRS(TPWMTHRS_register.sr);
	VACTUAL(VACTUAL_register.sr);
	CHOPCONF(CHOPCONF_register.cfg.sr);
	PWMCONF(PWMCONF_register.cfg.sr);
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
	uint8_t datagram[] = {TMC2208_SYNC, TMC2208_SLAVE_ADDR, addr, (uint8_t)(regVal>>24), (uint8_t)(regVal>>16), (uint8_t)(regVal>>8), (uint8_t)(regVal>>0), 0x00};

	datagram[len] = calcCRC(datagram, len);

	if (uses_sw_serial) {
		for(int i=0; i<=len; i++){
			bytesWritten += static_cast<SoftwareSerial*>(SerialObject)->write(datagram[i]);
		}
	} else {
		for(int i=0; i<=len; i++){
			bytesWritten += static_cast<Stream*>(SerialObject)->write(datagram[i]);
		}
	}
}

template<typename SERIAL_TYPE>
uint64_t _sendDatagram(SERIAL_TYPE *serPtr, uint8_t datagram[], uint8_t len, uint16_t replyDelay) {
	uint64_t out = 0x00000000UL;
	while (serPtr->available() > 0) serPtr->read(); // Flush

	for(int i=0; i<=len; i++) serPtr->write(datagram[i]);
	
	serPtr->flush(); // Wait for TX to finish
	for(int byte=0; byte<4; byte++) serPtr->read(); // Flush bytes written
	delay(replyDelay);

	while(serPtr->available() > 0) {
		uint8_t res = serPtr->read();
		out <<= 8;
		out |= res&0xFF;
	}
	return out;
}

uint32_t TMC2208Stepper::read(uint8_t addr) {
	uint8_t len = 3;
	uint8_t datagram[] = {TMC2208_SYNC, TMC2208_SLAVE_ADDR, addr, 0x00};
	datagram[len] = calcCRC(datagram, len);
	uint64_t out = 0x00000000UL;

	if (uses_sw_serial) {
		SoftwareSerial *sw_ptr = static_cast<SoftwareSerial*>(SerialObject);
		sw_ptr->listen();
		out = _sendDatagram(sw_ptr, datagram, len, replyDelay);
	} else {
		Stream *hw_ptr = static_cast<Stream*>(SerialObject);
		out = _sendDatagram(hw_ptr, datagram, len, replyDelay);
	}

	uint8_t out_datagram[] = {(uint8_t)(out>>56), (uint8_t)(out>>48), (uint8_t)(out>>40), (uint8_t)(out>>32), (uint8_t)(out>>24), (uint8_t)(out>>16), (uint8_t)(out>>8), (uint8_t)(out>>0)};
	if (calcCRC(out_datagram, 7) == (uint8_t)(out&0xFF)) {
		CRCerror = false;
	} else {
		CRCerror = true;
	}
	return out>>8;
}

uint8_t TMC2208Stepper::IFCNT() {
	return READ_REG(IFCNT);
}

void TMC2208Stepper::SLAVECONF(uint16_t input) {
	SLAVECONF_register.cfg.sr = input&0xF00;
	WRITE_REG(SLAVECONF);
}
uint16_t TMC2208Stepper::SLAVECONF() {
	return SLAVECONF_register.cfg.sr;
}
void TMC2208Stepper::senddelay(uint8_t B) 	{ SLAVECONF_register.cfg.opt.senddelay = B; WRITE_REG(SLAVECONF); }
uint8_t TMC2208Stepper::senddelay() 		{ return SLAVECONF_register.cfg.opt.senddelay; }

void TMC2208Stepper::OTP_PROG(uint16_t input) {
	write(OTP_PROG_register.address, input);
}

uint32_t TMC2208Stepper::OTP_READ() {
	return read(OTP_READ_register.address);
}

uint32_t TMC2208Stepper::IOIN() {
	IOIN_register.cfg.sr = READ_REG(IOIN);
	return IOIN_register.cfg.sr;
}
bool TMC2208Stepper::enn()			{ IOIN(); return IOIN_register.cfg.opt.enn;		}
bool TMC2208Stepper::ms1()			{ IOIN(); return IOIN_register.cfg.opt.ms1;		}
bool TMC2208Stepper::ms2()			{ IOIN(); return IOIN_register.cfg.opt.ms2;		}
bool TMC2208Stepper::diag()			{ IOIN(); return IOIN_register.cfg.opt.diag;		}
bool TMC2208Stepper::pdn_uart()		{ IOIN(); return IOIN_register.cfg.opt.pdn_uart;	}
bool TMC2208Stepper::step()			{ IOIN(); return IOIN_register.cfg.opt.step;		}
bool TMC2208Stepper::sel_a()		{ IOIN(); return IOIN_register.cfg.opt.sel_a;		}
bool TMC2208Stepper::dir()			{ IOIN(); return IOIN_register.cfg.opt.dir;		}
uint8_t TMC2208Stepper::version() 	{ IOIN(); return IOIN_register.cfg.opt.version;	}

uint32_t TMC2224Stepper::IOIN() {
	IOIN_register.cfg.sr = READ_REG(IOIN);
	return IOIN_register.cfg.sr;
}
bool TMC2224Stepper::enn()			{ IOIN(); return IOIN_register.cfg.opt.enn;		}
bool TMC2224Stepper::ms1()			{ IOIN(); return IOIN_register.cfg.opt.ms1;		}
bool TMC2224Stepper::ms2()			{ IOIN(); return IOIN_register.cfg.opt.ms2;		}
bool TMC2224Stepper::pdn_uart()		{ IOIN(); return IOIN_register.cfg.opt.pdn_uart;}
bool TMC2224Stepper::spread()		{ IOIN(); return IOIN_register.cfg.opt.spread;	}
bool TMC2224Stepper::step()			{ IOIN(); return IOIN_register.cfg.opt.step;	}
bool TMC2224Stepper::sel_a()		{ IOIN(); return IOIN_register.cfg.opt.sel_a;	}
bool TMC2224Stepper::dir()			{ IOIN(); return IOIN_register.cfg.opt.dir;		}
uint8_t TMC2224Stepper::version() 	{ IOIN(); return IOIN_register.cfg.opt.version;	}

uint16_t TMC2208Stepper::FACTORY_CONF() {
	if (write_only) return FACTORY_CONF_register.cfg.sr;
	FACTORY_CONF_register.cfg.sr = READ_REG(FACTORY_CONF);
	return FACTORY_CONF_register.cfg.sr;
}
void TMC2208Stepper::FACTORY_CONF(uint16_t input) {
	FACTORY_CONF_register.cfg.sr = input;
	WRITE_REG(FACTORY_CONF);
}
void TMC2208Stepper::fclktrim(uint8_t B){ FACTORY_CONF_register.cfg.opt.fclktrim = B; WRITE_REG(FACTORY_CONF); }
void TMC2208Stepper::ottrim(uint8_t B)	{ FACTORY_CONF_register.cfg.opt.ottrim = B; WRITE_REG(FACTORY_CONF); }
uint8_t TMC2208Stepper::fclktrim()		{ READ_REG(FACTORY_CONF); return FACTORY_CONF_register.cfg.opt.fclktrim; }
uint8_t TMC2208Stepper::ottrim()		{ READ_REG(FACTORY_CONF); return FACTORY_CONF_register.cfg.opt.ottrim; }

void TMC2208Stepper::VACTUAL(uint32_t input) {
	VACTUAL_register.sr = input;
	write(VACTUAL_register.address, VACTUAL_register.sr);
}
uint32_t TMC2208Stepper::VACTUAL() {
	return VACTUAL_register.sr;
}

uint16_t TMC2208Stepper::MSCNT() {
	return READ_REG(MSCNT);
}

uint32_t TMC2208Stepper::MSCURACT() {
	MSCURACT_register.cfg.sr = READ_REG(MSCURACT);
	return MSCURACT_register.cfg.sr;
}
int16_t TMC2208Stepper::cur_a() { MSCURACT(); return MSCURACT_register.cfg.opt.cur_a; }
int16_t TMC2208Stepper::cur_b() { MSCURACT(); return MSCURACT_register.cfg.opt.cur_b; }

uint32_t TMC2208Stepper::PWM_SCALE() {
	PWM_SCALE_register.cfg.sr = READ_REG(PWM_SCALE);
	return PWM_SCALE_register.cfg.sr;
}
uint8_t TMC2208Stepper::pwm_scale_sum() { PWM_SCALE(); return PWM_SCALE_register.cfg.opt.pwm_scale_sum; }
int16_t TMC2208Stepper::pwm_scale_auto() {
	PWM_SCALE();
	return PWM_SCALE_register.cfg.opt.pwm_scale_auto;
	// Not two's complement? 9nth bit determines sign
	/*
	uint32_t d = PWM_SCALE();
	int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
	if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
	else return response;
	*/
}
