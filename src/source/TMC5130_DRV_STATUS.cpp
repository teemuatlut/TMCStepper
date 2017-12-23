#include "TMCStepper.h"

uint32_t TMC5130Stepper::DRV_STATUS() { READ_REG_R(DRV_STATUS); }

uint16_t TMC5130Stepper::sg_result(){ GET_BYTE_R(DRV_STATUS, SG_RESULT); 	}
bool TMC5130Stepper::fsactive()		{ GET_BYTE_R(DRV_STATUS, FSACTIVE); 	}
uint8_t TMC5130Stepper::cs_actual()	{ GET_BYTE_R(DRV_STATUS, CS_ACTUAL); 	}
bool TMC5130Stepper::stallguard()	{ GET_BYTE_R(DRV_STATUS, STALLGUARD); 	}
bool TMC5130Stepper::ot()			{ GET_BYTE_R(DRV_STATUS, OT); 			}
bool TMC5130Stepper::otpw()			{ GET_BYTE_R(DRV_STATUS, OTPW); 		}
bool TMC5130Stepper::s2ga()			{ GET_BYTE_R(DRV_STATUS, S2GA); 		}
bool TMC5130Stepper::s2gb()			{ GET_BYTE_R(DRV_STATUS, S2GB); 		}
bool TMC5130Stepper::ola()			{ GET_BYTE_R(DRV_STATUS, OLA); 			}
bool TMC5130Stepper::olb()			{ GET_BYTE_R(DRV_STATUS, OLB); 			}
bool TMC5130Stepper::stst()			{ GET_BYTE_R(DRV_STATUS, STST); 		}
/*
uint16_t TMCStepper::sg_result()	{
	uint32_t drv_status = 0x00000000UL;
	Serial.print("drv_status=");
	Serial.print(drv_status);
	drv_status = DRV_STATUS();
	Serial.print("\tdrv_status=");
	Serial.print(drv_status);
	Serial.print("\t");

	return drv_status&SG_RESULT_bm;
}
*/
