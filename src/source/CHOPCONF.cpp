#include "TMCStepper.h"

// CHOPCONF
void TMC5160Stepper::diss2vs(bool B){ CHOPCONF_t r{ CHOPCONF() }; r.diss2vs = B; CHOPCONF(r.sr);}
void TMC5160Stepper::tpfd(uint8_t B){ CHOPCONF_t r{ CHOPCONF() }; r.tpfd = B; 	 CHOPCONF(r.sr);}
bool TMC5160Stepper::diss2vs()		{ return CHOPCONF_t{ CHOPCONF() }.diss2vs;	}
uint8_t TMC5160Stepper::tpfd()		{ return CHOPCONF_t{ CHOPCONF() }.tpfd;		}

void TMC2208Stepper::CHOPCONF(uint32_t input) {
	CHOPCONF_register.sr = input;
	write(CHOPCONF_register.address, CHOPCONF_register.sr);
}
uint32_t TMC2208Stepper::CHOPCONF() {
	return read(CHOPCONF_register.address);
}
void TMC2208Stepper::toff	( uint8_t  B )	{ CHOPCONF_register.toff = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::hstrt	( uint8_t  B )	{ CHOPCONF_register.hstrt = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::hend	( uint8_t  B )	{ CHOPCONF_register.hend = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::tbl	( uint8_t  B )	{ CHOPCONF_register.tbl = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::vsense	( bool     B )	{ CHOPCONF_register.vsense = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::mres	( uint8_t  B )	{ CHOPCONF_register.mres = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::intpol	( bool     B )	{ CHOPCONF_register.intpol = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::dedge	( bool     B )	{ CHOPCONF_register.dedge = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::diss2g	( bool     B )	{ CHOPCONF_register.diss2g = B;	write(CHOPCONF_register.address, CHOPCONF_register.sr); }
void TMC2208Stepper::diss2vs( bool     B )	{ CHOPCONF_register.diss2vs = B;write(CHOPCONF_register.address, CHOPCONF_register.sr); }

uint8_t TMC2208Stepper::toff()		{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.toff; 		}
uint8_t TMC2208Stepper::hstrt()		{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.hstrt; 	}
uint8_t TMC2208Stepper::hend()		{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.hend; 		}
uint8_t TMC2208Stepper::tbl()		{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.tbl;	 	}
bool 	TMC2208Stepper::vsense()	{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.vsense; 	}
uint8_t TMC2208Stepper::mres()		{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.mres; 		}
bool 	TMC2208Stepper::intpol()	{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.intpol; 	}
bool 	TMC2208Stepper::dedge()		{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.dedge; 	}
bool 	TMC2208Stepper::diss2g()	{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.diss2g; 	}
bool 	TMC2208Stepper::diss2vs()	{ return TMC2208_n::CHOPCONF_t{ CHOPCONF() }.diss2vs; 	}

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
