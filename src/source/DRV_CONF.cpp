#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(DRV_CONF).SETTING = B; SELF.write(ADR(DRV_CONF), REG(DRV_CONF).sr); }while(0)
#define GET_REG(SETTING) return REG(DRV_CONF).SETTING

// W: DRV_CONF
TT uint32_t TMC5160StepperBase<T>::DRV_CONF() { return REG(DRV_CONF).sr; }
TT void TMC5160StepperBase<T>::DRV_CONF(uint32_t input) {
	REG(DRV_CONF).sr = input;
	SELF.write(ADR(DRV_CONF), REG(DRV_CONF).sr);
}

TT void TMC5160StepperBase<T>::bbmtime(			uint8_t B)	{ SET_REG(bbmtime);			}
TT void TMC5160StepperBase<T>::bbmclks(			uint8_t B)	{ SET_REG(bbmclks);			}
TT void TMC5160StepperBase<T>::otselect(		uint8_t B)	{ SET_REG(otselect);		}
TT void TMC5160StepperBase<T>::drvstrength(	uint8_t B)	{ SET_REG(drvstrength);	}
TT void TMC5160StepperBase<T>::filt_isense(	uint8_t B)	{ SET_REG(filt_isense);	}
TT uint8_t TMC5160StepperBase<T>::bbmtime()			{ GET_REG(bbmtime);			}
TT uint8_t TMC5160StepperBase<T>::bbmclks()			{ GET_REG(bbmclks);			}
TT uint8_t TMC5160StepperBase<T>::otselect()		{ GET_REG(otselect);		}
TT uint8_t TMC5160StepperBase<T>::drvstrength()	{ GET_REG(drvstrength);	}
TT uint8_t TMC5160StepperBase<T>::filt_isense()	{ GET_REG(filt_isense);	}
