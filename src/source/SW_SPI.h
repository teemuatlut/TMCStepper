#pragma once

#if defined(bcm2835)
#include "source/rpi_bcm2835.h"
#include "source/bcm2835_spi.h"
#include "source/bcm2835_stream.h"
#endif

#include <stdint.h>
#include "TMC_HAL.h"

using namespace TMCStepper_n;

class SW_SPIClass {
	public:
		SW_SPIClass(PinDef mosi, PinDef miso, PinDef sck);
		void init();
		void begin() {};
		uint8_t transfer(uint8_t ulVal);
		void transfer(char *buf, uint8_t count);
		void endTransaction() {};
	private:
		const PinDef mosi_pin, sck_pin, miso_pin;
};
