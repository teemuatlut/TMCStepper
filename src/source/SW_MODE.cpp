#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(SW_MODE).SETTING = B; SELF.write(ADR(SW_MODE), REG(SW_MODE).sr); }while(0)
#define GET_REG(SETTING) do{ SW_MODE(); return REG(SW_MODE).SETTING; }while(0)

// SW_MODE
TT uint32_t TMC5130StepperBase<T>::SW_MODE() {
	REG(SW_MODE).sr = SELF.read(ADR(SW_MODE));
	return REG(SW_MODE).sr;
}
TT void TMC5130StepperBase<T>::SW_MODE(uint32_t input) {
	REG(SW_MODE).sr = input;
	SELF.write(ADR(SW_MODE), REG(SW_MODE).sr);
}

TT void TMC5130StepperBase<T>::stop_l_enable(bool B)		{ SET_REG(stop_l_enable);	}
TT void TMC5130StepperBase<T>::stop_r_enable(bool B)		{ SET_REG(stop_r_enable);	}
TT void TMC5130StepperBase<T>::pol_stop_l(bool B)				{ SET_REG(pol_stop_l);		}
TT void TMC5130StepperBase<T>::pol_stop_r(bool B)				{ SET_REG(pol_stop_r);		}
TT void TMC5130StepperBase<T>::swap_lr(bool B)					{ SET_REG(swap_lr);			}
TT void TMC5130StepperBase<T>::latch_l_active(bool B)		{ SET_REG(latch_l_active);	}
TT void TMC5130StepperBase<T>::latch_l_inactive(bool B)	{ SET_REG(latch_l_inactive);}
TT void TMC5130StepperBase<T>::latch_r_active(bool B)		{ SET_REG(latch_r_active);	}
TT void TMC5130StepperBase<T>::latch_r_inactive(bool B)	{ SET_REG(latch_r_inactive);}
TT void TMC5130StepperBase<T>::en_latch_encoder(bool B)	{ SET_REG(en_latch_encoder);}
TT void TMC5130StepperBase<T>::sg_stop(bool B)					{ SET_REG(sg_stop);			}
TT void TMC5130StepperBase<T>::en_softstop(bool B)			{ SET_REG(en_softstop);		}

TT bool TMC5130StepperBase<T>::stop_r_enable()		{ GET_REG(stop_r_enable);		}
TT bool TMC5130StepperBase<T>::pol_stop_l()				{ GET_REG(pol_stop_l);			}
TT bool TMC5130StepperBase<T>::pol_stop_r()				{ GET_REG(pol_stop_r);			}
TT bool TMC5130StepperBase<T>::swap_lr()					{ GET_REG(swap_lr);					}
TT bool TMC5130StepperBase<T>::latch_l_active()		{ GET_REG(latch_l_active);	}
TT bool TMC5130StepperBase<T>::latch_l_inactive()	{ GET_REG(latch_l_inactive);}
TT bool TMC5130StepperBase<T>::latch_r_active()		{ GET_REG(latch_r_active);	}
TT bool TMC5130StepperBase<T>::latch_r_inactive()	{ GET_REG(latch_r_inactive);}
TT bool TMC5130StepperBase<T>::en_latch_encoder()	{ GET_REG(en_latch_encoder);}
TT bool TMC5130StepperBase<T>::sg_stop()					{ GET_REG(sg_stop);					}
TT bool TMC5130StepperBase<T>::en_softstop()			{ GET_REG(en_softstop);			}
