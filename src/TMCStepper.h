#pragma once

//#define TMCDEBUG

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-variable"

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
#endif

#ifdef ARDUINO
	#include <HardwareSerial.h>
	#include <SPI.h>
#elif defined(bcm2835)
	#include <bcm2835.h>
	#include "source/bcm2835_spi.h"
	#include "source/bcm2835_stream.h"
#endif

#if (__cplusplus == 201703L) && defined(__has_include)
	#define SW_CAPABLE_PLATFORM __has_include(<SoftwareSerial.h>)
#elif defined(__AVR__) || defined(TARGET_LPC1768) || defined(ARDUINO_ARCH_STM32)
	#define SW_CAPABLE_PLATFORM true
#else
	#define SW_CAPABLE_PLATFORM false
#endif

#if SW_CAPABLE_PLATFORM
	#include <SoftwareSerial.h>
#endif

#include "source/TMC_HAL.h"

#pragma GCC diagnostic pop

#include "source/TMC2660_bitfields.h"

#include "source/interfaces/TMC2130.hpp"
#include "source/interfaces/TMC2160.hpp"
#include "source/interfaces/TMC5130.hpp"
#include "source/interfaces/TMC5160.hpp"
#include "source/interfaces/TMC2208.hpp"
#include "source/interfaces/TMC2209.hpp"
#include "source/interfaces/TMC2300.hpp"

#define TMCSTEPPER_VERSION 0x000703 // v0.7.3

struct TMC2130Stepper;
struct TMC2160Stepper;
struct TMC5130Stepper;
struct TMC5160Stepper;
struct TMC2208Stepper;
struct TMC2209Stepper;
struct TMC2300Stepper;

#include "source/TMC_SPI.hpp"
#include "source/TMC_UART.hpp"

namespace TMCStepper_n {

enum class RMS_TYPE {
	WITH_VSENSE, WITH_GLOBAL_SCALER, WITHOUT_VSENSE
};

template<typename TYPE>
class TMCcommon {
	public:
		uint8_t test_connection();

		// Helper functions
		void microsteps(uint16_t ms);
		uint16_t microsteps();
		void blank_time(uint8_t value);
		uint8_t blank_time();
		void hysteresis_end(int8_t value);
		int8_t hysteresis_end();
		void hysteresis_start(uint8_t value);
		uint8_t hysteresis_start();
};

template<class T, RMS_TYPE I> struct TMC_RMS;

template<class T>
struct TMC_RMS<T, RMS_TYPE::WITH_VSENSE> {
    uint16_t cs2rms(uint8_t CS);
    void rms_current(uint16_t mA);
    void rms_current(uint16_t mA, float mult) {
      hold_multiplier(mult);
      rms_current(mA);
    }
    uint16_t rms_current() {
      return cs2rms(static_cast<T*>(this)->irun());
    }
    void hold_multiplier(float val) { holdMultiplier = val*255; }
    float hold_multiplier() { return (holdMultiplier+0.5)/255.0; }
  protected:
    TMC_RMS(float RS) : Rsense(RS*255) {};

    const uint8_t Rsense;
    uint8_t holdMultiplier = 127;
};

template<class T>
struct TMC_RMS<T, RMS_TYPE::WITH_GLOBAL_SCALER> {
    uint16_t cs2rms(uint8_t CS);
    void rms_current(uint16_t mA);
    void rms_current(uint16_t mA, float mult) {
      hold_multiplier(mult);
      rms_current(mA);
    }
    uint16_t rms_current() {
      return cs2rms(static_cast<T*>(this)->irun());
    }
    void hold_multiplier(float val) { holdMultiplier = val*255; }
    float hold_multiplier() { return (holdMultiplier+0.5)/255.0; }
  protected:
    TMC_RMS(float RS) : Rsense(RS*255) {};

    const uint8_t Rsense;
    uint8_t holdMultiplier = 127;
};

template<class T>
struct TMC_RMS<T, RMS_TYPE::WITHOUT_VSENSE> {
    uint16_t cs2rms(uint8_t CS);
    void rms_current(uint16_t mA);
    void rms_current(uint16_t mA, float mult) {
      hold_multiplier(mult);
      rms_current(mA);
    }
    uint16_t rms_current() {
      return cs2rms(static_cast<T*>(this)->irun());
    }
    void hold_multiplier(float val) { holdMultiplier = val*255; }
    float hold_multiplier() { return (holdMultiplier+0.5)/255.0; }
  protected:
    TMC_RMS(float RS) : Rsense(RS*255) {};

    const uint8_t Rsense;
    uint8_t holdMultiplier = 127;
};

};

#include "source/interfaces/TMCStepper.hpp"

template<class T> struct TMCStepper;
template<> struct TMCStepper<TMC2130Stepper> : TMCStepper_n::TMCcommon<TMC2130Stepper>, TMCStepper_n::TMC_RMS<TMC2130Stepper, TMCStepper_n::RMS_TYPE::WITH_VSENSE> 			{ using TMC_RMS::TMC_RMS; };
template<> struct TMCStepper<TMC2160Stepper> : TMCStepper_n::TMCcommon<TMC2160Stepper>, TMCStepper_n::TMC_RMS<TMC2160Stepper, TMCStepper_n::RMS_TYPE::WITH_GLOBAL_SCALER> 	{ using TMC_RMS::TMC_RMS; };
template<> struct TMCStepper<TMC5130Stepper> : TMCStepper_n::TMCcommon<TMC5130Stepper>, TMCStepper_n::TMC_RMS<TMC5130Stepper, TMCStepper_n::RMS_TYPE::WITH_VSENSE> 			{ using TMC_RMS::TMC_RMS; };
template<> struct TMCStepper<TMC5160Stepper> : TMCStepper_n::TMCcommon<TMC5160Stepper>, TMCStepper_n::TMC_RMS<TMC5160Stepper, TMCStepper_n::RMS_TYPE::WITH_GLOBAL_SCALER> 	{ using TMC_RMS::TMC_RMS; };
template<> struct TMCStepper<TMC2208Stepper> : TMCStepper_n::TMCcommon<TMC2208Stepper>, TMCStepper_n::TMC_RMS<TMC2208Stepper, TMCStepper_n::RMS_TYPE::WITH_VSENSE> 			{ using TMC_RMS::TMC_RMS; };
template<> struct TMCStepper<TMC2209Stepper> : TMCStepper_n::TMCcommon<TMC2209Stepper>, TMCStepper_n::TMC_RMS<TMC2209Stepper, TMCStepper_n::RMS_TYPE::WITH_VSENSE> 			{ using TMC_RMS::TMC_RMS; };
template<> struct TMCStepper<TMC2300Stepper> : TMCStepper_n::TMCcommon<TMC2300Stepper>, TMCStepper_n::TMC_RMS<TMC2300Stepper, TMCStepper_n::RMS_TYPE::WITHOUT_VSENSE>   { using TMC_RMS::TMC_RMS; };

