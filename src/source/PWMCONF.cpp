#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(PWMCONF).SETTING = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }while(0)
#define GET_REG(SETTING) return REG(PWMCONF).SETTING

// PWMCONF
TT uint32_t TMC2130StepperBase<T>::PWMCONF() { return REG(PWMCONF).sr; }
TT void TMC2130StepperBase<T>::PWMCONF(uint32_t input) {
	REG(PWMCONF).sr = input;
	SELF.write(ADR(PWMCONF), REG(PWMCONF).sr);
}

TT void TMC2130StepperBase<T>::pwm_ampl(		uint8_t B )	{ SET_REG(pwm_ampl);		}
TT void TMC2130StepperBase<T>::pwm_grad(		uint8_t B )	{ SET_REG(pwm_grad);		}
TT void TMC2130StepperBase<T>::pwm_freq(		uint8_t B )	{ SET_REG(pwm_freq);		}
TT void TMC2130StepperBase<T>::pwm_autoscale(	bool 	B )	{ SET_REG(pwm_autoscale);	}
TT void TMC2130StepperBase<T>::pwm_symmetric(	bool 	B )	{ SET_REG(pwm_symmetric);	}
TT void TMC2130StepperBase<T>::freewheel(		uint8_t B )	{ SET_REG(freewheel);		}

TT uint8_t TMC2130StepperBase<T>::pwm_ampl()		{ GET_REG(pwm_ampl);		}
TT uint8_t TMC2130StepperBase<T>::pwm_grad()		{ GET_REG(pwm_grad);		}
TT uint8_t TMC2130StepperBase<T>::pwm_freq()		{ GET_REG(pwm_freq);		}
TT bool 	TMC2130StepperBase<T>::pwm_autoscale()	{ GET_REG(pwm_autoscale);	}
TT bool 	TMC2130StepperBase<T>::pwm_symmetric()	{ GET_REG(pwm_symmetric);	}
TT uint8_t TMC2130StepperBase<T>::freewheel()		{ GET_REG(freewheel);		}

TT uint32_t TMC2208StepperBase<T>::PWMCONF() {
	if (write_only) return REG(PWMCONF).sr;
	REG(PWMCONF).sr = SELF.read(ADR(PWMCONF));
	return REG(PWMCONF).sr;
}
TT void TMC2208StepperBase<T>::PWMCONF(uint32_t input) {
	REG(PWMCONF).sr = input;
	SELF.write(ADR(PWMCONF), REG(PWMCONF).sr);
}

TT void TMC2208StepperBase<T>::pwm_ofs		( uint8_t B ) { REG(PWMCONF).pwm_ofs = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::pwm_grad		( uint8_t B ) { REG(PWMCONF).pwm_grad = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::pwm_freq		( uint8_t B ) { REG(PWMCONF).pwm_freq = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::pwm_autoscale	( bool 	  B ) { REG(PWMCONF).pwm_autoscale = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::pwm_autograd	( bool    B ) { REG(PWMCONF).pwm_autograd = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::freewheel		( uint8_t B ) { REG(PWMCONF).freewheel = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::pwm_reg		( uint8_t B ) { REG(PWMCONF).pwm_reg = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }
TT void TMC2208StepperBase<T>::pwm_lim		( uint8_t B ) { REG(PWMCONF).pwm_lim = B; SELF.write(ADR(PWMCONF), REG(PWMCONF).sr); }

TT uint8_t TMC2208StepperBase<T>::pwm_ofs()		{ PWMCONF(); return REG(PWMCONF).pwm_ofs;		}
TT uint8_t TMC2208StepperBase<T>::pwm_grad()		{ PWMCONF(); return REG(PWMCONF).pwm_grad;		}
TT uint8_t TMC2208StepperBase<T>::pwm_freq()		{ PWMCONF(); return REG(PWMCONF).pwm_freq;		}
TT bool 	TMC2208StepperBase<T>::pwm_autoscale()	{ PWMCONF(); return REG(PWMCONF).pwm_autoscale;	}
TT bool 	TMC2208StepperBase<T>::pwm_autograd()	{ PWMCONF(); return REG(PWMCONF).pwm_autograd;	}
TT uint8_t TMC2208StepperBase<T>::freewheel()		{ PWMCONF(); return REG(PWMCONF).freewheel;		}
TT uint8_t TMC2208StepperBase<T>::pwm_reg()		{ PWMCONF(); return REG(PWMCONF).pwm_reg;		}
TT uint8_t TMC2208StepperBase<T>::pwm_lim()		{ PWMCONF(); return REG(PWMCONF).pwm_lim;		}
