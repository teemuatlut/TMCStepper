#pragma once

//#define TMCDEBUG

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#endif

#include <SPI.h>
#include "source/Definitions_library.h"
#include "source/TMC5130_MACROS.h"

const uint32_t TMCStepper_version = 0x10100; // v1.1.0

#define DEBUG_PRINT(CFG, VAL) Serial.print(CFG); Serial.print('('); Serial.print(VAL, HEX); Serial.println(')')

class TMCStepper {
  public:
    virtual void abstractClass() = 0;
    regdefs *cfg;
    virtual void write(uint32_t);
    uint32_t setBits(uint32_t reg, uint32_t bitmask, uint8_t bitpos, uint8_t B);
    uint32_t getBits(uint32_t sr, uint32_t bitmask, uint8_t bitpos);
    void setSPISpeed(uint32_t speed);
    void switchCSpin(bool state);
    uint8_t _pinEN;
    uint8_t _pinCS;
    float Rsense;
    bool _started;
    uint8_t status_response;
    bool flag_otpw = false;

//  protected:
    //const uint8_t WRITE     = 0b10000000;
    //const uint8_t READ      = 0b00000000;
    //const int MOSI_PIN    = 12;
    //const int MISO_PIN    = 11;
    //const int SCK_PIN     = 13;

    // Shadow registers
    uint32_t  GCONF_sr      = 0x00000000UL,
              IHOLD_IRUN_sr = 0x00000000UL,
              TSTEP_sr      = 0x00000000UL,
              TPWMTHRS_sr   = 0x00000000UL,
              TCOOLTHRS_sr  = 0x00000000UL,
              THIGH_sr      = 0x00000000UL,
              XDIRECT_sr    = 0x00000000UL,
              VDCMIN_sr     = 0x00000000UL,
              MSLUT0_sr     = 0x00000000UL,
              MSLUT1_sr     = 0x00000000UL,
              MSLUT2_sr     = 0x00000000UL,
              MSLUT3_sr     = 0x00000000UL,
              MSLUT4_sr     = 0x00000000UL,
              MSLUT5_sr     = 0x00000000UL,
              MSLUT6_sr     = 0x00000000UL,
              MSLUT7_sr     = 0x00000000UL,
              MSLUTSEL_sr   = 0x00000000UL,
              CHOPCONF_sr   = 0x00000000UL,
              COOLCONF_sr   = 0x00000000UL,
              DCCTRL_sr     = 0x00000000UL,
              PWMCONF_sr    = 0x00050480UL,
              tmp_sr        = 0x00000000UL,
              TPOWERDOWN_sr = 0x00000000UL,
              ENCM_CTRL_sr  = 0x00000000UL,
              GSTAT_sr      = 0x00000000UL,
              SW_MODE_sr    = 0x00000000UL,
              ENCMODE_sr    = 0x00000000UL,
              MSLUTSTART_sr = 0x00000000UL,
              SLAVECONF_sr  = 0x00000000UL,
              SPI_response	= 0x00000000UL;

    void write(uint8_t addressByte, uint32_t config);
    void write(uint8_t addressByte, int32_t config);
    void read(uint8_t addressByte, uint32_t *config);
    void read(uint8_t addressByte, int32_t *config);

    uint16_t val_mA           = 0;
    uint32_t spi_speed = 16000000/8; // Default 2MHz
};

