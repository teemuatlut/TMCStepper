
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

void TMC_SPI::initPeripheral() {}

void TMC_SPI::beginTransaction() {
    TMC_HW_SPI->active = true;
}

void TMC_SPI::transfer(void *dataBuffer, const uint8_t count) {
    if(TMC_HW_SPI->active) {
        uint8_t *buf = static_cast<uint8_t*>(dataBuffer);
        uint32_t data = *(uint32_t*)(buf+1);

        data = __builtin_bswap32(data);

        TMC_HW_SPI->sentCommands.emplace_back(*buf, data);

        const auto reg = [&] {
            if (TMC_HW_SPI->responses.size() > 0) {
                auto val = TMC_HW_SPI->responses.front();
                TMC_HW_SPI->responses.pop_front();
                return val;
            }
            else {
                return 0u;
            }
        }();

        *(uint32_t*)(buf+1) = __builtin_bswap32(reg);

        TMC_HW_SPI->transferCalls++;
    }
}

void TMC_SPI::endTransaction() {
    TMC_HW_SPI->active = false;
}

