#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) GCONF_register.cfg.opt.SETTING = B; WRITE_REG(GCONF)
#define GET_REG(SETTING) GCONF(); return GCONF_register.cfg.opt.SETTING

// GCONF
uint32_t TMC2130Stepper::GCONF() {
	GCONF_register.cfg.sr = READ_REG(GCONF);
	return GCONF_register.cfg.sr;
}
void TMC2130Stepper::GCONF(uint32_t input) {
	GCONF_register.cfg.sr = input;
	WRITE_REG(GCONF);
}

void TMC2130Stepper::I_scale_analog(bool B)			{ SET_REG(i_scale_analog);			}
void TMC2130Stepper::internal_Rsense(bool B)		{ SET_REG(internal_rsense);			}
void TMC2130Stepper::en_pwm_mode(bool B)			{ SET_REG(en_pwm_mode);				}
void TMC2130Stepper::enc_commutation(bool B)		{ SET_REG(enc_commutation);			}
void TMC2130Stepper::shaft(bool B) 					{ SET_REG(shaft);					}
void TMC2130Stepper::diag0_error(bool B) 			{ SET_REG(diag0_error);				}
void TMC2130Stepper::diag0_otpw(bool B) 			{ SET_REG(diag0_otpw);				}
void TMC2130Stepper::diag0_stall(bool B) 			{ SET_REG(diag0_stall);				}
void TMC2130Stepper::diag1_stall(bool B) 			{ SET_REG(diag1_stall);				}
void TMC2130Stepper::diag1_index(bool B) 			{ SET_REG(diag1_index);				}
void TMC2130Stepper::diag1_onstate(bool B) 			{ SET_REG(diag1_onstate);			}
void TMC2130Stepper::diag1_steps_skipped(bool B) 	{ SET_REG(diag1_steps_skipped);		}
void TMC2130Stepper::diag0_int_pushpull(bool B) 	{ SET_REG(diag0_int_pushpull);		}
void TMC2130Stepper::diag1_pushpull(bool B) 		{ SET_REG(diag1_poscomp_pushpull);	}
void TMC2130Stepper::small_hysterisis(bool B) 		{ SET_REG(small_hysterisis);		}
void TMC2130Stepper::stop_enable(bool B) 			{ SET_REG(stop_enable);				}
void TMC2130Stepper::direct_mode(bool B) 			{ SET_REG(direct_mode);				}

bool TMC2130Stepper::I_scale_analog()				{ GET_REG(i_scale_analog);			}
bool TMC2130Stepper::internal_Rsense()				{ GET_REG(internal_rsense);			}
bool TMC2130Stepper::en_pwm_mode()					{ GET_REG(en_pwm_mode);				}
bool TMC2130Stepper::enc_commutation()				{ GET_REG(enc_commutation);			}
bool TMC2130Stepper::shaft() 						{ GET_REG(shaft);					}
bool TMC2130Stepper::diag0_error() 					{ GET_REG(diag0_error);				}
bool TMC2130Stepper::diag0_otpw() 					{ GET_REG(diag0_otpw);				}
bool TMC2130Stepper::diag0_stall() 					{ GET_REG(diag0_stall);				}
bool TMC2130Stepper::diag1_stall() 					{ GET_REG(diag1_stall);				}
bool TMC2130Stepper::diag1_index() 					{ GET_REG(diag1_index);				}
bool TMC2130Stepper::diag1_onstate() 				{ GET_REG(diag1_onstate);			}
bool TMC2130Stepper::diag1_steps_skipped() 			{ GET_REG(diag1_steps_skipped);		}
bool TMC2130Stepper::diag0_int_pushpull() 			{ GET_REG(diag0_int_pushpull);		}
bool TMC2130Stepper::diag1_pushpull()		 		{ GET_REG(diag1_poscomp_pushpull);	}
bool TMC2130Stepper::small_hysterisis() 			{ GET_REG(small_hysterisis);		}
bool TMC2130Stepper::stop_enable() 					{ GET_REG(stop_enable);				}
bool TMC2130Stepper::direct_mode() 					{ GET_REG(direct_mode);				}

/*
bit 18 not implemented:
test_mode 0: 
Normal operation 1:
Enable analog test output on pin DCO. IHOLD[1..0] selects the function of DCO: 
0…2: T120, DAC, VDDH Attention:
Not for user, set to 0 for normal operation! 
*/
