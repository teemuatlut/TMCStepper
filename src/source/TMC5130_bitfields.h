#pragma once

struct SLAVECONF_t {
  union {
    uint16_t sr : 12;
    struct {
      uint8_t slaveaddr : 8;
      uint8_t senddelay : 4;
    };
  };
};

namespace TMC5130_n {
  struct IOIN_t {
    union {
      uint32_t sr;
      struct {
        bool  refl_step : 1,
              refr_dir : 1,
              encb_dcen_cfg4 : 1,
              enca_dcin_cfg5 : 1,
              drv_enn_cfg6 : 1,
              enc_n_dco : 1,
              sd_mode : 1,
              swcomp_in : 1;
        uint16_t : 16;
        uint8_t version : 8;
      };
    };
  };
}

struct OUTPUT_t {
  bool sr : 1;
};

struct X_COMPARE_t {
  uint32_t sr;
};

struct RAMPMODE_t {
  uint8_t sr : 2;
};

struct XACTUAL_t {
  uint32_t sr;
};

struct VSTART_t {
  uint32_t sr : 18;
};

struct A1_t {
  uint16_t sr : 16;
};

struct V1_t {
  uint32_t sr : 20;
};

struct AMAX_t {
  uint16_t sr : 16;
};

struct VMAX_t {
  uint32_t sr : 23;
};

struct DMAX_t {
  uint16_t sr : 16;
};

struct D1_t {
  uint16_t sr : 16;
};

struct VSTOP_t {
  uint32_t sr : 18;
};

struct TZEROWAIT_t {
  uint16_t sr : 16;
};

struct SW_MODE_t {
  union {
    uint16_t sr : 12;
    struct {
      bool  stop_l_enable : 1,
            stop_r_enable : 1,
            pol_stop_l : 1,
            pol_stop_r : 1,
            swap_lr : 1,
            latch_l_active : 1,
            latch_l_inactive : 1,
            latch_r_active : 1,
            latch_r_inactive : 1,
            en_latch_encoder : 1,
            sg_stop : 1,
            en_softstop : 1;
    };
  };
};

struct RAMP_STAT_t {
  union {
    uint16_t sr : 14;
    struct {
      bool  status_stop_l : 1,
            status_stop_r : 1,
            status_latch_l : 1,
            status_latch_r : 1,
            event_stop_l : 1,
            event_stop_r : 1,
            event_stop_sg : 1,
            event_pos_reached : 1,
            velocity_reached : 1,
            position_reached : 1,
            vzero : 1,
            t_zerowait_active : 1,
            second_move : 1,
            status_sg : 1;
    };
  };
};

struct ENCMODE_t {
  union {
    uint16_t sr : 11;
    struct {
      bool  pol_a : 1,
            pol_b : 1,
            pol_n : 1,
            ignore_ab : 1,
            clr_cont : 1,
            clr_once : 1,
            pos_edge : 1,
            neg_edge : 1,
            clr_enc_x : 1,
            latch_x_act : 1,
            enc_sel_decimal : 1;
    };
  };
};

struct ENC_CONST_t {
  int32_t sr;
};

struct MSLUT0_t {
  uint32_t sr;
};

struct MSLUT1_t {
  uint32_t sr;
};

struct MSLUT2_t {
  uint32_t sr;
};

struct MSLUT3_t {
  uint32_t sr;
};

struct MSLUT4_t {
  uint32_t sr;
};

struct MSLUT5_t {
  uint32_t sr;
};

struct MSLUT6_t {
  uint32_t sr;
};

struct MSLUT7_t {
  uint32_t sr;
};

struct MSLUTSEL_t {
  union {
    uint32_t sr;
    struct {
      uint8_t w0 : 2,
              w1 : 2,
              w2 : 2,
              w3 : 2,
              x1 : 8,
              x2 : 8,
              x3 : 8;
    };
  };
};

struct MSLUTSTART_t {
  union {
    uint32_t sr : 24;
    struct {
      uint8_t start_sin : 8,
                        : 8,
              start_sin90 : 8;
    };
  };
};

struct DCCTRL_t {
  union {
    uint32_t sr : 24;
    struct {
      uint16_t dc_time : 10,
                       : 5;
      uint8_t dc_sg : 8;
    };
  };
};
