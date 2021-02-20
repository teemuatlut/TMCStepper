
#if defined(bcm2835)

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../../TMCStepper.h"

void SPIClass::beginTransaction(SPISettings settings)
{
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(settings.order);
	bcm2835_spi_setDataMode(settings.mode);
	bcm2835_spi_set_speed_hz(settings.speed);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS_NONE);
}

uint32_t millis()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (uint32_t) ( now.tv_usec / 1000 );
}

void HardwareSerial::begin(unsigned long baud, int flags)
{
	struct termios options;

	fd = open(port, flags);
	if (fd == -1) {
		printf("[ERROR] UART open(%s)\n", port);
		return;
	}
	fcntl(fd, F_SETFL, O_RDWR);

	tcgetattr(fd, &options);
	options.c_cflag = CS8 | CLOCAL | CREAD | CBAUDEX;
	options.c_cflag &= ~CBAUD;
	options.c_iflag = IGNPAR;
	options.c_oflag = baud;
	options.c_lflag = baud;
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd, TCSANOW, &options);
}

int HardwareSerial::available()
{
	int result;
	if (ioctl(fd, FIONREAD, &result) == -1)
		return -1;
	return result;
}

uint8_t HardwareSerial::write(const uint8_t data)
{
    return (uint8_t)::write(fd, &data, 1);
}

uint8_t HardwareSerial::read()
{
	uint8_t data = -1;
	if (::read(fd, &data, 1) == -1)
		return -1;
	return data;
}

HardwareSerial Serial("/dev/serial0");
HardwareSerial Serial1("/dev/serial1");

#endif
