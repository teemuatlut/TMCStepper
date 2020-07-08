#include "TMCStepper.h"



void TMC2209Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	TPWMTHRS(TPWMTHRS_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
	SGTHRS(SGTHRS_i::r.sr);
	COOLCONF(COOLCONF_i::r.sr);
}
