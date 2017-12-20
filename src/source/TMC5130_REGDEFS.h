#pragma once

cfg.TMC_READ 						= 0x00;
cfg.TMC_WRITE 					= 0x80;

// Register memory positions
cfg.REG_GCONF	 					= 0x00;
cfg.REG_GSTAT	 					= 0x01;
cfg.REG_IFCNT						= 0x02;
cfg.REG_SLAVECONF	 			= 0x03;
cfg.REG_IOIN	 					= 0x04;
cfg.REG_OUTPUT					= 0x04;
cfg.REG_X_COMPARE				= 0x05;
cfg.REG_IHOLD_IRUN	 		= 0x10;
cfg.REG_TPOWERDOWN	 		= 0x11;
cfg.REG_TSTEP	 					= 0x12;
cfg.REG_TPWMTHRS	 			= 0x13;
cfg.REG_TCOOLTHRS				= 0x14;
cfg.REG_THIGH						= 0x15;
cfg.REG_RAMPMODE				= 0x20;
cfg.REG_XACTUAL					= 0x21;
cfg.REG_VACTUAL					= 0x22;
cfg.REG_VSTART					= 0x23;
cfg.REG_A1							= 0x24;
cfg.REG_V1							= 0x25;
cfg.REG_AMAX						= 0x26;
cfg.REG_VMAX						= 0x27;
cfg.REG_DMAX						= 0x28;
cfg.REG_D1							= 0x2A;
cfg.REG_VSTOP						= 0x2B;
cfg.REG_TZEROWAIT				= 0x2C;
cfg.REG_XTARGET					= 0x2D;
cfg.REG_VDCMIN					= 0x33;
cfg.REG_SW_MODE					= 0x34;
cfg.REG_RAMP_STAT				= 0x35;
cfg.REG_XLATCH					= 0x36;
cfg.REG_ENCMODE					= 0x38;
cfg.REG_X_ENC						= 0x39;
cfg.REG_ENC_CONST				= 0x3A;
cfg.REG_ENC_STATUS			= 0x3B;
cfg.REG_ENC_LATCH				= 0x3C;
cfg.REG_MSLUT0					= 0x60;
cfg.REG_MSLUT1					= 0x61;
cfg.REG_MSLUT2					= 0x62;
cfg.REG_MSLUT3					= 0x63;
cfg.REG_MSLUT4					= 0x64;
cfg.REG_MSLUT5					= 0x65;
cfg.REG_MSLUT6					= 0x66;
cfg.REG_MSLUT7					= 0x67;
cfg.REG_MSLUTSEL				= 0x68;
cfg.REG_MSLUTSTART			= 0x69;
cfg.REG_MSCNT	 					= 0x6A;
cfg.REG_MSCURACT	 			= 0x6B;
cfg.REG_CHOPCONF	 			= 0x6C;
cfg.REG_COOLCONF				= 0x6D;
cfg.REG_DCCTRL					= 0x6E;
cfg.REG_DRV_STATUS	 		= 0x6F;
cfg.REG_PWMCONF	 				= 0x70;
cfg.REG_PWM_SCALE	 			= 0x71;
cfg.REG_ENCM_CTRL	 			= 0x72;
cfg.REG_LOST_STEPS			= 0x73;

// SPI_STATUS
cfg.RESET_FLAG_bp				= 0;
cfg.DRIVER_ERROR_bp			= 1;
cfg.SG2_bp 							= 2;
cfg.STANDSTILL_bp				= 3;
cfg.RESET_FLAG_bm			= 0x1UL;
cfg.DRIVER_ERROR_bm		= 0x2UL;
cfg.SG2_bm 						= 0x4UL;
cfg.STANDSTILL_bm			= 0x8UL;

