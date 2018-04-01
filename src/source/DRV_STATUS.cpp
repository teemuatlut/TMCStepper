#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define GET_REG(SETTING) DRV_STATUS(); return DRV_STATUS_register.cfg.opt.SETTING;

uint32_t TMC2130Stepper::DRV_STATUS() {
	DRV_STATUS_register.cfg.sr = READ_REG(DRV_STATUS);
	return DRV_STATUS_register.cfg.sr;
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
