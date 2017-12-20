#include "TMCStepper.h"

// PWMCONF
uint32_t TMCStepper::PWMCONF() { return PWMCONF_sr; }
void TMCStepper::PWMCONF(uint32_t input) {
	PWMCONF_sr = input;
	WRITE_REG(PWMCONF);
}

void TMCStepper::pwm_ampl(		uint8_t B )	{ MOD_REG(PWMCONF, PWM_AMPL);		}
void TMCStepper::pwm_grad(		uint8_t B )	{ MOD_REG(PWMCONF, PWM_GRAD);		}
void TMCStepper::pwm_freq(		uint8_t B )	{ MOD_REG(PWMCONF, PWM_FREQ);		}
void TMCStepper::pwm_autoscale(	bool 	B )	{ MOD_REG(PWMCONF, PWM_AUTOSCALE);	}
void TMCStepper::pwm_symmetric(	bool 	B )	{ MOD_REG(PWMCONF, PWM_SYMMETRIC);	}
void TMCStepper::freewheel(		uint8_t B )	{ MOD_REG(PWMCONF, FREEWHEEL);		}

uint8_t TMCStepper::pwm_ampl()		{ GET_BYTE(PWMCONF, PWM_AMPL);		}
uint8_t TMCStepper::pwm_grad()		{ GET_BYTE(PWMCONF, PWM_GRAD);		}
uint8_t TMCStepper::pwm_freq()		{ GET_BYTE(PWMCONF, PWM_FREQ);		}
bool 	TMCStepper::pwm_autoscale()	{ GET_BYTE(PWMCONF, PWM_AUTOSCALE);	}
bool 	TMCStepper::pwm_symmetric()	{ GET_BYTE(PWMCONF, PWM_SYMMETRIC);	}
uint8_t TMCStepper::freewheel()		{ GET_BYTE(PWMCONF, FREEWHEEL);		}
