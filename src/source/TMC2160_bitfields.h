#pragma once
#pragma pack(push, 1)

namespace TMC2160_n {
  struct IOIN_t {
    constexpr static uint8_t address = 0x04;
    union {
      uint32_t sr;
      struct {
        bool  refl_step : 1,
              refr_dir : 1,
              encb_dcen_cfg4 : 1,
              enca_dcin_cfg5 : 1,
              drv_enn : 1,
              dco_cfg6 : 1,
              : 2;
        uint16_t : 16;
        uint8_t version : 8;
      };
    };
  };
}

#pragma pack(pop)
