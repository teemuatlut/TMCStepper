#pragma once

#include <stdint.h>
#include "TMC_HAL.h"

class SW_SPIClass {
	public:
		SW_SPIClass(const TMC_HAL::PinDef mosi, const TMC_HAL::PinDef miso, const TMC_HAL::PinDef sck);
		void init();
		void begin() {};
		void transfer(uint8_t *buf, uint8_t count);
		void endTransaction() {};
	private:
		const TMC_HAL::PinDef mosi_pin, sck_pin, miso_pin;
};

namespace TMCStepper_n {

struct TMC_SPI {
protected:

	// Allow register interfaces to call read and write methods
	template<class> friend class TMCStepper;
	template<class> friend class TMC2130_n::GCONF_i;
	template<class> friend class TMC2130_n::GSTAT_i;
	template<class> friend class TMC2130_n::IOIN_i;
	template<class> friend class TMC2130_n::IHOLD_IRUN_i;
	template<class> friend class TMC2130_n::TPOWERDOWN_i;
	template<class> friend class TMC2130_n::TSTEP_i;
	template<class> friend class TMC2130_n::TPWMTHRS_i;
	template<class> friend class TMC2130_n::TCOOLTHRS_i;
	template<class> friend class TMC2130_n::THIGH_i;
	template<class> friend class TMC2130_n::XDIRECT_i;
	template<class> friend class TMC2130_n::VDCMIN_i;
	template<class> friend class TMC2130_n::MSLUT0_i;
	template<class> friend class TMC2130_n::MSLUT1_i;
	template<class> friend class TMC2130_n::MSLUT2_i;
	template<class> friend class TMC2130_n::MSLUT3_i;
	template<class> friend class TMC2130_n::MSLUT4_i;
	template<class> friend class TMC2130_n::MSLUT5_i;
	template<class> friend class TMC2130_n::MSLUT6_i;
	template<class> friend class TMC2130_n::MSLUT7_i;
	template<class> friend class TMC2130_n::MSLUTSEL_i;
	template<class> friend class TMC2130_n::MSLUTSTART_i;
	template<class> friend class TMC2130_n::MSCNT_i;
	template<class> friend class TMC2130_n::MSCURACT_i;
	template<class> friend class TMC2130_n::CHOPCONF_i;
	template<class> friend class TMC2130_n::COOLCONF_i;
	template<class> friend class TMC2130_n::DCCTRL_i;
	template<class> friend class TMC2130_n::DRV_STATUS_i;
	template<class> friend class TMC2130_n::PWMCONF_i;
	template<class> friend class TMC2130_n::PWM_SCALE_i;
	template<class> friend class TMC2130_n::ENCM_CTRL_i;
	template<class> friend class TMC2130_n::LOST_STEPS_i;

	template<class> friend class TMC2160_n::CHOPCONF_i;
	template<class> friend class TMC2160_n::IOIN_i;
	template<class> friend class TMC2160_n::GLOBAL_SCALER_i;
	template<class> friend class TMC2160_n::OFFSET_READ_i;
	template<class> friend class TMC2160_n::PWM_SCALE_i;
	template<class> friend class TMC2160_n::SHORT_CONF_i;
	template<class> friend class TMC2160_n::DRV_CONF_i;
	template<class> friend class TMC2160_n::PWMCONF_i;

	template<class> friend class TMC5130_n::GCONF_i;
	template<class> friend class TMC5130_n::IOIN_i;
	template<class> friend class TMC5130_n::OUTPUT_i;
	template<class> friend class TMC5130_n::X_COMPARE_i;
	template<class> friend class TMC5130_n::RAMPMODE_i;
	template<class> friend class TMC5130_n::XACTUAL_i;
	template<class> friend class TMC5130_n::VACTUAL_i;
	template<class> friend class TMC5130_n::VSTART_i;
	template<class> friend class TMC5130_n::A1_i;
	template<class> friend class TMC5130_n::V1_i;
	template<class> friend class TMC5130_n::AMAX_i;
	template<class> friend class TMC5130_n::VMAX_i;
	template<class> friend class TMC5130_n::DMAX_i;
	template<class> friend class TMC5130_n::D1_i;
	template<class> friend class TMC5130_n::VSTOP_i;
	template<class> friend class TMC5130_n::TZEROWAIT_i;
	template<class> friend class TMC5130_n::XTARGET_i;
	template<class> friend class TMC5130_n::SW_MODE_i;
	template<class> friend class TMC5130_n::RAMP_STAT_i;
	template<class> friend class TMC5130_n::XLATCH_i;
	template<class> friend class TMC5130_n::ENCMODE_i;
	template<class> friend class TMC5130_n::X_ENC_i;
	template<class> friend class TMC5130_n::ENC_CONST_i;
	template<class> friend class TMC5130_n::ENC_STATUS_i;
	template<class> friend class TMC5130_n::ENC_LATCH_i;

	template<class> friend class TMC5160_n::GCONF_i;
	template<class> friend class TMC5160_n::SLAVECONF_i;
	template<class> friend class TMC5160_n::IOIN_i;
	template<class> friend class TMC5160_n::ENC_DEVIATION_i;
	template<class> friend class TMC5160_n::DRV_STATUS_i;

	template<class> friend class TMC2208_n::SLAVECONF_i; // For TMC5130
	template<class> friend class TMC2208_n::OTP_PROG_i; // For TMC5160
	template<class> friend class TMC2208_n::FACTORY_CONF_i;
	template<class> friend class TMC2208_n::PWM_AUTO_i; // Used by TMC5160

	TMC_SPI(SPIClass &spi, TMC_HAL::PinDef &cs, int8_t link);
	TMC_SPI(SW_SPIClass &spi, TMC_HAL::PinDef &cs, int8_t link);

	// |         8b        |       32b     |
	// | Address or Status | Register data |
	// |           40b data buffer         |
  #pragma pack(push, 1)
	union TransferData {
	    struct {
	        union {
	            uint8_t address;
	            uint8_t status;
	        };
	        uint32_t data;
	    };
	    uint8_t buffer[5] = {0};
	};
  #pragma pack(pop)

	void setSPISpeed(uint32_t speed);
	void switchCSpin(bool state);

	void beginTransaction();
	void endTransaction();
	void transfer(const uint8_t count);
	void transfer(uint8_t *buf, const uint8_t count);
	void write(uint8_t addressByte, uint32_t config);
	uint32_t read(uint8_t addressByte);

	uint8_t status_response;

	static constexpr uint8_t TMC_READ = 0x00,
													TMC_WRITE = 0x80;

	static uint32_t spi_speed; // Default 2MHz
	const TMC_HAL::PinDef pinCS;
	SPIClass *TMC_HW_SPI = nullptr;
	SW_SPIClass *TMC_SW_SPI = nullptr;

	int8_t link_index;
	static int8_t chain_length;
};

};

namespace TMC2660_n {

class TMC_SPI : public ::TMCStepper_n::TMC_SPI {
	public:
	using ::TMCStepper_n::TMC_SPI::TMC_SPI;

	// |    3b   |       17b     |
	// | Address | Register data |
	// |     24b data buffer     |
	union TransferData {
		uint32_t data : 24;
		uint8_t buffer[3];
	};

	void write(uint8_t addressByte, uint32_t config);
	uint32_t read(const uint32_t dummy);
};

}
