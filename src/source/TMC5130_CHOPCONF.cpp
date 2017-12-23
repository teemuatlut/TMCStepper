#include "TMCStepper.h"

// CHOPCONF
uint32_t TMC5130Stepper::CHOPCONF() { READ_REG(CHOPCONF); }
void TMC5130Stepper::CHOPCONF(uint32_t input) {
	CHOPCONF_sr = input;
	WRITE_REG(CHOPCONF);
}

void TMC5130Stepper::toff(		uint8_t B )	{ MOD_REG(CHOPCONF, TOFF);		}
void TMC5130Stepper::hstrt(		uint8_t B )	{ MOD_REG(CHOPCONF, HSTRT);		}
void TMC5130Stepper::hend(		int8_t  B )	{ MOD_REG(CHOPCONF, HEND);		}
void TMC5130Stepper::fd(		uint8_t B )	{ MOD_REG(CHOPCONF, FD);		}
void TMC5130Stepper::disfdcc(	bool 	B )	{ MOD_REG(CHOPCONF, DISFDCC);	}
void TMC5130Stepper::rndtf(		bool 	B )	{ MOD_REG(CHOPCONF, RNDTF);		}
void TMC5130Stepper::chm(		bool 	B )	{ MOD_REG(CHOPCONF, CHM);		}
void TMC5130Stepper::tbl(		uint8_t B )	{ MOD_REG(CHOPCONF, TBL);		}
void TMC5130Stepper::vsense(	bool 	B )	{ MOD_REG(CHOPCONF, VSENSE);	}
void TMC5130Stepper::vhighfs(	bool 	B )	{ MOD_REG(CHOPCONF, VHIGHFS);	}
void TMC5130Stepper::vhighchm(	bool 	B )	{ MOD_REG(CHOPCONF, VHIGHCHM);	}
void TMC5130Stepper::sync(		uint8_t B )	{ MOD_REG(CHOPCONF, SYNC);		}
void TMC5130Stepper::mres(		uint8_t B )	{ MOD_REG(CHOPCONF, MRES);		}
void TMC5130Stepper::intpol(	bool 	B )	{ MOD_REG(CHOPCONF, INTPOL);	}
void TMC5130Stepper::dedge(		bool 	B )	{ MOD_REG(CHOPCONF, DEDGE);		}
void TMC5130Stepper::diss2g(	bool 	B )	{ MOD_REG(CHOPCONF, DISS2G);	}

uint8_t TMC5130Stepper::toff()		{ GET_BYTE(CHOPCONF, TOFF);		}
uint8_t TMC5130Stepper::hstrt()		{ GET_BYTE(CHOPCONF, HSTRT);	}
int8_t  TMC5130Stepper::hend()		{ GET_BYTE(CHOPCONF, HEND);		}
uint8_t TMC5130Stepper::fd()		{ GET_BYTE(CHOPCONF, FD);		}
bool 	TMC5130Stepper::disfdcc()	{ GET_BYTE(CHOPCONF, DISFDCC);	}
bool 	TMC5130Stepper::rndtf()		{ GET_BYTE(CHOPCONF, RNDTF);	}
bool 	TMC5130Stepper::chm()		{ GET_BYTE(CHOPCONF, CHM);		}
uint8_t TMC5130Stepper::tbl()		{ GET_BYTE(CHOPCONF, TBL);		}
bool 	TMC5130Stepper::vsense()	{ GET_BIT( CHOPCONF, VSENSE);	}
bool 	TMC5130Stepper::vhighfs()	{ GET_BYTE(CHOPCONF, VHIGHFS);	}
bool 	TMC5130Stepper::vhighchm()	{ GET_BYTE(CHOPCONF, VHIGHCHM);	}
uint8_t TMC5130Stepper::sync()		{ GET_BYTE(CHOPCONF, SYNC);		}
uint8_t TMC5130Stepper::mres()		{ GET_BYTE(CHOPCONF, MRES);		}
bool 	TMC5130Stepper::intpol()	{ GET_BYTE(CHOPCONF, INTPOL);	}
bool 	TMC5130Stepper::dedge()		{ GET_BYTE(CHOPCONF, DEDGE);	}
bool 	TMC5130Stepper::diss2g()	{ GET_BYTE(CHOPCONF, DISS2G);	}

uint32_t TMC2660Stepper::CHOPCONF() { return CHOPCONF_sr; }
void TMC2660Stepper::CHOPCONF(uint32_t data) {
  CHOPCONF_sr = data;
  write(((uint32_t)cfg.REG_CHOPCONF<<17)|CHOPCONF_sr);
}
void TMC2660Stepper::tbl(uint8_t B) 	{ CHOPCONF(setBits(CHOPCONF_sr, cfg.TBL_bm,		cfg.TBL_bp,	 	B)); }
void TMC2660Stepper::chm(bool b) 		{ CHOPCONF(setBits(CHOPCONF_sr, cfg.CHM_bm,		cfg.CHM_bp,	 	b)); }
void TMC2660Stepper::rndtf(bool b) 		{ CHOPCONF(setBits(CHOPCONF_sr, cfg.RNDTF_bm,	cfg.RNDTF_bp,	b)); }
void TMC2660Stepper::hdec(uint8_t B) 	{ CHOPCONF(setBits(CHOPCONF_sr, cfg.HDEC_bm,	cfg.HDEC_bp,	B)); }
void TMC2660Stepper::hend(uint8_t B) 	{ CHOPCONF(setBits(CHOPCONF_sr, cfg.HEND_bm,	cfg.HEND_bp,	B)); }
void TMC2660Stepper::hstrt(uint8_t B) 	{ CHOPCONF(setBits(CHOPCONF_sr, cfg.HSTRT_bm,	cfg.HSTRT_bp,	B)); }
void TMC2660Stepper::toff(uint8_t B) 	{ CHOPCONF(setBits(CHOPCONF_sr, cfg.TOFF_bm,	cfg.TOFF_bp,	B)); }

uint8_t TMC2660Stepper::tbl() 	{ return getBits(CHOPCONF(), cfg.TBL_bm,	cfg.TBL_bp); }
bool TMC2660Stepper::chm() 		{ return getBits(CHOPCONF(), cfg.CHM_bm,	cfg.CHM_bp); }
bool TMC2660Stepper::rndtf() 	{ return getBits(CHOPCONF(), cfg.RNDTF_bm,	cfg.RNDTF_bp); }
uint8_t TMC2660Stepper::hdec() 	{ return getBits(CHOPCONF(), cfg.HDEC_bm,	cfg.HDEC_bp); }
uint8_t TMC2660Stepper::hend() 	{ return getBits(CHOPCONF(), cfg.HEND_bm,	cfg.HEND_bp); }
uint8_t TMC2660Stepper::hstrt() { return getBits(CHOPCONF(), cfg.HSTRT_bm,	cfg.HSTRT_bp); }
uint8_t TMC2660Stepper::toff() 	{ return getBits(CHOPCONF(), cfg.TOFF_bm,	cfg.TOFF_bp); }