class TMC5130Stepper : public TMCStepper {
	public:
		regdefs cfg;
		void abstractClass() override {};
		TMC5130Stepper(uint8_t pinCS);
		void checkStatus();
		void rms_current(uint16_t mA, float multiplier=0.5, float RS=0.15);
		uint16_t rms_current();
		void SilentStepStick(uint16_t mA);
		void setCurrent(uint16_t mA, float Rsense, float multiplier);
		uint16_t getCurrent();
		bool checkOT();
		bool getOTPW();
		void clear_otpw();
		bool isEnabled();
		// GCONF
		uint32_t GCONF();
		void GCONF(								uint32_t value);
		void I_scale_analog(			bool B);
		void internal_Rsense(			bool B);
		void en_pwm_mode(					bool B);
		void enc_commutation(			bool B);
		void shaft(								bool B);
		void diag0_error(					bool B);
		void diag0_otpw(					bool B);
		void diag0_stall(					bool B);
		void diag1_stall(					bool B);
		void diag1_index(					bool B);
		void diag1_onstate(				bool B);
		void diag1_steps_skipped(	bool B);
		void diag0_int_pushpull(	bool B);
		void diag1_poscomp_pushpull(bool B);
		void small_hysterisis(		bool B);
		void stop_enable(					bool B);
		void direct_mode(					bool B);
		bool I_scale_analog();
		bool internal_Rsense();
		bool en_pwm_mode();
		bool enc_commutation();
		bool shaft();
		bool diag0_error();
		bool diag0_otpw();
		bool diag0_stall();
		bool diag1_stall();
		bool diag1_index();
		bool diag1_onstate();
		bool diag1_steps_skipped();
		bool diag0_int_pushpull();
		bool diag1_poscomp_pushpull();
		bool small_hysterisis();
		bool stop_enable();
		bool direct_mode();
		// IHOLD_IRUN
		void IHOLD_IRUN(					uint32_t input);
		uint32_t IHOLD_IRUN();
		void 	ihold(							uint8_t B);
		void 	irun(								uint8_t B);
		void 	iholddelay(					uint8_t B);
		uint8_t ihold();
		uint8_t irun();
		uint8_t iholddelay();
		// GSTAT
		void 	GSTAT(							uint8_t input);
		uint8_t GSTAT();
		bool 	reset();
		bool 	drv_err();
		bool 	uv_cp();
		// R: IFCNT
		uint8_t IFCNT();
		// W: SLAVECONF
		uint16_t SLAVECONF();
		void SLAVECONF(uint16_t input);
		// IOIN
		uint32_t 	IOIN();
		bool 			refl_step();
		bool 			refr_dir();
		bool 			encb_dcen_cfg4();
		bool 			enca_dcin_cfg5();
		bool 			drv_enn_cfg6();
		bool 			enc_n_dco();
		bool 			sd_mode();
		bool 			swcomp_in();
		uint8_t 	version();
		// TPOWERDOWN
		uint32_t TPOWERDOWN();
		void TPOWERDOWN(					uint32_t input);
		// TSTEP
		uint32_t TSTEP();
		// TPWMTHRS
		uint32_t TPWMTHRS();
		void TPWMTHRS(						uint32_t input);
		// TCOOLTHRS
		uint32_t TCOOLTHRS();
		void TCOOLTHRS(						uint32_t input);
		// THIGH
		uint32_t THIGH();
		void THIGH(								uint32_t input);
		// XDRIRECT
		uint32_t XDIRECT();
		void XDIRECT(							uint32_t input);
		void coil_A(							int16_t 	B);
		void coil_B(							int16_t 	B);
		int16_t coil_A();
		int16_t coil_B();
		// VDCMIN
		uint32_t VDCMIN();
		void VDCMIN(							uint32_t input);
		// CHOPCONF
		uint32_t CHOPCONF();
		void CHOPCONF(						uint32_t value);
		void toff(								uint8_t B);
		void hstrt(								uint8_t B);
		void hend(								int8_t  B);
		void fd(									uint8_t B);
		void disfdcc(							bool 		B);
		void rndtf(								bool 		B);
		void chm(									bool 		B);
		void tbl(									uint8_t B);
		void vsense(							bool 		B);
		void vhighfs(							bool 		B);
		void vhighchm(						bool 		B);
		void sync(								uint8_t B);
		void mres(								uint8_t B);
		void intpol(							bool 		B);
		void dedge(								bool 		B);
		void diss2g(							bool 		B);
		uint8_t toff();
		uint8_t hstrt();
		int8_t  hend();
		uint8_t fd();
		bool 	disfdcc();
		bool 	rndtf();
		bool 	chm();
		uint8_t tbl();
		bool 	vsense();
		bool 	vhighfs();
		bool 	vhighchm();
		uint8_t sync();
		uint8_t mres();
		bool 	intpol();
		bool 	dedge();
		bool 	diss2g();
		// COOLCONF
		void COOLCONF(uint32_t value);
		uint32_t COOLCONF();
		void semin(								uint8_t B);
		void seup(								uint8_t B);
		void semax(								uint8_t B);
		void sedn(								uint8_t B);
		void seimin(							bool 		B);
		void sgt(									uint8_t B);
		void sfilt(								bool 		B);
		uint8_t semin();
		uint8_t seup();
		uint8_t semax();
		uint8_t sedn();
		bool seimin();
		uint8_t sgt();
		bool sfilt();
		// PWMCONF
		void PWMCONF(							uint32_t value);
		uint32_t PWMCONF();
		void pwm_ampl(						uint8_t B);
		void pwm_grad(						uint8_t B);
		void pwm_freq(						uint8_t B);
		void pwm_autoscale(				bool		B);
		void pwm_symmetric(				bool		B);
		void freewheel(						uint8_t B);
		uint8_t pwm_ampl();
		uint8_t pwm_grad();
		uint8_t pwm_freq();
		bool 	pwm_autoscale();
		bool 	pwm_symmetric();
		uint8_t freewheel();
		// DRVSTATUS
		uint32_t DRV_STATUS();
		uint16_t sg_result();
		bool fsactive();
		uint8_t cs_actual();
		bool stallguard();
		bool ot();
		bool otpw();
		bool s2ga();
		bool s2gb();
		bool ola();
		bool olb();
		bool stst();
		// PWM_SCALE
		uint8_t PWM_SCALE();
		// ENCM_CTRL
		uint8_t ENCM_CTRL();
		void ENCM_CTRL(						uint8_t input);
		void inv(									bool B);
		void maxspeed(						bool B);
		bool inv();
		bool maxspeed();
		// LOST_STEPS
		uint32_t LOST_STEPS();

