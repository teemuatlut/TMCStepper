#include "TMCStepper.h"

uint32_t TMC5130Stepper::RAMP_STAT() { READ_REG_R(RAMP_STAT); }

bool TMC5130Stepper::status_stop_l()		{ GET_BYTE(RAMP_STAT, STATUS_STOP_L);		}
bool TMC5130Stepper::status_stop_r()		{ GET_BYTE(RAMP_STAT, STATUS_STOP_R);		}
bool TMC5130Stepper::status_latch_l()		{ GET_BYTE(RAMP_STAT, STATUS_LATCH_L);		}
bool TMC5130Stepper::status_latch_r()		{ GET_BYTE(RAMP_STAT, STATUS_LATCH_R);		}
bool TMC5130Stepper::event_stop_l()			{ GET_BYTE(RAMP_STAT, EVENT_STOP_L);		}
bool TMC5130Stepper::event_stop_r()			{ GET_BYTE(RAMP_STAT, EVENT_STOP_R);		}
bool TMC5130Stepper::event_stop_sg()		{ GET_BYTE(RAMP_STAT, EVENT_STOP_SG);		}
bool TMC5130Stepper::event_pos_reached()	{ GET_BYTE(RAMP_STAT, EVENT_POS_REACHED);	}
bool TMC5130Stepper::velocity_reached()		{ GET_BYTE(RAMP_STAT, VELOCITY_REACHED);	}
bool TMC5130Stepper::position_reached()		{ GET_BYTE(RAMP_STAT, POSITION_REACHED);	}
bool TMC5130Stepper::vzero()				{ GET_BYTE(RAMP_STAT, VZERO);	 			}
bool TMC5130Stepper::t_zerowait_active()	{ GET_BYTE(RAMP_STAT, T_ZEROWAIT_ACTIVE);	}
bool TMC5130Stepper::second_move()			{ GET_BYTE(RAMP_STAT, SECOND_MOVE);			}
bool TMC5130Stepper::status_sg()			{ GET_BYTE(RAMP_STAT, STATUS_SG);	 		}
