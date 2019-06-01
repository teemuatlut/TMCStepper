#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC2209Stepper::TMC2209Stepper(Stream * SerialPort, float RS, uint8_t slave, bool has_rx) : TMC2208Stepper(SerialPort, RS, has_rx) {this->slave_addr = slave;}
#if SW_CAPABLE_PLATFORM
TMC2209Stepper::TMC2209Stepper(uint16_t SW_RX_pin, uint16_t SW_TX_pin, float RS, uint8_t slave, bool has_rx) :
			TMC2208Stepper(SW_RX_pin, SW_TX_pin, RS, has_rx){this->slave_addr = slave;}
#endif

void TMC2209Stepper::write(uint8_t addr, uint32_t regVal) {
	uint8_t len = 7;
	addr |= TMC_WRITE;
	uint8_t datagram[] = {TMC2209_SYNC, this->slave_addr, addr, (uint8_t)(regVal>>24), (uint8_t)(regVal>>16), (uint8_t)(regVal>>8), (uint8_t)(regVal>>0), 0x00};

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
extern uint64_t _sendDatagram(SERIAL_TYPE &serPtr, uint8_t datagram[], const uint8_t len, uint16_t timeout);

uint32_t TMC2209Stepper::read(uint8_t addr) {
	constexpr uint8_t len = 3;
	addr |= TMC_READ;
	uint8_t datagram[] = {TMC2209_SYNC, this->slave_addr, addr, 0x00};
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

void TMC2209Stepper::sgt(	uint8_t  B )	{ SGTHRS_register.sr = B; write(SGTHRS_register.address, SGTHRS_register.sr);		}
uint8_t TMC2209Stepper::sgt() {
	// Two's complement in a 7bit value
	uint8_t val = (SGTHRS_register.sr &  0x40) << 1; // Isolate sign bit
	val |= SGTHRS_register.sr & 0x7F;
	return val;
}

// W: TCOOLTHRS
uint32_t TMC2209Stepper::TCOOLTHRS() { return TCOOLTHRS_register.sr; }
void TMC2209Stepper::TCOOLTHRS(uint32_t input) {
  TCOOLTHRS_register.sr = input;
  write(TCOOLTHRS_register.address, TCOOLTHRS_register.sr);
}
