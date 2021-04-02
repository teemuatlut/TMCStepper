
#include <TMCStepper.h>

using namespace TMCStepper_n;
using namespace TMC_HAL;

InputPin::InputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void InputPin::setMode() const {
    //pinMode(pin, INPUT);
}

bool InputPin::read() const {
    return false; //digitalRead(pin);
}

OutputPin::OutputPin(const PinDef _pin) :
    PinCache(_pin)
    {}

void OutputPin::setMode() const {
    //pinMode(pin, OUTPUT);
}

void OutputPin::set() const {
    //digitalWrite(pin, HIGH);
}

void OutputPin::reset() const {
    //digitalWrite(pin, LOW);
}
