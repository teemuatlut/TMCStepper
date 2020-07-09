#pragma once

#include "TMCStepper.h"
#include "TMC2130.hpp"
#include "TMC2208.hpp"

namespace TMC5130_n {

  // 0x00 RW: GCONF
  template<typename TYPE>
  struct GCONF_i : public TMC2130_n::GCONF_i<TYPE> {
    void diag1_poscomp_pushpull(bool B) __attribute__((alias("TMC2130_n::GCONF_i<TYPE>::diag1_pushpull(bool B)")));
    bool diag1_poscomp_pushpull() __attribute__((alias("TMC2130_n::GCONF_i<TYPE>::diag1_pushpull()")));

  };
  // 0x01 R+c: GSTAT
  using TMC2130_n::GSTAT_i;
  // 0x02 R: IFCNT
  using TMC2208_n::IFCNT_i;
  // 0x03 W: SLAVECONF
  using TMC2208_n::SLAVECONF_i;
  // 0x04 R: IOIN
  template<typename TYPE>
  struct IOIN_i {
    #pragma pack(push, 1)
    struct IOIN_t {
      constexpr static uint8_t address = 0x04;
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
    #pragma pack(pop)

    uint32_t  IOIN() {
      return static_cast<TYPE*>(this)->read(IOIN_t::address);
    }
    bool    refl_step()      { return IOIN_t{ IOIN() }.refl_step; }
    bool    refr_dir()       { return IOIN_t{ IOIN() }.refr_dir; }
    bool    encb_dcen_cfg4() { return IOIN_t{ IOIN() }.encb_dcen_cfg4; }
    bool    enca_dcin_cfg5() { return IOIN_t{ IOIN() }.enca_dcin_cfg5; }
    bool    drv_enn_cfg6()   { return IOIN_t{ IOIN() }.drv_enn_cfg6; }
    bool    enc_n_dco()      { return IOIN_t{ IOIN() }.enc_n_dco; }
    bool    sd_mode()        { return IOIN_t{ IOIN() }.sd_mode; }
    bool    swcomp_in()      { return IOIN_t{ IOIN() }.swcomp_in; }
    uint8_t version()        { return IOIN_t{ IOIN() }.version; }
  };

  template<typename TYPE>
  struct OUTPUT_i {
    #pragma pack(push, 1)
    struct OUTPUT_t {
      constexpr static uint8_t address = 0x04;
      bool sr : 1;
    };
    #pragma pack(pop)
  
    bool TMC_OUTPUT() {
      return r.sr;
    }
    void TMC_OUTPUT(bool input) {
      static_cast<TYPE*>(this)->write(OUTPUT_t::address, input);
    }
    protected:
      OUTPUT_t r{};
  };

  template<typename TYPE>
  struct X_COMPARE_i {
    #pragma pack(push, 1)
    struct X_COMPARE_t {
      constexpr static uint8_t address = 0x05;
      uint32_t sr;
    };
    #pragma pack(pop)
  
    uint32_t X_COMPARE() {
      return r.sr;
    }
    void X_COMPARE(uint32_t input) {
      static_cast<TYPE*>(this)->write(X_COMPARE_t::address, input);
    }
    protected:
      X_COMPARE_t r{};
  };

  using TMC2130_n::IHOLD_IRUN_i;
  using TMC2130_n::TPOWERDOWN_i;
  using TMC2130_n::TSTEP_i;
  using TMC2130_n::TPWMTHRS_i;
  using TMC2130_n::TCOOLTHRS_i;
  using TMC2130_n::THIGH_i;

  template<typename TYPE>
  struct RAMPMODE_i {
    #pragma pack(push, 1)
    struct RAMPMODE_t {
      constexpr static uint8_t address = 0x20;
      uint8_t sr : 2;
    };
    #pragma pack(pop)
  
    uint8_t RAMPMODE() {
      return static_cast<TYPE*>(this)->read(RAMPMODE_t::address);
    }
    void RAMPMODE(uint8_t input) {
      static_cast<TYPE*>(this)->write(RAMPMODE_t::address, input);
    }
  };

  template<typename TYPE>
  struct XACTUAL_i {
    #pragma pack(push, 1)
    struct XACTUAL_t {
      constexpr static uint8_t address = 0x21;
    };
    #pragma pack(pop)
  
    int32_t XACTUAL() {
      return (int32_t)static_cast<TYPE*>(this)->read(XACTUAL_t::address);
    }
    void XACTUAL(int32_t input) {
      static_cast<TYPE*>(this)->write(XACTUAL_t::address, (uint32_t)input);
    }
  };

