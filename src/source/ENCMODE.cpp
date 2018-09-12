#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(ENCMODE).SETTING = B; SELF.write(ADR(ENCMODE), REG(ENCMODE).sr); }while(0)
#define GET_REG(SETTING) do{ ENCMODE(); return REG(ENCMODE).SETTING; }while(0)

// ENCMODE
TT uint32_t TMC5130StepperBase<T>::ENCMODE() {
	REG(ENCMODE).sr = SELF.read(ADR(ENCMODE));
	return REG(ENCMODE).sr;
}
TT void TMC5130StepperBase<T>::ENCMODE(uint32_t input) {
	REG(ENCMODE).sr = input;
	SELF.write(ADR(ENCMODE), REG(ENCMODE).sr);
}

TT void TMC5130StepperBase<T>::pol_a(bool B)			{ SET_REG(pol_a);			}
TT void TMC5130StepperBase<T>::pol_b(bool B)			{ SET_REG(pol_b);			}
TT void TMC5130StepperBase<T>::pol_n(bool B)			{ SET_REG(pol_n);			}
TT void TMC5130StepperBase<T>::ignore_ab(bool B)		{ SET_REG(ignore_ab);		}
TT void TMC5130StepperBase<T>::clr_cont(bool B)		{ SET_REG(clr_cont);		}
TT void TMC5130StepperBase<T>::clr_once(bool B)		{ SET_REG(clr_once);		}
TT void TMC5130StepperBase<T>::pos_edge(bool B)		{ SET_REG(pos_edge);		}
TT void TMC5130StepperBase<T>::neg_edge(bool B)		{ SET_REG(neg_edge);		}
TT void TMC5130StepperBase<T>::clr_enc_x(bool B)		{ SET_REG(clr_enc_x);		}
TT void TMC5130StepperBase<T>::latch_x_act(bool B)	{ SET_REG(latch_x_act);		}
TT void TMC5130StepperBase<T>::enc_sel_decimal(bool B){ SET_REG(enc_sel_decimal);	}

TT bool TMC5130StepperBase<T>::pol_a()			{ GET_REG(pol_a);			}
TT bool TMC5130StepperBase<T>::pol_b()			{ GET_REG(pol_b);			}
TT bool TMC5130StepperBase<T>::pol_n()			{ GET_REG(pol_n);			}
TT bool TMC5130StepperBase<T>::ignore_ab()		{ GET_REG(ignore_ab);		}
TT bool TMC5130StepperBase<T>::clr_cont()			{ GET_REG(clr_cont);		}
TT bool TMC5130StepperBase<T>::clr_once()			{ GET_REG(clr_once);		}
TT bool TMC5130StepperBase<T>::pos_edge()			{ GET_REG(pos_edge);		}
TT bool TMC5130StepperBase<T>::neg_edge()			{ GET_REG(neg_edge);		}
TT bool TMC5130StepperBase<T>::clr_enc_x()		{ GET_REG(clr_enc_x);		}
TT bool TMC5130StepperBase<T>::latch_x_act()		{ GET_REG(latch_x_act);		}
TT bool TMC5130StepperBase<T>::enc_sel_decimal()	{ GET_REG(enc_sel_decimal);	}
