#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(DRVCONF).SETTING = B; SELF.write(ADR(DRVCONF), REG(DRVCONF).sr); }while(0)
#define GET_REG(SETTING) return REG(DRVCONF).SETTING

uint32_t TMC2660Stepper::DRVCONF() { return REG(DRVCONF).sr; }
void TMC2660Stepper::DRVCONF(uint32_t data) {
  REG(DRVCONF).sr = data;
  SELF.write(ADR(DRVCONF), REG(DRVCONF).sr);
}

void TMC2660Stepper::tst(bool B)      { SET_REG(tst);	}
void TMC2660Stepper::slph(uint8_t B)  { SET_REG(slph);	}
void TMC2660Stepper::slpl(uint8_t B)  { SET_REG(slpl);	}
void TMC2660Stepper::diss2g(bool B)   { SET_REG(diss2g);}
void TMC2660Stepper::ts2g(uint8_t B)  { SET_REG(ts2g);	}
void TMC2660Stepper::sdoff(bool B)    { SET_REG(sdoff);	}
void TMC2660Stepper::vsense(bool B)   { SET_REG(vsense);}
void TMC2660Stepper::rdsel(uint8_t B) { SET_REG(rdsel);	}

bool	 TMC2660Stepper::tst()		{ GET_REG(tst);		}
uint8_t	 TMC2660Stepper::slph()		{ GET_REG(slph);	}
uint8_t	 TMC2660Stepper::slpl()		{ GET_REG(slpl);	}
bool	 TMC2660Stepper::diss2g()	{ GET_REG(diss2g);	}
uint8_t	 TMC2660Stepper::ts2g()		{ GET_REG(ts2g);	}
bool	 TMC2660Stepper::sdoff()	{ GET_REG(sdoff);	}
bool	 TMC2660Stepper::vsense()	{ GET_REG(vsense);	}
uint8_t	 TMC2660Stepper::rdsel()	{ GET_REG(rdsel);	}
