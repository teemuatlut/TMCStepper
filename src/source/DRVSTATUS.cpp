#include "TMCStepper.h"
#include "TMC_MACROS.h"

uint32_t TMC2660Stepper::DRVSTATUS() {
	uint32_t response = read()&0xFFCFF;
	READ_RDSEL00_register.sr = response & 0xFF;
	READ_RDSEL01_register.sr = response & 0xFF;
	READ_RDSEL10_register.sr = response & 0xFF;
	switch(rdsel()) {
		case 0b00: READ_RDSEL00_register.sr |= response & 0xFFC00; break;
		case 0b01: READ_RDSEL01_register.sr |= response & 0xFFC00; break;
		case 0b10: READ_RDSEL10_register.sr |= response & 0xFFC00; break;
		default: return 0;
	}
	return response;
}

uint16_t TMC2660Stepper::mstep() {
	if(rdsel() != 0b00)
		rdsel(0b00);

	DRVSTATUS();
	return READ_RDSEL00_register.mstep;
}
uint8_t TMC2660Stepper::se() {
	if(rdsel() != 0b10)
		rdsel(0b10);

	DRVSTATUS();
	return READ_RDSEL10_register.se;
}
bool TMC2660Stepper::stst() { DRVSTATUS(); return READ_RDSEL00_register.stst;	 }
bool TMC2660Stepper::olb() 	{ DRVSTATUS(); return READ_RDSEL00_register.olb;	 }
bool TMC2660Stepper::ola() 	{ DRVSTATUS(); return READ_RDSEL00_register.ola;	 }
bool TMC2660Stepper::s2gb() { DRVSTATUS(); return READ_RDSEL00_register.s2gb;	 }
bool TMC2660Stepper::s2ga() { DRVSTATUS(); return READ_RDSEL00_register.s2ga;	 }
bool TMC2660Stepper::otpw() { DRVSTATUS(); return READ_RDSEL00_register.otpw;	 }
bool TMC2660Stepper::ot() 	{ DRVSTATUS(); return READ_RDSEL00_register.ot;		 }
bool TMC2660Stepper::sg() 	{ DRVSTATUS(); return READ_RDSEL00_register.sg_value;}

uint16_t TMC2660Stepper::sg_result(){
	uint16_t out = 0;
	if (rdsel() == 0b00) rdsel(0b01);
	DRVSTATUS();
	switch(rdsel()) {
		case 0b01: out = READ_RDSEL01_register.sg_result; break;
		case 0b10: out = READ_RDSEL10_register.sg_result; break;
		default: break;
	}
	return out;
}
