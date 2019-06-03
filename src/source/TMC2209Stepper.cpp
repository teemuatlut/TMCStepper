#include "TMCStepper.h"

uint32_t TMC2209Stepper::IOIN() {
	IOIN_register.sr = read(IOIN_register.address);
	return IOIN_register.sr;
}
bool TMC2209Stepper::enn()			{ IOIN(); return IOIN_register.enn;			}
bool TMC2209Stepper::ms1()			{ IOIN(); return IOIN_register.ms1;			}
bool TMC2209Stepper::ms2()			{ IOIN(); return IOIN_register.ms2;			}
bool TMC2209Stepper::diag()			{ IOIN(); return IOIN_register.diag;		}
bool TMC2209Stepper::pdn_uart()		{ IOIN(); return IOIN_register.pdn_uart;	}
bool TMC2209Stepper::step()			{ IOIN(); return IOIN_register.step;		}
bool TMC2209Stepper::spread_en()	{ IOIN(); return IOIN_register.spread_en;	}
bool TMC2209Stepper::dir()			{ IOIN(); return IOIN_register.dir;			}
uint8_t TMC2209Stepper::version() 	{ IOIN(); return IOIN_register.version;		}

void TMC2209Stepper::SGTHRS(uint8_t input) {
	SGTHRS_register.sr = input;
	write(SGTHRS_register.address, SGTHRS_register.sr);
}

uint16_t TMC2209Stepper::SG_RESULT() {
	return read(TMC2209_n::SG_RESULT_t::address);
}
