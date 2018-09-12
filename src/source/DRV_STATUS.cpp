#include "TMCStepper.h"
#include "TMC_DECL.h"

#define GET_REG(NS, SETTING) do{ NS::DRV_STATUS_t r{0}; r.sr = SELF.read(ADR(DRV_STATUS)); return r.SETTING; }while(0)

TT uint32_t TMC2130StepperBase<T>::DRV_STATUS() { return SELF.read(ADR(DRV_STATUS)); }

TT uint16_t TMC2130StepperBase<T>::sg_result(){ GET_REG(TMC2130_n, sg_result); 	}
TT bool TMC2130StepperBase<T>::fsactive()		{ GET_REG(TMC2130_n, fsactive); 	}
TT uint8_t TMC2130StepperBase<T>::cs_actual()	{ GET_REG(TMC2130_n, cs_actual); 	}
TT bool TMC2130StepperBase<T>::stallguard()	{ GET_REG(TMC2130_n, stallGuard); 	}
TT bool TMC2130StepperBase<T>::ot()			{ GET_REG(TMC2130_n, ot); 			}
TT bool TMC2130StepperBase<T>::otpw()			{ GET_REG(TMC2130_n, otpw); 		}
TT bool TMC2130StepperBase<T>::s2ga()			{ GET_REG(TMC2130_n, s2ga); 		}
TT bool TMC2130StepperBase<T>::s2gb()			{ GET_REG(TMC2130_n, s2gb); 		}
TT bool TMC2130StepperBase<T>::ola()			{ GET_REG(TMC2130_n, ola); 		}
TT bool TMC2130StepperBase<T>::olb()			{ GET_REG(TMC2130_n, olb); 		}
TT bool TMC2130StepperBase<T>::stst()			{ GET_REG(TMC2130_n, stst); 		}

TT uint32_t TMC2208StepperBase<T>::DRV_STATUS() {
	if (write_only) return 0;
	REG(DRV_STATUS).sr = SELF.read(ADR(DRV_STATUS));
	return REG(DRV_STATUS).sr;
}

TT bool TMC2208StepperBase<T>::otpw()		{ GET_REG(TMC2208_n, otpw); 		}
TT bool TMC2208StepperBase<T>::ot() 		{ GET_REG(TMC2208_n, ot); 	 		}
TT bool TMC2208StepperBase<T>::s2ga() 		{ GET_REG(TMC2208_n, s2ga); 		}
TT bool TMC2208StepperBase<T>::s2gb() 		{ GET_REG(TMC2208_n, s2gb); 		}
TT bool TMC2208StepperBase<T>::s2vsa() 	{ GET_REG(TMC2208_n, s2vsa);		}
TT bool TMC2208StepperBase<T>::s2vsb() 	{ GET_REG(TMC2208_n, s2vsb);		}
TT bool TMC2208StepperBase<T>::ola() 		{ GET_REG(TMC2208_n, ola);  		}
TT bool TMC2208StepperBase<T>::olb() 		{ GET_REG(TMC2208_n, olb);  		}
TT bool TMC2208StepperBase<T>::t120() 		{ GET_REG(TMC2208_n, t120); 		}
TT bool TMC2208StepperBase<T>::t143() 		{ GET_REG(TMC2208_n, t143); 		}
TT bool TMC2208StepperBase<T>::t150() 		{ GET_REG(TMC2208_n, t150); 		}
TT bool TMC2208StepperBase<T>::t157() 		{ GET_REG(TMC2208_n, t157); 		}
TT uint16_t TMC2208StepperBase<T>::cs_actual()	{ GET_REG(TMC2208_n, cs_actual);	}
TT bool TMC2208StepperBase<T>::stealth() 	{ GET_REG(TMC2208_n, stealth);		}
TT bool TMC2208StepperBase<T>::stst() 		{ GET_REG(TMC2208_n, stst); 		}
