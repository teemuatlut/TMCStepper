#include "TMCStepper.h"

uint32_t TMC2660Stepper::DRVSTATUS() {
	// Send valid data to refresh SPI_response
	write(((uint32_t)cfg.REG_DRVCONF<<17)|DRVCONF_sr);
	return SPI_response;
}

uint16_t TMC2660Stepper::mstep()	{ if(rdsel() != 0b00) rdsel(0b00); return getBits(DRVSTATUS(), cfg.MSTEP_bm, cfg.MSTEP_bp); }
uint8_t TMC2660Stepper::se() 		{ if(rdsel() != 0b10) rdsel(0b10); return getBits(DRVSTATUS(), cfg.SE_bm, cfg.SE_bp); }
bool TMC2660Stepper::stst() 		{ return getBits(DRVSTATUS(), cfg.STST_bm, 	cfg.STST_bp); }
bool TMC2660Stepper::olb() 			{ return getBits(DRVSTATUS(), cfg.OLB_bm, 	cfg.OLB_bp); }
bool TMC2660Stepper::ola() 			{ return getBits(DRVSTATUS(), cfg.OLA_bm, 	cfg.OLA_bp); }
bool TMC2660Stepper::s2gb() 		{ return getBits(DRVSTATUS(), cfg.S2GB_bm, 	cfg.S2GB_bp); }
bool TMC2660Stepper::s2ga() 		{ return getBits(DRVSTATUS(), cfg.S2GA_bm, 	cfg.S2GA_bp); }
bool TMC2660Stepper::otpw() 		{ return getBits(DRVSTATUS(), cfg.OTPW_bm, 	cfg.OTPW_bp); }
bool TMC2660Stepper::ot() 			{ return getBits(DRVSTATUS(), cfg.OT_bm, 	cfg.OT_bp); }
bool TMC2660Stepper::sg() 			{ return getBits(DRVSTATUS(), cfg.SG_bm, 	cfg.SG_bp); }

uint16_t TMC2660Stepper::mstep(uint32_t data)		{ return getBits(data, cfg.MSTEP_bm, 	cfg.MSTEP_bp); }
uint16_t TMC2660Stepper::sg_result(uint32_t data)	{ return getBits(data, cfg.SG_RESULT_bm,cfg.SG_RESULT_bp); }
uint8_t TMC2660Stepper::se(uint32_t data) 			{ return getBits(data, cfg.SE_bm, 		cfg.SE_bp); }
bool TMC2660Stepper::stst(uint32_t data) 			{ return getBits(data, cfg.STST_bm, 	cfg.STST_bp); }
bool TMC2660Stepper::olb(uint32_t data) 			{ return getBits(data, cfg.OLB_bm, 		cfg.OLB_bp); }
bool TMC2660Stepper::ola(uint32_t data) 			{ return getBits(data, cfg.OLA_bm, 		cfg.OLA_bp); }
bool TMC2660Stepper::s2gb(uint32_t data) 			{ return getBits(data, cfg.S2GB_bm, 	cfg.S2GB_bp); }
bool TMC2660Stepper::s2ga(uint32_t data) 			{ return getBits(data, cfg.S2GA_bm, 	cfg.S2GA_bp); }
bool TMC2660Stepper::otpw(uint32_t data) 			{ return getBits(data, cfg.OTPW_bm, 	cfg.OTPW_bp); }
bool TMC2660Stepper::ot(uint32_t data) 				{ return getBits(data, cfg.OT_bm, 		cfg.OT_bp); }
bool TMC2660Stepper::sg(uint32_t data) 				{ return getBits(data, cfg.SG_bm, 		cfg.SG_bp); }

uint16_t TMC2660Stepper::sg_result(){
	uint16_t out = 0;
	if (rdsel() == 0b00) rdsel(0b01);
	switch(rdsel()) {
		case 0b01:
			out = getBits(DRVSTATUS(), cfg.SG_RESULT_bm, cfg.SG_RESULT_bp);
			break;
		case 0b10:
			out = getBits(DRVSTATUS(), cfg.SG_RESULT_bm, cfg.SG_RESULT_bp);
	}
	return out;
}

