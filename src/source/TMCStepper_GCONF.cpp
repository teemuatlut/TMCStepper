#include "TMCStepper.h"

// GCONF
uint32_t TMCStepper::GCONF() { READ_REG(GCONF); }
void TMCStepper::GCONF(uint32_t input) {
	GCONF_sr = input;
	WRITE_REG(GCONF);
}

void TMCStepper::I_scale_analog(bool B)			{ MOD_REG(GCONF, I_SCALE_ANALOG);				}
void TMCStepper::internal_Rsense(bool B)		{ MOD_REG(GCONF, INTERNAL_RSENSE);				}
void TMCStepper::en_pwm_mode(bool B)			{ MOD_REG(GCONF, EN_PWM_MODE);					}
void TMCStepper::enc_commutation(bool B)		{ MOD_REG(GCONF, ENC_COMMUTATION);				}
void TMCStepper::shaft(bool B) 					{ MOD_REG(GCONF, SHAFT);						}
void TMCStepper::diag0_error(bool B) 			{ MOD_REG(GCONF, DIAG0_ERROR);					}
void TMCStepper::diag0_otpw(bool B) 			{ MOD_REG(GCONF, DIAG0_OTPW);					}
void TMCStepper::diag0_stall(bool B) 			{ MOD_REG(GCONF, DIAG0_STALL);					}
void TMCStepper::diag1_stall(bool B) 			{ MOD_REG(GCONF, DIAG1_STALL);					}
void TMCStepper::diag1_index(bool B) 			{ MOD_REG(GCONF, DIAG1_INDEX);					}
void TMCStepper::diag1_onstate(bool B) 			{ MOD_REG(GCONF, DIAG1_ONSTATE);				}
void TMCStepper::diag1_steps_skipped(bool B) 	{ MOD_REG(GCONF, DIAG1_STEPS_SKIPPED);			}
void TMCStepper::diag0_int_pushpull(bool B) 	{ MOD_REG(GCONF, DIAG0_INT_PUSHPULL);			}
void TMCStepper::diag1_poscomp_pushpull(bool B) { MOD_REG(GCONF, DIAG1_POSCOMP_PUSHPULL);	}
void TMCStepper::small_hysterisis(bool B) 		{ MOD_REG(GCONF, SMALL_HYSTERISIS);				}
void TMCStepper::stop_enable(bool B) 			{ MOD_REG(GCONF, STOP_ENABLE);					}
void TMCStepper::direct_mode(bool B) 			{ MOD_REG(GCONF, DIRECT_MODE);					}

bool TMCStepper::I_scale_analog()				{ GET_BYTE(GCONF, I_SCALE_ANALOG);				}
bool TMCStepper::internal_Rsense()				{ GET_BYTE(GCONF, INTERNAL_RSENSE);				}
bool TMCStepper::en_pwm_mode()					{ GET_BYTE(GCONF, EN_PWM_MODE);					}
bool TMCStepper::enc_commutation()				{ GET_BYTE(GCONF, ENC_COMMUTATION);				}
bool TMCStepper::shaft() 						{ GET_BYTE(GCONF, SHAFT);						}
bool TMCStepper::diag0_error() 					{ GET_BYTE(GCONF, DIAG0_ERROR);					}
bool TMCStepper::diag0_otpw() 					{ GET_BYTE(GCONF, DIAG0_OTPW);					}
bool TMCStepper::diag0_stall() 					{ GET_BYTE(GCONF, DIAG0_STALL);					}
bool TMCStepper::diag1_stall() 					{ GET_BYTE(GCONF, DIAG1_STALL);					}
bool TMCStepper::diag1_index() 					{ GET_BYTE(GCONF, DIAG1_INDEX);					}
bool TMCStepper::diag1_onstate() 				{ GET_BYTE(GCONF, DIAG1_ONSTATE);				}
bool TMCStepper::diag1_steps_skipped() 			{ GET_BYTE(GCONF, DIAG1_STEPS_SKIPPED);			}
bool TMCStepper::diag0_int_pushpull() 			{ GET_BYTE(GCONF, DIAG0_INT_PUSHPULL);			}
bool TMCStepper::diag1_poscomp_pushpull() 		{ GET_BYTE(GCONF, DIAG1_POSCOMP_PUSHPULL);	}
bool TMCStepper::small_hysterisis() 			{ GET_BYTE(GCONF, SMALL_HYSTERISIS);			}
bool TMCStepper::stop_enable() 					{ GET_BYTE(GCONF, STOP_ENABLE);					}
bool TMCStepper::direct_mode() 					{ GET_BYTE(GCONF, DIRECT_MODE);					}

/*
bit 18 not implemented:
test_mode 0: 
Normal operation 1:
Enable analog test output on pin DCO. IHOLD[1..0] selects the function of DCO: 
0…2: T120, DAC, VDDH Attention:
Not for user, set to 0 for normal operation! 
*/
