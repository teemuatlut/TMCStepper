#include "TMCStepper.h"
#include "TMC_MACROS.h"

TMC2209Stepper::TMC2209Stepper(Stream * SerialPort, float RS, bool has_rx) : TMC2208Stepper(SerialPort, RS, has_rx) {}
#if SW_CAPABLE_PLATFORM
TMC2209Stepper::TMC2209Stepper(uint16_t SW_RX_pin, uint16_t SW_TX_pin, float RS, bool has_rx) :
			TMC2208Stepper(SW_RX_pin, SW_TX_pin, RS, has_rx){}
#endif

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