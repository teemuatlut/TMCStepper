#include "TMCStepper.h"

// CHOPCONF
uint32_t TMCStepper::CHOPCONF() { READ_REG(CHOPCONF); }
void TMCStepper::CHOPCONF(uint32_t input) {
	CHOPCONF_sr = input;
	WRITE_REG(CHOPCONF);
}

void TMCStepper::toff(		uint8_t B )	{ MOD_REG(CHOPCONF, TOFF);		}
void TMCStepper::hstrt(		uint8_t B )	{ MOD_REG(CHOPCONF, HSTRT);		}
void TMCStepper::hend(		int8_t  B )	{ MOD_REG(CHOPCONF, HEND);		}
void TMCStepper::fd(		uint8_t B )	{ MOD_REG(CHOPCONF, FD);		}
void TMCStepper::disfdcc(	bool 	B )	{ MOD_REG(CHOPCONF, DISFDCC);	}
void TMCStepper::rndtf(		bool 	B )	{ MOD_REG(CHOPCONF, RNDTF);		}
void TMCStepper::chm(		bool 	B )	{ MOD_REG(CHOPCONF, CHM);		}
void TMCStepper::tbl(		uint8_t B )	{ MOD_REG(CHOPCONF, TBL);		}
void TMCStepper::vsense(	bool 	B )	{ MOD_REG(CHOPCONF, VSENSE);	}
void TMCStepper::vhighfs(	bool 	B )	{ MOD_REG(CHOPCONF, VHIGHFS);	}
void TMCStepper::vhighchm(	bool 	B )	{ MOD_REG(CHOPCONF, VHIGHCHM);	}
void TMCStepper::sync(		uint8_t B )	{ MOD_REG(CHOPCONF, SYNC);		}
void TMCStepper::mres(		uint8_t B )	{ MOD_REG(CHOPCONF, MRES);		}
void TMCStepper::intpol(	bool 	B )	{ MOD_REG(CHOPCONF, INTPOL);	}
void TMCStepper::dedge(		bool 	B )	{ MOD_REG(CHOPCONF, DEDGE);		}
void TMCStepper::diss2g(	bool 	B )	{ MOD_REG(CHOPCONF, DISS2G);	}

uint8_t TMCStepper::toff()		{ GET_BYTE(CHOPCONF, TOFF);		}
uint8_t TMCStepper::hstrt()		{ GET_BYTE(CHOPCONF, HSTRT);	}
int8_t  TMCStepper::hend()		{ GET_BYTE(CHOPCONF, HEND);		}
uint8_t TMCStepper::fd()		{ GET_BYTE(CHOPCONF, FD);		}
bool 	TMCStepper::disfdcc()	{ GET_BYTE(CHOPCONF, DISFDCC);	}
bool 	TMCStepper::rndtf()		{ GET_BYTE(CHOPCONF, RNDTF);	}
bool 	TMCStepper::chm()		{ GET_BYTE(CHOPCONF, CHM);		}
uint8_t TMCStepper::tbl()		{ GET_BYTE(CHOPCONF, TBL);		}
bool 	TMCStepper::vsense()	{ GET_BIT( CHOPCONF, VSENSE);	}
bool 	TMCStepper::vhighfs()	{ GET_BYTE(CHOPCONF, VHIGHFS);	}
bool 	TMCStepper::vhighchm()	{ GET_BYTE(CHOPCONF, VHIGHCHM);	}
uint8_t TMCStepper::sync()		{ GET_BYTE(CHOPCONF, SYNC);		}
uint8_t TMCStepper::mres()		{ GET_BYTE(CHOPCONF, MRES);		}
bool 	TMCStepper::intpol()	{ GET_BYTE(CHOPCONF, INTPOL);	}
bool 	TMCStepper::dedge()		{ GET_BYTE(CHOPCONF, DEDGE);	}
bool 	TMCStepper::diss2g()	{ GET_BYTE(CHOPCONF, DISS2G);	}
