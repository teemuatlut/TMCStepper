#include "TMCStepper.h"

// ENCMODE
uint32_t TMCStepper::ENCMODE() { READ_REG(ENCMODE); }
void TMCStepper::ENCMODE(uint32_t input) {
	ENCMODE_sr = input;
	WRITE_REG(ENCMODE);
}

void TMCStepper::pol_a(bool B)					{ MOD_REG(ENCMODE, POL_A);			}
void TMCStepper::pol_b(bool B)					{ MOD_REG(ENCMODE, POL_B);			}
void TMCStepper::pol_n(bool B)					{ MOD_REG(ENCMODE, POL_N);			}
void TMCStepper::ignore_ab(bool B)				{ MOD_REG(ENCMODE, IGNORE_AB);		}
void TMCStepper::clr_cont(bool B)				{ MOD_REG(ENCMODE, CLR_CONT);		}
void TMCStepper::clr_once(bool B)				{ MOD_REG(ENCMODE, CLR_ONCE);		}
void TMCStepper::pos_edge(bool B)				{ MOD_REG(ENCMODE, POS_EDGE);		}
void TMCStepper::neg_edge(bool B)				{ MOD_REG(ENCMODE, NEG_EDGE);		}
void TMCStepper::clr_enc_x(bool B)				{ MOD_REG(ENCMODE, CLR_ENC_X);		}
void TMCStepper::latch_x_act(bool B)			{ MOD_REG(ENCMODE, LATCH_X_ACT);	}
void TMCStepper::enc_sel_decimal(bool B)		{ MOD_REG(ENCMODE, ENC_SEL_DECIMAL);}

bool TMCStepper::pol_a()						{ GET_BYTE(ENCMODE, POL_A);			}
bool TMCStepper::pol_b()						{ GET_BYTE(ENCMODE, POL_B);			}
bool TMCStepper::pol_n()						{ GET_BYTE(ENCMODE, POL_N);			}
bool TMCStepper::ignore_ab()					{ GET_BYTE(ENCMODE, IGNORE_AB);		}
bool TMCStepper::clr_cont()						{ GET_BYTE(ENCMODE, CLR_CONT);		}
bool TMCStepper::clr_once()						{ GET_BYTE(ENCMODE, CLR_ONCE);		}
bool TMCStepper::pos_edge()						{ GET_BYTE(ENCMODE, POS_EDGE);		}
bool TMCStepper::neg_edge()						{ GET_BYTE(ENCMODE, NEG_EDGE);		}
bool TMCStepper::clr_enc_x()					{ GET_BYTE(ENCMODE, CLR_ENC_X);		}
bool TMCStepper::latch_x_act()					{ GET_BYTE(ENCMODE, LATCH_X_ACT);	}
bool TMCStepper::enc_sel_decimal()				{ GET_BYTE(ENCMODE, ENC_SEL_DECIMAL);}