class TMC2130Stepper :
	public TMCStepper_n::TMC_SPI,
	public TMCStepper<TMC2130Stepper>,
	public TMC2130_n::GCONF_i<TMC2130Stepper>,
	public TMC2130_n::GSTAT_i<TMC2130Stepper>,
	public TMC2130_n::IOIN_i<TMC2130Stepper>,
	public TMC2130_n::IHOLD_IRUN_i<TMC2130Stepper>,
	public TMC2130_n::TPOWERDOWN_i<TMC2130Stepper>,
	public TMC2130_n::TSTEP_i<TMC2130Stepper>,
	public TMC2130_n::TPWMTHRS_i<TMC2130Stepper>,
	public TMC2130_n::TCOOLTHRS_i<TMC2130Stepper>,
	public TMC2130_n::THIGH_i<TMC2130Stepper>,
	public TMC2130_n::XDIRECT_i<TMC2130Stepper>,
	public TMC2130_n::VDCMIN_i<TMC2130Stepper>,
	public TMC2130_n::MSLUTSEL_i<TMC2130Stepper>,
	public TMC2130_n::MSLUTSTART_i<TMC2130Stepper>,
	public TMC2130_n::MSCNT_i<TMC2130Stepper>,
	public TMC2130_n::MSCURACT_i<TMC2130Stepper>,
	public TMC2130_n::CHOPCONF_i<TMC2130Stepper>,
	public TMC2130_n::COOLCONF_i<TMC2130Stepper>,
	public TMC2130_n::DCCTRL_i<TMC2130Stepper>,
	public TMC2130_n::DRV_STATUS_i<TMC2130Stepper>,
	public TMC2130_n::PWMCONF_i<TMC2130Stepper>,
	public TMC2130_n::PWM_SCALE_i<TMC2130Stepper>,
	public TMC2130_n::ENCM_CTRL_i<TMC2130Stepper>,
	public TMC2130_n::LOST_STEPS_i<TMC2130Stepper>
	{
	public:
		TMC2130Stepper(SPIClass &spi, TMCStepper_n::PinDef cs, float RS, int8_t link_index = -1);
		TMC2130Stepper(SW_SPIClass &spi, TMCStepper_n::PinDef cs, float RS, int8_t link_index = -1);

		void begin();
		void defaults();
		bool isEnabled();
		void push();

		// Helper functions
		void sg_current_decrease(uint8_t value);
		uint8_t sg_current_decrease();

		// Can be accessed for a common default value
		static constexpr float default_RS = 0.11;

		// Deleted functions
		__attribute__((deprecated("Please provide a sense resistor value")))
		TMC2130Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, int8_t link_index = -1) = delete;

		__attribute__((deprecated("Please provide a sense resistor value")))
		TMC2130Stepper(TMCStepper_n::PinDef) = delete;

		using GCONF_t           = TMC2130_n::GCONF_i          <TMC2130Stepper>::GCONF_t;
		using GSTAT_t           = TMC2130_n::GSTAT_i          <TMC2130Stepper>::GSTAT_t;
		using IOIN_t            = TMC2130_n::IOIN_i           <TMC2130Stepper>::IOIN_t;
		using IHOLD_IRUN_t      = TMC2130_n::IHOLD_IRUN_i     <TMC2130Stepper>::IHOLD_IRUN_t;
		using TPOWERDOWN_t      = TMC2130_n::TPOWERDOWN_i     <TMC2130Stepper>::TPOWERDOWN_t;
		using TSTEP_t           = TMC2130_n::TSTEP_i          <TMC2130Stepper>::TSTEP_t;
		using TPWMTHRS_t        = TMC2130_n::TPWMTHRS_i       <TMC2130Stepper>::TPWMTHRS_t;
		using TCOOLTHRS_t       = TMC2130_n::TCOOLTHRS_i      <TMC2130Stepper>::TCOOLTHRS_t;
		using THIGH_t           = TMC2130_n::THIGH_i          <TMC2130Stepper>::THIGH_t;
		using XDIRECT_t         = TMC2130_n::XDIRECT_i        <TMC2130Stepper>::XDIRECT_t;
		using VDCMIN_t          = TMC2130_n::VDCMIN_i         <TMC2130Stepper>::VDCMIN_t;
		using MSCNT_t           = TMC2130_n::MSCNT_i          <TMC2130Stepper>::MSCNT_t;
		using MSCURACT_t        = TMC2130_n::MSCURACT_i       <TMC2130Stepper>::MSCURACT_t;
		using CHOPCONF_t        = TMC2130_n::CHOPCONF_i       <TMC2130Stepper>::CHOPCONF_t;
		using COOLCONF_t        = TMC2130_n::COOLCONF_i       <TMC2130Stepper>::COOLCONF_t;
		using DCCTRL_t          = TMC2130_n::DCCTRL_i         <TMC2130Stepper>::DCCTRL_t;
		using DRV_STATUS_t      = TMC2130_n::DRV_STATUS_i     <TMC2130Stepper>::DRV_STATUS_t;
		using PWMCONF_t         = TMC2130_n::PWMCONF_i        <TMC2130Stepper>::PWMCONF_t;
		using PWM_SCALE_t       = TMC2130_n::PWM_SCALE_i      <TMC2130Stepper>::PWM_SCALE_t;
		using ENCM_CTRL_t       = TMC2130_n::ENCM_CTRL_i      <TMC2130Stepper>::ENCM_CTRL_t;
		using LOST_STEPS_t      = TMC2130_n::LOST_STEPS_i     <TMC2130Stepper>::LOST_STEPS_t;
};

class TMC2160Stepper :
	public TMCStepper_n::TMC_SPI,
	public TMCStepper<TMC2160Stepper>,
	public TMC2160_n::GCONF_i<TMC2160Stepper>,
	public TMC2160_n::GSTAT_i<TMC2160Stepper>,
	public TMC2160_n::IOIN_i<TMC2160Stepper>,
	public TMC2160_n::IHOLD_IRUN_i<TMC2160Stepper>,
	public TMC2160_n::TPOWERDOWN_i<TMC2160Stepper>,
	public TMC2160_n::TSTEP_i<TMC2160Stepper>,
	public TMC2160_n::TPWMTHRS_i<TMC2160Stepper>,
	public TMC2160_n::TCOOLTHRS_i<TMC2160Stepper>,
	public TMC2160_n::THIGH_i<TMC2160Stepper>,
	public TMC2160_n::XDIRECT_i<TMC2160Stepper>,
	public TMC2160_n::VDCMIN_i<TMC2160Stepper>,
	public TMC2160_n::MSLUTSEL_i<TMC2160Stepper>,
	public TMC2160_n::MSLUTSTART_i<TMC2160Stepper>,
	public TMC2160_n::MSCNT_i<TMC2160Stepper>,
	public TMC2160_n::MSCURACT_i<TMC2160Stepper>,
	public TMC2160_n::CHOPCONF_i<TMC2160Stepper>,
	public TMC2160_n::COOLCONF_i<TMC2160Stepper>,
	public TMC2160_n::DCCTRL_i<TMC2160Stepper>,
	public TMC2160_n::DRV_STATUS_i<TMC2160Stepper>,
	public TMC2160_n::PWMCONF_i<TMC2160Stepper>,
	public TMC2160_n::ENCM_CTRL_i<TMC2160Stepper>,
	public TMC2160_n::LOST_STEPS_i<TMC2160Stepper>,
	public TMC2160_n::SHORT_CONF_i<TMC2160Stepper>,
	public TMC2160_n::DRV_CONF_i<TMC2160Stepper>,
	public TMC2160_n::GLOBAL_SCALER_i<TMC2160Stepper>,
	public TMC2160_n::OFFSET_READ_i<TMC2160Stepper>,
	public TMC2160_n::PWM_SCALE_i<TMC2160Stepper>
	{
	public:
		TMC2160Stepper(SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS, int8_t link_index = -1);
		TMC2160Stepper(SW_SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS, int8_t link_index = -1);
		void begin();
		void defaults();
		void push();

		uint16_t cs2rms(uint8_t CS);
		void rms_current(uint16_t mA);
		void rms_current(uint16_t mA, float mult);
		uint16_t rms_current();

		// Deleted functions
		__attribute__((deprecated("Please provide a sense resistor value")))
		TMC2160Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, int8_t link_index = -1) = delete;

		static constexpr float default_RS = 0.075;

		using GCONF_t        	= TMC2160_n::GCONF_i          <TMC2160Stepper>::GCONF_t;
		using GSTAT_t        	= TMC2160_n::GSTAT_i          <TMC2160Stepper>::GSTAT_t;
		using IOIN_t         	= TMC2160_n::IOIN_i           <TMC2160Stepper>::IOIN_t;
		using IHOLD_IRUN_t   	= TMC2160_n::IHOLD_IRUN_i     <TMC2160Stepper>::IHOLD_IRUN_t;
		using TPOWERDOWN_t   	= TMC2160_n::TPOWERDOWN_i     <TMC2160Stepper>::TPOWERDOWN_t;
		using TSTEP_t        	= TMC2160_n::TSTEP_i          <TMC2160Stepper>::TSTEP_t;
		using TPWMTHRS_t     	= TMC2160_n::TPWMTHRS_i       <TMC2160Stepper>::TPWMTHRS_t;
		using TCOOLTHRS_t    	= TMC2160_n::TCOOLTHRS_i      <TMC2160Stepper>::TCOOLTHRS_t;
		using THIGH_t        	= TMC2160_n::THIGH_i          <TMC2160Stepper>::THIGH_t;
		using XDIRECT_t      	= TMC2160_n::XDIRECT_i        <TMC2160Stepper>::XDIRECT_t;
		using VDCMIN_t       	= TMC2160_n::VDCMIN_i         <TMC2160Stepper>::VDCMIN_t;
		using MSLUTSEL_t     	= TMC2160_n::MSLUTSEL_i       <TMC2160Stepper>::MSLUTSEL_t;
		using MSLUTSTART_t   	= TMC2160_n::MSLUTSTART_i     <TMC2160Stepper>::MSLUTSTART_t;
		using MSCNT_t        	= TMC2160_n::MSCNT_i          <TMC2160Stepper>::MSCNT_t;
		using MSCURACT_t     	= TMC2160_n::MSCURACT_i       <TMC2160Stepper>::MSCURACT_t;
		using CHOPCONF_t     	= TMC2160_n::CHOPCONF_i       <TMC2160Stepper>::CHOPCONF_t;
		using COOLCONF_t     	= TMC2160_n::COOLCONF_i       <TMC2160Stepper>::COOLCONF_t;
		using DCCTRL_t       	= TMC2160_n::DCCTRL_i         <TMC2160Stepper>::DCCTRL_t;
		using DRV_STATUS_t   	= TMC2160_n::DRV_STATUS_i     <TMC2160Stepper>::DRV_STATUS_t;
		using PWMCONF_t      	= TMC2160_n::PWMCONF_i        <TMC2160Stepper>::PWMCONF_t;
		using ENCM_CTRL_t    	= TMC2160_n::ENCM_CTRL_i      <TMC2160Stepper>::ENCM_CTRL_t;
		using LOST_STEPS_t   	= TMC2160_n::LOST_STEPS_i     <TMC2160Stepper>::LOST_STEPS_t;
		using SHORT_CONF_t   	= TMC2160_n::SHORT_CONF_i     <TMC2160Stepper>::SHORT_CONF_t;
		using DRV_CONF_t     	= TMC2160_n::DRV_CONF_i       <TMC2160Stepper>::DRV_CONF_t;
		using GLOBAL_SCALER_t	= TMC2160_n::GLOBAL_SCALER_i  <TMC2160Stepper>::GLOBAL_SCALER_t;
		using OFFSET_READ_t  	= TMC2160_n::OFFSET_READ_i    <TMC2160Stepper>::OFFSET_READ_t;
		using PWM_SCALE_t    	= TMC2160_n::PWM_SCALE_i      <TMC2160Stepper>::PWM_SCALE_t;
};

