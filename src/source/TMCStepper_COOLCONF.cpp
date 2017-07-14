#include "TMCStepper.h"
#include "TMCStepper_MACROS.h"

// COOLCONF
uint32_t TMCStepper::COOLCONF() { return COOLCONF_sr; }
void TMCStepper::COOLCONF(uint32_t input) {
	COOLCONF_sr = input;
	WRITE_REG(COOLCONF);
}

void TMCStepper::semin(		uint8_t B )	{ MOD_REG(COOLCONF, SEMIN);		}
void TMCStepper::seup(		uint8_t B )	{ MOD_REG(COOLCONF, SEUP);		}
void TMCStepper::semax(		uint8_t B )	{ MOD_REG(COOLCONF, SEMAX);		}
void TMCStepper::sedn(		uint8_t B )	{ MOD_REG(COOLCONF, SEDN);		}
void TMCStepper::seimin(	bool 	B )	{ MOD_REG(COOLCONF, SEIMIN);	}
void TMCStepper::sgt(		uint8_t B )	{ MOD_REG(COOLCONF, SGT);		}
void TMCStepper::sfilt(		bool 	B )	{ MOD_REG(COOLCONF, SFILT);		}

uint8_t TMCStepper::semin()	{ GET_BYTE(COOLCONF, SEMIN);	}
uint8_t TMCStepper::seup()	{ GET_BYTE(COOLCONF, SEUP);		}
uint8_t TMCStepper::semax()	{ GET_BYTE(COOLCONF, SEMAX);	}
uint8_t TMCStepper::sedn()	{ GET_BYTE(COOLCONF, SEDN);		}
bool 	TMCStepper::seimin(){ GET_BYTE(COOLCONF, SEIMIN);	}
uint8_t TMCStepper::sgt()	{ GET_BYTE(COOLCONF, SGT);		}
bool 	TMCStepper::sfilt()	{ GET_BYTE(COOLCONF, SFILT);	}
