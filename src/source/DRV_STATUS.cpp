#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define GET_REG(SETTING) DRV_STATUS(); return DRV_STATUS_register.SETTING;

uint32_t TMC2130Stepper::DRV_STATUS() {
	DRV_STATUS_register.sr = read(DRV_STATUS_address);
	return DRV_STATUS_register.sr;
}

uint16_t TMC2130Stepper::sg_result(){ GET_REG(sg_result); 	}
bool TMC2130Stepper::fsactive()		{ GET_REG(fsactive); 	}
uint8_t TMC2130Stepper::cs_actual()	{ GET_REG(cs_actual); 	}
bool TMC2130Stepper::stallguard()	{ GET_REG(stallGuard); 	}
bool TMC2130Stepper::ot()			{ GET_REG(ot); 			}
bool TMC2130Stepper::otpw()			{ GET_REG(otpw); 		}
bool TMC2130Stepper::s2ga()			{ GET_REG(s2ga); 		}
bool TMC2130Stepper::s2gb()			{ GET_REG(s2gb); 		}
bool TMC2130Stepper::ola()			{ GET_REG(ola); 		}
bool TMC2130Stepper::olb()			{ GET_REG(olb); 		}
bool TMC2130Stepper::stst()			{ GET_REG(stst); 		}

uint32_t TMC2208Stepper::DRV_STATUS() {
	if (write_only) return 0;
	DRV_STATUS_register.sr = read(DRV_STATUS_address);
	return DRV_STATUS_register.sr;
}

bool 		TMC2208Stepper::otpw()		{ GET_REG(otpw); 		}
bool 		TMC2208Stepper::ot() 		{ GET_REG(ot); 	 		}
bool 		TMC2208Stepper::s2ga() 		{ GET_REG(s2ga); 		}
bool 		TMC2208Stepper::s2gb() 		{ GET_REG(s2gb); 		}
bool 		TMC2208Stepper::s2vsa() 	{ GET_REG(s2vsa);		}
bool 		TMC2208Stepper::s2vsb() 	{ GET_REG(s2vsb);		}
bool 		TMC2208Stepper::ola() 		{ GET_REG(ola);  		}
bool 		TMC2208Stepper::olb() 		{ GET_REG(olb);  		}
bool 		TMC2208Stepper::t120() 		{ GET_REG(t120); 		}
bool 		TMC2208Stepper::t143() 		{ GET_REG(t143); 		}
bool 		TMC2208Stepper::t150() 		{ GET_REG(t150); 		}
bool 		TMC2208Stepper::t157() 		{ GET_REG(t157); 		}
uint16_t 	TMC2208Stepper::cs_actual()	{ GET_REG(cs_actual);	}
bool 		TMC2208Stepper::stealth() 	{ GET_REG(stealth);		}
bool 		TMC2208Stepper::stst() 		{ GET_REG(stst); 		}
