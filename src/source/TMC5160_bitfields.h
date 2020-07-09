#pragma once
#pragma pack(push, 1)

namespace TMC5160_n {
  struct ENC_DEVIATION_t {
    constexpr static uint8_t address = 0x3D;
    uint32_t sr : 20;
  };

  struct PWM_AUTO_t {
    constexpr static uint8_t address = 0x72;
    union {
      uint32_t sr;
      struct {
        uint8_t pwm_ofs_auto : 8,
                             : 8,
                pwm_grad_auto : 8;
      };
    };
  };
}

#pragma pack(pop)
