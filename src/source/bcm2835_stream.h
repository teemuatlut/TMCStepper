#pragma once
#if defined(bcm2835)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <bcm2835.h>

uint32_t millis();

class Stream
{
public:
	int available();
	uint8_t write(const uint8_t data);
	uint8_t read();
};

#endif