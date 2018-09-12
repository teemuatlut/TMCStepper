#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(CHOPCONF).SETTING = B; SELF.write(ADR(CHOPCONF), REG(CHOPCONF).sr); }while(0)
#define GET_REG(SETTING) do{ this->CHOPCONF(); return REG(CHOPCONF).SETTING; }while(0)

// CHOPCONF
TT uint32_t TMC2130StepperBase<T>::CHOPCONF() {
	REG(CHOPCONF).sr = SELF.read(ADR(CHOPCONF));
	return REG(CHOPCONF).sr;
}
TT void TMC2130StepperBase<T>::CHOPCONF(uint32_t input) {
	REG(CHOPCONF).sr = input;
	SELF.write(ADR(CHOPCONF), REG(CHOPCONF).sr);
}

TT void TMC2130StepperBase<T>::toff(		uint8_t B )	{ SET_REG(toff);	}
TT void TMC2130StepperBase<T>::hstrt(		uint8_t B )	{ SET_REG(hstrt);	}
TT void TMC2130StepperBase<T>::hend(		uint8_t B )	{ SET_REG(hend);	}
//TT //void TMC2130StepperBase<T>::fd(		uint8_t B )	{ SET_REG(fd);		}
TT void TMC2130StepperBase<T>::disfdcc(	bool 	B )	{ SET_REG(disfdcc);	}
TT void TMC2130StepperBase<T>::rndtf(		bool 	B )	{ SET_REG(rndtf);	}
TT void TMC2130StepperBase<T>::chm(		bool 	B )	{ SET_REG(chm);		}
TT void TMC2130StepperBase<T>::tbl(		uint8_t B )	{ SET_REG(tbl);		}
TT void TMC2130StepperBase<T>::vsense(		bool 	B )	{ SET_REG(vsense);	}
TT void TMC2130StepperBase<T>::vhighfs(	bool 	B )	{ SET_REG(vhighfs);	}
TT void TMC2130StepperBase<T>::vhighchm(	bool 	B )	{ SET_REG(vhighchm);}
TT void TMC2130StepperBase<T>::sync(		uint8_t B )	{ SET_REG(sync);	}
TT void TMC2130StepperBase<T>::mres(		uint8_t B )	{ SET_REG(mres);	}
TT void TMC2130StepperBase<T>::intpol(		bool 	B )	{ SET_REG(intpol);	}
TT void TMC2130StepperBase<T>::dedge(		bool 	B )	{ SET_REG(dedge);	}
TT void TMC2130StepperBase<T>::diss2g(		bool 	B )	{ SET_REG(diss2g);	}

TT uint8_t TMC2130StepperBase<T>::toff()		{ GET_REG(toff);	}
TT uint8_t TMC2130StepperBase<T>::hstrt()		{ GET_REG(hstrt);	}
TT uint8_t TMC2130StepperBase<T>::hend()		{ GET_REG(hend);	}
//TT //uint8_t TMC2130StepperBase<T>::fd()		{ GET_REG(fd);		}
TT bool 	TMC2130StepperBase<T>::disfdcc()	{ GET_REG(disfdcc);	}
TT bool 	TMC2130StepperBase<T>::rndtf()		{ GET_REG(rndtf);	}
TT bool 	TMC2130StepperBase<T>::chm()		{ GET_REG(chm);		}
TT uint8_t TMC2130StepperBase<T>::tbl()		{ GET_REG(tbl);		}
TT bool 	TMC2130StepperBase<T>::vsense()		{ GET_REG(vsense);	}
TT bool 	TMC2130StepperBase<T>::vhighfs()	{ GET_REG(vhighfs);	}
TT bool 	TMC2130StepperBase<T>::vhighchm()	{ GET_REG(vhighchm);}
TT uint8_t TMC2130StepperBase<T>::sync()		{ GET_REG(sync);	}
TT uint8_t TMC2130StepperBase<T>::mres()		{ GET_REG(mres);	}
TT bool 	TMC2130StepperBase<T>::intpol()		{ GET_REG(intpol);	}
TT bool 	TMC2130StepperBase<T>::dedge()		{ GET_REG(dedge);	}
TT bool 	TMC2130StepperBase<T>::diss2g()		{ GET_REG(diss2g);	}

