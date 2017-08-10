#ifndef TMCStepper_REGDEFS_h
#define TMCStepper_REGDEFS_h

#define TMC_READ 			0x00
#define TMC_WRITE 			0x80

// Register memory positions
#define REG_GCONF 				0x00
#define REG_GSTAT 				0x01
#define REG_IFCNT				0x02
#define REG_SLAVECONF 			0x03
#define REG_IOIN 				0x04
#define REG_OUTPUT				0x04
#define REG_X_COMPARE			0x05
#define REG_IHOLD_IRUN 			0x10
#define REG_TPOWERDOWN 			0x11
#define REG_TSTEP 				0x12
#define REG_TPWMTHRS 			0x13
#define REG_TCOOLTHRS			0x14
#define REG_THIGH				0x15
#define REG_RAMPMODE			0x20
#define REG_XACTUAL				0x21
#define REG_VACTUAL				0x22
#define REG_VSTART				0x23
#define REG_A1					0x24
#define REG_V1					0x25
#define REG_AMAX				0x26
#define REG_VMAX				0x27
#define REG_DMAX				0x28
#define REG_D1					0x2A
#define REG_VSTOP				0x2B
#define REG_TZEROWAIT			0x2C
#define REG_XTARGET				0x2D
#define REG_VDCMIN				0x33
#define REG_SW_MODE				0x34
#define REG_RAMP_STAT			0x35
#define REG_XLATCH				0x36
#define REG_ENCMODE				0x38
#define REG_X_ENC				0x39
#define REG_ENC_CONST			0x3A
#define REG_ENC_STATUS			0x3B
#define REG_ENC_LATCH			0x3C
#define REG_MSLUT0				0x60
#define REG_MSLUT1				0x61
#define REG_MSLUT2				0x62
#define REG_MSLUT3				0x63
#define REG_MSLUT4				0x64
#define REG_MSLUT5				0x65
#define REG_MSLUT6				0x66
#define REG_MSLUT7				0x67
#define REG_MSLUTSEL			0x68
#define REG_MSLUTSTART			0x69
#define REG_MSCNT 				0x6A
#define REG_MSCURACT 			0x6B
#define REG_CHOPCONF 			0x6C
#define REG_COOLCONF			0x6D
#define REG_DCCTRL				0x6E
#define REG_DRV_STATUS 			0x6F
#define REG_PWMCONF 			0x70
#define REG_PWM_SCALE 			0x71
#define REG_ENCM_CTRL 			0x72
#define REG_LOST_STEPS			0x73

// SPI_STATUS
#define RESET_FLAG_bp			0
#define DRIVER_ERROR_bp			1
#define SG2_bp 					2
#define STANDSTILL_bp			3
#define RESET_FLAG_bm			0x1UL
#define DRIVER_ERROR_bm			0x2UL
#define SG2_bm 					0x4UL
#define STANDSTILL_bm			0x8UL

