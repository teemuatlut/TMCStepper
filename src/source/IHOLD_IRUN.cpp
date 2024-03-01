#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) IHOLD_IRUN_register.SETTING = B; write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
#define GET_REG(SETTING) return IHOLD_IRUN_register.SETTING;

// IHOLD_IRUN
uint32_t TMCStepper::IHOLD_IRUN() { return IHOLD_IRUN_register.sr; }
void TMCStepper::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register.sr = input;
	write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
}

void 	TMCStepper::ihold(uint8_t B) 		{ SET_REG(ihold);		}
void 	TMCStepper::irun(uint8_t B)  		{ SET_REG(irun); 		}
void 	TMCStepper::iholddelay(uint8_t B)	{ SET_REG(iholddelay); 	}

uint8_t TMCStepper::ihold() 				{ GET_REG(ihold);		}
uint8_t TMCStepper::irun()  				{ GET_REG(irun); 		}
uint8_t TMCStepper::iholddelay()  			{ GET_REG(iholddelay);	}

// IHOLD_IRUN
uint32_t TMC2240Stepper::IHOLD_IRUN() { return IHOLD_IRUN_register.sr; }
void TMC2240Stepper::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register.sr = input;
	write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
}

void 	TMC2240Stepper::ihold(uint8_t B) 		{ SET_REG(ihold);		}
void 	TMC2240Stepper::irun(uint8_t B)  		{ SET_REG(irun); 		}
void 	TMC2240Stepper::iholddelay(uint8_t B)	{ SET_REG(iholddelay); 	}
void 	TMC2240Stepper::irundelay(uint8_t B)	{ SET_REG(irundelay); 	}

uint8_t TMC2240Stepper::ihold() 				{ GET_REG(ihold);		}
uint8_t TMC2240Stepper::irun()  				{ GET_REG(irun); 		}
uint8_t TMC2240Stepper::iholddelay()  			{ GET_REG(iholddelay);	}
uint8_t TMC2240Stepper::irundelay()  			{ GET_REG(irundelay);	}
