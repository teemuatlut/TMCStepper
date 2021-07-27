
#include "../TMCStepper.h"

using namespace TMCStepper_n;
using namespace TMC_HAL;

TMC_UART::TMC_UART(HardwareSerial * SerialPort, uint8_t addr, SSwitch *sw) :
	HWSerial(SerialPort),
	sswitch(sw),
	slaveAddress(addr)
	{}

#if SW_CAPABLE_PLATFORM
	TMC_UART::TMC_UART(SoftwareSerial *ser, uint8_t addr) :
		SWSerial(ser),
		slaveAddress(addr)
		{}
#endif

uint8_t TMC_UART::calcCRC(uint8_t datagram[], uint8_t len) {
	uint8_t crc = 0;
	for (uint8_t i = 0; i < (len-1); i++) {
		uint8_t currentByte = datagram[i];
		for (uint8_t j = 0; j < 8; j++) {
			if ((crc >> 7) ^ (currentByte & 0x01)) {
				crc = (crc << 1) ^ 0x07;
			} else {
				crc = (crc << 1);
			}
			crc &= 0xff;
			currentByte = currentByte >> 1;
		}
	}
	return crc;
}

void TMC_UART::WaitForInhibitTime() {
	while(getTime() - lastWriteTime < WriteInhibitTime);
}

TMC_WEAK_FUNCTION
void TMC_UART::write(uint8_t addr, uint32_t regVal) {
	WaitForInhibitTime();

    WriteDatagram datagram;
    datagram.driverAddress = slaveAddress;
    datagram.registerAddress = addr | TMC_WRITE;
    datagram.data = __builtin_bswap32(regVal);

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);

	preWriteCommunication();
	serial_write((uint8_t*)&datagram, datagram.length);
	postWriteCommunication();

	lastWriteTime = getTime();
}

TMC_UART::ReadResponse TMC_UART::sendReadRequest(ReadRequest &datagram) {
	WaitForInhibitTime();

	const uint32_t startTime = getTime();
	auto Timeout = [&] {
		return this->getTime() - startTime < this->abort_window;
	};

	auto byteCount = serial_write((uint8_t*)&datagram, datagram.length);

	while (byteCount != datagram.length && Timeout()) {
		byteCount = serial_write((uint8_t*)&datagram, datagram.length);
	}

    // scan for the rx frame and read it
    const uint32_t sync_target = static_cast<uint32_t>(datagram.sync)<<16 | 0xFF00 | datagram.registerAddress;
    uint32_t sync = 0;

    ReadResponse response{};

    do {
        if (available() > 0) {
		    sync <<= 8;
		    serial_read((uint8_t*)&sync, 1);
        }
    } while (((sync&0xFFFFFF) != sync_target) && Timeout());

    while (Timeout()) {
		if(available() >= 5) {
	        response.driverAddress = 0xFF;
	    	response.registerAddress = static_cast<uint8_t>(sync);

	    	serial_read((uint8_t*)&response.data, 5);
	    	break;
		}
	};

	lastWriteTime = getTime();

    return response;
}

uint32_t TMC_UART::read(uint8_t addr) {
    ReadResponse response;
    ReadRequest datagram;
    datagram.driverAddress = slaveAddress;
    datagram.registerAddress = addr | TMC_READ;

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);
    CRCerror = true;

    for (uint_fast8_t i = 0; i < max_retries; i++) {
        preReadCommunication();
        response = sendReadRequest(datagram);
        postReadCommunication();

        uint8_t crc = calcCRC((uint8_t*)&response, response.length);

        if (crc == response.crc && crc != 0) {
            CRCerror = false;
            break;
        }

        response.data = 0;

		const uint32_t startTime = getTime();
		while(getTime() - startTime < 20);
    }

    return __builtin_bswap32(response.data);
}

SSwitch::SSwitch(const PinDef pin1, const PinDef pin2) :
	p1(pin1),
	p2(pin2)
	{
	OutputPin(p1).setMode();
	OutputPin(p2).setMode();
	}

void SSwitch::active(const uint8_t addr) {
  OutputPin(p1).write(addr & 0b01 ? HIGH : LOW);
  OutputPin(p2).write(addr & 0b10 ? HIGH : LOW);
}