class TMC5130Stepper :
	public TMCStepper_n::TMC_SPI,
	public TMCStepper<TMC5130Stepper>,
	public TMC5130_n::GCONF_i         <TMC5130Stepper>,
	public TMC5130_n::GSTAT_i         <TMC5130Stepper>,
	public TMC5130_n::IFCNT_i         <TMC5130Stepper>,
	public TMC5130_n::SLAVECONF_i     <TMC5130Stepper>,
	public TMC5130_n::IOIN_i          <TMC5130Stepper>,
	public TMC5130_n::OUTPUT_i        <TMC5130Stepper>,
	public TMC5130_n::X_COMPARE_i     <TMC5130Stepper>,
	public TMC5130_n::IHOLD_IRUN_i    <TMC5130Stepper>,
	public TMC5130_n::TPOWERDOWN_i    <TMC5130Stepper>,
	public TMC5130_n::TSTEP_i         <TMC5130Stepper>,
	public TMC5130_n::TPWMTHRS_i      <TMC5130Stepper>,
	public TMC5130_n::TCOOLTHRS_i     <TMC5130Stepper>,
	public TMC5130_n::THIGH_i         <TMC5130Stepper>,
	public TMC5130_n::RAMPMODE_i      <TMC5130Stepper>,
	public TMC5130_n::XACTUAL_i       <TMC5130Stepper>,
	public TMC5130_n::VACTUAL_i       <TMC5130Stepper>,
	public TMC5130_n::VSTART_i        <TMC5130Stepper>,
	public TMC5130_n::A1_i            <TMC5130Stepper>,
	public TMC5130_n::V1_i            <TMC5130Stepper>,
	public TMC5130_n::AMAX_i          <TMC5130Stepper>,
	public TMC5130_n::VMAX_i          <TMC5130Stepper>,
	public TMC5130_n::DMAX_i          <TMC5130Stepper>,
	public TMC5130_n::D1_i            <TMC5130Stepper>,
	public TMC5130_n::VSTOP_i         <TMC5130Stepper>,
	public TMC5130_n::TZEROWAIT_i     <TMC5130Stepper>,
	public TMC5130_n::XTARGET_i       <TMC5130Stepper>,
	public TMC5130_n::VDCMIN_i        <TMC5130Stepper>,
	public TMC5130_n::SW_MODE_i       <TMC5130Stepper>,
	public TMC5130_n::RAMP_STAT_i     <TMC5130Stepper>,
	public TMC5130_n::XLATCH_i        <TMC5130Stepper>,
	public TMC5130_n::ENCMODE_i       <TMC5130Stepper>,
	public TMC5130_n::X_ENC_i         <TMC5130Stepper>,
	public TMC5130_n::ENC_CONST_i     <TMC5130Stepper>,
	public TMC5130_n::ENC_STATUS_i    <TMC5130Stepper>,
	public TMC5130_n::ENC_LATCH_i     <TMC5130Stepper>,
	public TMC5130_n::MSLUT0_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT1_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT2_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT3_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT4_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT5_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT6_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUT7_i        <TMC5130Stepper>,
	public TMC5130_n::MSLUTSEL_i      <TMC5130Stepper>,
	public TMC5130_n::MSLUTSTART_i    <TMC5130Stepper>,
	public TMC5130_n::MSCNT_i         <TMC5130Stepper>,
	public TMC5130_n::MSCURACT_i      <TMC5130Stepper>,
	public TMC5130_n::CHOPCONF_i      <TMC5130Stepper>,
	public TMC5130_n::COOLCONF_i      <TMC5130Stepper>,
	public TMC5130_n::DCCTRL_i        <TMC5130Stepper>,
	public TMC5130_n::DRV_STATUS_i    <TMC5130Stepper>,
	public TMC5130_n::PWMCONF_i       <TMC5130Stepper>,
	public TMC5130_n::PWM_SCALE_i     <TMC5130Stepper>,
	public TMC5130_n::ENCM_CTRL_i     <TMC5130Stepper>,
	public TMC5130_n::LOST_STEPS_i    <TMC5130Stepper>
	{
	public:
		TMC5130Stepper(SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS, int8_t link_index = -1);
		TMC5130Stepper(SW_SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS, int8_t link_index = -1);

		void begin();
		void defaults();
		void push();

		__attribute__((deprecated("Please provide a sense resistor value")))
		TMC5130Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, int8_t link_index = -1) = delete;

		static constexpr float default_RS = 0.15;

		using GCONF_t     	= TMC5130_n::GCONF_i         <TMC5130Stepper>::GCONF_t;
		using GSTAT_t     	= TMC5130_n::GSTAT_i         <TMC5130Stepper>::GSTAT_t;
		using IFCNT_t     	= TMC5130_n::IFCNT_i         <TMC5130Stepper>::IFCNT_t;
		using SLAVECONF_t 	= TMC5130_n::SLAVECONF_i     <TMC5130Stepper>::SLAVECONF_t;
		using IOIN_t      	= TMC5130_n::IOIN_i          <TMC5130Stepper>::IOIN_t;
		using OUTPUT_t    	= TMC5130_n::OUTPUT_i        <TMC5130Stepper>::OUTPUT_t;
		using X_COMPARE_t 	= TMC5130_n::X_COMPARE_i     <TMC5130Stepper>::X_COMPARE_t;
		using IHOLD_IRUN_t	= TMC5130_n::IHOLD_IRUN_i    <TMC5130Stepper>::IHOLD_IRUN_t;
		using TPOWERDOWN_t	= TMC5130_n::TPOWERDOWN_i    <TMC5130Stepper>::TPOWERDOWN_t;
		using TSTEP_t     	= TMC5130_n::TSTEP_i         <TMC5130Stepper>::TSTEP_t;
		using TPWMTHRS_t  	= TMC5130_n::TPWMTHRS_i      <TMC5130Stepper>::TPWMTHRS_t;
		using TCOOLTHRS_t 	= TMC5130_n::TCOOLTHRS_i     <TMC5130Stepper>::TCOOLTHRS_t;
		using THIGH_t     	= TMC5130_n::THIGH_i         <TMC5130Stepper>::THIGH_t;
		using RAMPMODE_t  	= TMC5130_n::RAMPMODE_i      <TMC5130Stepper>::RAMPMODE_t;
		using XACTUAL_t   	= TMC5130_n::XACTUAL_i       <TMC5130Stepper>::XACTUAL_t;
		using VACTUAL_t   	= TMC5130_n::VACTUAL_i       <TMC5130Stepper>::VACTUAL_t;
		using VSTART_t    	= TMC5130_n::VSTART_i        <TMC5130Stepper>::VSTART_t;
		using A1_t        	= TMC5130_n::A1_i            <TMC5130Stepper>::A1_t;
		using V1_t        	= TMC5130_n::V1_i            <TMC5130Stepper>::V1_t;
		using AMAX_t      	= TMC5130_n::AMAX_i          <TMC5130Stepper>::AMAX_t;
		using VMAX_t      	= TMC5130_n::VMAX_i          <TMC5130Stepper>::VMAX_t;
		using DMAX_t      	= TMC5130_n::DMAX_i          <TMC5130Stepper>::DMAX_t;
		using D1_t        	= TMC5130_n::D1_i            <TMC5130Stepper>::D1_t;
		using VSTOP_t     	= TMC5130_n::VSTOP_i         <TMC5130Stepper>::VSTOP_t;
		using TZEROWAIT_t 	= TMC5130_n::TZEROWAIT_i     <TMC5130Stepper>::TZEROWAIT_t;
		using XTARGET_t   	= TMC5130_n::XTARGET_i       <TMC5130Stepper>::XTARGET_t;
		using VDCMIN_t    	= TMC5130_n::VDCMIN_i        <TMC5130Stepper>::VDCMIN_t;
		using SW_MODE_t   	= TMC5130_n::SW_MODE_i       <TMC5130Stepper>::SW_MODE_t;
		using RAMP_STAT_t 	= TMC5130_n::RAMP_STAT_i     <TMC5130Stepper>::RAMP_STAT_t;
		using XLATCH_t    	= TMC5130_n::XLATCH_i        <TMC5130Stepper>::XLATCH_t;
		using ENCMODE_t   	= TMC5130_n::ENCMODE_i       <TMC5130Stepper>::ENCMODE_t;
		using X_ENC_t     	= TMC5130_n::X_ENC_i         <TMC5130Stepper>::X_ENC_t;
		using ENC_CONST_t 	= TMC5130_n::ENC_CONST_i     <TMC5130Stepper>::ENC_CONST_t;
		using ENC_STATUS_t	= TMC5130_n::ENC_STATUS_i    <TMC5130Stepper>::ENC_STATUS_t;
		using ENC_LATCH_t 	= TMC5130_n::ENC_LATCH_i     <TMC5130Stepper>::ENC_LATCH_t;
		using MSLUT0_t    	= TMC5130_n::MSLUT0_i        <TMC5130Stepper>::MSLUT0_t;
		using MSLUT1_t    	= TMC5130_n::MSLUT1_i        <TMC5130Stepper>::MSLUT1_t;
		using MSLUT2_t    	= TMC5130_n::MSLUT2_i        <TMC5130Stepper>::MSLUT2_t;
		using MSLUT3_t    	= TMC5130_n::MSLUT3_i        <TMC5130Stepper>::MSLUT3_t;
		using MSLUT4_t    	= TMC5130_n::MSLUT4_i        <TMC5130Stepper>::MSLUT4_t;
		using MSLUT5_t    	= TMC5130_n::MSLUT5_i        <TMC5130Stepper>::MSLUT5_t;
		using MSLUT6_t    	= TMC5130_n::MSLUT6_i        <TMC5130Stepper>::MSLUT6_t;
		using MSLUT7_t    	= TMC5130_n::MSLUT7_i        <TMC5130Stepper>::MSLUT7_t;
		using MSLUTSEL_t  	= TMC5130_n::MSLUTSEL_i      <TMC5130Stepper>::MSLUTSEL_t;
		using MSLUTSTART_t	= TMC5130_n::MSLUTSTART_i    <TMC5130Stepper>::MSLUTSTART_t;
		using MSCNT_t     	= TMC5130_n::MSCNT_i         <TMC5130Stepper>::MSCNT_t;
		using MSCURACT_t  	= TMC5130_n::MSCURACT_i      <TMC5130Stepper>::MSCURACT_t;
		using CHOPCONF_t  	= TMC5130_n::CHOPCONF_i      <TMC5130Stepper>::CHOPCONF_t;
		using COOLCONF_t  	= TMC5130_n::COOLCONF_i      <TMC5130Stepper>::COOLCONF_t;
		using DCCTRL_t    	= TMC5130_n::DCCTRL_i        <TMC5130Stepper>::DCCTRL_t;
		using DRV_STATUS_t	= TMC5130_n::DRV_STATUS_i    <TMC5130Stepper>::DRV_STATUS_t;
		using PWMCONF_t   	= TMC5130_n::PWMCONF_i       <TMC5130Stepper>::PWMCONF_t;
		using PWM_SCALE_t 	= TMC5130_n::PWM_SCALE_i     <TMC5130Stepper>::PWM_SCALE_t;
		using ENCM_CTRL_t 	= TMC5130_n::ENCM_CTRL_i     <TMC5130Stepper>::ENCM_CTRL_t;
		using LOST_STEPS_t	= TMC5130_n::LOST_STEPS_i    <TMC5130Stepper>::LOST_STEPS_t;
	};

