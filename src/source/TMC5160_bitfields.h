#pragma once

struct SHORT_CONF_t {
  uint8_t address;
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
  uint8_t address;
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

struct GLOBAL_SCALER_t {
  uint8_t address;
  uint8_t sr;
};

struct OFFSET_READ_t {
  uint8_t address;
  uint16_t sr;
};

struct ENC_DEVIATION_t {
  uint8_t address;
  uint32_t sr : 20;
};

struct PWM_SCALE_t {
  uint8_t address;
  union {
    uint32_t sr : 25;
    struct {
      uint8_t pwm_scale_sum : 8,
                            : 8;
      uint16_t pwm_scale_auto : 9;
    };
  };
};

struct PWM_AUTO_t {
  uint8_t address;
  union {
    uint32_t sr : 24;
    struct {
      uint8_t pwm_ofs_auto : 8,
                           : 8,
              pwm_grad_auto : 8;
    };
  };
};

namespace TMC5160 {
  struct PWMCONF_t {
    uint8_t address;
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
}
