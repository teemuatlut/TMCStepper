#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(GCONF).SETTING = B; SELF.write(ADR(GCONF), REG(GCONF).sr); }while(0)
#define GET_REG(SETTING) do{ this->GCONF(); return REG(GCONF).SETTING; }while(0)

// GCONF
TT uint32_t TMC2130StepperBase<T>::GCONF() {
	REG(GCONF).sr = SELF.read(ADR(GCONF));
	return REG(GCONF).sr;
}
TT void TMC2130StepperBase<T>::GCONF(uint32_t input) {
	REG(GCONF).sr = input;
	SELF.write(ADR(GCONF), REG(GCONF).sr);
}

TT void TMC2130StepperBase<T>::I_scale_analog(bool B)			{ SET_REG(i_scale_analog);				}
TT void TMC2130StepperBase<T>::internal_Rsense(bool B)		{ SET_REG(internal_rsense);				}
TT void TMC2130StepperBase<T>::en_pwm_mode(bool B)				{ SET_REG(en_pwm_mode);						}
TT void TMC2130StepperBase<T>::enc_commutation(bool B)		{ SET_REG(enc_commutation);				}
TT void TMC2130StepperBase<T>::shaft(bool B)							{ SET_REG(shaft);									}
TT void TMC2130StepperBase<T>::diag0_error(bool B)				{ SET_REG(diag0_error);						}
TT void TMC2130StepperBase<T>::diag0_otpw(bool B)					{ SET_REG(diag0_otpw);						}
TT void TMC2130StepperBase<T>::diag0_stall(bool B)				{ SET_REG(diag0_stall);						}
TT void TMC2130StepperBase<T>::diag1_stall(bool B)				{ SET_REG(diag1_stall);						}
TT void TMC2130StepperBase<T>::diag1_index(bool B)				{ SET_REG(diag1_index);						}
TT void TMC2130StepperBase<T>::diag1_onstate(bool B)			{ SET_REG(diag1_onstate);					}
TT void TMC2130StepperBase<T>::diag1_steps_skipped(bool B){ SET_REG(diag1_steps_skipped);		}
TT void TMC2130StepperBase<T>::diag0_int_pushpull(bool B)	{ SET_REG(diag0_int_pushpull);		}
TT void TMC2130StepperBase<T>::diag1_pushpull(bool B)			{ SET_REG(diag1_poscomp_pushpull);}
TT void TMC2130StepperBase<T>::small_hysteresis(bool B)		{ SET_REG(small_hysteresis);			}
TT void TMC2130StepperBase<T>::stop_enable(bool B)				{ SET_REG(stop_enable);						}
TT void TMC2130StepperBase<T>::direct_mode(bool B)				{ SET_REG(direct_mode);						}

TT bool TMC2130StepperBase<T>::I_scale_analog()						{ GET_REG(i_scale_analog);				}
TT bool TMC2130StepperBase<T>::internal_Rsense()					{ GET_REG(internal_rsense);				}
TT bool TMC2130StepperBase<T>::en_pwm_mode()							{ GET_REG(en_pwm_mode);						}
TT bool TMC2130StepperBase<T>::enc_commutation()					{ GET_REG(enc_commutation);				}
TT bool TMC2130StepperBase<T>::shaft()										{ GET_REG(shaft);									}
TT bool TMC2130StepperBase<T>::diag0_error()							{ GET_REG(diag0_error);						}
TT bool TMC2130StepperBase<T>::diag0_otpw()								{ GET_REG(diag0_otpw);						}
TT bool TMC2130StepperBase<T>::diag0_stall()							{ GET_REG(diag0_stall);						}
TT bool TMC2130StepperBase<T>::diag1_stall()							{ GET_REG(diag1_stall);						}
TT bool TMC2130StepperBase<T>::diag1_index()							{ GET_REG(diag1_index);						}
TT bool TMC2130StepperBase<T>::diag1_onstate()						{ GET_REG(diag1_onstate);					}
TT bool TMC2130StepperBase<T>::diag1_steps_skipped()			{ GET_REG(diag1_steps_skipped);		}
TT bool TMC2130StepperBase<T>::diag0_int_pushpull()				{ GET_REG(diag0_int_pushpull);		}
TT bool TMC2130StepperBase<T>::diag1_pushpull()		 				{ GET_REG(diag1_poscomp_pushpull);}
TT bool TMC2130StepperBase<T>::small_hysteresis()					{ GET_REG(small_hysteresis);			}
TT bool TMC2130StepperBase<T>::stop_enable()							{ GET_REG(stop_enable);						}
TT bool TMC2130StepperBase<T>::direct_mode()							{ GET_REG(direct_mode);						}