// GCONF
cfg.I_SCALE_ANALOG_bp						= 0;
cfg.INTERNAL_RSENSE_bp					= 1;
cfg.EN_PWM_MODE_bp							= 2;
cfg.ENC_COMMUTATION_bp					= 3;
cfg.SHAFT_bp										= 4;
cfg.DIAG0_ERROR_bp							= 5;
cfg.DIAG0_OTPW_bp								= 6;
cfg.DIAG0_STALL_bp							= 7;
cfg.DIAG0_STEP_bp								= 7;
cfg.DIAG1_STALL_bp							= 8;
cfg.DIAG1_DIR_bp								= 8;
cfg.DIAG1_INDEX_bp							= 9;
cfg.DIAG1_ONSTATE_bp	   				= 10;
cfg.DIAG1_STEPS_SKIPPED_bp 			= 11;
cfg.DIAG0_INT_PUSHPULL_bp  			= 12;
cfg.DIAG1_POSCOMP_PUSHPULL_bp 	= 13;
cfg.SMALL_HYSTERISIS_bp    			= 14;
cfg.STOP_ENABLE_bp		   				= 15;
cfg.DIRECT_MODE_bp		   				= 16;
cfg.GCONF_bm										= 0x3FFFFUL;
cfg.I_SCALE_ANALOG_bm					= 0x1UL;
cfg.INTERNAL_RSENSE_bm					= 0x2UL;
cfg.EN_PWM_MODE_bm							= 0x4UL;
cfg.ENC_COMMUTATION_bm					= 0x8UL;
cfg.SHAFT_bm										= 0x10UL;
cfg.DIAG0_ERROR_bm							= 0x20UL;
cfg.DIAG0_OTPW_bm							= 0x40UL;
cfg.DIAG0_STALL_bm							= 0x80UL;
cfg.DIAG0_STEP_bm							= 0x80UL;
cfg.DIAG1_STALL_bm							= 0x100UL;
cfg.DIAG1_DIR_bm								= 0x100UL;
cfg.DIAG1_INDEX_bm							= 0x200UL;
cfg.DIAG1_ONSTATE_bm						= 0x400UL;
cfg.DIAG1_STEPS_SKIPPED_bm			= 0x800UL;
cfg.DIAG0_INT_PUSHPULL_bm			= 0x1000UL;
cfg.DIAG1_POSCOMP_PUSHPULL_bm	= 0x2000UL;
cfg.SMALL_HYSTERISIS_bm				= 0x4000UL;
cfg.STOP_ENABLE_bm							= 0x8000UL;
cfg.DIRECT_MODE_bm							= 0x10000UL;
// GSTAT
cfg.RESET_bp 										= 0;
cfg.DRV_ERR_bp									= 1;
cfg.UV_CP_bp										= 2;
cfg.GSTAT_bm										= 0x7UL;
cfg.RESET_bm 									= 0b1UL;
cfg.DRV_ERR_bm									= 0b10UL;
cfg.UV_CP_bm										= 0b100UL;
// IFCNT
cfg.IFCNT_pb										= 0;
cfg.IFCNT_bm										= 0xFFUL;
// SLAVECONF
cfg.SLAVECONF_bp								= 0;
cfg.SLAVECONF_bm								= 0xF00UL;
cfg.SENDDELAY_bp								= 8;
cfg.SENDDELAY_bm								= 0xF00UL;
// IOIN
cfg.REFL_STEP_bp 								= 0;
cfg.REFR_DIR_bp									= 1;
cfg.ENCB_DCEN_CFG4_bp						= 2;
cfg.ENCA_DCIN_CFG5_bp						= 3;
cfg.DRV_ENN_CFG6_bp							= 4;
cfg.ENC_N_DCO_bp 								= 5;
cfg.SD_MODE_bp									= 6;
cfg.SWCOMP_IN_bp								= 7;
cfg.VERSION_bp		 	  					= 24;
cfg.IOIN_bm										= 0xFF00003FUL;
cfg.REFL_STEP_bm								= 0x1UL;
cfg.REFR_DIR_bm								= 0x2UL;
cfg.ENCB_DCEN_CFG4_bm					= 0x4UL;
cfg.ENCA_DCIN_CFG5_bm					= 0x8UL;
cfg.DRV_ENN_CFG6_bm						= 0x10UL;
cfg.ENC_N_DCO_bm								= 0x20UL;
cfg.SD_MODE_bm									= 0x40UL;
cfg.SWCOMP_IN_bm								= 0x80UL;
cfg.VERSION_bm									= 0xFF000000UL;
// OUTPUT
cfg.OUTPUT_bp										= 0;
cfg.OUTPUT_bm									= 0x1UL;
// X_COMPARE
cfg.X_COMPARE_bp								= 0;
cfg.X_COMPARE_bm								= 0xFFFFFFFFUL;
// IHOLD_IRUN
cfg.IHOLD_bp 										= 0;
cfg.IRUN_bp											= 8;
cfg.IHOLDDELAY_bp	   						= 16;
cfg.IHOLD_IRUN_bm							= 0xF1F1FUL;
cfg.IHOLD_bm 									= 0x1FUL;
cfg.IRUN_bm										= 0x1F00UL;
cfg.IHOLDDELAY_bm	    				= 0xF0000UL;
// TPOWERDOWN
cfg.TPOWERDOWN_bp								= 0;
cfg.TPOWERDOWN_bm							= 0xFFUL;
// TSTEP
cfg.TSTEP_bp										= 0;
cfg.TSTEP_bm										= 0xFFFFFUL;
// TPWMTHRS
cfg.TPWMTHRS_bp 								= 0;
cfg.TPWMTHRS_bm								= 0xFFFFFUL;
// TCOOLTHRS
cfg.TCOOLTHRS_bp								= 0;
cfg.TCOOLTHRS_bm								= 0xFFFFFUL;
// THIGH
cfg.THIGH_bp 										= 0;
cfg.THIGH_bm										= 0xFFFFFUL;
// RAMPMODE
cfg.RAMPMODE_bp									= 0;
cfg.RAMPMODE_bm								= 0x3UL;
// XACTUAL
cfg.XACTUAL_bp									= 0;
cfg.XACTUAL_bm									= 0xFFFFFFFFUL;
// VACTUAL
cfg.VACTUAL_bp									= 0;
cfg.VACTUAL_bm									= 0xFFFFFFUL;
// VSTART
cfg.VSTART_bp										= 0;
cfg.VSTART_bm									= 0x3FFFFUL;
// A1
cfg.A1_bp												= 0;
cfg.A1_bm											= 0xFFFFUL;
// V1
cfg.V1_bp												= 0;
cfg.V1_bm											= 0xFFFFFUL;
// AMAX
cfg.AMAX_bp											= 0;
cfg.AMAX_bm										= 0xFFFFUL;
// VMAX
cfg.VMAX_bp											= 0;
cfg.VMAX_bm										= 0x7FFFFF;
// DMAX
cfg.DMAX_bp											= 0;
cfg.DMAX_bm										= 0xFFFFUL;
// D1
cfg.D1_bp												= 0;
cfg.D1_bm											= 0xFFFFUL;
// VSTOP
cfg.VSTOP_bp										= 0;
cfg.VSTOP_bm										= 0x3FFFFUL;
// TZEROWAIT
cfg.TZEROWAIT_bp								= 0;
cfg.TZEROWAIT_bm								= 0xFFFFUL;
// XTARGET
cfg.XTARGET_bp									= 0;
cfg.XTARGET_bm									= 0xFFFFFFFFUL;
// VDCMIN
cfg.VDCMIN_bp										= 0;
cfg.VDCMIN_bm									= 0x7FFFFFUL;
// MSLUT0
cfg.MSLUT0_bp										= 0;
cfg.MSLUT0_bm									= 0xFFFFFFFFUL;
// MSLUT1
cfg.MSLUT1_bp										= 0;
cfg.MSLUT1_bm									= 0xFFFFFFFFUL;
// MSLUT2
cfg.MSLUT2_bp										= 0;
cfg.MSLUT2_bm									= 0xFFFFFFFFUL;
// MSLUT3
cfg.MSLUT3_bp										= 0;
cfg.MSLUT3_bm									= 0xFFFFFFFFUL;
// MSLUT4
cfg.MSLUT4_bp										= 0;
cfg.MSLUT4_bm									= 0xFFFFFFFFUL;
// MSLUT5
cfg.MSLUT5_bp										= 0;
cfg.MSLUT5_bm									= 0xFFFFFFFFUL;
// MSLUT6
cfg.MSLUT6_bp										= 0;
cfg.MSLUT6_bm									= 0xFFFFFFFFUL;
// MSLUT7
cfg.MSLUT7_bp										= 0;
cfg.MSLUT7_bm									= 0xFFFFFFFFUL;
// MSLUTSEL
cfg.MSLUTSEL_bp									= 0;
cfg.MSLUTSEL_bm								= 0xFFFFFFFFUL;
// MSLUTSTART
cfg.START_SIN_bp								= 0;
cfg.START_SIN90_bp							= 16;
cfg.START_SIN_bm 							= 0xFFUL;
cfg.START_SIN90_bm							= 0xFF0000UL;
// MSCNT
cfg.MSCNT_bp										= 0;
cfg.MSCNT_bm										= 0x3FFUL;
// MSCURACT
cfg.CUR_A_bp										= 0;
cfg.CUR_B_bp									  = 16;
cfg.CUR_A_bm										= 0x1FFUL;
cfg.CUR_B_bm										= 0x1FF0000UL;
// SW_MODE
cfg.STOP_L_ENABLE_bp						= 0;
cfg.STOP_R_ENABLE_bp						= 1;
cfg.POL_STOP_L_bp								= 2;
cfg.POL_STOP_R_bp								= 3;
cfg.SWAP_LR_bp									= 4;
cfg.LATCH_L_ACTIVE_bp						= 5;
cfg.LATCH_L_INACTIVE_bp					= 6;
cfg.LATCH_R_ACTIVE_bp						= 7;
cfg.LATCH_R_INACTIVE_bp					= 8;
cfg.EN_LATCH_ENCODER_bp					= 9;
cfg.SG_STOP_bp		   						= 10;
cfg.EN_SOFTSTOP_bp	   					= 11;
cfg.STOP_L_ENABLE_bm						= 0x1UL;
cfg.STOP_R_ENABLE_bm						= 0x2UL;
cfg.POL_STOP_L_bm							= 0x4UL;
cfg.POL_STOP_R_bm							= 0x8UL;
cfg.SWAP_LR_bm									= 0x10UL;
cfg.LATCH_L_ACTIVE_bm					= 0x20UL;
cfg.LATCH_L_INACTIVE_bm				= 0x40UL;
cfg.LATCH_R_ACTIVE_bm					= 0x80UL;
cfg.LATCH_R_INACTIVE_bm				= 0x100UL;
cfg.EN_LATCH_ENCODER_bm				= 0x200UL;
cfg.SG_STOP_bm									= 0x400UL;
cfg.EN_SOFTSTOP_bm							= 0x800UL;
// RAMP_STAT
cfg.STATUS_STOP_L_bp						= 0;
cfg.STATUS_STOP_R_bp						= 1;
cfg.STATUS_LATCH_L_bp						= 2;
cfg.STATUS_LATCH_R_bp						= 3;
cfg.EVENT_STOP_L_bp							= 4;
cfg.EVENT_STOP_R_bp							= 5;
cfg.EVENT_STOP_SG_bp						= 6;
cfg.EVENT_POS_REACHED_bp				= 7;
cfg.VELOCITY_REACHED_bp					= 8;
cfg.POSITION_REACHED_bp					= 9;
cfg.VZERO_bp										= 10;
cfg.T_ZEROWAIT_ACTIVE_bp				= 11;
cfg.SECOND_MOVE_bp							= 12;
cfg.STATUS_SG_bp								= 13;
cfg.STATUS_STOP_L_bm						= 0x1UL;
cfg.STATUS_STOP_R_bm						= 0x2UL;
cfg.STATUS_LATCH_L_bm					= 0x4UL;
cfg.STATUS_LATCH_R_bm					= 0x8UL;
cfg.EVENT_STOP_L_bm						= 0x10UL;
cfg.EVENT_STOP_R_bm						= 0x20UL;
cfg.EVENT_STOP_SG_bm						= 0x40UL;
cfg.EVENT_POS_REACHED_bm				= 0x80UL;
cfg.VELOCITY_REACHED_bm				= 0x100UL;
cfg.POSITION_REACHED_bm				= 0x200UL;
cfg.VZERO_bm										= 0x400UL;
cfg.T_ZEROWAIT_ACTIVE_bm				= 0x800UL;
cfg.SECOND_MOVE_bm							= 0x1000UL;
cfg.STATUS_SG_bm								= 0x2000UL;
// ENCMODE
cfg.POL_A_bp										= 0;
cfg.POL_B_bp										= 1;
cfg.POL_N_bp										= 2;
cfg.IGNORE_AB_bp								= 3;
cfg.CLR_CONT_bp									= 4;
cfg.CLR_ONCE_bp									= 5;
cfg.POS_EDGE_bp									= 6;
cfg.NEG_EDGE_bp									= 7;
cfg.CLR_ENC_X_bp								= 8;
cfg.LATCH_X_ACT_bp							= 9;
cfg.ENC_SEL_DECIMAL_bp					= 10;
cfg.POL_A_bm										= 0x1UL;
cfg.POL_B_bm										= 0x2UL;
cfg.POL_N_bm										= 0x4UL;
cfg.IGNORE_AB_bm								= 0x8UL;
cfg.CLR_CONT_bm								= 0x10UL;
cfg.CLR_ONCE_bm								= 0x20UL;
cfg.POS_EDGE_bm								= 0x40UL;
cfg.NEG_EDGE_bm								= 0x80UL;
cfg.CLR_ENC_X_bm								= 0x100UL;
cfg.LATCH_X_ACT_bm							= 0x200UL;
cfg.ENC_SEL_DECIMAL_bm					= 0x400UL;
// CHOPCONF
cfg.TOFF_bp											= 0;
cfg.HSTRT_bp										= 4;
cfg.FD_bp			  								= 4;
cfg.HEND_bp											= 7;
cfg.DISFDCC_bp		  						= 12;
cfg.RNDTF_bp		  							= 13;
cfg.CHM_bp			 								= 14;
cfg.TBL_bp 			 								= 15;
cfg.VSENSE_bp		  							= 17;
cfg.VHIGHFS_bp		  						= 18;
cfg.VHIGHCHM_bp		  						= 19;
cfg.SYNC_bp			 								= 20;
cfg.MRES_bp 		 								= 24;
cfg.INTPOL_bp		  							= 28;
cfg.DEDGE_bp		  							= 29;
cfg.DISS2G_bp		  							= 30;
cfg.CHOPCONF_bm								= 0xFFFFFFFFUL;
cfg.TOFF_bm			  						= 0xFUL;
cfg.HSTRT_bm		 								= 0x70UL;
cfg.FD_bm											= 0x830UL;
cfg.HEND_bm										= 0x780UL;
cfg.DISFDCC_bm									= 0x1000UL;
cfg.RNDTF_bm										= 0x2000UL;
cfg.CHM_bm											= 0x4000UL;
cfg.TBL_bm		  								= 0x18000UL;
cfg.VSENSE_bm	  							= 0x20000UL;
cfg.VHIGHFS_bm									= 0x40000UL;
cfg.VHIGHCHM_bm								= 0x80000UL;
cfg.SYNC_bm										= 0xF00000UL;
cfg.MRES_bm										= 0xF000000UL;
cfg.INTPOL_bm  								= 0x10000000UL;
cfg.DEDGE_bm   								= 0x20000000UL;
cfg.DISS2G_bm  								= 0x40000000UL;
// COOLCONF
cfg.SEMIN_bp										= 0;
cfg.SEUP_bp											= 5;
cfg.SEMAX_bp										= 8;
cfg.SEDN_bp											= 13;
cfg.SEIMIN_bp										= 15;
cfg.SGT_bp											= 16;
cfg.SFILT_bp										= 24;
cfg.COOLCONF_bm								= 0x3FFFFFFUL;
cfg.SEMIN_bm										= 0xFUL;
cfg.SEUP_bm										= 0x60UL;
cfg.SEMAX_bm										= 0xF00UL;
cfg.SEDN_bm										= 0x6000UL;
cfg.SEIMIN_bm									= 0x8000UL;
cfg.SGT_bm											= 0x7F0000UL;
cfg.SFILT_bm										= 0x1000000UL;
// DCCTRL
cfg.DC_TIME_bp									= 0;
cfg.DC_SG_bp										= 16;
cfg.DC_TIME_bm									= 0x3FFUL;
cfg.DC_SG_bm										= 0xFF0000UL;
// DRV_STATUS
cfg.SG_RESULT_bp								= 0;
cfg.FSACTIVE_bp									= 15;
cfg.CS_ACTUAL_bp								= 16;
cfg.STALLGUARD_bp								= 24;
cfg.OT_bp												= 25;
cfg.OTPW_bp											= 26;
cfg.S2GA_bp											= 27;
cfg.S2GB_bp											= 28;
cfg.OLA_bp											= 29;
cfg.OLB_bp											= 30;
cfg.STST_bp											= 31;
cfg.DRV_STATUS_bm							= 0xFFFFFFFFUL;
cfg.SG_RESULT_bm								= 0x3FFUL;
cfg.FSACTIVE_bm								= 0x8000UL;
cfg.CS_ACTUAL_bm								= 0x1F0000UL;
cfg.STALLGUARD_bm							= 0x1000000UL;
cfg.OT_bm											= 0x2000000UL;
cfg.OTPW_bm										= 0x4000000UL;
cfg.S2GA_bm										= 0x8000000UL;
cfg.S2GB_bm										= 0x10000000UL;
cfg.OLA_bm											= 0x20000000UL;
cfg.OLB_bm											= 0x40000000UL;
cfg.STST_bm										= 0x80000000UL;
// PWMCONF
cfg.PWM_AMPL_bp									= 0;
cfg.PWM_GRAD_bp									= 8;
cfg.PWM_FREQ_bp									= 16;
cfg.PWM_AUTOSCALE_bp						= 18;
cfg.PWM_SYMMETRIC_bp						= 19;
cfg.FREEWHEEL_bp								= 20;
cfg.PWMCONF_bm									= 0x7FFFFFUL;
cfg.PWM_AMPL_bm 								= 0xFFUL;
cfg.PWM_GRAD_bm 								= 0xFF00UL;
cfg.PWM_FREQ_bm 								= 0x30000UL;
cfg.PWM_AUTOSCALE_bm						= 0x40000UL;
cfg.PWM_SYMMETRIC_bm						= 0x80000UL;
cfg.FREEWHEEL_bm 							= 0x300000UL;
// PWM_SCALE
cfg.PWM_SCALE_bp								= 0;
cfg.PWM_SCALE_bm								= 0xFFUL;
// ENCM_CTRL
cfg.INV_bp											= 0;
cfg.MAXSPEED_bp									= 1;
cfg.INV_bm											= 0x1UL;
cfg.MAXSPEED_bm								= 0x2UL;
// LOST_STEPS
cfg.LOST_STEPS_bp								= 0;
cfg.LOST_STEPS_bm							= 0xFFFFFUL;
