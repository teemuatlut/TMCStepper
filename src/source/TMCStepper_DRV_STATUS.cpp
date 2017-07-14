#include "TMCStepper.h"
#include "TMCStepper_MACROS.h"

uint32_t TMCStepper::DRV_STATUS() { READ_REG_R(DRV_STATUS); }

uint16_t TMCStepper::sg_result(){ GET_BYTE_R(DRV_STATUS, SG_RESULT); 	}
bool TMCStepper::fsactive()		{ GET_BYTE_R(DRV_STATUS, FSACTIVE); 	}
uint8_t TMCStepper::cs_actual()	{ GET_BYTE_R(DRV_STATUS, CS_ACTUAL); 	}
bool TMCStepper::stallguard()	{ GET_BYTE_R(DRV_STATUS, STALLGUARD); 	}
bool TMCStepper::ot()			{ GET_BYTE_R(DRV_STATUS, OT); 			}
bool TMCStepper::otpw()			{ GET_BYTE_R(DRV_STATUS, OTPW); 		}
bool TMCStepper::s2ga()			{ GET_BYTE_R(DRV_STATUS, S2GA); 		}
bool TMCStepper::s2gb()			{ GET_BYTE_R(DRV_STATUS, S2GB); 		}
bool TMCStepper::ola()			{ GET_BYTE_R(DRV_STATUS, OLA); 			}
bool TMCStepper::olb()			{ GET_BYTE_R(DRV_STATUS, OLB); 			}
bool TMCStepper::stst()			{ GET_BYTE_R(DRV_STATUS, STST); 		}
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