#include "TMCStepper.h"

uint32_t TMC2660Stepper::SGCSCONF() { return SGCSCONF_sr; }
void TMC2660Stepper::SGCSCONF(uint32_t data) {
  SGCSCONF_sr = data;
  write(((uint32_t)cfg.REG_SGCSCONF<<17)|SGCSCONF_sr);
}

void TMC2660Stepper::sfilt(bool b) 	{ SGCSCONF(setBits(SGCSCONF_sr, cfg.SFILT_bm, 	cfg.SFILT_bp, 	b)); }
void TMC2660Stepper::sgt(uint8_t B) { SGCSCONF(setBits(SGCSCONF_sr, cfg.SGT_bm, 	cfg.SGT_bp, 	B)); }
void TMC2660Stepper::cs(uint8_t B) 	{ SGCSCONF(setBits(SGCSCONF_sr, cfg.CS_bm, 		cfg.CS_bp, 		B)); }