class TMC5160Stepper :
	public TMCStepper_n::TMC_SPI,
	public TMCStepper<TMC5160Stepper>,
	public TMC5160_n::GCONF_i            <TMC5160Stepper>,
	public TMC5160_n::GSTAT_i            <TMC5160Stepper>,
	public TMC5160_n::IFCNT_i            <TMC5160Stepper>,
	public TMC5160_n::SLAVECONF_i        <TMC5160Stepper>,
	public TMC5160_n::IOIN_i             <TMC5160Stepper>,
	public TMC5160_n::OUTPUT_i           <TMC5160Stepper>,
	public TMC5160_n::X_COMPARE_i        <TMC5160Stepper>,
	public TMC5160_n::OTP_PROG_i         <TMC5160Stepper>,
	public TMC5160_n::OTP_READ_i         <TMC5160Stepper>,
	public TMC5160_n::FACTORY_CONF_i     <TMC5160Stepper>,
	public TMC5160_n::SHORT_CONF_i       <TMC5160Stepper>,
	public TMC5160_n::DRV_CONF_i         <TMC5160Stepper>,
	public TMC5160_n::GLOBAL_SCALER_i    <TMC5160Stepper>,
	public TMC5160_n::OFFSET_READ_i      <TMC5160Stepper>,
	public TMC5160_n::IHOLD_IRUN_i       <TMC5160Stepper>,
	public TMC5160_n::TPOWERDOWN_i       <TMC5160Stepper>,
	public TMC5160_n::TSTEP_i            <TMC5160Stepper>,
	public TMC5160_n::TPWMTHRS_i         <TMC5160Stepper>,
	public TMC5160_n::TCOOLTHRS_i        <TMC5160Stepper>,
	public TMC5160_n::THIGH_i            <TMC5160Stepper>,
	public TMC5160_n::RAMPMODE_i         <TMC5160Stepper>,
	public TMC5160_n::XACTUAL_i          <TMC5160Stepper>,
	public TMC5160_n::VACTUAL_i          <TMC5160Stepper>,
	public TMC5160_n::VSTART_i           <TMC5160Stepper>,
	public TMC5160_n::A1_i               <TMC5160Stepper>,
	public TMC5160_n::V1_i               <TMC5160Stepper>,
	public TMC5160_n::AMAX_i             <TMC5160Stepper>,
	public TMC5160_n::VMAX_i             <TMC5160Stepper>,
	public TMC5160_n::DMAX_i             <TMC5160Stepper>,
	public TMC5160_n::D1_i               <TMC5160Stepper>,
	public TMC5160_n::VSTOP_i            <TMC5160Stepper>,
	public TMC5160_n::TZEROWAIT_i        <TMC5160Stepper>,
	public TMC5160_n::XTARGET_i          <TMC5160Stepper>,
	public TMC5160_n::VDCMIN_i           <TMC5160Stepper>,
	public TMC5160_n::SW_MODE_i          <TMC5160Stepper>,
	public TMC5160_n::RAMP_STAT_i        <TMC5160Stepper>,
	public TMC5160_n::XLATCH_i           <TMC5160Stepper>,
	public TMC5160_n::ENCMODE_i          <TMC5160Stepper>,
	public TMC5160_n::X_ENC_i            <TMC5160Stepper>,
	public TMC5160_n::ENC_CONST_i        <TMC5160Stepper>,
	public TMC5160_n::ENC_STATUS_i       <TMC5160Stepper>,
	public TMC5160_n::ENC_LATCH_i        <TMC5160Stepper>,
	public TMC5160_n::ENC_DEVIATION_i    <TMC5160Stepper>,
	public TMC5160_n::MSLUT0_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT1_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT2_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT3_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT4_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT5_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT6_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUT7_i           <TMC5160Stepper>,
	public TMC5160_n::MSLUTSEL_i         <TMC5160Stepper>,
	public TMC5160_n::MSLUTSTART_i       <TMC5160Stepper>,
	public TMC5160_n::MSCNT_i            <TMC5160Stepper>,
	public TMC5160_n::MSCURACT_i         <TMC5160Stepper>,
	public TMC5160_n::CHOPCONF_i         <TMC5160Stepper>,
	public TMC5160_n::COOLCONF_i         <TMC5160Stepper>,
	public TMC5160_n::DCCTRL_i           <TMC5160Stepper>,
	public TMC5160_n::DRV_STATUS_i       <TMC5160Stepper>,
	public TMC5160_n::PWMCONF_i          <TMC5160Stepper>,
	public TMC5160_n::PWM_SCALE_i        <TMC5160Stepper>,
	public TMC5160_n::PWM_AUTO_i         <TMC5160Stepper>,
	public TMC5160_n::LOST_STEPS_i       <TMC5160Stepper>
	{
	public:
		TMC5160Stepper(SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS, int8_t link_index = -1);
		TMC5160Stepper(SW_SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS, int8_t link_index = -1);

		void defaults();
		void push();

		__attribute__((deprecated("Please provide a sense resistor value")))
		TMC5160Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, TMCStepper_n::PinDef, int8_t link_index = -1) = delete;

		static constexpr float default_RS = 0.075;

        using GCONF_t        	= TMC5160_n::GCONF_i          <TMC5160Stepper>::GCONF_t;
        using GSTAT_t        	= TMC5160_n::GSTAT_i          <TMC5160Stepper>::GSTAT_t;
        using IFCNT_t        	= TMC5160_n::IFCNT_i          <TMC5160Stepper>::IFCNT_t;
        using SLAVECONF_t    	= TMC5160_n::SLAVECONF_i      <TMC5160Stepper>::SLAVECONF_t;
        using IOIN_t         	= TMC5160_n::IOIN_i           <TMC5160Stepper>::IOIN_t;
        using OUTPUT_t       	= TMC5160_n::OUTPUT_i         <TMC5160Stepper>::OUTPUT_t;
        using X_COMPARE_t    	= TMC5160_n::X_COMPARE_i      <TMC5160Stepper>::X_COMPARE_t;
        using OTP_PROG_t     	= TMC5160_n::OTP_PROG_i       <TMC5160Stepper>::OTP_PROG_t;
        using OTP_READ_t     	= TMC5160_n::OTP_READ_i       <TMC5160Stepper>::OTP_READ_t;
        using FACTORY_CONF_t 	= TMC5160_n::FACTORY_CONF_i   <TMC5160Stepper>::FACTORY_CONF_t;
        using SHORT_CONF_t   	= TMC5160_n::SHORT_CONF_i     <TMC5160Stepper>::SHORT_CONF_t;
        using DRV_CONF_t     	= TMC5160_n::DRV_CONF_i       <TMC5160Stepper>::DRV_CONF_t;
        using GLOBAL_SCALER_t	= TMC5160_n::GLOBAL_SCALER_i  <TMC5160Stepper>::GLOBAL_SCALER_t;
        using OFFSET_READ_t  	= TMC5160_n::OFFSET_READ_i    <TMC5160Stepper>::OFFSET_READ_t;
        using IHOLD_IRUN_t   	= TMC5160_n::IHOLD_IRUN_i     <TMC5160Stepper>::IHOLD_IRUN_t;
        using TPOWERDOWN_t   	= TMC5160_n::TPOWERDOWN_i     <TMC5160Stepper>::TPOWERDOWN_t;
        using TSTEP_t        	= TMC5160_n::TSTEP_i          <TMC5160Stepper>::TSTEP_t;
        using TPWMTHRS_t     	= TMC5160_n::TPWMTHRS_i       <TMC5160Stepper>::TPWMTHRS_t;
        using TCOOLTHRS_t    	= TMC5160_n::TCOOLTHRS_i      <TMC5160Stepper>::TCOOLTHRS_t;
        using THIGH_t        	= TMC5160_n::THIGH_i          <TMC5160Stepper>::THIGH_t;
        using RAMPMODE_t     	= TMC5160_n::RAMPMODE_i       <TMC5160Stepper>::RAMPMODE_t;
        using XACTUAL_t      	= TMC5160_n::XACTUAL_i        <TMC5160Stepper>::XACTUAL_t;
        using VACTUAL_t      	= TMC5160_n::VACTUAL_i        <TMC5160Stepper>::VACTUAL_t;
        using VSTART_t       	= TMC5160_n::VSTART_i         <TMC5160Stepper>::VSTART_t;
        using A1_t           	= TMC5160_n::A1_i             <TMC5160Stepper>::A1_t;
        using V1_t           	= TMC5160_n::V1_i             <TMC5160Stepper>::V1_t;
        using AMAX_t         	= TMC5160_n::AMAX_i           <TMC5160Stepper>::AMAX_t;
        using VMAX_t         	= TMC5160_n::VMAX_i           <TMC5160Stepper>::VMAX_t;
        using DMAX_t         	= TMC5160_n::DMAX_i           <TMC5160Stepper>::DMAX_t;
        using D1_t           	= TMC5160_n::D1_i             <TMC5160Stepper>::D1_t;
        using VSTOP_t        	= TMC5160_n::VSTOP_i          <TMC5160Stepper>::VSTOP_t;
        using TZEROWAIT_t    	= TMC5160_n::TZEROWAIT_i      <TMC5160Stepper>::TZEROWAIT_t;
        using XTARGET_t      	= TMC5160_n::XTARGET_i        <TMC5160Stepper>::XTARGET_t;
        using VDCMIN_t       	= TMC5160_n::VDCMIN_i         <TMC5160Stepper>::VDCMIN_t;
        using SW_MODE_t      	= TMC5160_n::SW_MODE_i        <TMC5160Stepper>::SW_MODE_t;
        using RAMP_STAT_t    	= TMC5160_n::RAMP_STAT_i      <TMC5160Stepper>::RAMP_STAT_t;
        using XLATCH_t       	= TMC5160_n::XLATCH_i         <TMC5160Stepper>::XLATCH_t;
        using ENCMODE_t      	= TMC5160_n::ENCMODE_i        <TMC5160Stepper>::ENCMODE_t;
        using X_ENC_t        	= TMC5160_n::X_ENC_i          <TMC5160Stepper>::X_ENC_t;
        using ENC_CONST_t    	= TMC5160_n::ENC_CONST_i      <TMC5160Stepper>::ENC_CONST_t;
        using ENC_STATUS_t   	= TMC5160_n::ENC_STATUS_i     <TMC5160Stepper>::ENC_STATUS_t;
        using ENC_LATCH_t    	= TMC5160_n::ENC_LATCH_i      <TMC5160Stepper>::ENC_LATCH_t;
        using ENC_DEVIATION_t	= TMC5160_n::ENC_DEVIATION_i  <TMC5160Stepper>::ENC_DEVIATION_t;
        using MSLUT0_t       	= TMC5160_n::MSLUT0_i         <TMC5160Stepper>::MSLUT0_t;
        using MSLUT1_t       	= TMC5160_n::MSLUT1_i         <TMC5160Stepper>::MSLUT1_t;
        using MSLUT2_t       	= TMC5160_n::MSLUT2_i         <TMC5160Stepper>::MSLUT2_t;
        using MSLUT3_t       	= TMC5160_n::MSLUT3_i         <TMC5160Stepper>::MSLUT3_t;
        using MSLUT4_t       	= TMC5160_n::MSLUT4_i         <TMC5160Stepper>::MSLUT4_t;
        using MSLUT5_t       	= TMC5160_n::MSLUT5_i         <TMC5160Stepper>::MSLUT5_t;
        using MSLUT6_t       	= TMC5160_n::MSLUT6_i         <TMC5160Stepper>::MSLUT6_t;
        using MSLUT7_t       	= TMC5160_n::MSLUT7_i         <TMC5160Stepper>::MSLUT7_t;
        using MSLUTSEL_t     	= TMC5160_n::MSLUTSEL_i       <TMC5160Stepper>::MSLUTSEL_t;
        using MSLUTSTART_t   	= TMC5160_n::MSLUTSTART_i     <TMC5160Stepper>::MSLUTSTART_t;
        using MSCNT_t        	= TMC5160_n::MSCNT_i          <TMC5160Stepper>::MSCNT_t;
        using MSCURACT_t     	= TMC5160_n::MSCURACT_i       <TMC5160Stepper>::MSCURACT_t;
        using CHOPCONF_t     	= TMC5160_n::CHOPCONF_i       <TMC5160Stepper>::CHOPCONF_t;
        using COOLCONF_t     	= TMC5160_n::COOLCONF_i       <TMC5160Stepper>::COOLCONF_t;
        using DCCTRL_t       	= TMC5160_n::DCCTRL_i         <TMC5160Stepper>::DCCTRL_t;
        using DRV_STATUS_t   	= TMC5160_n::DRV_STATUS_i     <TMC5160Stepper>::DRV_STATUS_t;
        using PWMCONF_t      	= TMC5160_n::PWMCONF_i        <TMC5160Stepper>::PWMCONF_t;
        using PWM_SCALE_t    	= TMC5160_n::PWM_SCALE_i      <TMC5160Stepper>::PWM_SCALE_t;
        using PWM_AUTO_t     	= TMC5160_n::PWM_AUTO_i       <TMC5160Stepper>::PWM_AUTO_t;
        using LOST_STEPS_t   	= TMC5160_n::LOST_STEPS_i     <TMC5160Stepper>::LOST_STEPS_t;
};

