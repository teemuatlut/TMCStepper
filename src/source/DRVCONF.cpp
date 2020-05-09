#include "TMCStepper.h"

uint32_t TMC2660Stepper::DRVCONF() { return DRVCONF_register.sr; }
void TMC2660Stepper::DRVCONF(uint32_t data) {
  DRVCONF_register.sr = data;
  write(DRVCONF_register.address, DRVCONF_register.sr);
}

void TMC2660Stepper::tst(bool B)      { DRVCONF_register.tst = B; 		write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::slph(uint8_t B)  { DRVCONF_register.slph = B; 		write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::slpl(uint8_t B)  { DRVCONF_register.slpl = B; 		write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::diss2g(bool B)   { DRVCONF_register.diss2g = B; 	write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::ts2g(uint8_t B)  { DRVCONF_register.ts2g = B; 		write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::sdoff(bool B)    { DRVCONF_register.sdoff = B; 	write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::vsense(bool B)   { DRVCONF_register.vsense = B; 	write(DRVCONF_register.address, DRVCONF_register.sr);}
void TMC2660Stepper::rdsel(uint8_t B) { DRVCONF_register.rdsel = B; 	write(DRVCONF_register.address, DRVCONF_register.sr);}

bool	 TMC2660Stepper::tst()		{ return DRVCONF_register.tst;		}
uint8_t	 TMC2660Stepper::slph()		{ return DRVCONF_register.slph;		}
uint8_t	 TMC2660Stepper::slpl()		{ return DRVCONF_register.slpl;		}
bool	 TMC2660Stepper::diss2g()	{ return DRVCONF_register.diss2g;	}
uint8_t	 TMC2660Stepper::ts2g()		{ return DRVCONF_register.ts2g;		}
bool	 TMC2660Stepper::sdoff()	{ return DRVCONF_register.sdoff;	}
bool	 TMC2660Stepper::vsense()	{ return DRVCONF_register.vsense;	}
uint8_t	 TMC2660Stepper::rdsel()	{ return DRVCONF_register.rdsel;	}