		// SW_MODE
		uint32_t SW_MODE();
		void SW_MODE(uint32_t input);

		void stop_l_enable(bool B);
		void stop_r_enable(bool B);
		void pol_stop_l(bool B);
		void pol_stop_r(bool B);
		void swap_lr(bool B);
		void latch_l_active(bool B);
		void latch_l_inactive(bool B);
		void latch_r_active(bool B);
		void latch_r_inactive(bool B);
		void en_latch_encoder(bool B);
		void sg_stop(bool B);
		void en_softstop(bool B);

		bool stop_r_enable();
		bool pol_stop_l();
		bool pol_stop_r();
		bool swap_lr();
		bool latch_l_active();
		bool latch_l_inactive();
		bool latch_r_active();
		bool latch_r_inactive();
		bool en_latch_encoder();
		bool sg_stop();
		bool en_softstop();

		// RAMP_STAT
		uint32_t RAMP_STAT();
		bool status_stop_l();
		bool status_stop_r();
		bool status_latch_l();
		bool status_latch_r();
		bool event_stop_l();
		bool event_stop_r();
		bool event_stop_sg();
		bool event_pos_reached();
		bool velocity_reached();
		bool position_reached();
		bool vzero();
		bool t_zerowait_active();
		bool second_move();
		bool status_sg();

		// ENCMODE
		uint32_t ENCMODE();
		void ENCMODE(uint32_t input);
		void pol_a(bool B);
		void pol_b(bool B);
		void pol_n(bool B);
		void ignore_ab(bool B);
		void clr_cont(bool B);
		void clr_once(bool B);
		void pos_edge(bool B);
		void neg_edge(bool B);
		void clr_enc_x(bool B);
		void latch_x_act(bool B);
		void enc_sel_decimal(bool B);