typedef TMC5160Stepper TMC5161Stepper;

class TMC2208Stepper :
	public TMCStepper_n::TMC_UART,
	public TMCStepper<TMC2208Stepper>,
	public TMC2208_n::GCONF_i<TMC2208Stepper>,
	public TMC2208_n::GSTAT_i<TMC2208Stepper>,
	public TMC2208_n::IFCNT_i<TMC2208Stepper>,
	public TMC2208_n::SLAVECONF_i<TMC2208Stepper>,
	public TMC2208_n::OTP_PROG_i<TMC2208Stepper>,
	public TMC2208_n::OTP_READ_i<TMC2208Stepper>,
	public TMC2208_n::IOIN_i<TMC2208Stepper>,
	public TMC2208_n::FACTORY_CONF_i<TMC2208Stepper>,
	public TMC2208_n::IHOLD_IRUN_i<TMC2208Stepper>,
	public TMC2208_n::TPOWERDOWN_i<TMC2208Stepper>,
	public TMC2208_n::TSTEP_i<TMC2208Stepper>,
	public TMC2208_n::TPWMTHRS_i<TMC2208Stepper>,
	public TMC2208_n::VACTUAL_i<TMC2208Stepper>,
	public TMC2208_n::MSCNT_i<TMC2208Stepper>,
	public TMC2208_n::MSCURACT_i<TMC2208Stepper>,
	public TMC2208_n::CHOPCONF_i<TMC2208Stepper>,
	public TMC2208_n::DRV_STATUS_i<TMC2208Stepper>,
	public TMC2208_n::PWMCONF_i<TMC2208Stepper>,
	public TMC2208_n::PWM_SCALE_i<TMC2208Stepper>,
	public TMC2208_n::PWM_AUTO_i<TMC2208Stepper>
	{
	public:
	    TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr, TMCStepper_n::PinDef mul_pin1, TMCStepper_n::PinDef mul_pin2);
		TMC2208Stepper(HardwareSerial * SerialPort, float RS) :
			TMC2208Stepper(SerialPort, RS, TMC2208_SLAVE_ADDR)
			{}
		#if SW_CAPABLE_PLATFORM
			TMC2208Stepper(TMCStepper_n::PinDef SW_RX_pin, TMCStepper_n::PinDef SW_TX_pin, float RS) :
				TMC2208Stepper(SW_RX_pin, SW_TX_pin, RS, TMC2208_SLAVE_ADDR)
				{}

			__attribute__((deprecated("Boolean argument has been deprecated and does nothing")))
			TMC2208Stepper(TMCStepper_n::PinDef SW_RX_pin, TMCStepper_n::PinDef SW_TX_pin, float RS, bool) :
				TMC2208Stepper(SW_RX_pin, SW_TX_pin, RS, TMC2208_SLAVE_ADDR)
				{};
		#else
			TMC2208Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, float) = delete; // Your platform does not currently support Software Serial
		#endif
		void defaults();
		void push();
		void begin();
		#if SW_CAPABLE_PLATFORM
			void beginSerial(uint32_t baudrate);
		#else
			void beginSerial(uint32_t) = delete; // Your platform does not currently support Software Serial
		#endif
		bool isEnabled();

	protected:

		TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr);
		#if SW_CAPABLE_PLATFORM
			TMC2208Stepper(TMCStepper_n::PinDef SW_RX_pin, TMCStepper_n::PinDef SW_TX_pin, float RS, uint8_t addr);
		#endif
		using GCONF_t       	= TMC2208_n::GCONF_i       	<TMC2208Stepper>::GCONF_t;
		using GSTAT_t       	= TMC2208_n::GSTAT_i       	<TMC2208Stepper>::GSTAT_t;
		using IFCNT_t       	= TMC2208_n::IFCNT_i       	<TMC2208Stepper>::IFCNT_t;
		using SLAVECONF_t   	= TMC2208_n::SLAVECONF_i   	<TMC2208Stepper>::SLAVECONF_t;
		using OTP_PROG_t    	= TMC2208_n::OTP_PROG_i    	<TMC2208Stepper>::OTP_PROG_t;
		using OTP_READ_t    	= TMC2208_n::OTP_READ_i    	<TMC2208Stepper>::OTP_READ_t;
		using IOIN_t        	= TMC2208_n::IOIN_i        	<TMC2208Stepper>::IOIN_t;
		using FACTORY_CONF_t	= TMC2208_n::FACTORY_CONF_i	<TMC2208Stepper>::FACTORY_CONF_t;
		using IHOLD_IRUN_t  	= TMC2208_n::IHOLD_IRUN_i  	<TMC2208Stepper>::IHOLD_IRUN_t;
		using TPOWERDOWN_t  	= TMC2208_n::TPOWERDOWN_i  	<TMC2208Stepper>::TPOWERDOWN_t;
		using TSTEP_t       	= TMC2208_n::TSTEP_i       	<TMC2208Stepper>::TSTEP_t;
		using TPWMTHRS_t    	= TMC2208_n::TPWMTHRS_i    	<TMC2208Stepper>::TPWMTHRS_t;
		using VACTUAL_t     	= TMC2208_n::VACTUAL_i     	<TMC2208Stepper>::VACTUAL_t;
		using MSCNT_t       	= TMC2208_n::MSCNT_i       	<TMC2208Stepper>::MSCNT_t;
		using MSCURACT_t    	= TMC2208_n::MSCURACT_i    	<TMC2208Stepper>::MSCURACT_t;
		using CHOPCONF_t    	= TMC2208_n::CHOPCONF_i    	<TMC2208Stepper>::CHOPCONF_t;
		using DRV_STATUS_t  	= TMC2208_n::DRV_STATUS_i  	<TMC2208Stepper>::DRV_STATUS_t;
		using PWMCONF_t     	= TMC2208_n::PWMCONF_i     	<TMC2208Stepper>::PWMCONF_t;
		using PWM_SCALE_t   	= TMC2208_n::PWM_SCALE_i   	<TMC2208Stepper>::PWM_SCALE_t;
		using PWM_AUTO_t    	= TMC2208_n::PWM_AUTO_i    	<TMC2208Stepper>::PWM_AUTO_t;
};

