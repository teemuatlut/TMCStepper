#pragma once

constexpr uint8_t TMC_READ 						= 0x00;
constexpr uint8_t TMC_WRITE 					= 0x80;

// Register memory positions
constexpr uint8_t REG_GCONF	 					= 0x00;
constexpr uint8_t REG_GSTAT	 					= 0x01;
constexpr uint8_t REG_IFCNT						= 0x02;
constexpr uint8_t REG_SLAVECONF	 			= 0x03;
constexpr uint8_t REG_IOIN	 					= 0x04;
constexpr uint8_t REG_OUTPUT					= 0x04;
constexpr uint8_t REG_X_COMPARE				= 0x05;
constexpr uint8_t REG_IHOLD_IRUN	 		= 0x10;
constexpr uint8_t REG_TPOWERDOWN	 		= 0x11;
constexpr uint8_t REG_TSTEP	 					= 0x12;
constexpr uint8_t REG_TPWMTHRS	 			= 0x13;
constexpr uint8_t REG_TCOOLTHRS				= 0x14;
constexpr uint8_t REG_THIGH						= 0x15;
constexpr uint8_t REG_RAMPMODE				= 0x20;
constexpr uint8_t REG_XACTUAL					= 0x21;
constexpr uint8_t REG_VACTUAL					= 0x22;
constexpr uint8_t REG_VSTART					= 0x23;
constexpr uint8_t REG_A1							= 0x24;
constexpr uint8_t REG_V1							= 0x25;
constexpr uint8_t REG_AMAX						= 0x26;
constexpr uint8_t REG_VMAX						= 0x27;
constexpr uint8_t REG_DMAX						= 0x28;
constexpr uint8_t REG_D1							= 0x2A;
constexpr uint8_t REG_VSTOP						= 0x2B;
constexpr uint8_t REG_TZEROWAIT				= 0x2C;
constexpr uint8_t REG_XTARGET					= 0x2D;
constexpr uint8_t REG_VDCMIN					= 0x33;
constexpr uint8_t REG_SW_MODE					= 0x34;
constexpr uint8_t REG_RAMP_STAT				= 0x35;
constexpr uint8_t REG_XLATCH					= 0x36;
constexpr uint8_t REG_ENCMODE					= 0x38;
constexpr uint8_t REG_X_ENC						= 0x39;
constexpr uint8_t REG_ENC_CONST				= 0x3A;
constexpr uint8_t REG_ENC_STATUS			= 0x3B;
constexpr uint8_t REG_ENC_LATCH				= 0x3C;
constexpr uint8_t REG_MSLUT0					= 0x60;
constexpr uint8_t REG_MSLUT1					= 0x61;
constexpr uint8_t REG_MSLUT2					= 0x62;
constexpr uint8_t REG_MSLUT3					= 0x63;
constexpr uint8_t REG_MSLUT4					= 0x64;
constexpr uint8_t REG_MSLUT5					= 0x65;
constexpr uint8_t REG_MSLUT6					= 0x66;
constexpr uint8_t REG_MSLUT7					= 0x67;
constexpr uint8_t REG_MSLUTSEL				= 0x68;
constexpr uint8_t REG_MSLUTSTART			= 0x69;
constexpr uint8_t REG_MSCNT	 					= 0x6A;
constexpr uint8_t REG_MSCURACT	 			= 0x6B;
constexpr uint8_t REG_CHOPCONF	 			= 0x6C;
constexpr uint8_t REG_COOLCONF				= 0x6D;
constexpr uint8_t REG_DCCTRL					= 0x6E;
constexpr uint8_t REG_DRV_STATUS	 		= 0x6F;
constexpr uint8_t REG_PWMCONF	 				= 0x70;
constexpr uint8_t REG_PWM_SCALE	 			= 0x71;
constexpr uint8_t REG_ENCM_CTRL	 			= 0x72;
constexpr uint8_t REG_LOST_STEPS			= 0x73;

