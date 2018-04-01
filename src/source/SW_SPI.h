#pragma once

#include <Arduino.h>

class SW_SPIClass {
	public:
		void setPins(uint16_t sw_mosi_pin, uint16_t sw_miso_pin, uint16_t sw_sck_pin);
		void init();
		void begin() {};
		byte transfer(uint8_t ulVal, uint8_t ulBitOrder=MSBFIRST);
		uint16_t transfer16(uint16_t data);
		void endTransaction() {};
	private:
		uint16_t mosi_pin,
				miso_pin,
				sck_pin;
		uint8_t mosi_bm,
				miso_bm,
				sck_bm;
		volatile uint8_t *mosi_register,
						 *miso_register,
						 *sck_register;
};

extern SW_SPIClass TMC_SW_SPI;