  template<typename TYPE>
  struct VACTUAL_i {
    #pragma pack(push, 1)
    struct VACTUAL_t  { constexpr static uint8_t address = 0x22; };
    #pragma pack(pop)
  
    int32_t VACTUAL() {
      uint32_t int24 = read(VACTUAL_t::address);
      if((int24 >> 23) & 0x01) {
        int24 |= 0xFF000000;
      }
      return int24;
    }
  };

  template<typename TYPE>
  struct VSTART_i {
    #pragma pack(push, 1)
    struct VSTART_t {
      constexpr static uint8_t address = 0x23;
      uint32_t sr : 18;
    };
    #pragma pack(pop)
  
    uint32_t VSTART() {
      return r.sr;
    }
    void VSTART(uint32_t input) {
      static_cast<TYPE*>(this)->write(VSTART_t::address, input);
    }
    protected:
      VSTART_t r{};
  };

  template<typename TYPE>
  struct A1_i {
    #pragma pack(push, 1)
    struct A1_t {
      constexpr static uint8_t address = 0x24;
      uint16_t sr : 16;
    };
    #pragma pack(pop)
  
    uint16_t A1() {
      return r.sr;
    }
    void A1(uint16_t input) {
      static_cast<TYPE*>(this)->write(A1_t::address, input);
    }
    protected:
      A1_t r{};
  };

  template<typename TYPE>
  struct V1_i {
    #pragma pack(push, 1)
    struct V1_t {
      constexpr static uint8_t address = 0x25;
      uint32_t sr : 20;
    };
    #pragma pack(pop)
  
    uint32_t V1() {
      return r.sr;
    }
    void V1(uint32_t input) {
      static_cast<TYPE*>(this)->write(V1_t::address, input);
    }
    protected:
      V1_t r{};
  };

  template<typename TYPE>
  struct AMAX_i {
    #pragma pack(push, 1)
    struct AMAX_t {
      constexpr static uint8_t address = 0x26;
      uint16_t sr : 16;
    };
    #pragma pack(pop)
  
    uint16_t AMAX() {
      return r.sr;
    }
    void AMAX(uint16_t input) {
      static_cast<TYPE*>(this)->write(AMAX_t::address, input);
    }
    protected:
      AMAX_t r{};
  };

  template<typename TYPE>
  struct VMAX_i {
    #pragma pack(push, 1)
    struct VMAX_t {
      constexpr static uint8_t address = 0x27;
      uint32_t sr : 23;
    };
    #pragma pack(pop)
  
    uint32_t VMAX() {
      return r.sr;
    }
    void VMAX(uint32_t input) {
      static_cast<TYPE*>(this)->write(VMAX_t::address, input);
    }
    protected:
      VMAX_t r{};
  };

  template<typename TYPE>
  struct DMAX_i {
    #pragma pack(push, 1)
    struct DMAX_t {
      constexpr static uint8_t address = 0x28;
      uint16_t sr : 16;
    };
    #pragma pack(pop)
  
    uint16_t DMAX() {
      return r.sr;
    }
    void DMAX(uint16_t input) {
      static_cast<TYPE*>(this)->write(DMAX_t::address, input);
    }
    protected:
      DMAX_t r{};
  };

  template<typename TYPE>
  struct D1_i {
    #pragma pack(push, 1)
    struct D1_t {
      constexpr static uint8_t address = 0x2A;
      uint16_t sr : 16;
    };
    #pragma pack(pop)
  
    uint16_t D1() {
      return r.sr;
    }
    void D1(uint16_t input) {
      static_cast<TYPE*>(this)->write(D1_t::address, input);
    }
    protected:
      D1_t r{};
  };

  template<typename TYPE>
  struct VSTOP_i {
    #pragma pack(push, 1)
    struct VSTOP_t {
      constexpr static uint8_t address = 0x2B;
      uint32_t sr : 18;
    };
    #pragma pack(pop)
  
    uint32_t VSTOP() {
      return r.sr;
    }
    void VSTOP(uint32_t input) {
      if (input == 0 && static_cast<TYPE*>(this)->RAMPMODE() == 0) return;
      r.sr = input;
      static_cast<TYPE*>(this)->write(r.address, r.sr);
    }
    protected:
      VSTOP_t r{};
  };

