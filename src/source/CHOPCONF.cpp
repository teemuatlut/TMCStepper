#include "TMCStepper.h"
/*
// CHOPCONF
void TMC5160Stepper::diss2vs(bool B){ TMC2130_n::CHOPCONF_t r{ CHOPCONF() }; r.diss2vs = B; CHOPCONF(r.sr);}
void TMC5160Stepper::tpfd(uint8_t B){ TMC2130_n::CHOPCONF_t r{ CHOPCONF() }; r.tpfd = B; 	 CHOPCONF(r.sr);}
bool TMC5160Stepper::diss2vs()		{ return TMC2130_n::CHOPCONF_t{ CHOPCONF() }.diss2vs;	}
uint8_t TMC5160Stepper::tpfd()		{ return TMC2130_n::CHOPCONF_t{ CHOPCONF() }.tpfd;		}
*/


uint32_t TMC2660Stepper::CHOPCONF() { return CHOPCONF_register.sr; }
void TMC2660Stepper::CHOPCONF(uint32_t data) {
  CHOPCONF_register.sr = data;
  write(CHOPCONF_register.address, CHOPCONF_register.sr);
}

void TMC2660Stepper::toff(uint8_t B) 	{
	CHOPCONF_register.toff = B;
	write(CHOPCONF_register.address, CHOPCONF_register.sr);

	if (B>0)
		_savedToff = B;
}
void TMC2660Stepper::hstrt(uint8_t B) 	{ CHOPCONF_register.hstrt = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2660Stepper::hend(uint8_t B) 	{ CHOPCONF_register.hend = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr);	}
void TMC2660Stepper::hdec(uint8_t B) 	{ CHOPCONF_register.hdec = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr);	}
void TMC2660Stepper::rndtf(bool B) 		{ CHOPCONF_register.rndtf = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr);	}
void TMC2660Stepper::chm(bool B) 		{ CHOPCONF_register.chm = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr);	}
void TMC2660Stepper::tbl(uint8_t B) 	{ CHOPCONF_register.tbl = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr);	}

uint8_t TMC2660Stepper::toff() 	{ return CHOPCONF_register.toff;	}
uint8_t TMC2660Stepper::hstrt() { return CHOPCONF_register.hstrt;	}
uint8_t TMC2660Stepper::hend() 	{ return CHOPCONF_register.hend;	}
uint8_t TMC2660Stepper::hdec() 	{ return CHOPCONF_register.hdec;	}
bool 	TMC2660Stepper::rndtf() { return CHOPCONF_register.rndtf;	}
bool 	TMC2660Stepper::chm() 	{ return CHOPCONF_register.chm;		}
uint8_t TMC2660Stepper::tbl() 	{ return CHOPCONF_register.tbl;		}
