#include "TMCStepper.h"

uint32_t TMC2208Stepper::DRV_STATUS() {
	return read(TMC2208_n::DRV_STATUS_t::address);
}

bool 		TMC2208Stepper::otpw()		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.otpw; 		}
bool 		TMC2208Stepper::ot() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.ot;  		}
bool 		TMC2208Stepper::s2ga() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.s2ga; 		}
bool 		TMC2208Stepper::s2gb() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.s2gb; 		}
bool 		TMC2208Stepper::s2vsa() 	{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.s2vsa;		}
bool 		TMC2208Stepper::s2vsb() 	{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.s2vsb;		}
bool 		TMC2208Stepper::ola() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.ola;  		}
bool 		TMC2208Stepper::olb() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.olb;  		}
bool 		TMC2208Stepper::t120() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.t120; 		}
bool 		TMC2208Stepper::t143() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.t143; 		}
bool 		TMC2208Stepper::t150() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.t150; 		}
bool 		TMC2208Stepper::t157() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.t157; 		}
uint16_t 	TMC2208Stepper::cs_actual()	{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.cs_actual;	}
bool 		TMC2208Stepper::stealth() 	{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.stealth;	}
bool 		TMC2208Stepper::stst() 		{ return TMC2208_n::DRV_STATUS_t{ DRV_STATUS() }.stst; 		}
