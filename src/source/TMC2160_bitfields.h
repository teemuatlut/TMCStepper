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

  struct PWMCONF_t {
    constexpr static uint8_t address = 0x70;
    union {
      uint32_t sr;
      struct {
        uint8_t pwm_ofs : 8,
                pwm_grad : 8,
                pwm_freq : 2;
        bool pwm_autoscale : 1,
             pwm_autograd : 1;
        uint8_t freewheel : 2,
                          : 2,
                pwm_reg : 4,
                pwm_lim : 4;
      };
    };
  };

  struct PWM_SCALE_t {
    constexpr static uint8_t address = 0x71;
    union {
      uint32_t sr;
      struct {
        uint8_t pwm_scale_sum : 8,
                              : 8;
        uint16_t pwm_scale_auto : 9;
      };
    };
  };

  struct GLOBAL_SCALER_t {
    constexpr static uint8_t address = 0x0B;
    uint8_t sr;
  };

  struct OFFSET_READ_t {
    constexpr static uint8_t address = 0x0C;
  };

  struct SHORT_CONF_t {
    constexpr static uint8_t address = 0x09;
    union {
      uint32_t sr : 19;
      struct {
        uint8_t s2vs_level  : 4,
                            : 4,
                s2g_level   : 4,
                            : 4,
                shortfilter : 2;
        bool shortdelay : 1;
      };
    };
  };

  struct DRV_CONF_t {
    constexpr static uint8_t address = 0x0A;
    union {
      uint32_t sr : 22;
      struct {
        uint8_t bbmtime : 5,
                        : 3,
                bbmclks : 4,
                        : 4,
                otselect : 2,
                drvstrength : 2,
                filt_isense : 2;
      };
    };
  };
}

#pragma pack(pop)
