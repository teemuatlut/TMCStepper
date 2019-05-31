#pragma once
#pragma pack(push, 1)

namespace TMC2209_n {
  struct TCOOLTHRS_t {
    constexpr static uint8_t address = 0x14;
    uint32_t sr : 20;
  };
}

struct SGTHRS_t {
  constexpr static uint8_t address = 0x40;
  uint8_t sr : 8;
};

struct SG_RESULT_t {
  constexpr static uint8_t address = 0x41;
  uint16_t sr : 10;
};

namespace TMC2209_n {
  struct COOLCONF_t {
    constexpr static uint8_t address = 0x42;
    union {
      uint16_t sr : 16;
      struct {
        bool  seimin : 1,
              sedn1 : 1,
              sedn0 : 1,
                    : 1,
              semax3 : 1,
              semax2 : 1,
              semax1 : 1,
              semax0 : 1,
                    : 1,
              seup1 : 1,
              seup0 : 1,
                    : 1,
              semin3 : 1,
              semin2 : 1,
              semin1 : 1,
              semin0 : 1;
      };
    };
  };
};
#pragma pack(pop)
