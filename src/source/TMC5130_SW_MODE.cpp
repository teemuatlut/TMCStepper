#include "TMCStepper.h"

// SW_MODE
uint32_t TMC5130Stepper::SW_MODE() { READ_REG(SW_MODE); }
void TMC5130Stepper::SW_MODE(uint32_t input) {
	SW_MODE_sr = input;
	WRITE_REG(SW_MODE);
}

void TMC5130Stepper::stop_l_enable(bool B)			{ MOD_REG(SW_MODE, STOP_L_ENABLE);		}
void TMC5130Stepper::stop_r_enable(bool B)			{ MOD_REG(SW_MODE, STOP_R_ENABLE);		}
void TMC5130Stepper::pol_stop_l(bool B)				{ MOD_REG(SW_MODE, POL_STOP_L);			}
void TMC5130Stepper::pol_stop_r(bool B)				{ MOD_REG(SW_MODE, POL_STOP_R);			}
void TMC5130Stepper::swap_lr(bool B)				{ MOD_REG(SW_MODE, SWAP_LR);			}
void TMC5130Stepper::latch_l_active(bool B)			{ MOD_REG(SW_MODE, LATCH_L_ACTIVE);		}
void TMC5130Stepper::latch_l_inactive(bool B)		{ MOD_REG(SW_MODE, LATCH_L_INACTIVE);	}
void TMC5130Stepper::latch_r_active(bool B)			{ MOD_REG(SW_MODE, LATCH_R_ACTIVE);		}
void TMC5130Stepper::latch_r_inactive(bool B)		{ MOD_REG(SW_MODE, LATCH_R_INACTIVE);	}
void TMC5130Stepper::en_latch_encoder(bool B)		{ MOD_REG(SW_MODE, EN_LATCH_ENCODER);	}
void TMC5130Stepper::sg_stop(bool B)				{ MOD_REG(SW_MODE, SG_STOP);			}
void TMC5130Stepper::en_softstop(bool B)			{ MOD_REG(SW_MODE, EN_SOFTSTOP);		}

bool TMC5130Stepper::stop_r_enable()				{ GET_BYTE(SW_MODE, STOP_R_ENABLE);		}
bool TMC5130Stepper::pol_stop_l()					{ GET_BYTE(SW_MODE, POL_STOP_L);		}
bool TMC5130Stepper::pol_stop_r()					{ GET_BYTE(SW_MODE, POL_STOP_R);		}
bool TMC5130Stepper::swap_lr()						{ GET_BYTE(SW_MODE, SWAP_LR);			}
bool TMC5130Stepper::latch_l_active()				{ GET_BYTE(SW_MODE, LATCH_L_ACTIVE);	}
bool TMC5130Stepper::latch_l_inactive()				{ GET_BYTE(SW_MODE, LATCH_L_INACTIVE);	}
bool TMC5130Stepper::latch_r_active()				{ GET_BYTE(SW_MODE, LATCH_R_ACTIVE);	}
bool TMC5130Stepper::latch_r_inactive()				{ GET_BYTE(SW_MODE, LATCH_R_INACTIVE);	}
bool TMC5130Stepper::en_latch_encoder()				{ GET_BYTE(SW_MODE, EN_LATCH_ENCODER);	}
bool TMC5130Stepper::sg_stop()						{ GET_BYTE(SW_MODE, SG_STOP);			}
bool TMC5130Stepper::en_softstop()					{ GET_BYTE(SW_MODE, EN_SOFTSTOP);		}
