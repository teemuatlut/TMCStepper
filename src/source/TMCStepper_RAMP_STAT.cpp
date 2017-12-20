#include "TMCStepper.h"

uint32_t TMCStepper::RAMP_STAT() { READ_REG_R(RAMP_STAT); }

bool TMCStepper::status_stop_l()		{ GET_BYTE(RAMP_STAT, STATUS_STOP_L);		}
bool TMCStepper::status_stop_r()		{ GET_BYTE(RAMP_STAT, STATUS_STOP_R);		}
bool TMCStepper::status_latch_l()		{ GET_BYTE(RAMP_STAT, STATUS_LATCH_L);		}
bool TMCStepper::status_latch_r()		{ GET_BYTE(RAMP_STAT, STATUS_LATCH_R);		}
bool TMCStepper::event_stop_l()			{ GET_BYTE(RAMP_STAT, EVENT_STOP_L);		}
bool TMCStepper::event_stop_r()			{ GET_BYTE(RAMP_STAT, EVENT_STOP_R);		}
bool TMCStepper::event_stop_sg()		{ GET_BYTE(RAMP_STAT, EVENT_STOP_SG);		}
bool TMCStepper::event_pos_reached()	{ GET_BYTE(RAMP_STAT, EVENT_POS_REACHED);	}
bool TMCStepper::velocity_reached()		{ GET_BYTE(RAMP_STAT, VELOCITY_REACHED);	}
bool TMCStepper::position_reached()		{ GET_BYTE(RAMP_STAT, POSITION_REACHED);	}
bool TMCStepper::vzero()				{ GET_BYTE(RAMP_STAT, VZERO);	 			}
bool TMCStepper::t_zerowait_active()	{ GET_BYTE(RAMP_STAT, T_ZEROWAIT_ACTIVE);	}
bool TMCStepper::second_move()			{ GET_BYTE(RAMP_STAT, SECOND_MOVE);			}
bool TMCStepper::status_sg()			{ GET_BYTE(RAMP_STAT, STATUS_SG);	 		}
