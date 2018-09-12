#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(SMARTEN).SETTING = B; SELF.write(ADR(SMARTEN), REG(SMARTEN).sr); }while(0)
#define GET_REG(SETTING) return REG(SMARTEN).SETTING

uint32_t TMC2660Stepper::SMARTEN() { return REG(SMARTEN).sr; }
void TMC2660Stepper::SMARTEN(uint32_t data) {
  REG(SMARTEN).sr = data;
  SELF.write(ADR(SMARTEN), REG(SMARTEN).sr);
}

void TMC2660Stepper::seimin(bool B) 	{ SET_REG(seimin);	}
void TMC2660Stepper::sedn(uint8_t B) 	{ SET_REG(sedn); 	}
void TMC2660Stepper::semax(uint8_t B) 	{ SET_REG(semax);	}
void TMC2660Stepper::seup(uint8_t B) 	{ SET_REG(seup);	}
void TMC2660Stepper::semin(uint8_t B) 	{ SET_REG(semin);	}

bool TMC2660Stepper::seimin() 	{ GET_REG(seimin);	}
uint8_t TMC2660Stepper::sedn() 	{ GET_REG(sedn);	}
uint8_t TMC2660Stepper::semax() { GET_REG(semax);	}
uint8_t TMC2660Stepper::seup() 	{ GET_REG(seup);	}
uint8_t TMC2660Stepper::semin() { GET_REG(semin);	}