class TMC2209Stepper :
	public TMC2208Stepper,
	public TMC2209_n::IOIN_i<TMC2209Stepper>,
	public TMC2209_n::TCOOLTHRS_i<TMC2209Stepper>,
	public TMC2209_n::SGTHRS_i<TMC2209Stepper>,
	public TMC2209_n::SG_RESULT_i<TMC2209Stepper>,
	public TMC2209_n::COOLCONF_i<TMC2209Stepper>
	{
	public:
		TMC2209Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr) :
			TMC2208Stepper(SerialPort, RS, addr) {}

		#if SW_CAPABLE_PLATFORM
			TMC2209Stepper(TMCStepper_n::PinDef SW_RX_pin, TMCStepper_n::PinDef SW_TX_pin, float RS, uint8_t addr) :
				TMC2208Stepper(SW_RX_pin, SW_TX_pin, RS, addr) {}
		#else
			TMC2209Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, float, uint8_t) = delete; // Your platform does not currently support Software Serial
		#endif
		void push();

		using GCONF_t       	= TMC2209_n::GCONF_i       	<TMC2209Stepper>::GCONF_t;
		using GSTAT_t       	= TMC2209_n::GSTAT_i       	<TMC2209Stepper>::GSTAT_t;
		using IFCNT_t       	= TMC2209_n::IFCNT_i       	<TMC2209Stepper>::IFCNT_t;
		using SLAVECONF_t   	= TMC2209_n::SLAVECONF_i   	<TMC2209Stepper>::SLAVECONF_t;
		using OTP_PROG_t    	= TMC2209_n::OTP_PROG_i    	<TMC2209Stepper>::OTP_PROG_t;
		using OTP_READ_t    	= TMC2209_n::OTP_READ_i    	<TMC2209Stepper>::OTP_READ_t;
		using IOIN_t        	= TMC2209_n::IOIN_i        	<TMC2209Stepper>::IOIN_t;
		using FACTORY_CONF_t	= TMC2209_n::FACTORY_CONF_i	<TMC2209Stepper>::FACTORY_CONF_t;
		using IHOLD_IRUN_t  	= TMC2209_n::IHOLD_IRUN_i  	<TMC2209Stepper>::IHOLD_IRUN_t;
		using TPOWERDOWN_t  	= TMC2209_n::TPOWERDOWN_i  	<TMC2209Stepper>::TPOWERDOWN_t;
		using TSTEP_t       	= TMC2209_n::TSTEP_i       	<TMC2209Stepper>::TSTEP_t;
		using TPWMTHRS_t    	= TMC2209_n::TPWMTHRS_i    	<TMC2209Stepper>::TPWMTHRS_t;
		using TCOOLTHRS_t   	= TMC2209_n::TCOOLTHRS_i   	<TMC2209Stepper>::TCOOLTHRS_t;
		using VACTUAL_t     	= TMC2209_n::VACTUAL_i     	<TMC2209Stepper>::VACTUAL_t;
		using SGTHRS_t      	= TMC2209_n::SGTHRS_i      	<TMC2209Stepper>::SGTHRS_t;
		using SG_RESULT_t   	= TMC2209_n::SG_RESULT_i   	<TMC2209Stepper>::SG_RESULT_t;
		using COOLCONF_t    	= TMC2209_n::COOLCONF_i    	<TMC2209Stepper>::COOLCONF_t;
		using MSCNT_t       	= TMC2209_n::MSCNT_i       	<TMC2209Stepper>::MSCNT_t;
		using MSCURACT_t    	= TMC2209_n::MSCURACT_i    	<TMC2209Stepper>::MSCURACT_t;
		using CHOPCONF_t    	= TMC2209_n::CHOPCONF_i    	<TMC2209Stepper>::CHOPCONF_t;
		using DRV_STATUS_t  	= TMC2209_n::DRV_STATUS_i  	<TMC2209Stepper>::DRV_STATUS_t;
		using PWMCONF_t     	= TMC2209_n::PWMCONF_i     	<TMC2209Stepper>::PWMCONF_t;
		using PWM_SCALE_t   	= TMC2209_n::PWM_SCALE_i   	<TMC2209Stepper>::PWM_SCALE_t;
		using PWM_AUTO_t    	= TMC2209_n::PWM_AUTO_i    	<TMC2209Stepper>::PWM_AUTO_t;
};

