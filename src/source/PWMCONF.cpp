#include "TMCStepper.h"

// PWMCONF

uint32_t TMC2160Stepper::PWMCONF() {
	return PWMCONF_register.sr;
}
void TMC2160Stepper::PWMCONF(uint32_t input) {
	PWMCONF_register.sr = input;
	write(PWMCONF_register.address, PWMCONF_register.sr);
}

void TMC2160Stepper::pwm_ofs		( uint8_t B ) { PWMCONF_register.pwm_ofs = B; 		write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::pwm_grad		( uint8_t B ) { PWMCONF_register.pwm_grad = B; 		write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::pwm_freq		( uint8_t B ) { PWMCONF_register.pwm_freq = B; 		write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::pwm_autoscale	( bool 	  B ) { PWMCONF_register.pwm_autoscale = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::pwm_autograd	( bool    B ) { PWMCONF_register.pwm_autograd = B; 	write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::freewheel		( uint8_t B ) { PWMCONF_register.freewheel = B; 	write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::pwm_reg		( uint8_t B ) { PWMCONF_register.pwm_reg = B; 		write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2160Stepper::pwm_lim		( uint8_t B ) { PWMCONF_register.pwm_lim = B; 		write(PWMCONF_register.address, PWMCONF_register.sr); }

uint8_t TMC2160Stepper::pwm_ofs()		{ return PWMCONF_register.pwm_ofs;		}
uint8_t TMC2160Stepper::pwm_grad()		{ return PWMCONF_register.pwm_grad;		}
uint8_t TMC2160Stepper::pwm_freq()		{ return PWMCONF_register.pwm_freq;		}
bool 	TMC2160Stepper::pwm_autoscale()	{ return PWMCONF_register.pwm_autoscale;}
bool 	TMC2160Stepper::pwm_autograd()	{ return PWMCONF_register.pwm_autograd;	}
uint8_t TMC2160Stepper::freewheel()		{ return PWMCONF_register.freewheel;	}
uint8_t TMC2160Stepper::pwm_reg()		{ return PWMCONF_register.pwm_reg;		}
uint8_t TMC2160Stepper::pwm_lim()		{ return PWMCONF_register.pwm_lim;		}

uint32_t TMC2208Stepper::PWMCONF() {
	return read(PWMCONF_register.address);
}
void TMC2208Stepper::PWMCONF(uint32_t input) {
	PWMCONF_register.sr = input;
	write(PWMCONF_register.address, PWMCONF_register.sr);
}

void TMC2208Stepper::pwm_ofs		( uint8_t B ) { PWMCONF_register.pwm_ofs = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::pwm_grad		( uint8_t B ) { PWMCONF_register.pwm_grad = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::pwm_freq		( uint8_t B ) { PWMCONF_register.pwm_freq = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::pwm_autoscale	( bool 	  B ) { PWMCONF_register.pwm_autoscale = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::pwm_autograd	( bool    B ) { PWMCONF_register.pwm_autograd = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::freewheel		( uint8_t B ) { PWMCONF_register.freewheel = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::pwm_reg		( uint8_t B ) { PWMCONF_register.pwm_reg = B; write(PWMCONF_register.address, PWMCONF_register.sr); }
void TMC2208Stepper::pwm_lim		( uint8_t B ) { PWMCONF_register.pwm_lim = B; write(PWMCONF_register.address, PWMCONF_register.sr); }

uint8_t TMC2208Stepper::pwm_ofs()		{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_ofs;			}
uint8_t TMC2208Stepper::pwm_grad()		{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_grad;		}
uint8_t TMC2208Stepper::pwm_freq()		{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_freq;		}
bool 	TMC2208Stepper::pwm_autoscale()	{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_autoscale;	}
bool 	TMC2208Stepper::pwm_autograd()	{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_autograd;	}
uint8_t TMC2208Stepper::freewheel()		{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.freewheel;		}
uint8_t TMC2208Stepper::pwm_reg()		{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_reg;			}
uint8_t TMC2208Stepper::pwm_lim()		{ return TMC2208_n::PWMCONF_t{ PWMCONF() }.pwm_lim;			}
