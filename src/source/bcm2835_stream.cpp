#include "bcm2835_stream.h"

uint32_t millis()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (uint32_t)now.tv_usec;
}

int Stream::available()
{
    return 0;
}

uint8_t Stream::write(const uint8_t data)
{
    return uint8_t();
}

uint8_t Stream::read()
{
    return uint8_t();
}
