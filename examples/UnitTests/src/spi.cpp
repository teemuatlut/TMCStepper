
#include <TMCStepper.h>

#include <iostream>

using namespace TMCStepper_n;
using namespace TMC_HAL;

std::ostream& operator<< (std::ostream &out, const SPIClass &cmdList) {
    auto oldFormat = out.flags(std::ios::right | std::ios::hex | std::ios::showbase);

    out << "[ ";
    for (auto cmd : cmdList.sentCommands) {
        out << std::hex << "{" << (uint16_t)cmd.address << ", " << cmd.data << "} ";
    }
    out << "]";

    out.flags(oldFormat);
    return out;
}

void TMC_SPI::beginTransaction() {
    TMC_HW_SPI->active = true;
}

void TMC_SPI::transfer(uint8_t *buf, const uint8_t count) {
    if(TMC_HW_SPI->active) {

        uint32_t data = *(uint32_t*)(buf+1);

        data = __builtin_bswap32(data);

        TMC_HW_SPI->sentCommands.emplace_back(*buf, data);

        auto reg = TMC_HW_SPI->registerValue;

        *(uint32_t*)(buf+1) = __builtin_bswap32(reg);

        TMC_HW_SPI->transferCalls++;
    }
}

void TMC_SPI::endTransaction() {
    TMC_HW_SPI->active = false;
}

