#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) IHOLD_IRUN_register.cfg.opt.SETTING = B; WRITE_REG(IHOLD_IRUN);
#define GET_REG(SETTING) return IHOLD_IRUN_register.cfg.opt.SETTING;

// IHOLD_IRUN
uint32_t TMC2130Stepper::IHOLD_IRUN() { return IHOLD_IRUN_register.cfg.sr; }
void TMC2130Stepper::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register.cfg.sr = input;
	WRITE_REG(IHOLD_IRUN);
}

void 	TMC2130Stepper::ihold(uint8_t B) 		{ SET_REG(ihold);		}
void 	TMC2130Stepper::irun(uint8_t B)  		{ SET_REG(irun); 		}
void 	TMC2130Stepper::iholddelay(uint8_t B)	{ SET_REG(iholddelay); 	}

uint8_t TMC2130Stepper::ihold() 				{ GET_REG(ihold);		}
uint8_t TMC2130Stepper::irun()  				{ GET_REG(irun); 		}
uint8_t TMC2130Stepper::iholddelay()  			{ GET_REG(iholddelay);	}