class TMC2300Stepper :
	public TMCStepper_n::TMC_UART,
	public TMCStepper<TMC2300Stepper>,
	public TMC2300_n::GCONF_i<TMC2300Stepper>,
	public TMC2300_n::GSTAT_i<TMC2300Stepper>,
	public TMC2300_n::IFCNT_i<TMC2300Stepper>,
	public TMC2300_n::SLAVECONF_i<TMC2300Stepper>,
	public TMC2300_n::IOIN_i<TMC2300Stepper>,
	public TMC2300_n::IHOLD_IRUN_i<TMC2300Stepper>,
	public TMC2300_n::TPOWERDOWN_i<TMC2300Stepper>,
	public TMC2300_n::TSTEP_i<TMC2300Stepper>,
	public TMC2300_n::VACTUAL_i<TMC2300Stepper>,
	public TMC2300_n::TCOOLTHRS_i<TMC2300Stepper>,
	public TMC2300_n::SGTHRS_i<TMC2300Stepper>,
	public TMC2300_n::SG_VALUE_i<TMC2300Stepper>,
	public TMC2300_n::COOLCONF_i<TMC2300Stepper>,
	public TMC2300_n::MSCNT_i<TMC2300Stepper>,
	public TMC2300_n::CHOPCONF_i<TMC2300Stepper>,
	public TMC2300_n::DRV_STATUS_i<TMC2300Stepper>,
	public TMC2300_n::PWMCONF_i<TMC2300Stepper>,
	public TMC2300_n::PWM_SCALE_i<TMC2300Stepper>,
	public TMC2300_n::PWM_AUTO_i<TMC2300Stepper>
	{
		public:
			TMC2300Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr);

			#if SW_CAPABLE_PLATFORM
				TMC2300Stepper(TMCStepper_n::PinDef SW_RX_pin, TMCStepper_n::PinDef SW_TX_pin, float RS, uint8_t addr);
			#else
				TMC2300Stepper(TMCStepper_n::PinDef, TMCStepper_n::PinDef, float, uint8_t) = delete; // Your platform does not currently support Software Serial
			#endif
			void defaults();
			void push();
			void begin();
			#if SW_CAPABLE_PLATFORM
				void beginSerial(uint32_t baudrate);
			#else
				void beginSerial(uint32_t) = delete; // Your platform does not currently support Software Serial
			#endif
			bool isEnabled();

			using GCONF_t       = TMC2300_n::GCONF_i       <TMC2300Stepper>::GCONF_t;
			using GSTAT_t       = TMC2300_n::GSTAT_i       <TMC2300Stepper>::GSTAT_t;
			using IFCNT_t       = TMC2300_n::IFCNT_i       <TMC2300Stepper>::IFCNT_t;
			using SLAVECONF_t   = TMC2300_n::SLAVECONF_i   <TMC2300Stepper>::SLAVECONF_t;
			using IOIN_t        = TMC2300_n::IOIN_i        <TMC2300Stepper>::IOIN_t;
			using IHOLD_IRUN_t  = TMC2300_n::IHOLD_IRUN_i  <TMC2300Stepper>::IHOLD_IRUN_t;
			using TPOWERDOWN_t  = TMC2300_n::TPOWERDOWN_i  <TMC2300Stepper>::TPOWERDOWN_t;
			using TSTEP_t       = TMC2300_n::TSTEP_i       <TMC2300Stepper>::TSTEP_t;
			using VACTUAL_t     = TMC2300_n::VACTUAL_i     <TMC2300Stepper>::VACTUAL_t;
			using TCOOLTHRS_t   = TMC2300_n::TCOOLTHRS_i   <TMC2300Stepper>::TCOOLTHRS_t;
			using SGTHRS_t      = TMC2300_n::SGTHRS_i      <TMC2300Stepper>::SGTHRS_t;
			using SG_VALUE_t    = TMC2300_n::SG_VALUE_i    <TMC2300Stepper>::SG_VALUE_t;
			using COOLCONF_t    = TMC2300_n::COOLCONF_i    <TMC2300Stepper>::COOLCONF_t;
			using MSCNT_t       = TMC2300_n::MSCNT_i       <TMC2300Stepper>::MSCNT_t;
			using CHOPCONF_t    = TMC2300_n::CHOPCONF_i    <TMC2300Stepper>::CHOPCONF_t;
			using DRV_STATUS_t  = TMC2300_n::DRV_STATUS_i  <TMC2300Stepper>::DRV_STATUS_t;
			using PWMCONF_t     = TMC2300_n::PWMCONF_i     <TMC2300Stepper>::PWMCONF_t;
			using PWM_SCALE_t   = TMC2300_n::PWM_SCALE_i   <TMC2300Stepper>::PWM_SCALE_t;
			using PWM_AUTO_t    = TMC2300_n::PWM_AUTO_i    <TMC2300Stepper>::PWM_AUTO_t;
};

