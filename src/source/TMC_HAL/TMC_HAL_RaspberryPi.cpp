
#if defined(__linux__)

#include <termios.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../../TMCStepper.h"

using namespace std;
using namespace TMCStepper_n;
using namespace TMC_HAL;

namespace TMC_HAL {
    void abort(std::string_view str, const int ret);
}

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
	pin.request({"TMCStepper", ::gpiod::line_request::DIRECTION_INPUT}, 0);
}

bool InputPin::read() const {
	return pin.get_value();
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
	pin.request({"TMCStepper", ::gpiod::line_request::DIRECTION_OUTPUT}, 0);
}

void OutputPin::set() const {
	pin.set_value(1);
}

void OutputPin::reset() const {
	pin.set_value(0);
}

TMC_HAL::HW_port::HW_port(std::string_view port) {
	fd = open(port.begin(), O_RDWR);

	if (fd < 0)
		TMC_HAL::abort(string("Failed to open device: ").append(port), fd);
}

__attribute__((weak))
void TMC_SPI::initPeripheral() {
	if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();
}

void TMC_SPI::beginTransaction() {
	if(TMC_HW_SPI != nullptr) {
		const int fd = TMC_HW_SPI->fd;
        int ret = -1;

        uint32_t mode = SPI_MODE_3 | SPI_NO_CS;
        uint32_t bits = 8;

        ret = ioctl(fd, SPI_IOC_WR_MODE32, &mode);
        if (ret < 0) abort("Can't set spi mode ", ret);

        ret = ioctl(fd, SPI_IOC_RD_MODE32, &mode);
        if (ret < 0) abort("Can't get spi mode", ret);

        ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
        if (ret < 0) abort("can't set bits per word", ret);

        ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
        if (ret < 0) abort("can't get bits per word", ret);

        ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed);
        if (ret < 0) abort("can't set max speed hz", ret);

        ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &spi_speed);
        if (ret < 0) abort("can't get max speed hz", ret);

		if (ret != 0) exit(1);
	}
}

__attribute__((weak))
void TMC_SPI::transfer(void *buf, const uint8_t count) {
    if(TMC_HW_SPI != nullptr) {

        spi_ioc_transfer tr = {
            .tx_buf = (unsigned long)buf,
            .rx_buf = (unsigned long)buf,
            .len = 5,
            .speed_hz = spi_speed,
            .delay_usecs = 1,
            .bits_per_word = 8,
            .cs_change = 0,
            .tx_nbits = 0,
            .rx_nbits = 0,
            .word_delay_usecs = 0
        };

        const int ret = ioctl(TMC_HW_SPI->fd, SPI_IOC_MESSAGE(1), &tr);
        if (ret < 1) abort("can't send spi message", ret);

    }
    else if(TMC_SW_SPI != nullptr) {
        TMC_SW_SPI->transfer((uint8_t*)buf, count);
    }
}

__attribute__((weak))
void TMC_SPI::endTransaction() {}

__attribute__((weak))
size_t TMC_UART::getTime() const {
	timeval now;
	gettimeofday(&now, NULL);
	return (uint32_t) ( now.tv_usec / 1000 );
}

__attribute__((weak))
void TMC_UART::begin(uint32_t baud)
{
	if (HWSerial == nullptr) return;

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

	const int fd = HWSerial->fd;
	const int flags = O_RDWR | O_NOCTTY | O_NDELAY;

	fd = open(port, flags);
	if (fd == -1) {
		printf("[ERROR] UART open(%s)\n", port);
		return;
	}
	fcntl(fd, F_SETFL, O_RDWR);

	termios options{};
	int ret = -1;

	ret = tcgetattr(fd, &options);
	if (ret < 0) abort("Failed to get UART attributes ", ret);

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

	ret = tcflush(fd, TCIOFLUSH); // flush both tx and rx
	if (ret < 0) abort("Failed to flush UART ", ret);

	ret = tcsetattr(fd, TCSANOW, &options);
	if (ret < 0) abort("Failed to set UART attributes ", ret);

	// Maybe add 10ms delay (belt and braces) to let UART setup correctly
	usleep(1000 * 10);
}

int TMC_UART::available() {
	int result;
	if (ioctl(HWSerial->fd, FIONREAD, &result) == -1)
		return -1;
	return result;
}

__attribute__((weak))
void TMC_UART::preWriteCommunication() {}

__attribute__((weak))
void TMC_UART::preReadCommunication() {}

__attribute__((weak))
size_t TMC_UART::serial_write(const void *data, int8_t length) {
    if (HWSerial != nullptr) {
        return ::write(HWSerial->fd, (const uint8_t*)data, length);
    }
    return 0;
}

__attribute__((weak))
size_t TMC_UART::serial_read(void *data, int8_t length) {
    if (HWSerial != nullptr && available() > 0) {
        return ::read(HWSerial->fd, (uint8_t*)data, length);
    }
    return 0;
}

__attribute__((weak))
void TMC_UART::postWriteCommunication() {}

__attribute__((weak))
void TMC_UART::postReadCommunication() {}

void TMC_HAL::abort(std::string_view str, const int ret) {
    cerr << "abort: " << str << " (" << ret << ')' << endl;
    cerr << "errno=" << errno << endl;
    cerr << strerror(errno) << endl;
}

#endif
