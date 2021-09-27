#if defined(bcm2835)
#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bcm2835_stream.h"

uint32_t millis()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return (uint32_t) ( now.tv_usec / 1000 );
}

Stream::Stream(const char* port)
{
	Stream::port = port;
}

void Stream::begin(unsigned long baud, int flags)
{
	struct termios options;

	fd = open(port, flags);
	if (fd == -1) {
		printf("[ERROR] UART open(%s)\n", port);
		return;
	}
	fcntl(fd, F_SETFL, O_RDWR);


	speed_t myBaud;
	switch ( baud )
	{
		case      50:	myBaud =      B50; break;
		case      75:	myBaud =      B75; break;
		case     110:	myBaud =     B110; break;
		case     134:	myBaud =     B134; break;
		case     150:	myBaud =     B150; break;
		case     200:	myBaud =     B200; break;
		case     300:	myBaud =     B300; break;
		case     600:	myBaud =     B600; break;
		case    1200:	myBaud =    B1200; break;
		case    1800:	myBaud =    B1800; break;
		case    2400:	myBaud =    B2400; break;
		case    4800:	myBaud =    B4800; break;
		case    9600:	myBaud =    B9600; break;
		case   19200:	myBaud =   B19200; break;
		case   38400:	myBaud =   B38400; break;
		case   57600:	myBaud =   B57600; break;
		case  115200:	myBaud =  B115200; break;
		case  230400:	myBaud =  B230400; break;
		case  460800:	myBaud =  B460800; break;
		case  500000:	myBaud =  B500000; break;
		case  576000:	myBaud =  B576000; break;
		case  921600:	myBaud =  B921600; break;
		case 1000000:	myBaud = B1000000; break;
		case 1152000:	myBaud = B1152000; break;
		case 1500000:	myBaud = B1500000; break;
		case 2000000:	myBaud = B2000000; break;
		case 2500000:	myBaud = B2500000; break;
		case 3000000:	myBaud = B3000000; break;
		case 3500000:	myBaud = B3500000; break;
		case 4000000:	myBaud = B4000000; break;

		default:
			printf("[ERROR] UART invalid baud: %ld for port: %s\n", baud, port);
			return;
	}


	struct termios options;
	memset( &options, 0, sizeof(options) );

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
	options.c_cc[VTIME] = 100;       // VTIME defined as tenths of a second so 100 is actually 10 seconds

	tcflush(fd, TCIOFLUSH); // flush both tx and rx
	tcsetattr(fd, TCSANOW, &options);

	// Maybe add 10ms delay (belt and braces) to let UART setup correctly
	const int DELAY_MS_10 = 10;
	usleep( 1000 * DELAY_MS_10 );
}

void Stream::end()
{
	::close(fd);
}

int Stream::available()
{
	int result;
	if (ioctl(fd, FIONREAD, &result) == -1)
		return -1;
	return result;
}

uint8_t Stream::write(const uint8_t data)
{
    return (uint8_t)::write(fd, &data, 1);
}

uint8_t Stream::read()
{
	uint8_t data = -1;
	if (::read(fd, &data, 1) == -1)
		return -1;
	return data;
}

Stream Serial("/dev/serial0");
Stream Serial1("/dev/serial1");

#endif
