#include "TMCStepper.h"

// SW_MODE
uint32_t TMCStepper::SW_MODE() { READ_REG(SW_MODE); }
void TMCStepper::SW_MODE(uint32_t input) {
	SW_MODE_sr = input;
	WRITE_REG(SW_MODE);
}

void TMCStepper::stop_l_enable(bool B)			{ MOD_REG(SW_MODE, STOP_L_ENABLE);		}
void TMCStepper::stop_r_enable(bool B)			{ MOD_REG(SW_MODE, STOP_R_ENABLE);		}
void TMCStepper::pol_stop_l(bool B)				{ MOD_REG(SW_MODE, POL_STOP_L);			}
void TMCStepper::pol_stop_r(bool B)				{ MOD_REG(SW_MODE, POL_STOP_R);			}
void TMCStepper::swap_lr(bool B)				{ MOD_REG(SW_MODE, SWAP_LR);			}
void TMCStepper::latch_l_active(bool B)			{ MOD_REG(SW_MODE, LATCH_L_ACTIVE);		}
void TMCStepper::latch_l_inactive(bool B)		{ MOD_REG(SW_MODE, LATCH_L_INACTIVE);	}
void TMCStepper::latch_r_active(bool B)			{ MOD_REG(SW_MODE, LATCH_R_ACTIVE);		}
void TMCStepper::latch_r_inactive(bool B)		{ MOD_REG(SW_MODE, LATCH_R_INACTIVE);	}
void TMCStepper::en_latch_encoder(bool B)		{ MOD_REG(SW_MODE, EN_LATCH_ENCODER);	}
void TMCStepper::sg_stop(bool B)				{ MOD_REG(SW_MODE, SG_STOP);			}
void TMCStepper::en_softstop(bool B)			{ MOD_REG(SW_MODE, EN_SOFTSTOP);		}

bool TMCStepper::stop_r_enable()				{ GET_BYTE(SW_MODE, STOP_R_ENABLE);		}
bool TMCStepper::pol_stop_l()					{ GET_BYTE(SW_MODE, POL_STOP_L);		}
bool TMCStepper::pol_stop_r()					{ GET_BYTE(SW_MODE, POL_STOP_R);		}
bool TMCStepper::swap_lr()						{ GET_BYTE(SW_MODE, SWAP_LR);			}
bool TMCStepper::latch_l_active()				{ GET_BYTE(SW_MODE, LATCH_L_ACTIVE);	}
bool TMCStepper::latch_l_inactive()				{ GET_BYTE(SW_MODE, LATCH_L_INACTIVE);	}
bool TMCStepper::latch_r_active()				{ GET_BYTE(SW_MODE, LATCH_R_ACTIVE);	}
bool TMCStepper::latch_r_inactive()				{ GET_BYTE(SW_MODE, LATCH_R_INACTIVE);	}
bool TMCStepper::en_latch_encoder()				{ GET_BYTE(SW_MODE, EN_LATCH_ENCODER);	}
bool TMCStepper::sg_stop()						{ GET_BYTE(SW_MODE, SG_STOP);			}
bool TMCStepper::en_softstop()					{ GET_BYTE(SW_MODE, EN_SOFTSTOP);		}
