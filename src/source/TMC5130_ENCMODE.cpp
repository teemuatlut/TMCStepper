#include "TMCStepper.h"

// ENCMODE
uint32_t TMC5130Stepper::ENCMODE() { READ_REG(ENCMODE); }
void TMC5130Stepper::ENCMODE(uint32_t input) {
	ENCMODE_sr = input;
	WRITE_REG(ENCMODE);
}

void TMC5130Stepper::pol_a(bool B)					{ MOD_REG(ENCMODE, POL_A);			}
void TMC5130Stepper::pol_b(bool B)					{ MOD_REG(ENCMODE, POL_B);			}
void TMC5130Stepper::pol_n(bool B)					{ MOD_REG(ENCMODE, POL_N);			}
void TMC5130Stepper::ignore_ab(bool B)				{ MOD_REG(ENCMODE, IGNORE_AB);		}
void TMC5130Stepper::clr_cont(bool B)				{ MOD_REG(ENCMODE, CLR_CONT);		}
void TMC5130Stepper::clr_once(bool B)				{ MOD_REG(ENCMODE, CLR_ONCE);		}
void TMC5130Stepper::pos_edge(bool B)				{ MOD_REG(ENCMODE, POS_EDGE);		}
void TMC5130Stepper::neg_edge(bool B)				{ MOD_REG(ENCMODE, NEG_EDGE);		}
void TMC5130Stepper::clr_enc_x(bool B)				{ MOD_REG(ENCMODE, CLR_ENC_X);		}
void TMC5130Stepper::latch_x_act(bool B)			{ MOD_REG(ENCMODE, LATCH_X_ACT);	}
void TMC5130Stepper::enc_sel_decimal(bool B)		{ MOD_REG(ENCMODE, ENC_SEL_DECIMAL);}

bool TMC5130Stepper::pol_a()						{ GET_BYTE(ENCMODE, POL_A);			}
bool TMC5130Stepper::pol_b()						{ GET_BYTE(ENCMODE, POL_B);			}
bool TMC5130Stepper::pol_n()						{ GET_BYTE(ENCMODE, POL_N);			}
bool TMC5130Stepper::ignore_ab()					{ GET_BYTE(ENCMODE, IGNORE_AB);		}
bool TMC5130Stepper::clr_cont()						{ GET_BYTE(ENCMODE, CLR_CONT);		}
bool TMC5130Stepper::clr_once()						{ GET_BYTE(ENCMODE, CLR_ONCE);		}
bool TMC5130Stepper::pos_edge()						{ GET_BYTE(ENCMODE, POS_EDGE);		}
bool TMC5130Stepper::neg_edge()						{ GET_BYTE(ENCMODE, NEG_EDGE);		}
bool TMC5130Stepper::clr_enc_x()					{ GET_BYTE(ENCMODE, CLR_ENC_X);		}
bool TMC5130Stepper::latch_x_act()					{ GET_BYTE(ENCMODE, LATCH_X_ACT);	}
bool TMC5130Stepper::enc_sel_decimal()				{ GET_BYTE(ENCMODE, ENC_SEL_DECIMAL);}