		bool pol_a();
		bool pol_b();
		bool pol_n();
		bool ignore_ab();
		bool clr_cont();
		bool clr_once();
		bool pos_edge();
		bool neg_edge();
		bool clr_enc_x();
		bool latch_x_act();
		bool enc_sel_decimal();

		// W: OUTPUT
		uint8_t TMC_OUTPUT();
		void TMC_OUTPUT(uint8_t input);
		// W: X_COMPARE
		uint32_t X_COMPARE();
		void X_COMPARE(uint32_t input);
		// RW: RAMPMODE
		uint8_t RAMPMODE();
		void RAMPMODE(uint8_t input);
		// RW: XACTUAL
		int32_t XACTUAL();
		void XACTUAL(int32_t input);
		// R: VACTUAL
		int32_t VACTUAL();
		// W: VSTART
		uint32_t VSTART();
		void VSTART(uint32_t input);
		// W: A1
		uint16_t A1();
		void A1(uint16_t input);
		// W: V1
		uint32_t V1();
		void V1(uint32_t input);
		// W: AMAX
		uint16_t AMAX();
		void AMAX(uint16_t input);
		// W: VMAX
		uint32_t VMAX();
		void VMAX(uint32_t input);
		// W: DMAX
		uint16_t DMAX();
		void DMAX(uint16_t input);
		// W: D1
		uint16_t D1();
		void D1(uint16_t input);
		// W: VSTOP
		uint32_t VSTOP();
		void VSTOP(uint32_t input);
		// W: TZEROWAIT
		uint16_t TZEROWAIT();
		void TZEROWAIT(uint16_t input);
		// RW: XTARGET
		int32_t XTARGET();
		void XTARGET(int32_t input);

		// Helper functions
		void microsteps(uint16_t ms);
		uint16_t microsteps();
		void blank_time(uint8_t value);
		uint8_t blank_time();
		void hysterisis_low(int8_t value);
		int8_t hysterisis_low();
		void hysterisis_start(uint8_t value);
		uint8_t hysterisis_start();
		void sg_current_decrease(uint8_t value);
		uint8_t sg_current_decrease();

		// Aliases