class TMC2224Stepper : public TMC2208Stepper, public TMC2224_n::IOIN_i<TMC2224Stepper> {
	using TMC2208Stepper::TMC2208Stepper;
};

class TMC2660Stepper {
	public:
		TMC2660Stepper(SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS);
		TMC2660Stepper(SW_SPIClass &spi, TMCStepper_n::PinDef pinCS, float RS);
		void begin();
		bool isEnabled();
		uint8_t test_connection();
		uint16_t cs2rms(uint8_t CS);
		uint16_t rms_current();
		void rms_current(uint16_t mA);
		//uint16_t getMilliamps() {return val_mA;}
		void push();
		uint8_t savedToff() { return _savedToff; }

		// Helper functions
		void microsteps(uint16_t ms);
		uint16_t microsteps();
		void blank_time(uint8_t value);
		uint8_t blank_time();
		void hysteresis_end(int8_t value);
		int8_t hysteresis_end();
		void hysteresis_start(uint8_t value);
		uint8_t hysteresis_start();

		// W: DRVCONF
		void DRVCONF(uint32_t);
		void tst(bool);
		void slph(uint8_t);
		void slpl(uint8_t);
		void diss2g(bool);
		void ts2g(uint8_t);
		void sdoff(bool);
		void vsense(bool);
		void rdsel(uint8_t);
		uint32_t DRVCONF();
		bool tst();
		uint8_t slph();
		uint8_t slpl();
		bool diss2g();
		uint8_t ts2g();
		bool sdoff();
		bool vsense();
		uint8_t rdsel();

		// W: DRVCTRL
		void DRVCTRL(uint32_t);
		void pha(bool B);
		void ca(uint8_t B);
		void phb(bool B);
		void cb(uint8_t B);
		bool pha();
		uint8_t ca();
		bool phb();
		uint8_t cb();
		void intpol(bool);
		void dedge(bool);
		void mres(uint8_t);
		uint32_t DRVCTRL();
		bool intpol();
		bool dedge();
		uint8_t mres();

		// W: CHOPCONF
		void CHOPCONF(uint32_t);
		void tbl(uint8_t);
		void chm(bool);
		void rndtf(bool);
		void hdec(uint8_t);
		void hend(uint8_t);
		void hstrt(uint8_t);
		void toff(uint8_t);
		uint32_t CHOPCONF();
		uint8_t tbl();
		bool chm();
		bool rndtf();
		uint8_t hdec();
		uint8_t hend();
		uint8_t hstrt();
		uint8_t toff();

		// R: DRVSTATUS
		uint32_t DRV_STATUS() { return DRVSTATUS(); }
		uint32_t DRVSTATUS();
		uint16_t mstep();
		uint8_t se();
		bool stst();
		bool olb();
		bool ola();
		bool s2gb();
		bool s2ga();
		bool otpw();
		bool ot();
		bool sg();
		uint16_t sg_result();

		// W: SGCSCONF
		uint32_t SGCSCONF();
		void sfilt(bool);
		void sgt(uint8_t);
		void cs(uint8_t);
		void SGCSCONF(uint32_t);
		bool sfilt();
		uint8_t sgt();
		uint8_t cs();

		// W: SMARTEN
		void SMARTEN(uint32_t);
		void seimin(bool B);
		void sedn(uint8_t B);
		void semax(uint8_t B);
		void seup(uint8_t B);
		void semin(uint8_t B);
		uint32_t SMARTEN();
		bool seimin();
		uint8_t sedn();
		uint8_t semax();
		uint8_t seup();
		uint8_t semin();
		/*
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
		SET_ALIAS(void, hysteresis_decrement, uint8_t, hdec);
		SET_ALIAS(void, hysteresis_low, uint8_t, hend);
		SET_ALIAS(void, hysteresis_start, uint8_t, hstrt);
		SET_ALIAS(void, off_time, uint8_t, toff);
		*/

		uint8_t status_response;

		// Deleted functions
		__attribute__((deprecated("Please provide a sense resistor value")))
		TMC2660Stepper(TMCStepper_n::PinDef pinCS, TMCStepper_n::PinDef pinMOSI, TMCStepper_n::PinDef pinMISO, TMCStepper_n::PinDef pinSCK, int8_t link_index = -1) = delete;

	private:
		DRVCTRL_1_t DRVCTRL_1_register{{.sr=0}};
		DRVCTRL_0_t DRVCTRL_0_register{{.sr=0}};
		TMC2660_n::CHOPCONF_t CHOPCONF_register{{.sr=0}};
		SMARTEN_t SMARTEN_register{{.sr=0}};
		SGCSCONF_t SGCSCONF_register{{.sr=0}};
		DRVCONF_t DRVCONF_register{{.sr=0}};
		READ_RDSEL00_t READ_RDSEL00_register{{.sr=0}};
		READ_RDSEL01_t READ_RDSEL01_register{{.sr=0}};
		READ_RDSEL10_t READ_RDSEL10_register{{.sr=0}};

		const TMCStepper_n::PinDef pinCS;
		const float Rsense;
		static constexpr float default_RS = 0.1;
		float holdMultiplier = 0.5;
		uint32_t spi_speed = 16000000/8; // Default 2MHz
		uint8_t _savedToff = 0;
		SPIClass *TMC_HW_SPI = nullptr;
		SW_SPIClass *TMC_SW_SPI = nullptr;

        void write(uint8_t addressByte, uint32_t config);
        uint32_t read();
        void beginTransaction();
        void endTransaction();
        void transfer(char *buf, const uint8_t count);
};
