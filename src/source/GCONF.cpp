#include "TMCStepper.h"

// GCONF
uint32_t TMC2130Stepper::GCONF() {
	return read(GCONF_register.address);
}
void TMC2130Stepper::GCONF(uint32_t input) {
	GCONF_register.sr = input;
	write(GCONF_register.address, GCONF_register.sr);
}

void TMC2130Stepper::I_scale_analog(bool B)			{ GCONF_register.i_scale_analog = B;			write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::internal_Rsense(bool B)		{ GCONF_register.internal_rsense = B;			write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::en_pwm_mode(bool B)			{ GCONF_register.en_pwm_mode = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::enc_commutation(bool B)		{ GCONF_register.enc_commutation = B;			write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::shaft(bool B) 					{ GCONF_register.shaft = B;						write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag0_error(bool B) 			{ GCONF_register.diag0_error = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag0_otpw(bool B) 			{ GCONF_register.diag0_otpw = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag0_stall(bool B) 			{ GCONF_register.diag0_stall = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag1_stall(bool B) 			{ GCONF_register.diag1_stall = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag1_index(bool B) 			{ GCONF_register.diag1_index = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag1_onstate(bool B) 			{ GCONF_register.diag1_onstate = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag1_steps_skipped(bool B) 	{ GCONF_register.diag1_steps_skipped = B;		write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag0_int_pushpull(bool B) 	{ GCONF_register.diag0_int_pushpull = B;		write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::diag1_pushpull(bool B) 		{ GCONF_register.diag1_poscomp_pushpull = B;	write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::small_hysteresis(bool B) 		{ GCONF_register.small_hysteresis = B;			write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::stop_enable(bool B) 			{ GCONF_register.stop_enable = B;				write(GCONF_register.address, GCONF_register.sr); }
void TMC2130Stepper::direct_mode(bool B) 			{ GCONF_register.direct_mode = B;				write(GCONF_register.address, GCONF_register.sr); }

bool TMC2130Stepper::I_scale_analog()				{ return GCONF_t{ GCONF() }.i_scale_analog;			}
bool TMC2130Stepper::internal_Rsense()				{ return GCONF_t{ GCONF() }.internal_rsense;		}
bool TMC2130Stepper::en_pwm_mode()					{ return GCONF_t{ GCONF() }.en_pwm_mode;			}
bool TMC2130Stepper::enc_commutation()				{ return GCONF_t{ GCONF() }.enc_commutation;		}
bool TMC2130Stepper::shaft() 						{ return GCONF_t{ GCONF() }.shaft;					}
bool TMC2130Stepper::diag0_error() 					{ return GCONF_t{ GCONF() }.diag0_error;			}
bool TMC2130Stepper::diag0_otpw() 					{ return GCONF_t{ GCONF() }.diag0_otpw;				}
bool TMC2130Stepper::diag0_stall() 					{ return GCONF_t{ GCONF() }.diag0_stall;			}
bool TMC2130Stepper::diag1_stall() 					{ return GCONF_t{ GCONF() }.diag1_stall;			}
bool TMC2130Stepper::diag1_index() 					{ return GCONF_t{ GCONF() }.diag1_index;			}
bool TMC2130Stepper::diag1_onstate() 				{ return GCONF_t{ GCONF() }.diag1_onstate;			}
bool TMC2130Stepper::diag1_steps_skipped() 			{ return GCONF_t{ GCONF() }.diag1_steps_skipped;	}
bool TMC2130Stepper::diag0_int_pushpull() 			{ return GCONF_t{ GCONF() }.diag0_int_pushpull;		}
bool TMC2130Stepper::diag1_pushpull()		 		{ return GCONF_t{ GCONF() }.diag1_poscomp_pushpull;	}
bool TMC2130Stepper::small_hysteresis() 			{ return GCONF_t{ GCONF() }.small_hysteresis;		}
bool TMC2130Stepper::stop_enable() 					{ return GCONF_t{ GCONF() }.stop_enable;			}
bool TMC2130Stepper::direct_mode() 					{ return GCONF_t{ GCONF() }.direct_mode;			}

/*
bit 18 not implemented:
test_mode 0:
Normal operation 1:
Enable analog test output on pin DCO. IHOLD[1..0] selects the function of DCO:
0…2: T120, DAC, VDDH Attention:
Not for user, set to 0 for normal operation!
*/

void TMC5160Stepper::recalibrate(bool B)			{ GCONF_register.recalibrate = B; 	 write(GCONF_register.address, GCONF_register.sr); }
void TMC5160Stepper::faststandstill(bool B)			{ GCONF_register.faststandstill = B; write(GCONF_register.address, GCONF_register.sr); }
void TMC5160Stepper::multistep_filt(bool B)			{ GCONF_register.multistep_filt = B; write(GCONF_register.address, GCONF_register.sr); }
bool TMC5160Stepper::recalibrate()					{ return GCONF_t{ GCONF() }.recalibrate; 	}
bool TMC5160Stepper::faststandstill()				{ return GCONF_t{ GCONF() }.faststandstill; }
bool TMC5160Stepper::multistep_filt()				{ return GCONF_t{ GCONF() }.multistep_filt; }

uint16_t TMC2208Stepper::GCONF() {
	return read(GCONF_register.address);
}
void TMC2208Stepper::GCONF(uint16_t input) {
	GCONF_register.sr = input;
	write(GCONF_register.address, GCONF_register.sr);
}

void TMC2208Stepper::I_scale_analog(bool B)		{ GCONF_register.i_scale_analog = B; 	write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::internal_Rsense(bool B)	{ GCONF_register.internal_rsense = B; 	write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::en_spreadCycle(bool B)		{ GCONF_register.en_spreadcycle = B; 	write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::shaft(bool B) 				{ GCONF_register.shaft = B; 			write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::index_otpw(bool B)			{ GCONF_register.index_otpw = B; 		write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::index_step(bool B)			{ GCONF_register.index_step = B; 		write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::pdn_disable(bool B)		{ GCONF_register.pdn_disable = B; 		write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::mstep_reg_select(bool B)	{ GCONF_register.mstep_reg_select = B; 	write(GCONF_register.address, GCONF_register.sr); }
void TMC2208Stepper::multistep_filt(bool B)		{ GCONF_register.multistep_filt = B; 	write(GCONF_register.address, GCONF_register.sr); }

bool TMC2208Stepper::I_scale_analog()	{ return TMC2208_n::GCONF_t{ GCONF() }.i_scale_analog;	}
bool TMC2208Stepper::internal_Rsense()	{ return TMC2208_n::GCONF_t{ GCONF() }.internal_rsense;	}
bool TMC2208Stepper::en_spreadCycle()	{ return TMC2208_n::GCONF_t{ GCONF() }.en_spreadcycle;	}
bool TMC2208Stepper::shaft()			{ return TMC2208_n::GCONF_t{ GCONF() }.shaft;			}
bool TMC2208Stepper::index_otpw()		{ return TMC2208_n::GCONF_t{ GCONF() }.index_otpw;		}
bool TMC2208Stepper::index_step()		{ return TMC2208_n::GCONF_t{ GCONF() }.index_step;		}
bool TMC2208Stepper::pdn_disable()		{ return TMC2208_n::GCONF_t{ GCONF() }.pdn_disable;		}
bool TMC2208Stepper::mstep_reg_select()	{ return TMC2208_n::GCONF_t{ GCONF() }.mstep_reg_select;}
bool TMC2208Stepper::multistep_filt()	{ return TMC2208_n::GCONF_t{ GCONF() }.multistep_filt;	}