		// RW: GCONF
		inline bool			external_ref()										__attribute__((always_inline)) { return I_scale_analog(); 					}
		inline bool 		internal_sense_R()								__attribute__((always_inline)) { return internal_Rsense(); 					}
		inline bool 		stealthChop()											__attribute__((always_inline)) { return en_pwm_mode(); 							}
		inline bool 		commutation()											__attribute__((always_inline)) { return enc_commutation(); 					}
		inline bool 		shaft_dir()												__attribute__((always_inline)) { return shaft(); 										}
		inline bool 		diag0_errors()										__attribute__((always_inline)) { return diag0_error(); 							}
		inline bool 		diag0_temp_prewarn()							__attribute__((always_inline)) { return diag0_otpw();								}
		inline bool 		diag1_chopper_on()								__attribute__((always_inline)) { return diag1_onstate(); 						}
		inline bool 		diag0_active_high()								__attribute__((always_inline)) { return diag0_int_pushpull(); 			}
		inline bool 		diag1_active_high()								__attribute__((always_inline)) { return diag1_poscomp_pushpull(); 	}
		inline void			external_ref(					bool value)	__attribute__((always_inline)) { 				I_scale_analog(value); 			}
		inline void 		internal_sense_R(			bool value)	__attribute__((always_inline)) {				internal_Rsense(value); 		}
		inline void 		stealthChop(					bool value)	__attribute__((always_inline)) {				en_pwm_mode(value); 				}
		inline void 		commutation(					bool value)	__attribute__((always_inline)) {				enc_commutation(value); 		}
		inline void 		shaft_dir(						bool value)	__attribute__((always_inline)) {				shaft(value); 							}
		inline void 		diag0_errors(					bool value)	__attribute__((always_inline)) {				diag0_error(value); 				}
		inline void 		diag0_temp_prewarn(		bool value)	__attribute__((always_inline)) {				diag0_otpw(value);					}
		inline void 		diag1_chopper_on(			bool value)	__attribute__((always_inline)) {				diag1_onstate(value); 			}
		inline void 		diag0_active_high(		bool value)	__attribute__((always_inline)) {				diag0_int_pushpull(value); 	}
		inline void 		diag1_active_high(		bool value)	__attribute__((always_inline)) {				diag1_poscomp_pushpull(value);}
		// RC
		inline uint8_t 	status_flags()										__attribute__((always_inline)) { return GSTAT(); 										}
		// R
		inline uint32_t input()														__attribute__((always_inline)) { return IOIN(); 										}
		// W: IHOLD_IRUN
		inline uint8_t 	hold_current()										__attribute__((always_inline)) { return ihold(); 										}
		inline uint8_t 	run_current()											__attribute__((always_inline)) { return irun(); 										}
		inline uint8_t 	hold_delay()											__attribute__((always_inline)) { return iholddelay(); 							}
		inline void 		hold_current(			 uint8_t value) __attribute__((always_inline)) {				ihold(value); 							}
		inline void 		run_current(			 uint8_t value) __attribute__((always_inline)) {				irun(value); 								}
		inline void 		hold_delay(				 uint8_t value) __attribute__((always_inline)) {				iholddelay(value); 					}
		// W
		inline uint8_t 	power_down_delay()								__attribute__((always_inline)) { return TPOWERDOWN(); 							}
		inline void 		power_down_delay(	 uint8_t value) __attribute__((always_inline)) { 				TPOWERDOWN(value); 					}
		// R
		inline uint32_t microstep_time()									__attribute__((always_inline)) { return TSTEP(); 										}
		// W
		inline uint32_t stealth_max_speed()								__attribute__((always_inline)) { return TPWMTHRS(); 								}
		inline void 		stealth_max_speed(uint32_t value)	__attribute__((always_inline)) {				TPWMTHRS(value); 						}
		// W
		inline uint32_t coolstep_min_speed()							__attribute__((always_inline)) { return TCOOLTHRS(); 								}
		inline void    coolstep_min_speed(uint32_t value) __attribute__((always_inline)) {				TCOOLTHRS(value); 					}
		// W
		inline uint32_t mode_sw_speed()										__attribute__((always_inline)) { return THIGH(); 										}
		inline void 		mode_sw_speed(		uint32_t value)	__attribute__((always_inline)) {				THIGH(value); 							}
		// RW: XDIRECT
		inline int16_t 	coil_A_current()									__attribute__((always_inline)) { return coil_A(); 									}
		inline void 		coil_A_current(		 int16_t value)	__attribute__((always_inline)) {				coil_B(value); 							}
		inline int16_t 	coil_B_current()									__attribute__((always_inline)) { return coil_A(); 									}
		inline void 		coil_B_current(		 int16_t value)	__attribute__((always_inline)) {				coil_B(value); 							}
		// W
		inline uint32_t DCstep_min_speed()								__attribute__((always_inline)) { return VDCMIN(); 									}
		inline void 		DCstep_min_speed(	uint32_t value)	__attribute__((always_inline)) {				VDCMIN(value); 							}
		// RW: CHOPCONF
		inline uint8_t 	off_time()												__attribute__((always_inline)) { return toff(); 										}
		//inline uint8_t 	hysterisis_start()								__attribute__((always_inline)) { return hstrt(); 										}
		//inline int8_t 	hysterisis_low()									__attribute__((always_inline)) { return hend(); 										}
		inline uint8_t 	fast_decay_time()									__attribute__((always_inline)) { return fd(); 											}
		inline bool 		disable_I_comparator()						__attribute__((always_inline)) { return disfdcc(); 									}
		inline bool 		random_off_time()									__attribute__((always_inline)) { return rndtf(); 										}
		inline bool 		chopper_mode()										__attribute__((always_inline)) { return chm(); 											}
		//inline uint8_t 	blank_time()											__attribute__((always_inline)) { return tbl(); 											}
		inline bool 		high_sense_R()										__attribute__((always_inline)) { return vsense(); 									}
		inline bool 		fullstep_threshold()							__attribute__((always_inline)) { return vhighfs(); 									}
		inline bool 		high_speed_mode()									__attribute__((always_inline)) { return vhighchm(); 								}
		inline uint8_t 	sync_phases()											__attribute__((always_inline)) { return sync(); 										}
		//inline uint16_t microsteps()											__attribute__((always_inline)) { return mres(); 										}
		inline bool 		interpolate()											__attribute__((always_inline)) { return intpol(); 									}
		inline bool 		double_edge_step()								__attribute__((always_inline)) { return dedge(); 										}
		inline bool 		disable_short_protection()				__attribute__((always_inline)) { return diss2g(); 									}
		inline void 		off_time(					 uint8_t value)	__attribute__((always_inline)) {				toff(value); 								}
		//inline void 		hysterisis_start(	 uint8_t value)	__attribute__((always_inline)) {				hstrt(value); 							}
		//inline void 		hysterisis_low(		  int8_t value)	__attribute__((always_inline)) {				hend(value); 								}
		inline void 		fast_decay_time(	 uint8_t value)	__attribute__((always_inline)) {				fd(value); 									}
		inline void 		disable_I_comparator( bool value)	__attribute__((always_inline)) {				disfdcc(value);							}
		inline void 		random_off_time(			bool value)	__attribute__((always_inline)) {				rndtf(value); 							}
		inline void 		chopper_mode(					bool value)	__attribute__((always_inline)) {				chm(value); 								}
		//inline void 		blank_time(				 uint8_t value)	__attribute__((always_inline)) {				tbl(value); 								}
		inline void 		high_sense_R(					bool value)	__attribute__((always_inline)) {				vsense(value); 							}
		inline void 		fullstep_threshold(		bool value)	__attribute__((always_inline)) {				vhighfs(value); 						}
		inline void 		high_speed_mode(			bool value)	__attribute__((always_inline)) {				vhighchm(value); 						}
		inline void 		sync_phases(			 uint8_t value)	__attribute__((always_inline)) {				sync(value); 								}
		//inline void			microsteps(				uint16_t value)	__attribute__((always_inline)) {				mres(value); 								}
		inline void 		interpolate(					bool value)	__attribute__((always_inline)) {				intpol(value); 							}
		inline void 		double_edge_step(			bool value)	__attribute__((always_inline)) {				dedge(value); 							}
		inline void 	disable_short_protection(bool value)__attribute__((always_inline)) {				diss2g(value); 							}
		// W: COOLCONF
		inline uint8_t 	sg_min()													__attribute__((always_inline)) { return semin(); 										}
		inline uint8_t 	sg_step_width()										__attribute__((always_inline)) { return seup(); 										}
		inline uint8_t 	sg_max()													__attribute__((always_inline)) { return semax(); 										}
		//inline uint8_t 	sg_current_decrease()							__attribute__((always_inline)) { return sedn(); 										}
		inline uint8_t 	smart_min_current()								__attribute__((always_inline)) { return seimin(); 									}
		inline int8_t 	sg_stall_value()									__attribute__((always_inline)) { return sgt(); 											}
		inline bool 		sg_filter()												__attribute__((always_inline)) { return sfilt(); 										}
		inline void 		sg_min(						 uint8_t value)	__attribute__((always_inline)) {				semin(value); 							}
		inline void 		sg_step_width(		 uint8_t value)	__attribute__((always_inline)) {				seup(value); 								}
		inline void 		sg_max(						 uint8_t value)	__attribute__((always_inline)) {				semax(value); 							}
		//inline void 		sg_current_decrease(uint8_t value)__attribute__((always_inline)) {				sedn(value); 								}
		inline void 		smart_min_current( uint8_t value)	__attribute__((always_inline)) {				seimin(value); 							}
		inline void 		sg_stall_value(			int8_t value)	__attribute__((always_inline)) {				sgt(value); 								}
		inline void 		sg_filter(						bool value)	__attribute__((always_inline)) {				sfilt(value); 							}
		// W: PWMCONF
		inline uint8_t 	stealth_amplitude()								__attribute__((always_inline)) { return pwm_ampl(); 								}
		inline uint8_t 	stealth_gradient()								__attribute__((always_inline)) { return pwm_grad(); 								}
		inline uint8_t 	stealth_freq()										__attribute__((always_inline)) { return pwm_freq(); 								}
		inline bool 		stealth_autoscale()								__attribute__((always_inline)) { return pwm_autoscale(); 						}
		inline bool 		stealth_symmetric()								__attribute__((always_inline)) { return pwm_symmetric(); 						}
		inline uint8_t 	standstill_mode()									__attribute__((always_inline)) { return freewheel(); 								}
		inline void 		stealth_amplitude( uint8_t value)	__attribute__((always_inline)) {				pwm_ampl(value); 						}
		inline void 		stealth_gradient(	 uint8_t value)	__attribute__((always_inline)) {				pwm_grad(value); 						}
		inline void 		stealth_freq(			 uint8_t value)	__attribute__((always_inline)) {				pwm_freq(value); 						}
		inline void 		stealth_autoscale(		bool value)	__attribute__((always_inline)) {				pwm_autoscale(value); 			}
		inline void 		stealth_symmetric(		bool value)	__attribute__((always_inline)) {				pwm_symmetric(value); 			}
		inline void 		standstill_mode(	 uint8_t value)	__attribute__((always_inline)) {				freewheel(value); 					}
		// W: ENCM_CTRL
		inline bool 		invert_encoder()									__attribute__((always_inline)) { return inv(); 											}
		inline void 		invert_encoder(				bool value)	__attribute__((always_inline)) {				inv(value); 								}
		// R: DRV_STATUS
		inline uint32_t DRVSTATUS()												__attribute__((always_inline)) { return DRV_STATUS(); 							}