  template<typename TYPE>
  struct TZEROWAIT_i {
    #pragma pack(push, 1)
    struct TZEROWAIT_t {
      constexpr static uint8_t address = 0x2C;
      uint16_t sr : 16;
    };
    #pragma pack(pop)
  
    uint16_t TZEROWAIT() {
      return r.sr;
    }
    void TZEROWAIT(uint16_t input) {
      static_cast<TYPE*>(this)->write(TZEROWAIT_t::address, input);
    }
    protected:
      TZEROWAIT_t r{};
  };

  template<typename TYPE>
  struct XTARGET_i {
    #pragma pack(push, 1)
    struct XTARGET_t  { constexpr static uint8_t address = 0x2D; };
    #pragma pack(pop)
  
    int32_t XTARGET() {
      return static_cast<TYPE*>(this)->read(XTARGET_t::address);
    }
    void XTARGET(int32_t input) {
      static_cast<TYPE*>(this)->write(XTARGET_t::address, input);
    }
  };

  using TMC2130_n::VDCMIN_i;

  template<typename TYPE>
    struct SW_MODE_i {
      #pragma pack(push, 1)
      struct SW_MODE_t {
        constexpr static uint8_t address = 0x34;
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
      #pragma pack(pop)
    
      uint16_t SW_MODE() {
        return static_cast<TYPE*>(this)->read(SW_MODE_t::address);
      }
      void SW_MODE(uint16_t input) {
        static_cast<TYPE*>(this)->write(SW_MODE_t::address, input);
      }

      void stop_l_enable(bool B)    { SW_MODE_t r{ SW_MODE() }; r.stop_l_enable = B;    SW_MODE(r.sr); }
      void stop_r_enable(bool B)    { SW_MODE_t r{ SW_MODE() }; r.stop_r_enable = B;    SW_MODE(r.sr); }
      void pol_stop_l(bool B)       { SW_MODE_t r{ SW_MODE() }; r.pol_stop_l = B;       SW_MODE(r.sr); }
      void pol_stop_r(bool B)       { SW_MODE_t r{ SW_MODE() }; r.pol_stop_r = B;       SW_MODE(r.sr); }
      void swap_lr(bool B)          { SW_MODE_t r{ SW_MODE() }; r.swap_lr = B;          SW_MODE(r.sr); }
      void latch_l_active(bool B)   { SW_MODE_t r{ SW_MODE() }; r.latch_l_active = B;   SW_MODE(r.sr); }
      void latch_l_inactive(bool B) { SW_MODE_t r{ SW_MODE() }; r.latch_l_inactive = B; SW_MODE(r.sr); }
      void latch_r_active(bool B)   { SW_MODE_t r{ SW_MODE() }; r.latch_r_active = B;   SW_MODE(r.sr); }
      void latch_r_inactive(bool B) { SW_MODE_t r{ SW_MODE() }; r.latch_r_inactive = B; SW_MODE(r.sr); }
      void en_latch_encoder(bool B) { SW_MODE_t r{ SW_MODE() }; r.en_latch_encoder = B; SW_MODE(r.sr); }
      void sg_stop(bool B)          { SW_MODE_t r{ SW_MODE() }; r.sg_stop = B;          SW_MODE(r.sr); }
      void en_softstop(bool B)      { SW_MODE_t r{ SW_MODE() }; r.en_softstop = B;      SW_MODE(r.sr); }

      bool stop_l_enable()          { return SW_MODE_t{ SW_MODE() }.stop_r_enable;    }
      bool stop_r_enable()          { return SW_MODE_t{ SW_MODE() }.stop_r_enable;    }
      bool pol_stop_l()             { return SW_MODE_t{ SW_MODE() }.pol_stop_l;       }
      bool pol_stop_r()             { return SW_MODE_t{ SW_MODE() }.pol_stop_r;       }
      bool swap_lr()                { return SW_MODE_t{ SW_MODE() }.swap_lr;          }
      bool latch_l_active()         { return SW_MODE_t{ SW_MODE() }.latch_l_active;   }
      bool latch_l_inactive()       { return SW_MODE_t{ SW_MODE() }.latch_l_inactive; }
      bool latch_r_active()         { return SW_MODE_t{ SW_MODE() }.latch_r_active;   }
      bool latch_r_inactive()       { return SW_MODE_t{ SW_MODE() }.latch_r_inactive; }
      bool en_latch_encoder()       { return SW_MODE_t{ SW_MODE() }.en_latch_encoder; }
      bool sg_stop()                { return SW_MODE_t{ SW_MODE() }.sg_stop;          }
      bool en_softstop()            { return SW_MODE_t{ SW_MODE() }.en_softstop;      }
    };

