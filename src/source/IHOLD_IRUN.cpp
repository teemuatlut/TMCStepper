#include "TMCStepper.h"

// IHOLD_IRUN
uint32_t TMCStepper::IHOLD_IRUN() { return IHOLD_IRUN_register.sr; }
void TMCStepper::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register.sr = input;
	write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
}

void 	TMCStepper::ihold(uint8_t B) 		{ IHOLD_IRUN_register.ihold = B; 		write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr); }
void 	TMCStepper::irun(uint8_t B)  		{ IHOLD_IRUN_register.irun = B; 		write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr); }
void 	TMCStepper::iholddelay(uint8_t B)	{ IHOLD_IRUN_register.iholddelay = B; 	write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr); }

uint8_t TMCStepper::ihold() 				{ return IHOLD_IRUN_register.ihold;		}
uint8_t TMCStepper::irun()  				{ return IHOLD_IRUN_register.irun; 		}
uint8_t TMCStepper::iholddelay()  			{ return IHOLD_IRUN_register.iholddelay;}
