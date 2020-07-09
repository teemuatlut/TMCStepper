#include "TMCStepper.h"

#define GET_REG(SETTING) RAMP_STAT_t r{0}; r.sr = RAMP_STAT(); return r.SETTING
/*
uint16_t TMC5130Stepper::RAMP_STAT() {
	return read(RAMP_STAT_t::address);
}

bool TMC5130Stepper::status_stop_l()		{ return RAMP_STAT_t{ RAMP_STAT() }.status_stop_l;		}
bool TMC5130Stepper::status_stop_r()		{ return RAMP_STAT_t{ RAMP_STAT() }.status_stop_r;		}
bool TMC5130Stepper::status_latch_l()		{ return RAMP_STAT_t{ RAMP_STAT() }.status_latch_l;		}
bool TMC5130Stepper::status_latch_r()		{ return RAMP_STAT_t{ RAMP_STAT() }.status_latch_r;		}
bool TMC5130Stepper::event_stop_l()			{ return RAMP_STAT_t{ RAMP_STAT() }.event_stop_l;		}
bool TMC5130Stepper::event_stop_r()			{ return RAMP_STAT_t{ RAMP_STAT() }.event_stop_r;		}
bool TMC5130Stepper::event_stop_sg()		{ return RAMP_STAT_t{ RAMP_STAT() }.event_stop_sg;		}
bool TMC5130Stepper::event_pos_reached()	{ return RAMP_STAT_t{ RAMP_STAT() }.event_pos_reached;	}
bool TMC5130Stepper::velocity_reached()		{ return RAMP_STAT_t{ RAMP_STAT() }.velocity_reached;	}
bool TMC5130Stepper::position_reached()		{ return RAMP_STAT_t{ RAMP_STAT() }.position_reached;	}
bool TMC5130Stepper::vzero()				{ return RAMP_STAT_t{ RAMP_STAT() }.vzero;	 			}
bool TMC5130Stepper::t_zerowait_active()	{ return RAMP_STAT_t{ RAMP_STAT() }.t_zerowait_active;	}
bool TMC5130Stepper::second_move()			{ return RAMP_STAT_t{ RAMP_STAT() }.second_move;		}
bool TMC5130Stepper::status_sg()			{ return RAMP_STAT_t{ RAMP_STAT() }.status_sg;	 		}
*/