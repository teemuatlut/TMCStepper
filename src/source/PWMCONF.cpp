#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define SET_REG(SETTING) PWMCONF_register.cfg.opt.SETTING = B; WRITE_REG(PWMCONF);
#define GET_REG(SETTING) return PWMCONF_register.cfg.opt.SETTING;

// PWMCONF
uint32_t TMC2130Stepper::PWMCONF() { return PWMCONF_register.cfg.sr; }
void TMC2130Stepper::PWMCONF(uint32_t input) {
	PWMCONF_register.cfg.sr = input;
	WRITE_REG(PWMCONF);
}

void TMC2130Stepper::pwm_ampl(		uint8_t B )	{ SET_REG(pwm_ampl);		}
void TMC2130Stepper::pwm_grad(		uint8_t B )	{ SET_REG(pwm_grad);		}
void TMC2130Stepper::pwm_freq(		uint8_t B )	{ SET_REG(pwm_freq);		}
void TMC2130Stepper::pwm_autoscale(	bool 	B )	{ SET_REG(pwm_autoscale);	}
void TMC2130Stepper::pwm_symmetric(	bool 	B )	{ SET_REG(pwm_symmetric);	}
void TMC2130Stepper::freewheel(		uint8_t B )	{ SET_REG(freewheel);		}

uint8_t TMC2130Stepper::pwm_ampl()		{ GET_REG(pwm_ampl);		}
uint8_t TMC2130Stepper::pwm_grad()		{ GET_REG(pwm_grad);		}
uint8_t TMC2130Stepper::pwm_freq()		{ GET_REG(pwm_freq);		}
bool 	TMC2130Stepper::pwm_autoscale()	{ GET_REG(pwm_autoscale);	}
bool 	TMC2130Stepper::pwm_symmetric()	{ GET_REG(pwm_symmetric);	}
uint8_t TMC2130Stepper::freewheel()		{ GET_REG(freewheel);		}

uint32_t TMC2208Stepper::PWMCONF() {
	if (write_only) return PWMCONF_register.cfg.sr;
	PWMCONF_register.cfg.sr = READ_REG(PWMCONF);
	return PWMCONF_register.cfg.sr;
}
void TMC2208Stepper::PWMCONF(uint32_t input) {
	PWMCONF_register.cfg.sr = input;
	WRITE_REG(PWMCONF);
}

void TMC2208Stepper::pwm_ofs		( uint8_t B ) { PWMCONF_register.cfg.opt.pwm_ofs = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::pwm_grad		( uint8_t B ) { PWMCONF_register.cfg.opt.pwm_grad = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::pwm_freq		( uint8_t B ) { PWMCONF_register.cfg.opt.pwm_freq = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::pwm_autoscale	( bool 	  B ) { PWMCONF_register.cfg.opt.pwm_autoscale = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::pwm_autograd	( bool    B ) { PWMCONF_register.cfg.opt.pwm_autograd = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::freewheel		( uint8_t B ) { PWMCONF_register.cfg.opt.freewheel = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::pwm_reg		( uint8_t B ) { PWMCONF_register.cfg.opt.pwm_reg = B; WRITE_REG(PWMCONF); }
void TMC2208Stepper::pwm_lim		( uint8_t B ) { PWMCONF_register.cfg.opt.pwm_lim = B; WRITE_REG(PWMCONF); }

uint8_t TMC2208Stepper::pwm_ofs()		{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_ofs;		}
uint8_t TMC2208Stepper::pwm_grad()		{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_grad;		}
uint8_t TMC2208Stepper::pwm_freq()		{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_freq;		}
bool 	TMC2208Stepper::pwm_autoscale()	{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_autoscale;	}
bool 	TMC2208Stepper::pwm_autograd()	{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_autograd;	}
uint8_t TMC2208Stepper::freewheel()		{ PWMCONF(); return PWMCONF_register.cfg.opt.freewheel;		}
uint8_t TMC2208Stepper::pwm_reg()		{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_reg;		}
uint8_t TMC2208Stepper::pwm_lim()		{ PWMCONF(); return PWMCONF_register.cfg.opt.pwm_lim;		}
