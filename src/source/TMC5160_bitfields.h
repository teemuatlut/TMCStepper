#pragma once

struct reg_SHORT_CONF {
  uint8_t address;
  union {
    struct {
      uint8_t s2vs_level  : 4,
                          : 4,
              s2g_level   : 4,
                          : 4,
              shortfilter : 2;
      bool shortdelay : 1;
    } opt;
    uint32_t sr : 19;
  } cfg;
};

struct reg_DRV_CONF {
  uint8_t address;
  union {
    struct {
      uint8_t bbmtime : 5,
                      : 3,
              bbmclks : 4,
                      : 4,
              otselect : 2,
              drvstrength : 2,
              filt_isense : 2;
    } opt;
    uint32_t sr : 22;
  } cfg;
};

struct reg_GLOBAL_SCALER {
  uint8_t address;
  uint8_t sr;
};

struct reg_OFFSET_READ {
  uint8_t address;
  uint16_t sr;
};

struct reg_ENC_DEVIATION {
  uint8_t address;
  uint32_t sr : 20;
};

struct reg_PWM_SCALE {
  uint8_t address;
  union {
    struct {
      uint8_t pwm_scale_sum : 8,
                            : 8;
      uint16_t pwm_scale_auto : 9;
    } opt;
    uint32_t sr : 25;
  } cfg;
};

struct reg_PWM_AUTO {
  uint8_t address;
  union {
    struct {
      uint8_t pwm_ofs_auto : 8,
                           : 8,
              pwm_grad_auto : 8;
    } opt;
    uint32_t sr : 24;
  } cfg;
};

struct reg_TMC5160PWMCONF {
  uint8_t address;
  union {
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
    } opt;
    uint32_t sr;
  } cfg;
};
