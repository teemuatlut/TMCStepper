#include "TMCStepper.h"

uint32_t TMC2660Stepper::DRVCONF() { return DRVCONF_sr; }
void TMC2660Stepper::DRVCONF(uint32_t data) {
  DRVCONF_sr = data;
  write(((uint32_t)cfg.REG_DRVCONF<<17)|DRVCONF_sr);
}

void TMC2660Stepper::tst(bool b)      { DRVCONF(setBits(DRVCONF_sr, cfg.TST_bm,     cfg.TST_bp,     b)); }
void TMC2660Stepper::slph(uint8_t B)  { DRVCONF(setBits(DRVCONF_sr, cfg.SLPH_bm,    cfg.SLPH_bp,    B)); }
void TMC2660Stepper::slpl(uint8_t B)  { DRVCONF(setBits(DRVCONF_sr, cfg.SLPL_bm,    cfg.SLPL_bp,    B)); }
void TMC2660Stepper::diss2g(bool b)   { DRVCONF(setBits(DRVCONF_sr, cfg.DISS2G_bm,  cfg.DISS2G_bp,  b)); }
void TMC2660Stepper::ts2g(uint8_t B)  { DRVCONF(setBits(DRVCONF_sr, cfg.TS2G_bm,    cfg.TS2G_bp,    B)); }
void TMC2660Stepper::sdoff(bool b)    { DRVCONF(setBits(DRVCONF_sr, cfg.SDOFF_bm,   cfg.SDOFF_bp,   b)); }
void TMC2660Stepper::vsense(bool b)   { DRVCONF(setBits(DRVCONF_sr, cfg.VSENSE_bm,  cfg.VSENSE_bp,  b)); }
void TMC2660Stepper::rdsel(uint8_t B) { DRVCONF(setBits(DRVCONF_sr, cfg.RDSEL_bm,   cfg.RDSEL_bp,   B)); }

bool TMC2660Stepper::tst()		{ getBits(DRVCONF(), cfg.TST_bm,     cfg.TST_bp);	}
uint8_t TMC2660Stepper::slph()	{ getBits(DRVCONF(), cfg.SLPH_bm,    cfg.SLPH_bp);	}
uint8_t TMC2660Stepper::slpl()	{ getBits(DRVCONF(), cfg.SLPL_bm,    cfg.SLPL_bp);	}
bool TMC2660Stepper::diss2g()	{ getBits(DRVCONF(), cfg.DISS2G_bm,  cfg.DISS2G_bp);}
uint8_t TMC2660Stepper::ts2g()	{ getBits(DRVCONF(), cfg.TS2G_bm,    cfg.TS2G_bp);	}
bool TMC2660Stepper::sdoff()	{ getBits(DRVCONF(), cfg.SDOFF_bm,   cfg.SDOFF_bp);	}
bool TMC2660Stepper::vsense()	{ getBits(DRVCONF(), cfg.VSENSE_bm,  cfg.VSENSE_bp);}
uint8_t TMC2660Stepper::rdsel()	{ getBits(DRVCONF(), cfg.RDSEL_bm,   cfg.RDSEL_bp);	}