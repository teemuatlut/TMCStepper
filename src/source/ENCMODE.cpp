#include "TMCStepper.h"
/*
// ENCMODE
uint16_t TMC5130Stepper::ENCMODE() {
	return read(ENCMODE_register.address);
}
void TMC5130Stepper::ENCMODE(uint16_t input) {
	ENCMODE_register.sr = input;
	write(ENCMODE_register.address, ENCMODE_register.sr);
}

void TMC5130Stepper::pol_a(bool B)			{ ENCMODE_register.pol_a = B; 			write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::pol_b(bool B)			{ ENCMODE_register.pol_b = B; 			write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::pol_n(bool B)			{ ENCMODE_register.pol_n = B; 			write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::ignore_ab(bool B)		{ ENCMODE_register.ignore_ab = B; 		write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::clr_cont(bool B)		{ ENCMODE_register.clr_cont = B; 		write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::clr_once(bool B)		{ ENCMODE_register.clr_once = B; 		write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::pos_edge(bool B)		{ ENCMODE_register.pos_edge = B; 		write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::neg_edge(bool B)		{ ENCMODE_register.neg_edge = B; 		write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::clr_enc_x(bool B)		{ ENCMODE_register.clr_enc_x = B; 		write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::latch_x_act(bool B)	{ ENCMODE_register.latch_x_act = B; 	write(ENCMODE_register.address, ENCMODE_register.sr); }
void TMC5130Stepper::enc_sel_decimal(bool B){ ENCMODE_register.enc_sel_decimal = B; write(ENCMODE_register.address, ENCMODE_register.sr); }

bool TMC5130Stepper::pol_a()			{ return ENCMODE_t{ ENCMODE() }.pol_a;			}
bool TMC5130Stepper::pol_b()			{ return ENCMODE_t{ ENCMODE() }.pol_b;			}
bool TMC5130Stepper::pol_n()			{ return ENCMODE_t{ ENCMODE() }.pol_n;			}
bool TMC5130Stepper::ignore_ab()		{ return ENCMODE_t{ ENCMODE() }.ignore_ab;		}
bool TMC5130Stepper::clr_cont()			{ return ENCMODE_t{ ENCMODE() }.clr_cont;		}
bool TMC5130Stepper::clr_once()			{ return ENCMODE_t{ ENCMODE() }.clr_once;		}
bool TMC5130Stepper::pos_edge()			{ return ENCMODE_t{ ENCMODE() }.pos_edge;		}
bool TMC5130Stepper::neg_edge()			{ return ENCMODE_t{ ENCMODE() }.neg_edge;		}
bool TMC5130Stepper::clr_enc_x()		{ return ENCMODE_t{ ENCMODE() }.clr_enc_x;		}
bool TMC5130Stepper::latch_x_act()		{ return ENCMODE_t{ ENCMODE() }.latch_x_act;	}
bool TMC5130Stepper::enc_sel_decimal()	{ return ENCMODE_t{ ENCMODE() }.enc_sel_decimal;}
*/