    template<typename TYPE>
    struct RAMP_STAT_i {
      #pragma pack(push, 1)
      struct RAMP_STAT_t {
        RAMP_STAT_t(const uint16_t data) : sr(data) {};
        constexpr static uint8_t address = 0x35;
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
      #pragma pack(pop)
    
      uint16_t RAMP_STAT() {
        return static_cast<TYPE*>(this)->read(RAMP_STAT_t::address);
      }
      void RAMP_STAT(uint16_t input) {
        static_cast<TYPE*>(this)->write(RAMP_STAT_t::address, input);
      }

      bool status_stop_l()      { return RAMP_STAT_t{ RAMP_STAT() }.status_stop_l;      }
      bool status_stop_r()      { return RAMP_STAT_t{ RAMP_STAT() }.status_stop_r;      }
      bool status_latch_l()     { return RAMP_STAT_t{ RAMP_STAT() }.status_latch_l;     }
      bool status_latch_r()     { return RAMP_STAT_t{ RAMP_STAT() }.status_latch_r;     }
      bool event_stop_l()       { return RAMP_STAT_t{ RAMP_STAT() }.event_stop_l;       }
      bool event_stop_r()       { return RAMP_STAT_t{ RAMP_STAT() }.event_stop_r;       }
      bool event_stop_sg()      { return RAMP_STAT_t{ RAMP_STAT() }.event_stop_sg;      }
      bool event_pos_reached()  { return RAMP_STAT_t{ RAMP_STAT() }.event_pos_reached;  }
      bool velocity_reached()   { return RAMP_STAT_t{ RAMP_STAT() }.velocity_reached;   }
      bool position_reached()   { return RAMP_STAT_t{ RAMP_STAT() }.position_reached;   }
      bool vzero()              { return RAMP_STAT_t{ RAMP_STAT() }.vzero;              }
      bool t_zerowait_active()  { return RAMP_STAT_t{ RAMP_STAT() }.t_zerowait_active;  }
      bool second_move()        { return RAMP_STAT_t{ RAMP_STAT() }.second_move;        }
      bool status_sg()          { return RAMP_STAT_t{ RAMP_STAT() }.status_sg;          }
    };

    template<typename TYPE>
    struct XLATCH_i {
      #pragma pack(push, 1)
      struct XLATCH_t {
        constexpr static uint8_t address = 0x36;
      };
      #pragma pack(pop)
    
      uint32_t XLATCH() {
        return static_cast<TYPE*>(this)->read(XLATCH_t::address);
      }
    };

    template<typename TYPE>
    struct ENCMODE_i {
      #pragma pack(push, 1)
      struct ENCMODE_t {
        ENCMODE_t(const uint16_t data) : sr(data) {};
        constexpr static uint8_t address = 0x38;
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
      #pragma pack(pop)
    
      uint16_t ENCMODE() {
        return static_cast<TYPE*>(this)->read(ENCMODE_t::address);
      }
      void ENCMODE(uint16_t input) {
        static_cast<TYPE*>(this)->write(ENCMODE_t::address, input);
      }

      void pol_a(bool B)            { ENCMODE_t r{ ENCMODE() }; r.pol_a = B;            ENCMODE(r.sr); }
      void pol_b(bool B)            { ENCMODE_t r{ ENCMODE() }; r.pol_b = B;            ENCMODE(r.sr); }
      void pol_n(bool B)            { ENCMODE_t r{ ENCMODE() }; r.pol_n = B;            ENCMODE(r.sr); }
      void ignore_ab(bool B)        { ENCMODE_t r{ ENCMODE() }; r.ignore_ab = B;        ENCMODE(r.sr); }
      void clr_cont(bool B)         { ENCMODE_t r{ ENCMODE() }; r.clr_cont = B;         ENCMODE(r.sr); }
      void clr_once(bool B)         { ENCMODE_t r{ ENCMODE() }; r.clr_once = B;         ENCMODE(r.sr); }
      void pos_edge(bool B)         { ENCMODE_t r{ ENCMODE() }; r.pos_edge = B;         ENCMODE(r.sr); }
      void neg_edge(bool B)         { ENCMODE_t r{ ENCMODE() }; r.neg_edge = B;         ENCMODE(r.sr); }
      void clr_enc_x(bool B)        { ENCMODE_t r{ ENCMODE() }; r.clr_enc_x = B;        ENCMODE(r.sr); }
      void latch_x_act(bool B)      { ENCMODE_t r{ ENCMODE() }; r.latch_x_act = B;      ENCMODE(r.sr); }
      void enc_sel_decimal(bool B)  { ENCMODE_t r{ ENCMODE() }; r.enc_sel_decimal = B;  ENCMODE(r.sr); }

