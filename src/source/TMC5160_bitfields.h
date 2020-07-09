#pragma once
#pragma pack(push, 1)

namespace TMC5160_n {
  struct ENC_DEVIATION_t {
    constexpr static uint8_t address = 0x3D;
    uint32_t sr : 20;
  };


}

#pragma pack(pop)