// GCONF
#define I_SCALE_ANALOG_bp			0
#define INTERNAL_RSENSE_bp			1
#define EN_PWM_MODE_bp				2
#define ENC_COMMUTATION_bp			3
#define SHAFT_bp					4
#define DIAG0_ERROR_bp				5
#define DIAG0_OTPW_bp				6
#define DIAG0_STALL_bp				7
#define DIAG0_STEP_bp				7
#define DIAG1_STALL_bp				8
#define DIAG1_DIR_bp				8
#define DIAG1_INDEX_bp				9
#define DIAG1_ONSTATE_bp	   		10
#define DIAG1_STEPS_SKIPPED_bp 		11
#define DIAG0_INT_PUSHPULL_bp  		12
#define DIAG1_POSCOMP_PUSHPULL_bp 	13
#define SMALL_HYSTERISIS_bp    		14
#define STOP_ENABLE_bp		   		15
#define DIRECT_MODE_bp		   		16
#define GCONF_bm					0x3FFFFUL
#define I_SCALE_ANALOG_bm			0x1UL
#define INTERNAL_RSENSE_bm			0x2UL
#define EN_PWM_MODE_bm				0x4UL
#define ENC_COMMUTATION_bm			0x8UL
#define SHAFT_bm					0x10UL
#define DIAG0_ERROR_bm				0x20UL
#define DIAG0_OTPW_bm				0x40UL
#define DIAG0_STALL_bm				0x80UL
#define DIAG0_STEP_bm				0x80UL
#define DIAG1_STALL_bm				0x100UL
#define DIAG1_DIR_bm				0x100UL
#define DIAG1_INDEX_bm				0x200UL
#define DIAG1_ONSTATE_bm	    	0x400UL
#define DIAG1_STEPS_SKIPPED_bm  	0x800UL
#define DIAG0_INT_PUSHPULL_bm   	0x1000UL
#define DIAG1_POSCOMP_PUSHPULL_bm  	0x2000UL
#define SMALL_HYSTERISIS_bm     	0x4000UL
#define STOP_ENABLE_bm		    	0x8000UL
#define DIRECT_MODE_bm		    	0x10000UL
// GSTAT
#define RESET_bp 					0
#define DRV_ERR_bp					1
#define UV_CP_bp					2
#define GSTAT_bm					0x7
#define RESET_bm 					0b1
#define DRV_ERR_bm					0b10
#define UV_CP_bm					0b100
// IFCNT
#define IFCNT_pb					0
#define IFCNT_bm					0xFF
// SLAVECONF
#define SLAVECONF_bp				0
#define SLAVECONF_bm				0xF00
#define SENDDELAY_bp				8
#define SENDDELAY_bm				0xF00
// IOIN
#define REFL_STEP_bp 				0
#define REFR_DIR_bp					1
#define ENCB_DCEN_CFG4_bp			2
#define ENCA_DCIN_CFG5_bp			3
#define DRV_ENN_CFG6_bp				4
#define ENC_N_DCO_bp 				5
#define SD_MODE_bp					6
#define SWCOMP_IN_bp				7
#define VERSION_bp		 	  		24
#define IOIN_bm						0xFF00003FUL
#define REFL_STEP_bm 				0x1UL
#define REFR_DIR_bm					0x2UL
#define ENCB_DCEN_CFG4_bm			0x4UL
#define ENCA_DCIN_CFG5_bm			0x8UL
#define DRV_ENN_CFG6_bm				0x10UL
#define ENC_N_DCO_bm 				0x20UL
#define SD_MODE_bm					0x40UL
#define SWCOMP_IN_bm				0x80UL
#define VERSION_bm					0xFF000000UL
// OUTPUT
#define OUTPUT_bp					0
#define OUTPUT_bm					0x1UL
// X_COMPARE
#define X_COMPARE_bp				0
#define X_COMPARE_bm				0xFFFFFFFFUL
// IHOLD_IRUN
#define IHOLD_bp 			0
#define IRUN_bp				8
#define IHOLDDELAY_bp	   16
#define IHOLD_IRUN_bm		0xF1F1FUL
#define IHOLD_bm 			0x1FUL
#define IRUN_bm				0x1F00UL
#define IHOLDDELAY_bm	    0xF0000UL
// TPOWERDOWN
#define TPOWERDOWN_bp		0
#define TPOWERDOWN_bm		0xFFUL
// TSTEP
#define TSTEP_bp			0
#define TSTEP_bm			0xFFFFFUL
// TPWMTHRS
#define TPWMTHRS_bp 		0
#define TPWMTHRS_bm			0xFFFFFUL
// TCOOLTHRS
#define TCOOLTHRS_bp		0
#define TCOOLTHRS_bm		0xFFFFFUL
// THIGH
#define THIGH_bp 			0
#define THIGH_bm			0xFFFFFUL
// RAMPMODE
#define RAMPMODE_bp			0
#define RAMPMODE_bm			0x3UL
// XACTUAL
#define XACTUAL_bp			0
#define XACTUAL_bm			0xFFFFFFFFUL
// VACTUAL
#define VACTUAL_bp			0
#define VACTUAL_bm			0xFFFFFFUL
// VSTART
#define VSTART_bp			0
#define VSTART_bm			0x3FFFFUL
// A1
#define A1_bp				0
#define A1_bm				0xFFFFUL
// V1
#define V1_bp				0
#define V1_bm				0xFFFFFUL
// AMAX
#define AMAX_bp				0
#define AMAX_bm				0xFFFFUL
// VMAX
#define VMAX_bp				0
#define VMAX_bm				0x7FFFFF
// DMAX
#define DMAX_bp				0
#define DMAX_bm				0xFFFFUL
// D1
#define D1_bp				0
#define D1_bm				0xFFFFUL
// VSTOP
#define VSTOP_bp			0
#define VSTOP_bm			0x3FFFFUL
// TZEROWAIT
#define TZEROWAIT_bp		0
#define TZEROWAIT_bm		0xFFFFUL
// XTARGET
#define XTARGET_bp			0
#define XTARGET_bm			0xFFFFFFFFUL
// VDCMIN
#define VDCMIN_bp			0
#define VDCMIN_bm			0x7FFFFFUL
// MSLUT0
#define MSLUT0_bp			0
#define MSLUT0_bm			0xFFFFFFFFUL
// MSLUT1
#define MSLUT1_bp			0
#define MSLUT1_bm			0xFFFFFFFFUL
// MSLUT2
#define MSLUT2_bp			0
#define MSLUT2_bm			0xFFFFFFFFUL
// MSLUT3
#define MSLUT3_bp			0
#define MSLUT3_bm			0xFFFFFFFFUL
// MSLUT4
#define MSLUT4_bp			0
#define MSLUT4_bm			0xFFFFFFFFUL
// MSLUT5
#define MSLUT5_bp			0
#define MSLUT5_bm			0xFFFFFFFFUL
// MSLUT6
#define MSLUT6_bp			0
#define MSLUT6_bm			0xFFFFFFFFUL
// MSLUT7
#define MSLUT7_bp			0
#define MSLUT7_bm			0xFFFFFFFFUL
// MSLUTSEL
#define MSLUTSEL_bp			0
#define MSLUTSEL_bm			0xFFFFFFFFUL
// MSLUTSTART
#define START_SIN_bp		0
#define START_SIN90_bp	   16
#define START_SIN_bm 		0xFFUL
#define START_SIN90_bm 		0xFF0000UL
// MSCNT
#define MSCNT_bp			0
#define MSCNT_bm			0x3FFUL
// MSCURACT
#define CUR_A_bp			0
#define CUR_B_bp		   16
#define CUR_A_bm			0x1FFUL
#define CUR_B_bm			0x1FF0000UL
// SW_MODE
#define STOP_L_ENABLE_bp	0
#define STOP_R_ENABLE_bp	1
#define POL_STOP_L_bp		2
#define POL_STOP_R_bp		3
#define SWAP_LR_bp			4
#define LATCH_L_ACTIVE_bp	5
#define LATCH_L_INACTIVE_bp	6
#define LATCH_R_ACTIVE_bp	7
#define LATCH_R_INACTIVE_bp	8
#define EN_LATCH_ENCODER_bp	9
#define SG_STOP_bp		   10
#define EN_SOFTSTOP_bp	   11
#define STOP_L_ENABLE_bm	0x1UL
#define STOP_R_ENABLE_bm	0x2UL
#define POL_STOP_L_bm		0x4UL
#define POL_STOP_R_bm		0x8UL
#define SWAP_LR_bm			0x10UL
#define LATCH_L_ACTIVE_bm	0x20UL
#define LATCH_L_INACTIVE_bm	0x40UL
#define LATCH_R_ACTIVE_bm	0x80UL
#define LATCH_R_INACTIVE_bm	0x100UL
#define EN_LATCH_ENCODER_bm	0x200UL
#define SG_STOP_bm			0x400UL
#define EN_SOFTSTOP_bm		0x800UL
// RAMP_STAT
#define STATUS_STOP_L_bp		0
#define STATUS_STOP_R_bp		1
#define STATUS_LATCH_L_bp		2
#define STATUS_LATCH_R_bp		3
#define EVENT_STOP_L_bp			4
#define EVENT_STOP_R_bp			5
#define EVENT_STOP_SG_bp		6
#define EVENT_POS_REACHED_bp	7
#define VELOCITY_REACHED_bp		8
#define POSITION_REACHED_bp		9
#define VZERO_bp				10
#define T_ZEROWAIT_ACTIVE_bp	11
#define SECOND_MOVE_bp			12
#define STATUS_SG_bp			13
#define STATUS_STOP_L_bm		0x1UL
#define STATUS_STOP_R_bm		0x2UL
#define STATUS_LATCH_L_bm		0x4UL
#define STATUS_LATCH_R_bm		0x8UL
#define EVENT_STOP_L_bm			0x10UL
#define EVENT_STOP_R_bm			0x20UL
#define EVENT_STOP_SG_bm		0x40UL
#define EVENT_POS_REACHED_bm	0x80UL
#define VELOCITY_REACHED_bm		0x100UL
#define POSITION_REACHED_bm		0x200UL
#define VZERO_bm				0x400UL
#define T_ZEROWAIT_ACTIVE_bm	0x800UL
#define SECOND_MOVE_bm			0x1000UL
#define STATUS_SG_bm			0x2000UL
// ENCMODE
#define POL_A_bp				0
#define POL_B_bp				1
#define POL_N_bp				2
#define IGNORE_AB_bp			3
#define CLR_CONT_bp				4
#define CLR_ONCE_bp				5
#define POS_EDGE_bp				6
#define NEG_EDGE_bp				7
#define CLR_ENC_X_bp			8
#define LATCH_X_ACT_bp			9
#define ENC_SEL_DECIMAL_bp		10
#define POL_A_bm				0x1UL
#define POL_B_bm				0x2UL
#define POL_N_bm				0x4UL
#define IGNORE_AB_bm			0x8UL
#define CLR_CONT_bm				0x10UL
#define CLR_ONCE_bm				0x20UL
#define POS_EDGE_bm				0x40UL
#define NEG_EDGE_bm				0x80UL
#define CLR_ENC_X_bm			0x100UL
#define LATCH_X_ACT_bm			0x200UL
#define ENC_SEL_DECIMAL_bm		0x400UL
// CHOPCONF
#define TOFF_bp				0
#define HSTRT_bp			4
#define FD_bp			    4
#define HEND_bp				7
#define DISFDCC_bp		   12
#define RNDTF_bp		   13
#define CHM_bp			   14
#define TBL_bp 			   15
#define VSENSE_bp		   17
#define VHIGHFS_bp		   18
#define VHIGHCHM_bp		   19
#define SYNC_bp			   20
#define MRES_bp 		   24
#define INTPOL_bp		   28
#define DEDGE_bp		   29
#define DISS2G_bp		   30
#define CHOPCONF_bm			0xFFFFFFFFUL
#define TOFF_bm			  	0xFUL
#define HSTRT_bm		 	0x70UL
#define FD_bm				0x830UL
#define HEND_bm				0x780UL
#define DISFDCC_bm			0x1000UL
#define RNDTF_bm			0x2000UL
#define CHM_bm				0x4000UL
#define TBL_bm		  		0x18000UL
#define VSENSE_bm	  		0x20000UL
#define VHIGHFS_bm			0x40000UL
#define VHIGHCHM_bm			0x80000UL
#define SYNC_bm				0xF00000UL
#define MRES_bm				0xF000000UL
#define INTPOL_bm  			0x10000000UL
#define DEDGE_bm   			0x20000000UL
#define DISS2G_bm  			0x40000000UL
// COOLCONF
#define SEMIN_bp			0
#define SEUP_bp				5
#define SEMAX_bp			8
#define SEDN_bp			   13
#define SEIMIN_bp		   15
#define SGT_bp			   16
#define SFILT_bp		   24
#define COOLCONF_bm			0x3FFFFFFUL
#define SEMIN_bm			0xFUL
#define SEUP_bm				0x60UL
#define SEMAX_bm			0xF00UL
#define SEDN_bm				0x6000UL
#define SEIMIN_bm			0x8000UL
#define SGT_bm				0x7F0000UL
#define SFILT_bm			0x1000000UL
// DCCTRL
#define DC_TIME_bp			0
#define DC_SG_bp		   16
#define DC_TIME_bm			0x3FFUL
#define DC_SG_bm			0xFF0000UL
// DRV_STATUS
#define SG_RESULT_bp		0
#define FSACTIVE_bp		   15
#define CS_ACTUAL_bp	   16
#define STALLGUARD_bp	   24
#define OT_bp			   25
#define OTPW_bp			   26
#define S2GA_bp			   27
#define S2GB_bp			   28
#define OLA_bp			   29
#define OLB_bp			   30
#define STST_bp			   31
#define DRV_STATUS_bm		0xFFFFFFFFUL
#define SG_RESULT_bm		0x3FFUL
#define FSACTIVE_bm			0x8000UL
#define CS_ACTUAL_bm		0x1F0000UL
#define STALLGUARD_bm		0x1000000UL
#define OT_bm				0x2000000UL
#define OTPW_bm				0x4000000UL
#define S2GA_bm				0x8000000UL
#define S2GB_bm				0x10000000UL
#define OLA_bm				0x20000000UL
#define OLB_bm				0x40000000UL
#define STST_bm				0x80000000UL
// PWMCONF
#define PWM_AMPL_bp 		0
#define PWM_GRAD_bp 		8
#define PWM_FREQ_bp 	   16
#define PWM_AUTOSCALE_bp   18
#define PWM_SYMMETRIC_bp   19
#define FREEWHEEL_bp 	   20
#define PWMCONF_bm			0x7FFFFFUL
#define PWM_AMPL_bm 		0xFFUL
#define PWM_GRAD_bm 		0xFF00UL
#define PWM_FREQ_bm 		0x30000UL
#define PWM_AUTOSCALE_bm	0x40000UL
#define PWM_SYMMETRIC_bm	0x80000UL
#define FREEWHEEL_bm 		0x300000UL
// PWM_SCALE
#define PWM_SCALE_bp		0
#define PWM_SCALE_bm		0xFFUL
// ENCM_CTRL
#define INV_bp				0
#define MAXSPEED_bp			1
#define INV_bm				0x1UL
#define MAXSPEED_bm			0x2UL
// LOST_STEPS
#define LOST_STEPS_bp		0
#define LOST_STEPS_bm		0xFFFFFUL

#endif
