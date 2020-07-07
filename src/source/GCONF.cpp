#include "TMCStepper.h"

// GCONF


/*
bit 18 not implemented:
test_mode 0:
Normal operation 1:
Enable analog test output on pin DCO. IHOLD[1..0] selects the function of DCO:
0…2: T120, DAC, VDDH Attention:
Not for user, set to 0 for normal operation!
*/

void TMC5160Stepper::recalibrate(bool B)			{ auto r=GCONF_t{ GCONF() }; r.recalibrate = B; 	 GCONF(r.sr); }
void TMC5160Stepper::faststandstill(bool B)			{ auto r=GCONF_t{ GCONF() }; r.faststandstill = B; GCONF(r.sr); }
void TMC5160Stepper::multistep_filt(bool B)			{ auto r=GCONF_t{ GCONF() }; r.multistep_filt = B; GCONF(r.sr); }
bool TMC5160Stepper::recalibrate()					{ return GCONF_t{ GCONF() }.recalibrate; 	}
bool TMC5160Stepper::faststandstill()				{ return GCONF_t{ GCONF() }.faststandstill; }
bool TMC5160Stepper::multistep_filt()				{ return GCONF_t{ GCONF() }.multistep_filt; }


