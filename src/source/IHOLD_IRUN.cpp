#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(IHOLD_IRUN).SETTING = B; SELF.write(ADR(IHOLD_IRUN), REG(IHOLD_IRUN).sr); }while(0)
#define GET_REG(SETTING) return REG(IHOLD_IRUN).SETTING

// IHOLD_IRUN
TT uint32_t TMCStepper<T>::IHOLD_IRUN() { return REG(IHOLD_IRUN).sr; }
TT void TMCStepper<T>::IHOLD_IRUN(uint32_t input) {
	REG(IHOLD_IRUN).sr = input;
	SELF.write(ADR(IHOLD_IRUN), REG(IHOLD_IRUN).sr);
}

TT void			TMCStepper<T>::ihold(			uint8_t B)	{ SET_REG(ihold);				}
TT void			TMCStepper<T>::irun(			uint8_t B)	{ SET_REG(irun); 				}
TT void			TMCStepper<T>::iholddelay(uint8_t B)	{ SET_REG(iholddelay);	}

TT uint8_t	TMCStepper<T>::ihold()			{ GET_REG(ihold);				}
TT uint8_t	TMCStepper<T>::irun()				{ GET_REG(irun); 				}
TT uint8_t	TMCStepper<T>::iholddelay()	{ GET_REG(iholddelay);	}
