#include "TMCStepper.h"
#include "SERIAL_SWITCH.h"

using namespace TMCStepper_n;
using namespace TMC2208_n;

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

// Protected
// addr needed for TMC2209
TMC2208Stepper::TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr) :
	TMC_UART(SerialPort, addr),
	TMCStepper(RS)
	{
		HWSerial = SerialPort;
		defaults();
	}

TMC2208Stepper::TMC2208Stepper(HardwareSerial * SerialPort, float RS, uint8_t addr, PinDef mul_pin1, PinDef mul_pin2) :
	TMC2208Stepper(SerialPort, RS)
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

	// Protected
	// addr needed for TMC2209
	TMC2208Stepper::TMC2208Stepper(PinDef SW_RX_pin, PinDef SW_TX_pin, float RS, uint8_t addr) :
		TMC_UART(SW_RX_pin, SW_TX_pin, addr),
		TMCStepper(RS)
		{
			defaults();
		}

	void TMC2208Stepper::beginSerial(uint32_t baudrate) {
		if (SWSerial != nullptr)
		{
			SWSerial->begin(baudrate);
			SWSerial->end();
		}
		#if defined(ARDUINO_ARCH_AVR)
			if (RXTX_pin > 0) {
				digitalWrite(RXTX_pin, HIGH);
				pinMode(RXTX_pin, OUTPUT);
			}
		#endif
	}
#endif

void TMC2208Stepper::begin() {
	#if SW_CAPABLE_PLATFORM
		beginSerial(115200);
	#endif
	pdn_disable(true);
	mstep_reg_select(true);

}

void TMC2208Stepper::defaults() {
	GCONF_t gconf{0};
	gconf.i_scale_analog = 1;
	gconf.internal_rsense = 0; // OTP
	gconf.en_spreadcycle = 0; // OTP
	gconf.multistep_filt = 1; // OTP
	GCONF(gconf.sr);

	IHOLD_IRUN_i::r.iholddelay = 1; // OTP
	TPOWERDOWN_i::r.sr = 20;
	CHOPCONF(0x10000053);
	PWMCONF(0xC10D0024);
  //MSLUT0_register.sr = ???;
  //MSLUT1_register.sr = ???;
  //MSLUT2_register.sr = ???;
  //MSLUT3_register.sr = ???;
  //MSLUT4_register.sr = ???;
  //MSLUT5_register.sr = ???;
  //MSLUT6_register.sr = ???;
  //MSLUT7_register.sr = ???;
  //MSLUTSTART_register.start_sin90 = 247;
}

void TMC2208Stepper::push() {
	IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
	SLAVECONF(SLAVECONF_i::r.sr);
	TPOWERDOWN(TPOWERDOWN_i::r.sr);
	TPWMTHRS(TPWMTHRS_i::r.sr);
	VACTUAL(VACTUAL_i::r.sr);
}

bool TMC2208Stepper::isEnabled() { return !enn() && toff(); }

uint8_t TMC_UART::calcCRC(uint8_t datagram[], uint8_t len) {
	uint8_t crc = 0;
	for (uint8_t i = 0; i < len; i++) {
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
    datagram.data = regVal;

    datagram.crc = calcCRC((uint8_t*)&datagram, datagram.length);

	preWriteCommunication();
	serial_write((uint8_t*)&datagram, datagram.length);
	postWriteCommunication();

	delay(replyDelay);
}

TMC_UART::ReadResponse TMC_UART::sendReadRequest(ReadRequest &datagram) {
    serial_write((uint8_t*)&datagram, datagram.length);

    //delay(this->replyDelay);
    const uint32_t timeout = this->getTime() + this->abort_window;

    // scan for the rx frame and read it
    const uint32_t sync_target = static_cast<uint32_t>(datagram.sync)<<16 | 0xFF00 | datagram.registerAddress;
    uint32_t sync = 0;

    do {
        sync <<= 8;
        serial_read((uint8_t*)&sync, 1);

        if (this->getTime() > timeout) {
            return ReadResponse{};
        }
    } while (sync != sync_target);

    ReadResponse response;
    response.driverAddress = 0xFF;
    response.registerAddress = static_cast<uint8_t>(sync);

    serial_read((uint8_t*)&response.data, 5);

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

        if (crc == response.crc || crc != 0) {
            CRCerror = false;
            break;
        }

        response.data = 0;
    }

    return response.data;
}
