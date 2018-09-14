#include "TMCStepper.h"
#include "TMC_DECL.h"

#define GET_REG(SETTING) do{ RAMP_STAT(); return REG(RAMP_STAT).SETTING; }while(0)

TT uint32_t TMC5130StepperBase<T>::RAMP_STAT() {
	REG(RAMP_STAT).sr = SELF.read(ADR(RAMP_STAT));
	return REG(RAMP_STAT).sr;
}

TT bool TMC5130StepperBase<T>::status_stop_l()			{ GET_REG(status_stop_l);			}
TT bool TMC5130StepperBase<T>::status_stop_r()			{ GET_REG(status_stop_r);			}
TT bool TMC5130StepperBase<T>::status_latch_l()			{ GET_REG(status_latch_l);		}
TT bool TMC5130StepperBase<T>::status_latch_r()			{ GET_REG(status_latch_r);		}
TT bool TMC5130StepperBase<T>::event_stop_l()				{ GET_REG(event_stop_l);			}
TT bool TMC5130StepperBase<T>::event_stop_r()				{ GET_REG(event_stop_r);			}
TT bool TMC5130StepperBase<T>::event_stop_sg()			{ GET_REG(event_stop_sg);			}
TT bool TMC5130StepperBase<T>::event_pos_reached()	{ GET_REG(event_pos_reached);	}
TT bool TMC5130StepperBase<T>::velocity_reached()		{ GET_REG(velocity_reached);	}
TT bool TMC5130StepperBase<T>::position_reached()		{ GET_REG(position_reached);	}
TT bool TMC5130StepperBase<T>::vzero()							{ GET_REG(vzero);	 						}
TT bool TMC5130StepperBase<T>::t_zerowait_active()	{ GET_REG(t_zerowait_active);	}
TT bool TMC5130StepperBase<T>::second_move()				{ GET_REG(second_move);				}
TT bool TMC5130StepperBase<T>::status_sg()					{ GET_REG(status_sg);	 				}
