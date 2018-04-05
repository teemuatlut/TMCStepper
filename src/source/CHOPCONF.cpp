#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) CHOPCONF_register.cfg.opt.SETTING = B; WRITE_REG(CHOPCONF);
#define GET_REG(SETTING) CHOPCONF(); return CHOPCONF_register.cfg.opt.SETTING;

// CHOPCONF
uint32_t TMC2130Stepper::CHOPCONF() {
	CHOPCONF_register.cfg.sr = READ_REG(CHOPCONF);
	return CHOPCONF_register.cfg.sr;
}
void TMC2130Stepper::CHOPCONF(uint32_t input) {
	CHOPCONF_register.cfg.sr = input;
	WRITE_REG(CHOPCONF);
}

void TMC2130Stepper::toff(		uint8_t B )	{ SET_REG(toff);	}
void TMC2130Stepper::hstrt(		uint8_t B )	{ SET_REG(hstrt);	}
void TMC2130Stepper::hend(		int8_t  B )	{ SET_REG(hend);	}
//void TMC2130Stepper::fd(		uint8_t B )	{ SET_REG(fd);		}
void TMC2130Stepper::disfdcc(	bool 	B )	{ SET_REG(disfdcc);	}
void TMC2130Stepper::rndtf(		bool 	B )	{ SET_REG(rndtf);	}
void TMC2130Stepper::chm(		bool 	B )	{ SET_REG(chm);		}
void TMC2130Stepper::tbl(		uint8_t B )	{ SET_REG(tbl);		}
void TMC2130Stepper::vsense(	bool 	B )	{ SET_REG(vsense);	}
void TMC2130Stepper::vhighfs(	bool 	B )	{ SET_REG(vhighfs);	}
void TMC2130Stepper::vhighchm(	bool 	B )	{ SET_REG(vhighchm);}
void TMC2130Stepper::sync(		uint8_t B )	{ SET_REG(sync);	}
void TMC2130Stepper::mres(		uint8_t B )	{ SET_REG(mres);	}
void TMC2130Stepper::intpol(	bool 	B )	{ SET_REG(intpol);	}
void TMC2130Stepper::dedge(		bool 	B )	{ SET_REG(dedge);	}
void TMC2130Stepper::diss2g(	bool 	B )	{ SET_REG(diss2g);	}

uint8_t TMC2130Stepper::toff()		{ GET_REG(toff);	}
uint8_t TMC2130Stepper::hstrt()		{ GET_REG(hstrt);	}
int8_t  TMC2130Stepper::hend()		{ GET_REG(hend);	}
//uint8_t TMC2130Stepper::fd()		{ GET_REG(fd);		}
bool 	TMC2130Stepper::disfdcc()	{ GET_REG(disfdcc);	}
bool 	TMC2130Stepper::rndtf()		{ GET_REG(rndtf);	}
bool 	TMC2130Stepper::chm()		{ GET_REG(chm);		}
uint8_t TMC2130Stepper::tbl()		{ GET_REG(tbl);		}
bool 	TMC2130Stepper::vsense()	{ GET_REG(vsense);	}
bool 	TMC2130Stepper::vhighfs()	{ GET_REG(vhighfs);	}
bool 	TMC2130Stepper::vhighchm()	{ GET_REG(vhighchm);}
uint8_t TMC2130Stepper::sync()		{ GET_REG(sync);	}
uint8_t TMC2130Stepper::mres()		{ GET_REG(mres);	}
bool 	TMC2130Stepper::intpol()	{ GET_REG(intpol);	}
bool 	TMC2130Stepper::dedge()		{ GET_REG(dedge);	}
bool 	TMC2130Stepper::diss2g()	{ GET_REG(diss2g);	}

#define GET_REG_2660(SETTING) return CHOPCONF_register.cfg.opt.SETTING;

uint32_t TMC2660Stepper::CHOPCONF() { return CHOPCONF_register.cfg.sr; }
void TMC2660Stepper::CHOPCONF(uint32_t data) {
  SMARTEN_register.cfg.sr = data;
  WRITE_REG(SMARTEN);
}

void TMC2660Stepper::toff(uint8_t B) 	{
	SET_REG(toff);
	if (B>0) _savedToff = B;
}
void TMC2660Stepper::hstrt(uint8_t B) 	{ SET_REG(hstrt); 	}
void TMC2660Stepper::hend(uint8_t B) 	{ SET_REG(hend);	}
void TMC2660Stepper::hdec(uint8_t B) 	{ SET_REG(hdec);	}
void TMC2660Stepper::rndtf(bool B) 	{ SET_REG(rndtf);	}
void TMC2660Stepper::chm(bool B) 	{ SET_REG(chm);	}
void TMC2660Stepper::tbl(uint8_t B) 	{ SET_REG(tbl);	}

uint8_t TMC2660Stepper::toff() 	{ GET_REG_2660(toff);	}
uint8_t TMC2660Stepper::hstrt() 	{ GET_REG_2660(hstrt);	}
uint8_t TMC2660Stepper::hend() { GET_REG_2660(hend);	}
uint8_t TMC2660Stepper::hdec() 	{ GET_REG_2660(hdec);	}
bool TMC2660Stepper::rndtf() { GET_REG_2660(rndtf);	}
bool TMC2660Stepper::chm() 	{ GET_REG_2660(chm);	}
uint8_t TMC2660Stepper::tbl() { GET_REG_2660(tbl);	}
