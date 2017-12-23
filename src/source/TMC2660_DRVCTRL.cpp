#include "TMCStepper.h"

uint32_t TMC2660Stepper::DRVCTRL() { return DRVCTRL_sr; }
void TMC2660Stepper::DRVCTRL(uint32_t data) {
  DRVCTRL_sr = data;
  write(((uint32_t)cfg.REG_DRVCTRL<<17)|DRVCTRL_sr);
}

// DRVCTRL (SPI)
void TMC2660Stepper::pha(bool b)    { if(sdoff() != 1) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.PHA_bm, cfg.PHA_bp, b));  }
void TMC2660Stepper::ca(uint8_t B)  { if(sdoff() != 1) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.CA_bm, cfg.CA_bp, B));    }
void TMC2660Stepper::phb(bool b)    { if(sdoff() != 1) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.PHB_bm, cfg.PHB_bp, b));  }
void TMC2660Stepper::cb(uint8_t B)  { if(sdoff() != 1) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.CB_bm, cfg.CB_bp, B));    }

bool TMC2660Stepper::pha()    { if(sdoff() != 1) sdoff(1); return getBits(DRVCTRL(), cfg.PHA_bm, cfg.PHA_bp);  }
uint8_t TMC2660Stepper::ca()  { if(sdoff() != 1) sdoff(1); return getBits(DRVCTRL(), cfg.CA_bm, cfg.CA_bp);    }
bool TMC2660Stepper::phb()    { if(sdoff() != 1) sdoff(1); return getBits(DRVCTRL(), cfg.PHB_bm, cfg.PHB_bp);  }
uint8_t TMC2660Stepper::cb()  { if(sdoff() != 1) sdoff(1); return getBits(DRVCTRL(), cfg.CB_bm, cfg.CB_bp);    }

// DRVCTRL (STEP/DIR)
void TMC2660Stepper::intpol(bool b) { if(sdoff()) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.INTPOL_bm, cfg.INTPOL_bp, b)); }
void TMC2660Stepper::dedge(bool b)  { if(sdoff()) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.DEDGE_bm, cfg.DEDGE_bp, b)); }
void TMC2660Stepper::mres(uint8_t B){ if(sdoff()) return; DRVCTRL(setBits(DRVCTRL_sr, cfg.MRES_bm, cfg.MRES_bp, B)); }

bool TMC2660Stepper::intpol() { if(sdoff()) return 0; return getBits(DRVCTRL(), cfg.INTPOL_bm, cfg.INTPOL_bp); }
bool TMC2660Stepper::dedge()  { if(sdoff()) return 0; return getBits(DRVCTRL(), cfg.DEDGE_bm, cfg.DEDGE_bp); }
uint8_t TMC2660Stepper::mres(){ if(sdoff()) return 0; return getBits(DRVCTRL(), cfg.MRES_bm, cfg.MRES_bp); }
