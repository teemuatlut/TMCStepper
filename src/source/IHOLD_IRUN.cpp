#include "TMCStepper.h"

template class TMCStepper<TMC2130Stepper>;
template class TMCStepper<TMC2208Stepper>;

// IHOLD_IRUN
template<typename TYPE> uint32_t TMCStepper<TYPE>::IHOLD_IRUN() { return IHOLD_IRUN_register.sr; }
template<typename TYPE> void TMCStepper<TYPE>::IHOLD_IRUN(uint32_t input) {
	IHOLD_IRUN_register.sr = input;
	static_cast<TYPE*>(this)->write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr);
}

template<typename TYPE> void 	TMCStepper<TYPE>::ihold(uint8_t B) 		{ IHOLD_IRUN_register.ihold = B; 		static_cast<TYPE*>(this)->write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr); }
template<typename TYPE> void 	TMCStepper<TYPE>::irun(uint8_t B)  		{ IHOLD_IRUN_register.irun = B; 		static_cast<TYPE*>(this)->write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr); }
template<typename TYPE> void 	TMCStepper<TYPE>::iholddelay(uint8_t B)	{ IHOLD_IRUN_register.iholddelay = B; 	static_cast<TYPE*>(this)->write(IHOLD_IRUN_register.address, IHOLD_IRUN_register.sr); }

template<typename TYPE> uint8_t TMCStepper<TYPE>::ihold() 				{ return IHOLD_IRUN_register.ihold;		}
template<typename TYPE> uint8_t TMCStepper<TYPE>::irun()  				{ return IHOLD_IRUN_register.irun; 		}
template<typename TYPE> uint8_t TMCStepper<TYPE>::iholddelay()  			{ return IHOLD_IRUN_register.iholddelay;}