// SPI_STATUS
constexpr uint8_t RESET_FLAG_bp				= 0;
constexpr uint8_t DRIVER_ERROR_bp			= 1;
constexpr uint8_t SG2_bp 							= 2;
constexpr uint8_t STANDSTILL_bp				= 3;
constexpr uint32_t RESET_FLAG_bm			= 0x1UL;
constexpr uint32_t DRIVER_ERROR_bm		= 0x2UL;
constexpr uint32_t SG2_bm 						= 0x4UL;
constexpr uint32_t STANDSTILL_bm			= 0x8UL;

// GCONF
constexpr uint8_t I_SCALE_ANALOG_bp						= 0;
constexpr uint8_t INTERNAL_RSENSE_bp					= 1;
constexpr uint8_t EN_PWM_MODE_bp							= 2;
constexpr uint8_t ENC_COMMUTATION_bp					= 3;
constexpr uint8_t SHAFT_bp										= 4;
constexpr uint8_t DIAG0_ERROR_bp							= 5;
constexpr uint8_t DIAG0_OTPW_bp								= 6;
constexpr uint8_t DIAG0_STALL_bp							= 7;
constexpr uint8_t DIAG0_STEP_bp								= 7;
constexpr uint8_t DIAG1_STALL_bp							= 8;
constexpr uint8_t DIAG1_DIR_bp								= 8;
constexpr uint8_t DIAG1_INDEX_bp							= 9;
constexpr uint8_t DIAG1_ONSTATE_bp	   				= 10;
constexpr uint8_t DIAG1_STEPS_SKIPPED_bp 			= 11;
constexpr uint8_t DIAG0_INT_PUSHPULL_bp  			= 12;
constexpr uint8_t DIAG1_POSCOMP_PUSHPULL_bp 	= 13;
constexpr uint8_t SMALL_HYSTERISIS_bp    			= 14;
constexpr uint8_t STOP_ENABLE_bp		   				= 15;
constexpr uint8_t DIRECT_MODE_bp		   				= 16;
constexpr uint32_t GCONF_bm										= 0x3FFFFUL;
constexpr uint32_t I_SCALE_ANALOG_bm					= 0x1UL;
constexpr uint32_t INTERNAL_RSENSE_bm					= 0x2UL;
constexpr uint32_t EN_PWM_MODE_bm							= 0x4UL;
constexpr uint32_t ENC_COMMUTATION_bm					= 0x8UL;
constexpr uint32_t SHAFT_bm										= 0x10UL;
constexpr uint32_t DIAG0_ERROR_bm							= 0x20UL;
constexpr uint32_t DIAG0_OTPW_bm							= 0x40UL;
constexpr uint32_t DIAG0_STALL_bm							= 0x80UL;
constexpr uint32_t DIAG0_STEP_bm							= 0x80UL;
constexpr uint32_t DIAG1_STALL_bm							= 0x100UL;
constexpr uint32_t DIAG1_DIR_bm								= 0x100UL;
constexpr uint32_t DIAG1_INDEX_bm							= 0x200UL;
constexpr uint32_t DIAG1_ONSTATE_bm						= 0x400UL;
constexpr uint32_t DIAG1_STEPS_SKIPPED_bm			= 0x800UL;
constexpr uint32_t DIAG0_INT_PUSHPULL_bm			= 0x1000UL;
constexpr uint32_t DIAG1_POSCOMP_PUSHPULL_bm	= 0x2000UL;
constexpr uint32_t SMALL_HYSTERISIS_bm				= 0x4000UL;
constexpr uint32_t STOP_ENABLE_bm							= 0x8000UL;
constexpr uint32_t DIRECT_MODE_bm							= 0x10000UL;
// GSTAT
constexpr uint8_t RESET_bp 										= 0;
constexpr uint8_t DRV_ERR_bp									= 1;
constexpr uint8_t UV_CP_bp										= 2;
constexpr uint32_t GSTAT_bm										= 0x7UL;
constexpr uint32_t RESET_bm 									= 0b1UL;
constexpr uint32_t DRV_ERR_bm									= 0b10UL;
constexpr uint32_t UV_CP_bm										= 0b100UL;
// IFCNT
constexpr uint8_t IFCNT_pb										= 0;
constexpr uint32_t IFCNT_bm										= 0xFFUL;
// SLAVECONF
constexpr uint8_t SLAVECONF_bp								= 0;
constexpr uint32_t SLAVECONF_bm								= 0xF00UL;
constexpr uint8_t SENDDELAY_bp								= 8;
constexpr uint32_t SENDDELAY_bm								= 0xF00UL;
// IOIN
constexpr uint8_t REFL_STEP_bp 								= 0;
constexpr uint8_t REFR_DIR_bp									= 1;
constexpr uint8_t ENCB_DCEN_CFG4_bp						= 2;
constexpr uint8_t ENCA_DCIN_CFG5_bp						= 3;
constexpr uint8_t DRV_ENN_CFG6_bp							= 4;
constexpr uint8_t ENC_N_DCO_bp 								= 5;
constexpr uint8_t SD_MODE_bp									= 6;
constexpr uint8_t SWCOMP_IN_bp								= 7;
constexpr uint8_t VERSION_bp		 	  					= 24;
constexpr uint32_t IOIN_bm										= 0xFF00003FUL;
constexpr uint32_t REFL_STEP_bm								= 0x1UL;
constexpr uint32_t REFR_DIR_bm								= 0x2UL;
constexpr uint32_t ENCB_DCEN_CFG4_bm					= 0x4UL;
constexpr uint32_t ENCA_DCIN_CFG5_bm					= 0x8UL;
constexpr uint32_t DRV_ENN_CFG6_bm						= 0x10UL;
constexpr uint32_t ENC_N_DCO_bm								= 0x20UL;
constexpr uint32_t SD_MODE_bm									= 0x40UL;
constexpr uint32_t SWCOMP_IN_bm								= 0x80UL;
constexpr uint32_t VERSION_bm									= 0xFF000000UL;
// OUTPUT
constexpr uint8_t OUTPUT_bp										= 0;
constexpr uint32_t OUTPUT_bm									= 0x1UL;
// X_COMPARE
constexpr uint8_t X_COMPARE_bp								= 0;
constexpr uint32_t X_COMPARE_bm								= 0xFFFFFFFFUL;
// IHOLD_IRUN
constexpr uint8_t IHOLD_bp 										= 0;
constexpr uint8_t IRUN_bp											= 8;
constexpr uint8_t IHOLDDELAY_bp	   						= 16;
constexpr uint32_t IHOLD_IRUN_bm							= 0xF1F1FUL;
constexpr uint32_t IHOLD_bm 									= 0x1FUL;
constexpr uint32_t IRUN_bm										= 0x1F00UL;
constexpr uint32_t IHOLDDELAY_bm	    				= 0xF0000UL;
// TPOWERDOWN
constexpr uint8_t TPOWERDOWN_bp								= 0;
constexpr uint32_t TPOWERDOWN_bm							= 0xFFUL;
// TSTEP
constexpr uint8_t TSTEP_bp										= 0;
constexpr uint32_t TSTEP_bm										= 0xFFFFFUL;
// TPWMTHRS
constexpr uint8_t TPWMTHRS_bp 								= 0;
constexpr uint32_t TPWMTHRS_bm								= 0xFFFFFUL;
// TCOOLTHRS
constexpr uint8_t TCOOLTHRS_bp								= 0;
constexpr uint32_t TCOOLTHRS_bm								= 0xFFFFFUL;
// THIGH
constexpr uint8_t THIGH_bp 										= 0;
constexpr uint32_t THIGH_bm										= 0xFFFFFUL;
// RAMPMODE
constexpr uint8_t RAMPMODE_bp									= 0;
constexpr uint32_t RAMPMODE_bm								= 0x3UL;
// XACTUAL
constexpr uint8_t XACTUAL_bp									= 0;
constexpr uint32_t XACTUAL_bm									= 0xFFFFFFFFUL;
// VACTUAL
constexpr uint8_t VACTUAL_bp									= 0;
constexpr uint32_t VACTUAL_bm									= 0xFFFFFFUL;
// VSTART
constexpr uint8_t VSTART_bp										= 0;
constexpr uint32_t VSTART_bm									= 0x3FFFFUL;
// A1
constexpr uint8_t A1_bp												= 0;
constexpr uint32_t A1_bm											= 0xFFFFUL;
// V1
constexpr uint8_t V1_bp												= 0;
constexpr uint32_t V1_bm											= 0xFFFFFUL;
// AMAX
constexpr uint8_t AMAX_bp											= 0;
constexpr uint32_t AMAX_bm										= 0xFFFFUL;
// VMAX
constexpr uint8_t VMAX_bp											= 0;
constexpr uint32_t VMAX_bm										= 0x7FFFFF;
// DMAX
constexpr uint8_t DMAX_bp											= 0;
constexpr uint32_t DMAX_bm										= 0xFFFFUL;
// D1
constexpr uint8_t D1_bp												= 0;
constexpr uint32_t D1_bm											= 0xFFFFUL;
// VSTOP
constexpr uint8_t VSTOP_bp										= 0;
constexpr uint32_t VSTOP_bm										= 0x3FFFFUL;
// TZEROWAIT
constexpr uint8_t TZEROWAIT_bp								= 0;
constexpr uint32_t TZEROWAIT_bm								= 0xFFFFUL;
// XTARGET
constexpr uint8_t XTARGET_bp									= 0;
constexpr uint32_t XTARGET_bm									= 0xFFFFFFFFUL;
// VDCMIN
constexpr uint8_t VDCMIN_bp										= 0;
constexpr uint32_t VDCMIN_bm									= 0x7FFFFFUL;
// MSLUT0
constexpr uint8_t MSLUT0_bp										= 0;
constexpr uint32_t MSLUT0_bm									= 0xFFFFFFFFUL;
// MSLUT1
constexpr uint8_t MSLUT1_bp										= 0;
constexpr uint32_t MSLUT1_bm									= 0xFFFFFFFFUL;
// MSLUT2
constexpr uint8_t MSLUT2_bp										= 0;
constexpr uint32_t MSLUT2_bm									= 0xFFFFFFFFUL;
// MSLUT3
constexpr uint8_t MSLUT3_bp										= 0;
constexpr uint32_t MSLUT3_bm									= 0xFFFFFFFFUL;
// MSLUT4
constexpr uint8_t MSLUT4_bp										= 0;
constexpr uint32_t MSLUT4_bm									= 0xFFFFFFFFUL;
// MSLUT5
constexpr uint8_t MSLUT5_bp										= 0;
constexpr uint32_t MSLUT5_bm									= 0xFFFFFFFFUL;
// MSLUT6
constexpr uint8_t MSLUT6_bp										= 0;
constexpr uint32_t MSLUT6_bm									= 0xFFFFFFFFUL;
// MSLUT7
constexpr uint8_t MSLUT7_bp										= 0;
constexpr uint32_t MSLUT7_bm									= 0xFFFFFFFFUL;
// MSLUTSEL
constexpr uint8_t MSLUTSEL_bp									= 0;
constexpr uint32_t MSLUTSEL_bm								= 0xFFFFFFFFUL;
// MSLUTSTART
constexpr uint8_t START_SIN_bp								= 0;
constexpr uint8_t START_SIN90_bp							= 16;
constexpr uint32_t START_SIN_bm 							= 0xFFUL;
constexpr uint32_t START_SIN90_bm							= 0xFF0000UL;
// MSCNT
constexpr uint8_t MSCNT_bp										= 0;
constexpr uint32_t MSCNT_bm										= 0x3FFUL;
// MSCURACT
constexpr uint8_t CUR_A_bp										= 0;
constexpr uint8_t CUR_B_bp									  = 16;
constexpr uint32_t CUR_A_bm										= 0x1FFUL;
constexpr uint32_t CUR_B_bm										= 0x1FF0000UL;
// SW_MODE
constexpr uint8_t STOP_L_ENABLE_bp						= 0;
constexpr uint8_t STOP_R_ENABLE_bp						= 1;
constexpr uint8_t POL_STOP_L_bp								= 2;
constexpr uint8_t POL_STOP_R_bp								= 3;
constexpr uint8_t SWAP_LR_bp									= 4;
constexpr uint8_t LATCH_L_ACTIVE_bp						= 5;
constexpr uint8_t LATCH_L_INACTIVE_bp					= 6;
constexpr uint8_t LATCH_R_ACTIVE_bp						= 7;
constexpr uint8_t LATCH_R_INACTIVE_bp					= 8;
constexpr uint8_t EN_LATCH_ENCODER_bp					= 9;
constexpr uint8_t SG_STOP_bp		   						= 10;
constexpr uint8_t EN_SOFTSTOP_bp	   					= 11;
constexpr uint32_t STOP_L_ENABLE_bm						= 0x1UL;
constexpr uint32_t STOP_R_ENABLE_bm						= 0x2UL;
constexpr uint32_t POL_STOP_L_bm							= 0x4UL;
constexpr uint32_t POL_STOP_R_bm							= 0x8UL;
constexpr uint32_t SWAP_LR_bm									= 0x10UL;
constexpr uint32_t LATCH_L_ACTIVE_bm					= 0x20UL;
constexpr uint32_t LATCH_L_INACTIVE_bm				= 0x40UL;
constexpr uint32_t LATCH_R_ACTIVE_bm					= 0x80UL;
constexpr uint32_t LATCH_R_INACTIVE_bm				= 0x100UL;
constexpr uint32_t EN_LATCH_ENCODER_bm				= 0x200UL;
constexpr uint32_t SG_STOP_bm									= 0x400UL;
constexpr uint32_t EN_SOFTSTOP_bm							= 0x800UL;
// RAMP_STAT
constexpr uint8_t STATUS_STOP_L_bp						= 0;
constexpr uint8_t STATUS_STOP_R_bp						= 1;
constexpr uint8_t STATUS_LATCH_L_bp						= 2;
constexpr uint8_t STATUS_LATCH_R_bp						= 3;
constexpr uint8_t EVENT_STOP_L_bp							= 4;
constexpr uint8_t EVENT_STOP_R_bp							= 5;
constexpr uint8_t EVENT_STOP_SG_bp						= 6;
constexpr uint8_t EVENT_POS_REACHED_bp				= 7;
constexpr uint8_t VELOCITY_REACHED_bp					= 8;
constexpr uint8_t POSITION_REACHED_bp					= 9;
constexpr uint8_t VZERO_bp										= 10;
constexpr uint8_t T_ZEROWAIT_ACTIVE_bp				= 11;
constexpr uint8_t SECOND_MOVE_bp							= 12;
constexpr uint8_t STATUS_SG_bp								= 13;
constexpr uint32_t STATUS_STOP_L_bm						= 0x1UL;
constexpr uint32_t STATUS_STOP_R_bm						= 0x2UL;
constexpr uint32_t STATUS_LATCH_L_bm					= 0x4UL;
constexpr uint32_t STATUS_LATCH_R_bm					= 0x8UL;
constexpr uint32_t EVENT_STOP_L_bm						= 0x10UL;
constexpr uint32_t EVENT_STOP_R_bm						= 0x20UL;
constexpr uint32_t EVENT_STOP_SG_bm						= 0x40UL;
constexpr uint32_t EVENT_POS_REACHED_bm				= 0x80UL;
constexpr uint32_t VELOCITY_REACHED_bm				= 0x100UL;
constexpr uint32_t POSITION_REACHED_bm				= 0x200UL;
constexpr uint32_t VZERO_bm										= 0x400UL;
constexpr uint32_t T_ZEROWAIT_ACTIVE_bm				= 0x800UL;
constexpr uint32_t SECOND_MOVE_bm							= 0x1000UL;
constexpr uint32_t STATUS_SG_bm								= 0x2000UL;
// ENCMODE
constexpr uint8_t POL_A_bp										= 0;
constexpr uint8_t POL_B_bp										= 1;
constexpr uint8_t POL_N_bp										= 2;
constexpr uint8_t IGNORE_AB_bp								= 3;
constexpr uint8_t CLR_CONT_bp									= 4;
constexpr uint8_t CLR_ONCE_bp									= 5;
constexpr uint8_t POS_EDGE_bp									= 6;
constexpr uint8_t NEG_EDGE_bp									= 7;
constexpr uint8_t CLR_ENC_X_bp								= 8;
constexpr uint8_t LATCH_X_ACT_bp							= 9;
constexpr uint8_t ENC_SEL_DECIMAL_bp					= 10;
constexpr uint32_t POL_A_bm										= 0x1UL;
constexpr uint32_t POL_B_bm										= 0x2UL;
constexpr uint32_t POL_N_bm										= 0x4UL;
constexpr uint32_t IGNORE_AB_bm								= 0x8UL;
constexpr uint32_t CLR_CONT_bm								= 0x10UL;
constexpr uint32_t CLR_ONCE_bm								= 0x20UL;
constexpr uint32_t POS_EDGE_bm								= 0x40UL;
constexpr uint32_t NEG_EDGE_bm								= 0x80UL;
constexpr uint32_t CLR_ENC_X_bm								= 0x100UL;
constexpr uint32_t LATCH_X_ACT_bm							= 0x200UL;
constexpr uint32_t ENC_SEL_DECIMAL_bm					= 0x400UL;
// CHOPCONF
constexpr uint8_t TOFF_bp											= 0;
constexpr uint8_t HSTRT_bp										= 4;
constexpr uint8_t FD_bp			  								= 4;
constexpr uint8_t HEND_bp											= 7;
constexpr uint8_t DISFDCC_bp		  						= 12;
constexpr uint8_t RNDTF_bp		  							= 13;
constexpr uint8_t CHM_bp			 								= 14;
constexpr uint8_t TBL_bp 			 								= 15;
constexpr uint8_t VSENSE_bp		  							= 17;
constexpr uint8_t VHIGHFS_bp		  						= 18;
constexpr uint8_t VHIGHCHM_bp		  						= 19;
constexpr uint8_t SYNC_bp			 								= 20;
constexpr uint8_t MRES_bp 		 								= 24;
constexpr uint8_t INTPOL_bp		  							= 28;
constexpr uint8_t DEDGE_bp		  							= 29;
constexpr uint8_t DISS2G_bp		  							= 30;
constexpr uint32_t CHOPCONF_bm								= 0xFFFFFFFFUL;
constexpr uint32_t TOFF_bm			  						= 0xFUL;
constexpr uint32_t HSTRT_bm		 								= 0x70UL;
constexpr uint32_t FD_bm											= 0x830UL;
constexpr uint32_t HEND_bm										= 0x780UL;
constexpr uint32_t DISFDCC_bm									= 0x1000UL;
constexpr uint32_t RNDTF_bm										= 0x2000UL;
constexpr uint32_t CHM_bm											= 0x4000UL;
constexpr uint32_t TBL_bm		  								= 0x18000UL;
constexpr uint32_t VSENSE_bm	  							= 0x20000UL;
constexpr uint32_t VHIGHFS_bm									= 0x40000UL;
constexpr uint32_t VHIGHCHM_bm								= 0x80000UL;
constexpr uint32_t SYNC_bm										= 0xF00000UL;
constexpr uint32_t MRES_bm										= 0xF000000UL;
constexpr uint32_t INTPOL_bm  								= 0x10000000UL;
constexpr uint32_t DEDGE_bm   								= 0x20000000UL;
constexpr uint32_t DISS2G_bm  								= 0x40000000UL;
// COOLCONF
constexpr uint8_t SEMIN_bp										= 0;
constexpr uint8_t SEUP_bp											= 5;
constexpr uint8_t SEMAX_bp										= 8;
constexpr uint8_t SEDN_bp											= 13;
constexpr uint8_t SEIMIN_bp										= 15;
constexpr uint8_t SGT_bp											= 16;
constexpr uint8_t SFILT_bp										= 24;
constexpr uint32_t COOLCONF_bm								= 0x3FFFFFFUL;
constexpr uint32_t SEMIN_bm										= 0xFUL;
constexpr uint32_t SEUP_bm										= 0x60UL;
constexpr uint32_t SEMAX_bm										= 0xF00UL;
constexpr uint32_t SEDN_bm										= 0x6000UL;
constexpr uint32_t SEIMIN_bm									= 0x8000UL;
constexpr uint32_t SGT_bm											= 0x7F0000UL;
constexpr uint32_t SFILT_bm										= 0x1000000UL;
// DCCTRL
constexpr uint8_t DC_TIME_bp									= 0;
constexpr uint8_t DC_SG_bp										= 16;
constexpr uint32_t DC_TIME_bm									= 0x3FFUL;
constexpr uint32_t DC_SG_bm										= 0xFF0000UL;
// DRV_STATUS
constexpr uint8_t SG_RESULT_bp								= 0;
constexpr uint8_t FSACTIVE_bp									= 15;
constexpr uint8_t CS_ACTUAL_bp								= 16;
constexpr uint8_t STALLGUARD_bp								= 24;
constexpr uint8_t OT_bp												= 25;
constexpr uint8_t OTPW_bp											= 26;
constexpr uint8_t S2GA_bp											= 27;
constexpr uint8_t S2GB_bp											= 28;
constexpr uint8_t OLA_bp											= 29;
constexpr uint8_t OLB_bp											= 30;
constexpr uint8_t STST_bp											= 31;
constexpr uint32_t DRV_STATUS_bm							= 0xFFFFFFFFUL;
constexpr uint32_t SG_RESULT_bm								= 0x3FFUL;
constexpr uint32_t FSACTIVE_bm								= 0x8000UL;
constexpr uint32_t CS_ACTUAL_bm								= 0x1F0000UL;
constexpr uint32_t STALLGUARD_bm							= 0x1000000UL;
constexpr uint32_t OT_bm											= 0x2000000UL;
constexpr uint32_t OTPW_bm										= 0x4000000UL;
constexpr uint32_t S2GA_bm										= 0x8000000UL;
constexpr uint32_t S2GB_bm										= 0x10000000UL;
constexpr uint32_t OLA_bm											= 0x20000000UL;
constexpr uint32_t OLB_bm											= 0x40000000UL;
constexpr uint32_t STST_bm										= 0x80000000UL;
// PWMCONF
constexpr uint8_t PWM_AMPL_bp									= 0;
constexpr uint8_t PWM_GRAD_bp									= 8;
constexpr uint8_t PWM_FREQ_bp									= 16;
constexpr uint8_t PWM_AUTOSCALE_bp						= 18;
constexpr uint8_t PWM_SYMMETRIC_bp						= 19;
constexpr uint8_t FREEWHEEL_bp								= 20;
constexpr uint32_t PWMCONF_bm									= 0x7FFFFFUL;
constexpr uint32_t PWM_AMPL_bm 								= 0xFFUL;
constexpr uint32_t PWM_GRAD_bm 								= 0xFF00UL;
constexpr uint32_t PWM_FREQ_bm 								= 0x30000UL;
constexpr uint32_t PWM_AUTOSCALE_bm						= 0x40000UL;
constexpr uint32_t PWM_SYMMETRIC_bm						= 0x80000UL;
constexpr uint32_t FREEWHEEL_bm 							= 0x300000UL;
// PWM_SCALE
constexpr uint8_t PWM_SCALE_bp								= 0;
constexpr uint32_t PWM_SCALE_bm								= 0xFFUL;
// ENCM_CTRL
constexpr uint8_t INV_bp											= 0;
constexpr uint8_t MAXSPEED_bp									= 1;
constexpr uint32_t INV_bm											= 0x1UL;
constexpr uint32_t MAXSPEED_bm								= 0x2UL;
// LOST_STEPS
constexpr uint8_t LOST_STEPS_bp								= 0;
constexpr uint32_t LOST_STEPS_bm							= 0xFFFFFUL;
