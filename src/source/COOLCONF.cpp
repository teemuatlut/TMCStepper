#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(COOLCONF).SETTING = B; SELF.write(ADR(COOLCONF), REG(COOLCONF).sr); }while(0)
#define GET_REG(SETTING) do{ COOLCONF(); return REG(COOLCONF).SETTING; }while(0)

// COOLCONF
TT uint32_t TMC2130StepperBase<T>::COOLCONF() { return REG(COOLCONF).sr; }
TT void TMC2130StepperBase<T>::COOLCONF(uint32_t input) {
	REG(COOLCONF).sr = input;
	SELF.write(ADR(COOLCONF), REG(COOLCONF).sr);
}

TT void TMC2130StepperBase<T>::semin(	uint8_t B )	{ SET_REG(semin);	}
TT void TMC2130StepperBase<T>::seup(	uint8_t B )	{ SET_REG(seup);	}
TT void TMC2130StepperBase<T>::semax(	uint8_t B )	{ SET_REG(semax);	}
TT void TMC2130StepperBase<T>::sedn(	uint8_t B )	{ SET_REG(sedn);	}
TT void TMC2130StepperBase<T>::seimin(bool 	B )	{ SET_REG(seimin);	}
TT void TMC2130StepperBase<T>::sgt(	int8_t  B )	{ SET_REG(sgt);		}
TT void TMC2130StepperBase<T>::sfilt(	bool 	B )	{ SET_REG(sfilt);	}

TT uint8_t TMC2130StepperBase<T>::semin()	{ GET_REG(semin);	}
TT uint8_t TMC2130StepperBase<T>::seup()	{ GET_REG(seup);	}
TT uint8_t TMC2130StepperBase<T>::semax()	{ GET_REG(semax);	}
TT uint8_t TMC2130StepperBase<T>::sedn()	{ GET_REG(sedn);	}
TT bool 	TMC2130StepperBase<T>::seimin(){ GET_REG(seimin);	}
TT bool 	TMC2130StepperBase<T>::sfilt()	{ GET_REG(sfilt);	}

TT int8_t TMC2130StepperBase<T>::sgt() {
	// Two's complement in a 7bit value
	int8_t val = (REG(COOLCONF).sgt &  0x40) << 1; // Isolate sign bit
	val |= REG(COOLCONF).sgt & 0x7F;
	return val;
}