      bool pol_a()            { return ENCMODE_t{ ENCMODE() }.pol_a;            }
      bool pol_b()            { return ENCMODE_t{ ENCMODE() }.pol_b;            }
      bool pol_n()            { return ENCMODE_t{ ENCMODE() }.pol_n;            }
      bool ignore_ab()        { return ENCMODE_t{ ENCMODE() }.ignore_ab;        }
      bool clr_cont()         { return ENCMODE_t{ ENCMODE() }.clr_cont;         }
      bool clr_once()         { return ENCMODE_t{ ENCMODE() }.clr_once;         }
      bool pos_edge()         { return ENCMODE_t{ ENCMODE() }.pos_edge;         }
      bool neg_edge()         { return ENCMODE_t{ ENCMODE() }.neg_edge;         }
      bool clr_enc_x()        { return ENCMODE_t{ ENCMODE() }.clr_enc_x;        }
      bool latch_x_act()      { return ENCMODE_t{ ENCMODE() }.latch_x_act;      }
      bool enc_sel_decimal()  { return ENCMODE_t{ ENCMODE() }.enc_sel_decimal;  }
    };

    template<typename TYPE>
    struct X_ENC_i {
      #pragma pack(push, 1)
      struct X_ENC_t {
        constexpr static uint8_t address = 0x39; 
      };
      #pragma pack(pop)
    
      int32_t XENC() {
        return static_cast<TYPE*>(this)->read(X_ENC_t::address);
      }
      void XENC(int32_t input) {
        static_cast<TYPE*>(this)->write(X_ENC_t::address, input);
      }
    };

    template<typename TYPE>
    struct ENC_CONST_i {
      #pragma pack(push, 1)
      struct ENC_CONST_t {
        constexpr static uint8_t address = 0x3A;
        uint32_t sr;
      };
      #pragma pack(pop)
    
      uint32_t ENC_CONST() {
        return r.sr;
      }
      void ENC_CONST(uint32_t input) {
        static_cast<TYPE*>(this)->write(ENC_CONST_t::address, input);
      }
      protected:
        ENC_CONST_t r{};
    };

    template<typename TYPE>
    struct ENC_STATUS_i {
      #pragma pack(push, 1)
      struct ENC_STATUS_t {
        constexpr static uint8_t address = 0x3B;
      };
      #pragma pack(pop)
    
      bool ENC_STATUS() {
        return static_cast<TYPE*>(this)->read(ENC_STATUS_t::address);
      }
      void ENC_STATUS(bool input) {
        static_cast<TYPE*>(this)->write(ENC_STATUS_t::address, input);
      }
    };

    template<typename TYPE>
    struct ENC_LATCH_i {
      #pragma pack(push, 1)
      struct ENC_LATCH_t {
        constexpr static uint8_t address = 0x3C;
      };
      #pragma pack(pop)
    
      uint32_t ENC_LATCH() {
        return static_cast<TYPE*>(this)->read(ENC_LATCH_t::address);
      }
    };

    using TMC2130_n::MSLUT0_i;
    using TMC2130_n::MSLUT1_i;
    using TMC2130_n::MSLUT2_i;
    using TMC2130_n::MSLUT3_i;
    using TMC2130_n::MSLUT4_i;
    using TMC2130_n::MSLUT5_i;
    using TMC2130_n::MSLUT6_i;
    using TMC2130_n::MSLUT7_i;
    using TMC2130_n::MSLUTSEL_i;
    using TMC2130_n::MSLUTSTART_i;
    using TMC2130_n::MSCNT_i;
    using TMC2130_n::MSCURACT_i;
    using TMC2130_n::CHOPCONF_i;
    using TMC2130_n::COOLCONF_i;
    using TMC2130_n::DCCTRL_i;
    using TMC2130_n::DRV_STATUS_i;
    using TMC2130_n::PWMCONF_i;
    using TMC2130_n::PWM_SCALE_i;
    using TMC2130_n::ENCM_CTRL_i;
    using TMC2130_n::LOST_STEPS_i;
}
