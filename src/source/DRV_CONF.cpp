#include "TMCStepper.h"

#define SET_REG(SETTING) DRV_CONF_register.SETTING = B; write(DRV_CONF_register.address, DRV_CONF_register.sr);
#define GET_REG(SETTING) return DRV_CONF_register.SETTING;

// W: DRV_CONF
uint32_t TMC2160Stepper::DRV_CONF() { return DRV_CONF_register.sr; }
void TMC2160Stepper::DRV_CONF(uint32_t input) {
	DRV_CONF_register.sr = input;
	write(DRV_CONF_register.address, DRV_CONF_register.sr);
}

void TMC2160Stepper::bbmtime(uint8_t B)		{ DRV_CONF_register.bbmtime = B; 		write(DRV_CONF_register.address, DRV_CONF_register.sr); }
void TMC2160Stepper::bbmclks(uint8_t B)		{ DRV_CONF_register.bbmclks = B; 		write(DRV_CONF_register.address, DRV_CONF_register.sr); }
void TMC2160Stepper::otselect(uint8_t B)	{ DRV_CONF_register.otselect = B; 		write(DRV_CONF_register.address, DRV_CONF_register.sr); }
void TMC2160Stepper::drvstrength(uint8_t B)	{ DRV_CONF_register.drvstrength = B; 	write(DRV_CONF_register.address, DRV_CONF_register.sr); }
void TMC2160Stepper::filt_isense(uint8_t B)	{ DRV_CONF_register.filt_isense = B; 	write(DRV_CONF_register.address, DRV_CONF_register.sr); }
uint8_t TMC2160Stepper::bbmtime()			{ return DRV_CONF_register.bbmtime;		}
uint8_t TMC2160Stepper::bbmclks()			{ return DRV_CONF_register.bbmclks;		}
uint8_t TMC2160Stepper::otselect()			{ return DRV_CONF_register.otselect;	}
uint8_t TMC2160Stepper::drvstrength()		{ return DRV_CONF_register.drvstrength;	}
uint8_t TMC2160Stepper::filt_isense()		{ return DRV_CONF_register.filt_isense;	}
