
#if defined(bcm2835)

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../../TMCStepper.h"

using namespace TMC_HAL

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
	bcm2835_gpio_fsel(pin, BCM2835_GPIO_PUD_UP);
	bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP)
}

bool InputPin::read() const {
    return bcm2835_gpio_lev(pin);
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
	bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
}

void OutputPin::set() const {
	bcm2835_gpio_write(pin, 1);
}

void OutputPin::reset() const {
	bcm2835_gpio_write(pin, 0);
}

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
	speed_t myBaud;
	switch(baud)
	{
		case    9600:	myBaud =    B9600; break;
		case   19200:	myBaud =   B19200; break;
		case   38400:	myBaud =   B38400; break;
		case   57600:	myBaud =   B57600; break;
		case  115200:	myBaud =  B115200; break;
		case  230400:	myBaud =  B230400; break;
		case  460800:	myBaud =  B460800; break;
		case  500000:	myBaud =  B500000; break;
		case  576000:	myBaud =  B576000; break;

		// The TMC2209 maxed out around 750kbaud so other enums after 576kbaud is not needed.

		default:
			printf("[ERROR] UART invalid baud: %ld for port: %s\n", baud, port);
			return;
	}

	fd = open(port, flags);
	if (fd == -1) {
		printf("[ERROR] UART open(%s)\n", port);
		return;
	}
	fcntl(fd, F_SETFL, O_RDWR);

	termios options{};

	tcgetattr(fd, &options);

	cfmakeraw( &options );
	cfsetispeed( &options, myBaud );
	cfsetospeed( &options, myBaud );

	// See: https://www.mkssoftware.com/docs/man5/struct_termios.5.asp
	// Use 8 data bit, no parity and 1 stop bit
	// Set bits per byte
	options.c_cflag |= ( CREAD | CLOCAL ) ;   // turn on READ and ignore modem ctrl lines
	// CBAUDEX no need to use extended baud; setting this for some reason shows incorrect timing on the oscilloscope for 9600 but OK for 57600
	// Not setting it seems to be OK on the oscilloscope for both 9600 and 57600.
	options.c_cflag &= ~PARENB;     // no parity
	options.c_cflag &= ~CSTOPB;     // 1 stop bit
	options.c_cflag &= ~CSIZE;      // reset number of bits mask
	options.c_cflag |= CS8;         // 8 data bit
	options.c_cflag &= ~CRTSCTS;   // no flow control

	options.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
	options.c_iflag |= IGNPAR;       // ignore characters with parity errors

	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG) ;    // make raw

	options.c_oflag &= ~OPOST;  // make raw

	// See: http://unixwiz.net/techtips/termios-vmin-vtime.html
	options.c_cc[VMIN]  = 0;
	// Cannot set VTIME to 0 as it creates more problems such as cannot read the driver properly.
    // Also, you do not want to set to 100 because it is a blocking read and timeout in VTIME and can take up to 10 seconds and
    // if retries are implemented in caller then it feels like something is blocking for N retries x VTIME.
	options.c_cc[VTIME] = 10;       // VTIME defined as tenths of a second so 10 is actually 1 seconds

	tcflush(fd, TCIOFLUSH); // flush both tx and rx
	tcsetattr(fd, TCSANOW, &options);

	// Maybe add 10ms delay (belt and braces) to let UART setup correctly
	usleep(1000 * 10);
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
