
#include "TMCStepper.h"

using namespace TMCStepper_n;

TMC_UART::TMC_UART(HardwareSerial * SerialPort, uint8_t addr = TMC2208_SLAVE_ADDR) :
	slaveAddress(addr)
	{
		HWSerial = SerialPort;
	}

TMC_UART::TMC_UART(HardwareSerial * SerialPort, uint8_t addr, PinDef mul_pin1, PinDef mul_pin2) :
	TMC_UART(SerialPort)
	{
		SSwitch *SMulObj = new SSwitch(mul_pin1, mul_pin2, addr);
		sswitch = SMulObj;
	}

#if SW_CAPABLE_PLATFORM
	TMC_UART::TMC_UART(PinDef SW_RX_pin, PinDef SW_TX_pin, uint8_t addr) :
		RXTX_pin(SW_RX_pin == SW_TX_pin ? SW_RX_pin : 0),
		slaveAddress(addr)
		{
			SoftwareSerial *SWSerialObj = new SoftwareSerial(SW_RX_pin, SW_TX_pin);
			SWSerial = SWSerialObj;
		}
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

__attribute__((weak))
void TMC_UART::write(uint8_t addr, uint32_t regVal) {
    WriteDatagram datagram;
    datagram.driverAddress = slaveAddress;
    datagram.registerAddress = addr | TMC_WRITE;
    datagram.data = __builtin_bswap32(regVal);

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);

	preWriteCommunication();
	serial_write((uint8_t*)&datagram, datagram.length);
	postWriteCommunication();

	delay(replyDelay);
}

TMC_UART::ReadResponse TMC_UART::sendReadRequest(ReadRequest &datagram) {
    serial_write((uint8_t*)&datagram, datagram.length);
    const uint32_t timeout = this->getTime() + this->abort_window;

    // scan for the rx frame and read it
    const uint32_t sync_target = static_cast<uint32_t>(datagram.sync)<<16 | 0xFF00 | datagram.registerAddress;
    uint32_t sync = 0;

    ReadResponse response{};

    do {
        if (available() > 0) {
		    sync <<= 8;
		    serial_read((uint8_t*)&sync, 1);
        }
    } while (((sync&0xFFFFFF) != sync_target) && (this->getTime() < timeout));

    while (this->getTime() < timeout) {
		if(available() > 0) {
	        response.driverAddress = 0xFF;
	    	response.registerAddress = static_cast<uint8_t>(sync);

	    	serial_read((uint8_t*)&response.data, 5);
	    	break;
		}
	};

    return response;
}

uint32_t TMC_UART::read(uint8_t addr) {
    ReadResponse response;
    ReadRequest datagram;
    datagram.driverAddress = slaveAddress;
    datagram.registerAddress = addr | TMC_READ;

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);
    CRCerror = true;

    for (uint8_t i = 0; i < max_retries; i++) {
        preReadCommunication();
        response = sendReadRequest(datagram);
        postReadCommunication();

        uint8_t crc = calcCRC((uint8_t*)&response, response.length);

        if (crc == response.crc && crc != 0) {
            CRCerror = false;
            break;
        }

        response.data = 0;
    }

	delay(replyDelay);

    return __builtin_bswap32(response.data);
}

SSwitch::SSwitch(const PinDef pin1, const PinDef pin2, const uint8_t address) :
  p1(pin1),
  p2(pin2),
  addr(address)
	{
		OutputPin(p1).mode(OUTPUT);		
    	OutputPin(p2).mode(OUTPUT);
	}

void SSwitch::active() {
  OutputPin(p1).write(addr & 0b01 ? HIGH : LOW);
  OutputPin(p2).write(addr & 0b10 ? HIGH : LOW);
}
