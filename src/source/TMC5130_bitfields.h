#pragma once

struct reg_IFCNT {
  uint8_t address;
};

struct reg_SLAVECONF {
  uint8_t address;
  union {
    struct {
      uint8_t slaveaddr : 8;
      uint8_t senddelay : 4;
    } opt;
    uint16_t sr : 12;
  } cfg;
};

struct reg_IOIN_5130 {
  uint8_t address;
  union {
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
    } opt;
    uint32_t sr;
  } cfg;
};

struct reg_OUTPUT {
  uint8_t address;
  bool sr : 1;
};

struct reg_X_COMPARE {
  uint8_t address;
  uint32_t sr;
};

struct reg_RAMPMODE {
  uint8_t address;
  uint8_t sr : 2;
};

struct reg_XACTUAL {
  uint8_t address;
};

struct reg_VACTUAL {
  uint8_t address;
};

struct reg_VSTART {
  uint8_t address;
  uint32_t sr : 18;
};

struct reg_A1 {
  uint8_t address;
  uint16_t sr : 16;
};

struct reg_V1 {
  uint8_t address;
  uint32_t sr : 20;
};

struct reg_AMAX {
  uint8_t address;
  uint16_t sr : 16;
};

struct reg_VMAX {
  uint8_t address;
  uint32_t sr : 23;
};

struct reg_DMAX {
  uint8_t address;
  uint16_t sr : 16;
};

struct reg_D1 {
  uint8_t address;
  uint16_t sr : 16;
};

struct reg_VSTOP {
  uint8_t address;
  uint32_t sr : 18;
};

struct reg_TZEROWAIT {
  uint8_t address;
  uint16_t sr : 16;
};

struct reg_XTARGET {
  uint8_t address;
};

struct reg_SW_MODE {
  uint8_t address;
  union {
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
    } opt;
    uint16_t sr : 12;
  } cfg;
};

struct reg_RAMP_STAT {
  uint8_t address;
  union {
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
    } opt;
    uint16_t sr : 14;
  } cfg;
};

struct reg_XLATCH {
  uint8_t address;
};

struct reg_ENCMODE {
  uint8_t address;
  union {
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
    } opt;
    uint16_t sr : 11;
  } cfg;
};

struct reg_X_ENC {
  uint8_t address;
};

struct reg_ENC_CONST {
  uint8_t address;
  int32_t sr;
};

struct reg_ENC_STATUS {
  uint8_t address;
};

struct reg_ENC_LATCH {
  uint8_t address;
};

struct reg_MSLUT0 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT1 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT2 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT3 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT4 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT5 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT6 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUT7 {
  uint8_t address;
  uint32_t sr;
};

struct reg_MSLUTSEL {
  uint8_t address;
  union {
    struct {
      uint8_t w0 : 2,
              w1 : 2,
              w2 : 2,
              w3 : 2,
              x1 : 8,
              x2 : 8,
              x3 : 8;
    } opt;
    uint32_t sr;
  } cfg;
};

struct reg_MSLUTSTART {
  uint8_t address;
  union {
    struct {
      uint8_t start_sin : 8,
                        : 8,
              start_sin90 : 8;
    } opt;
    uint32_t sr : 24;
  } cfg;
};

struct reg_MSCNT {
  uint8_t address;
};

struct reg_MSCURACT {
  uint8_t address;
  union {
    struct {
      uint16_t  cur_a : 9,
                      : 7,
                cur_b : 9;
    } opt;
    uint32_t sr : 25;
  } cfg;
};

struct reg_DCCTRL {
  uint8_t address;
  union {
    struct {
      uint16_t dc_time : 10,
                       : 5;
      uint8_t dc_sg : 8;
    } opt;
    uint32_t sr : 24;
  } cfg;
};
