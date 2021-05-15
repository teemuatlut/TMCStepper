#pragma once

/*
****************************************************
DUMMY IMPLEMENTATION
****************************************************
DOES NOT ACTUALLY DO ANYTHING
****************************************************
*/

#if defined(ESP_PLATFORM)

#include <cstdint>

#define MSBFIRST 0
#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

class SPIClass;

struct SPISettings
{
	friend class SPIClass;
	SPISettings(uint32_t s, uint32_t o, uint32_t m) {
		speed = s;
		order = o;
		mode = m;
	}

	uint32_t speed;
	uint32_t order;
	uint32_t mode;
};

class SPIClass
{
public:
	void beginTransaction(SPISettings settings) {}
	void endTransaction() {}
	uint8_t transfer(uint8_t) {
		return 0;
	}
};

extern SPIClass SPI;
#endif