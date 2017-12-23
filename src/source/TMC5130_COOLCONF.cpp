#include "TMCStepper.h"

// COOLCONF
uint32_t TMC5130Stepper::COOLCONF() { return COOLCONF_sr; }
void TMC5130Stepper::COOLCONF(uint32_t input) {
	COOLCONF_sr = input;
	WRITE_REG(COOLCONF);
}

void TMC5130Stepper::semin(		uint8_t B )	{ MOD_REG(COOLCONF, SEMIN);		}
void TMC5130Stepper::seup(		uint8_t B )	{ MOD_REG(COOLCONF, SEUP);		}
void TMC5130Stepper::semax(		uint8_t B )	{ MOD_REG(COOLCONF, SEMAX);		}
void TMC5130Stepper::sedn(		uint8_t B )	{ MOD_REG(COOLCONF, SEDN);		}
void TMC5130Stepper::seimin(	bool 	B )	{ MOD_REG(COOLCONF, SEIMIN);	}
void TMC5130Stepper::sgt(		uint8_t B )	{ MOD_REG(COOLCONF, SGT);		}
void TMC5130Stepper::sfilt(		bool 	B )	{ MOD_REG(COOLCONF, SFILT);		}

uint8_t TMC5130Stepper::semin()	{ GET_BYTE(COOLCONF, SEMIN);	}
uint8_t TMC5130Stepper::seup()	{ GET_BYTE(COOLCONF, SEUP);		}
uint8_t TMC5130Stepper::semax()	{ GET_BYTE(COOLCONF, SEMAX);	}
uint8_t TMC5130Stepper::sedn()	{ GET_BYTE(COOLCONF, SEDN);		}
bool 	TMC5130Stepper::seimin(){ GET_BYTE(COOLCONF, SEIMIN);	}
uint8_t TMC5130Stepper::sgt()	{ GET_BYTE(COOLCONF, SGT);		}
bool 	TMC5130Stepper::sfilt()	{ GET_BYTE(COOLCONF, SFILT);	}
