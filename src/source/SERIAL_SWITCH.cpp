#include "SERIAL_SWITCH.h"

using namespace TMCStepper_n;

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