  private:
    // Shadow registers
    uint32_t  OUTPUT_sr     = 0x00000000UL,
              X_COMPARE_sr  = 0x00000000UL,
              RAMPMODE_sr   = 0x00000000UL,
              VSTART_sr     = 0x00000000UL,
              A1_sr         = 0x00000000UL,
              V1_sr         = 0x00000000UL,
              AMAX_sr       = 0x00000000UL,
              VMAX_sr       = 0x00000000UL,
              DMAX_sr       = 0x00000000UL,
              D1_sr         = 0x00000000UL,
              VSTOP_sr      = 0x00000000UL,
              TZEROWAIT_sr  = 0x00000000UL;

    int32_t XTARGET_sr = 0x00000000UL,
            XACTUAL_sr    = 0x00000000UL;
};

#define SET_ALIAS(TYPE, NEW, ARG, OLD) TYPE (TMC2660Stepper::*NEW)(ARG) = &TMC2660Stepper::OLD

class TMC2660Stepper : public TMCStepper {
  public:
    regdefs cfg;
    void abstractClass() override {};
    TMC2660Stepper(uint8_t pinCS);
    void write(uint32_t);
    uint32_t read();
    bool isEnabled();

    void DRVCTRL(uint32_t);
    uint32_t DRVCTRL();
    // DRVCTRL (SPI)
    void pha(bool);
    void ca(uint8_t);
    void phb(bool);
    void cb(uint8_t);
    bool pha();
    uint8_t ca();
    bool phb();
    uint8_t cb();
    // DRVCTRL (STEP/DIR)
    void intpol(bool);
    void dedge(bool);
    void mres(uint8_t);
    bool intpol();
    bool dedge();
    uint8_t mres();
    // CHOPCONF
    uint32_t CHOPCONF();
    void CHOPCONF(uint32_t);
    void tbl(uint8_t);
    void chm(bool);
    void rndtf(bool);
    void hdec(uint8_t);
    void hend(uint8_t);
    void hstrt(uint8_t);
    void toff(uint8_t);
    uint8_t tbl();
    bool chm();
    bool rndtf();
    uint8_t hdec();
    uint8_t hend();
    uint8_t hstrt();
    uint8_t toff();
    // SMARTEN
    uint32_t SMARTEN();
    void SMARTEN(uint32_t);
    void seimin(bool);
    void sedn(uint8_t);
    void semax(uint8_t);
    void seup(uint8_t);
    void semin(uint8_t);
    bool seimin();
    uint8_t sedn();
    uint8_t semax();
    uint8_t seup();
    uint8_t semin();
    // SGCSCONF
    uint32_t SGCSCONF();
    void SGCSCONF(uint32_t);
    void sfilt(bool);
    void sgt(uint8_t);
    void cs(uint8_t);
    bool sfilt();
    uint8_t sgt();
    uint8_t cs();
    // DRVCONF
    void DRVCONF(uint32_t);
    uint32_t DRVCONF();
    void tst(bool);
    void slph(uint8_t);
    void slpl(uint8_t);
    void diss2g(bool);
    void ts2g(uint8_t);
    void sdoff(bool);
    void vsense(bool);
    void rdsel(uint8_t);
    bool tst();
    uint8_t slph();
    uint8_t slpl();
    bool diss2g();
    uint8_t ts2g();
    bool sdoff();
    bool vsense();
    uint8_t rdsel();
    // DRVSTATUS
    uint32_t DRVSTATUS();
    uint16_t mstep();
    uint16_t sg_result();
    uint8_t se();
    bool stst();
    bool olb();
    bool ola();
    bool s2gb();
    bool s2ga();
    bool otpw();
    bool ot();
    bool sg();
    uint16_t mstep(uint32_t);
    uint16_t sg_result(uint32_t);
    uint8_t se(uint32_t);
    bool stst(uint32_t);
    bool olb(uint32_t);
    bool ola(uint32_t);
    bool s2gb(uint32_t);
    bool s2ga(uint32_t);
    bool otpw(uint32_t);
    bool ot(uint32_t);
    bool sg(uint32_t);
    // Alias
    SET_ALIAS(void, polarity_A, bool, pha);
    SET_ALIAS(void, current_A, uint8_t, ca);
    SET_ALIAS(void, polarity_B, bool, phb);
    SET_ALIAS(void, current_b, uint8_t, cb);
    SET_ALIAS(void, interpolate, bool, intpol);
    SET_ALIAS(void, double_edge_step, bool, dedge);
    SET_ALIAS(void, microsteps, uint8_t, mres);
    SET_ALIAS(void, blank_time, uint8_t, tbl);
    SET_ALIAS(void, chopper_mode, bool, chm);
    SET_ALIAS(void, random_off_time, bool, rndtf);
    SET_ALIAS(void, hysterisis_decrement, uint8_t, hdec);
    SET_ALIAS(void, hysterisis_low, uint8_t, hend);
    SET_ALIAS(void, hysterisis_start, uint8_t, hstrt);
    SET_ALIAS(void, off_time, uint8_t, toff);
  //private:
    // TMC2660: Shadow registers
    uint32_t DRVCTRL_sr     = 0x0UL,
             CHOPCONF_sr    = 0x0UL,
             SMARTEN_sr     = 0x0UL,
             SGCSCONF_sr    = 0x0UL,
             DRVCONF_sr     = 0x0UL;
};