/*
bit 18 not implemented:
test_mode 0:
Normal operation 1:
Enable analog test output on pin DCO. IHOLD[1..0] selects the function of DCO:
0…2: T120, DAC, VDDH Attention:
Not for user, set to 0 for normal operation!
*/

TT void TMC5160StepperBase<T>::recalibrate(bool B)		{ SET_REG(recalibrate);			}
TT void TMC5160StepperBase<T>::faststandstill(bool B)	{ SET_REG(faststandstill);	}
TT void TMC5160StepperBase<T>::multistep_filt(bool B)	{ SET_REG(multistep_filt);	}
TT bool TMC5160StepperBase<T>::recalibrate()					{ GET_REG(recalibrate);			}
TT bool TMC5160StepperBase<T>::faststandstill()				{ GET_REG(faststandstill);	}
TT bool TMC5160StepperBase<T>::multistep_filt()				{ GET_REG(multistep_filt);	}

TT uint32_t TMC2208StepperBase<T>::GCONF() {
	if (write_only) return REG(GCONF).sr;
	REG(GCONF).sr = SELF.read(ADR(GCONF));
	return REG(GCONF).sr;
}
TT void TMC2208StepperBase<T>::GCONF(uint32_t input) {
	REG(GCONF).sr = input;
	SELF.write(ADR(GCONF), REG(GCONF).sr);
}

TT void TMC2208StepperBase<T>::I_scale_analog(bool B)		{ SET_REG(i_scale_analog);	}
TT void TMC2208StepperBase<T>::internal_Rsense(bool B)	{ SET_REG(internal_rsense);	}
TT void TMC2208StepperBase<T>::en_spreadCycle(bool B)		{ SET_REG(en_spreadcycle);	}
TT void TMC2208StepperBase<T>::shaft(bool B) 						{ SET_REG(shaft);						}
TT void TMC2208StepperBase<T>::index_otpw(bool B)				{ SET_REG(index_otpw);			}
TT void TMC2208StepperBase<T>::index_step(bool B)				{ SET_REG(index_step);			}
TT void TMC2208StepperBase<T>::pdn_disable(bool B)			{ SET_REG(pdn_disable);			}
TT void TMC2208StepperBase<T>::mstep_reg_select(bool B)	{ SET_REG(mstep_reg_select);}
TT void TMC2208StepperBase<T>::multistep_filt(bool B)		{ SET_REG(multistep_filt);	}

TT bool TMC2208StepperBase<T>::I_scale_analog()		{ GET_REG(i_scale_analog);	}
TT bool TMC2208StepperBase<T>::internal_Rsense()	{ GET_REG(internal_rsense);	}
TT bool TMC2208StepperBase<T>::en_spreadCycle()		{ GET_REG(en_spreadcycle);	}
TT bool TMC2208StepperBase<T>::shaft()						{ GET_REG(shaft);						}
TT bool TMC2208StepperBase<T>::index_otpw()				{ GET_REG(index_otpw);			}
TT bool TMC2208StepperBase<T>::index_step()				{ GET_REG(index_step);			}
TT bool TMC2208StepperBase<T>::pdn_disable()			{ GET_REG(pdn_disable);			}
TT bool TMC2208StepperBase<T>::mstep_reg_select()	{ GET_REG(mstep_reg_select);}
TT bool TMC2208StepperBase<T>::multistep_filt()		{ GET_REG(multistep_filt);	}
