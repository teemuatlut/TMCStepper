#include "TMCStepper.h"

// GCONF
uint32_t TMC5130Stepper::GCONF() { READ_REG(GCONF); }
void TMC5130Stepper::GCONF(uint32_t input) {
	GCONF_sr = input;
	WRITE_REG(GCONF);
}

void TMC5130Stepper::I_scale_analog(bool B)			{ MOD_REG(GCONF, I_SCALE_ANALOG);				}
void TMC5130Stepper::internal_Rsense(bool B)		{ MOD_REG(GCONF, INTERNAL_RSENSE);				}
void TMC5130Stepper::en_pwm_mode(bool B)			{ MOD_REG(GCONF, EN_PWM_MODE);					}
void TMC5130Stepper::enc_commutation(bool B)		{ MOD_REG(GCONF, ENC_COMMUTATION);				}
void TMC5130Stepper::shaft(bool B) 					{ MOD_REG(GCONF, SHAFT);						}
void TMC5130Stepper::diag0_error(bool B) 			{ MOD_REG(GCONF, DIAG0_ERROR);					}
void TMC5130Stepper::diag0_otpw(bool B) 			{ MOD_REG(GCONF, DIAG0_OTPW);					}
void TMC5130Stepper::diag0_stall(bool B) 			{ MOD_REG(GCONF, DIAG0_STALL);					}
void TMC5130Stepper::diag1_stall(bool B) 			{ MOD_REG(GCONF, DIAG1_STALL);					}
void TMC5130Stepper::diag1_index(bool B) 			{ MOD_REG(GCONF, DIAG1_INDEX);					}
void TMC5130Stepper::diag1_onstate(bool B) 			{ MOD_REG(GCONF, DIAG1_ONSTATE);				}
void TMC5130Stepper::diag1_steps_skipped(bool B) 	{ MOD_REG(GCONF, DIAG1_STEPS_SKIPPED);			}
void TMC5130Stepper::diag0_int_pushpull(bool B) 	{ MOD_REG(GCONF, DIAG0_INT_PUSHPULL);			}
void TMC5130Stepper::diag1_poscomp_pushpull(bool B) { MOD_REG(GCONF, DIAG1_POSCOMP_PUSHPULL);	}
void TMC5130Stepper::small_hysterisis(bool B) 		{ MOD_REG(GCONF, SMALL_HYSTERISIS);				}
void TMC5130Stepper::stop_enable(bool B) 			{ MOD_REG(GCONF, STOP_ENABLE);					}
void TMC5130Stepper::direct_mode(bool B) 			{ MOD_REG(GCONF, DIRECT_MODE);					}

bool TMC5130Stepper::I_scale_analog()				{ GET_BYTE(GCONF, I_SCALE_ANALOG);				}
bool TMC5130Stepper::internal_Rsense()				{ GET_BYTE(GCONF, INTERNAL_RSENSE);				}
bool TMC5130Stepper::en_pwm_mode()					{ GET_BYTE(GCONF, EN_PWM_MODE);					}
bool TMC5130Stepper::enc_commutation()				{ GET_BYTE(GCONF, ENC_COMMUTATION);				}
bool TMC5130Stepper::shaft() 						{ GET_BYTE(GCONF, SHAFT);						}
bool TMC5130Stepper::diag0_error() 					{ GET_BYTE(GCONF, DIAG0_ERROR);					}
bool TMC5130Stepper::diag0_otpw() 					{ GET_BYTE(GCONF, DIAG0_OTPW);					}
bool TMC5130Stepper::diag0_stall() 					{ GET_BYTE(GCONF, DIAG0_STALL);					}
bool TMC5130Stepper::diag1_stall() 					{ GET_BYTE(GCONF, DIAG1_STALL);					}
bool TMC5130Stepper::diag1_index() 					{ GET_BYTE(GCONF, DIAG1_INDEX);					}
bool TMC5130Stepper::diag1_onstate() 				{ GET_BYTE(GCONF, DIAG1_ONSTATE);				}
bool TMC5130Stepper::diag1_steps_skipped() 			{ GET_BYTE(GCONF, DIAG1_STEPS_SKIPPED);			}
bool TMC5130Stepper::diag0_int_pushpull() 			{ GET_BYTE(GCONF, DIAG0_INT_PUSHPULL);			}
bool TMC5130Stepper::diag1_poscomp_pushpull() 		{ GET_BYTE(GCONF, DIAG1_POSCOMP_PUSHPULL);	}
bool TMC5130Stepper::small_hysterisis() 			{ GET_BYTE(GCONF, SMALL_HYSTERISIS);			}
bool TMC5130Stepper::stop_enable() 					{ GET_BYTE(GCONF, STOP_ENABLE);					}
bool TMC5130Stepper::direct_mode() 					{ GET_BYTE(GCONF, DIRECT_MODE);					}

/*
bit 18 not implemented:
test_mode 0: 
Normal operation 1:
Enable analog test output on pin DCO. IHOLD[1..0] selects the function of DCO: 
0…2: T120, DAC, VDDH Attention:
Not for user, set to 0 for normal operation! 
*/
