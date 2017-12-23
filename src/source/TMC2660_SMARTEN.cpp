#include "TMCStepper.h"

uint32_t TMC2660Stepper::SMARTEN() { return SMARTEN_sr; }
void TMC2660Stepper::SMARTEN(uint32_t data) {
  SMARTEN_sr = data;
  write(((uint32_t)cfg.REG_SMARTEN<<17)|SMARTEN_sr);
}

void TMC2660Stepper::seimin(bool b) 	{ SMARTEN(setBits(SMARTEN_sr, cfg.SEIMIN_bm, 	cfg.SEIMIN_bp	, b)); }
void TMC2660Stepper::sedn(uint8_t B) 	{ SMARTEN(setBits(SMARTEN_sr, cfg.SEDN_bm, 		cfg.SEDN_bp		, B)); }
void TMC2660Stepper::semax(uint8_t B) 	{ SMARTEN(setBits(SMARTEN_sr, cfg.SEMAX_bm, 	cfg.SEMAX_bp	, B)); }
void TMC2660Stepper::seup(uint8_t B) 	{ SMARTEN(setBits(SMARTEN_sr, cfg.SEUP_bm, 		cfg.SEUP_bp		, B)); }
void TMC2660Stepper::semin(uint8_t B) 	{ SMARTEN(setBits(SMARTEN_sr, cfg.SEMIN_bm, 	cfg.SEMIN_bp	, B)); }

bool TMC2660Stepper::seimin() 	{ return getBits(SMARTEN(), cfg.SEIMIN_bm, cfg.SEIMIN_bp); }
uint8_t TMC2660Stepper::sedn() 	{ return getBits(SMARTEN(), cfg.SEDN_bm, 	cfg.SEDN_bp); }
uint8_t TMC2660Stepper::semax() { return getBits(SMARTEN(), cfg.SEMAX_bm, 	cfg.SEMAX_bp); }
uint8_t TMC2660Stepper::seup() 	{ return getBits(SMARTEN(), cfg.SEUP_bm, 	cfg.SEUP_bp); }
uint8_t TMC2660Stepper::semin() { return getBits(SMARTEN(), cfg.SEMIN_bm, 	cfg.SEMIN_bp); }
