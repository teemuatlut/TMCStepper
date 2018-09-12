#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(SHORT_CONF).SETTING = B; SELF.write(ADR(SHORT_CONF), REG(SHORT_CONF).sr); }while(0)
#define GET_REG(SETTING) return REG(SHORT_CONF).SETTING

TT uint32_t TMC5160StepperBase<T>::SHORT_CONF() { return REG(SHORT_CONF).sr; }
TT void TMC5160StepperBase<T>::SHORT_CONF(uint32_t input) {
	REG(SHORT_CONF).sr = input;
	SELF.write(ADR(SHORT_CONF), REG(SHORT_CONF).sr);
}

TT void TMC5160StepperBase<T>::s2vs_level(uint8_t B)	{ SET_REG(s2vs_level);	}
TT void TMC5160StepperBase<T>::s2g_level(uint8_t B)	{ SET_REG(s2g_level);	}
TT void TMC5160StepperBase<T>::shortfilter(uint8_t B)	{ SET_REG(shortfilter);	}
TT void TMC5160StepperBase<T>::shortdelay(bool B)		{ SET_REG(shortdelay);	}
TT uint8_t TMC5160StepperBase<T>::s2vs_level()		{ GET_REG(s2vs_level);	}
TT uint8_t TMC5160StepperBase<T>::s2g_level()			{ GET_REG(s2g_level);	}
TT uint8_t TMC5160StepperBase<T>::shortfilter()		{ GET_REG(shortfilter);	}
TT bool TMC5160StepperBase<T>::shortdelay()			{ GET_REG(shortdelay);	}
