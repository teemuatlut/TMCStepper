#include "TMCStepper.h"
#include "TMCStepper_MACROS.h"

// IHOLD_IRUN
void TMCStepper::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_sr = input;
	WRITE_REG(IHOLD_IRUN);
}
uint32_t TMCStepper::IHOLD_IRUN() { return IHOLD_IRUN_sr; }

void 	TMCStepper::ihold(uint8_t B) 		{ MOD_REG(IHOLD_IRUN, IHOLD);		}
void 	TMCStepper::irun(uint8_t B)  		{ MOD_REG(IHOLD_IRUN, IRUN); 		}
void 	TMCStepper::iholddelay(uint8_t B)	{ MOD_REG(IHOLD_IRUN, IHOLDDELAY); 	}
uint8_t TMCStepper::ihold() 				{ GET_BYTE(IHOLD_IRUN, IHOLD);		}
uint8_t TMCStepper::irun()  				{ GET_BYTE(IHOLD_IRUN, IRUN); 		}
uint8_t TMCStepper::iholddelay()  			{ GET_BYTE(IHOLD_IRUN, IHOLDDELAY);	}
