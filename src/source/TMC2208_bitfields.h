#pragma once

struct reg_GCONF_2208 {
  uint8_t address;
  union {
    struct {
      bool  i_scale_analog : 1,
            internal_rsense : 1,
            en_spreadcycle : 1,
            shaft : 1,
            index_otpw : 1,
            index_step : 1,
            pdn_disable : 1,
            mstep_reg_select : 1,
            multistep_filt : 1,
            test_mode : 1;
    } opt;
    uint16_t sr : 10;
  } cfg;
};

struct reg_OTP_PROG {
	uint8_t address;
};

struct reg_OTP_READ {
	uint8_t address;
};

struct reg_IOIN_2208 {
  uint8_t address;
  union {
    struct {
      bool  enn : 1,
            : 1,
            ms1 : 1,
            ms2 : 1,
            diag : 1,
            : 1,
            pdn_uart : 1,
            step : 1,
            sel_a : 1,
            dir : 1;
      uint16_t : 14;
      uint8_t version : 8;
    } opt;
    uint32_t sr;
  } cfg;
};

struct reg_IOIN_2224 {
  uint8_t address;
  union {
    struct {
      bool  : 1,
            pdn_uart : 1,
            spread : 1,
            dir : 1,
            enn : 1,
            step : 1,
            ms1 : 1,
            ms2 : 1,
            sel_a : 1;
      uint16_t : 15;
      uint8_t version : 8;
    } opt;
    uint32_t sr;
  } cfg;
};

struct reg_FACTORY_CONF {
    uint8_t address;
    union {
        struct {
            uint8_t fclktrim : 5,
                    : 3,
                    ottrim : 2;
        } opt;
        uint16_t sr;
    } cfg;
};

struct reg_VACTUAL_2208 {
    uint8_t address;
    uint32_t sr;
};

struct reg_MSCNT {
  uint8_t address;
};

struct reg_MSCURACT {
  uint8_t address;
  union {
    struct {
      int16_t cur_a : 9,
                    : 7,
              cur_b : 9;
    } opt;
    uint32_t sr : 25;
  } cfg;
};

struct reg_CHOPCONF_2208 {
  uint8_t address;
  union {
    struct {
      uint8_t toff : 4,
              hstrt : 3;
      int8_t  hend : 4,
                   : 4,
              tbl : 2;
      bool    vsense : 1;
      uint8_t : 6,
              mres : 4;
      bool    intpol : 1,
              dedge : 1,
              diss2g : 1,
              diss2vs : 1;
    } opt;
    uint32_t sr;
  } cfg;
};

struct reg_PWMCONF_2208 {
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

struct reg_DRV_STATUS_2208 {
  uint8_t address;
  union {
    struct {
      bool otpw : 1,
           ot : 1,
           s2ga : 1,
           s2gb : 1,
           s2vsa : 1,
           s2vsb : 1,
           ola : 1,
           olb : 1,
           t120 : 1,
           t143 : 1,
           t150 : 1,
           t157 : 1;
      uint8_t : 4,
              cs_actual : 5,
              : 2;
      bool stealth : 1,
           stst : 1;
    } opt;
    uint32_t sr;
  } cfg;
};

struct reg_PWM_SCALE_2208 {
  uint8_t address;
  union {
    struct {
      uint8_t pwm_scale_sum : 8,
              : 8;
      int16_t pwm_scale_auto : 9;
    } opt;
    uint32_t sr;
  } cfg;
};
/*
struct reg_PWM_AUTO {
  uint8_t address;
  struct {
    union {
      uint8_t pwm_ofs_auto : 8,
              : 8,
              pwm_grad_auto : 8;
    } opt;
    uint32_t sr : 24;
  } cfg;
};
*/