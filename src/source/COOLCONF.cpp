#include "TMCStepper.h"

#define SET_REG(SETTING) COOLCONF_register.SETTING = B; write(COOLCONF_register.address, COOLCONF_register.sr);
#define GET_REG(SETTING) return COOLCONF_register.SETTING;

// COOLCONF