TT void TMC2208StepperBase<T>::CHOPCONF(uint32_t input) {
	REG(CHOPCONF).sr = input;
	SELF.write(ADR(CHOPCONF), REG(CHOPCONF).sr);
}
TT uint32_t TMC2208StepperBase<T>::CHOPCONF() {
	if (write_only) return REG(CHOPCONF).sr;
	REG(CHOPCONF).sr = SELF.read(ADR(CHOPCONF));
	return REG(CHOPCONF).sr;
}
TT void TMC2208StepperBase<T>::toff	( uint8_t  B )	{ SET_REG(toff); 	}
TT void TMC2208StepperBase<T>::hstrt	( uint8_t  B )	{ SET_REG(hstrt); 	}
TT void TMC2208StepperBase<T>::hend	( uint8_t  B )	{ SET_REG(hend); 	}
TT void TMC2208StepperBase<T>::tbl		( uint8_t  B )	{ SET_REG(tbl); 	}
TT void TMC2208StepperBase<T>::vsense	( bool     B )	{ SET_REG(vsense); 	}
TT void TMC2208StepperBase<T>::mres	( uint8_t  B )	{ SET_REG(mres); 	}
TT void TMC2208StepperBase<T>::intpol	( bool     B )	{ SET_REG(intpol); 	}
TT void TMC2208StepperBase<T>::dedge	( bool     B )	{ SET_REG(dedge); 	}
TT void TMC2208StepperBase<T>::diss2g	( bool     B )	{ SET_REG(diss2g); 	}
TT void TMC2208StepperBase<T>::diss2vs	( bool     B )	{ SET_REG(diss2vs); }

TT uint8_t TMC2208StepperBase<T>::toff()		{ GET_REG(toff); 	}
TT uint8_t TMC2208StepperBase<T>::hstrt()		{ GET_REG(hstrt); 	}
TT uint8_t TMC2208StepperBase<T>::hend()		{ GET_REG(hend); 	}
TT uint8_t TMC2208StepperBase<T>::tbl()		{ GET_REG(tbl); 	}
TT bool 	TMC2208StepperBase<T>::vsense()		{ GET_REG(vsense); 	}
TT uint8_t TMC2208StepperBase<T>::mres()		{ GET_REG(mres); 	}
TT bool 	TMC2208StepperBase<T>::intpol()		{ GET_REG(intpol); 	}
TT bool 	TMC2208StepperBase<T>::dedge()		{ GET_REG(dedge); 	}
TT bool 	TMC2208StepperBase<T>::diss2g()		{ GET_REG(diss2g); 	}
TT bool 	TMC2208StepperBase<T>::diss2vs()	{ GET_REG(diss2vs); }

#define GET_REG_2660(SETTING) return REG(CHOPCONF).SETTING;

uint32_t TMC2660Stepper::CHOPCONF() { return REG(CHOPCONF).sr; }
void TMC2660Stepper::CHOPCONF(uint32_t data) {
  REG(CHOPCONF).sr = data;
  SELF.write(ADR(CHOPCONF), REG(CHOPCONF).sr);
}

void TMC2660Stepper::toff(uint8_t B) 	{
	SET_REG(toff);
	if (B>0) _savedToff = B;
}
void TMC2660Stepper::hstrt(uint8_t B)	{ SET_REG(hstrt);	}
void TMC2660Stepper::hend(uint8_t B)	{ SET_REG(hend);	}
void TMC2660Stepper::hdec(uint8_t B)	{ SET_REG(hdec);	}
void TMC2660Stepper::rndtf(bool B)		{ SET_REG(rndtf);	}
void TMC2660Stepper::chm(bool B)		{ SET_REG(chm);		}
void TMC2660Stepper::tbl(uint8_t B)		{ SET_REG(tbl);		}

uint8_t TMC2660Stepper::toff()	{ GET_REG_2660(toff);	}
uint8_t TMC2660Stepper::hstrt()	{ GET_REG_2660(hstrt);	}
uint8_t TMC2660Stepper::hend()	{ GET_REG_2660(hend);	}
uint8_t TMC2660Stepper::hdec() 	{ GET_REG_2660(hdec);	}
bool TMC2660Stepper::rndtf()	{ GET_REG_2660(rndtf);	}
bool TMC2660Stepper::chm()		{ GET_REG_2660(chm);	}
uint8_t TMC2660Stepper::tbl()	{ GET_REG_2660(tbl);	}
