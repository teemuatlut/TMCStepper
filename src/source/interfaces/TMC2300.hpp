#pragma once

#include "TMCStepper.h"
#include "TMC2130.hpp"
#include "TMC2208.hpp"
#include "TMC2209.hpp"

namespace TMC2300_n {
  template<typename TYPE>
  struct GCONF_i {
    #pragma pack(push, 1)
    struct GCONF_t {
      constexpr static uint8_t address = 0x00;
      union {
        uint8_t sr;
        struct {
          bool
            : 1,                // 0
            extcap : 1,         // 1
            : 1,                // 2
            shaft : 1,          // 3
            diag_index : 1,     // 4
            diag_step : 1,      // 5
            multistep_filt : 1; // 6
        };
      };
    };
    #pragma pack(pop)

    uint8_t GCONF() {
      return static_cast<TYPE*>(this)->read(GCONF_t::address);
    }
    void GCONF(uint8_t input) {
      static_cast<TYPE*>(this)->write(GCONF_t::address, input);
    }

    void extcap(bool B)         { GCONF_t r{ GCONF() }; r.extcap = B;         GCONF(r.sr); }
    void shaft(bool B)          { GCONF_t r{ GCONF() }; r.shaft = B;          GCONF(r.sr); }
    void diag_index(bool B)     { GCONF_t r{ GCONF() }; r.diag_index = B;     GCONF(r.sr); }
    void diag_step(bool B)      { GCONF_t r{ GCONF() }; r.diag_step = B;      GCONF(r.sr); }
    void multistep_filt(bool B) { GCONF_t r{ GCONF() }; r.multistep_filt = B; GCONF(r.sr); }

    bool extcap()         { return GCONF_t{ GCONF() }.extcap; }
    bool shaft()          { return GCONF_t{ GCONF() }.shaft; }
    bool diag_index()     { return GCONF_t{ GCONF() }.diag_index; }
    bool diag_step()      { return GCONF_t{ GCONF() }.diag_step; }
    bool multistep_filt() { return GCONF_t{ GCONF() }.multistep_filt; }
  };

  template<typename TYPE>
  struct GSTAT_i {
    #pragma pack(push, 1)
    struct GSTAT_t {
      constexpr static uint8_t address = 0x01;
      union {
        uint8_t sr;
        struct {
          bool
            reset : 1,  // 0
            drv_err : 1,// 1
            u3v5 : 1;   // 2
        };
      };
    };
    #pragma pack(pop)
  
    uint8_t GSTAT() {
      return static_cast<TYPE*>(this)->read(GSTAT_t::address);
    }
    void GSTAT(uint8_t input) {
      static_cast<TYPE*>(this)->write(GSTAT_t::address, input);
    }

    void reset(bool B)    { GSTAT_t r{ GSTAT() }; r.reset = B;    GSTAT(r.sr); }
    void drv_err(bool B)  { GSTAT_t r{ GSTAT() }; r.drv_err = B;  GSTAT(r.sr); }
    void u3v5(bool B)     { GSTAT_t r{ GSTAT() }; r.u3v5 = B;     GSTAT(r.sr); }


    bool reset()    { return GSTAT_t{ GSTAT() }.reset; }
    bool drv_err()  { return GSTAT_t{ GSTAT() }.drv_err; }
    bool u3v5()     { return GSTAT_t{ GSTAT() }.u3v5; }
  };

  using TMC2208_n::IFCNT_i;
  using TMC2208_n::SLAVECONF_i;

  template<typename TYPE>
  struct IOIN_i {
    #pragma pack(push, 1)
    struct IOIN_t {
      constexpr static uint8_t address = 0x06;
      union {
        uint32_t sr;
        struct {
          bool
            en : 1,             //  0
            nstdby : 1,         //  1
            ad0 : 1,            //  2
            ad1 : 1,            //  3
            diag : 1,           //  4
            stepper : 1,        //  5
            pdn_uart : 1,       //  6
            mode : 1,           //  7
            step : 1,           //  8
            dir : 1,            //  9
            comp_a1a2 : 1,      // 10
            comp_b1b2 : 1;      // 11
          uint16_t : 12;
          uint8_t version : 1;  // 24
        };
      };
    };
    #pragma pack(pop)
  
    uint32_t IOIN() {
      return static_cast<TYPE*>(this)->read(IOIN_t::address);
    }

    bool en()         { return IOIN_t{ IOIN() }.en; }
    bool nstdby()     { return IOIN_t{ IOIN() }.nstdby; }
    bool ad0()        { return IOIN_t{ IOIN() }.ad0; }
    bool ad1()        { return IOIN_t{ IOIN() }.ad1; }
    bool diag()       { return IOIN_t{ IOIN() }.diag; }
    bool stepper()    { return IOIN_t{ IOIN() }.stepper; }
    bool pdn_uart()   { return IOIN_t{ IOIN() }.pdn_uart; }
    bool mode()       { return IOIN_t{ IOIN() }.mode; }
    bool step()       { return IOIN_t{ IOIN() }.step; }
    bool dir()        { return IOIN_t{ IOIN() }.dir; }
    bool comp_a1a2()  { return IOIN_t{ IOIN() }.comp_a1a2; }
    bool comp_b1b2()  { return IOIN_t{ IOIN() }.comp_b1b2; }
    uint8_t version() { return IOIN_t{ IOIN() }.version; }
  };

  using TMC2130_n::IHOLD_IRUN_i;
  using TMC2130_n::TPOWERDOWN_i;
  using TMC2130_n::TSTEP_i;
  using TMC2208_n::VACTUAL_i;
  using TMC2130_n::TCOOLTHRS_i;
  using TMC2209_n::SGTHRS_i;

  // 0x41 R: SG_VALUE
  template<typename TYPE>
  struct SG_VALUE_i {
      struct SG_VALUE_t {
          constexpr static uint8_t address = 0x41;
      };

      uint16_t SG_VALUE() {
          return static_cast<TYPE*>(this)->read(SG_VALUE_t::address);
      }
  };

  using TMC2209_n::COOLCONF_i;
  using TMC2130_n::MSCNT_i;

  // 0x6C RW: CHOPCONF
  template<typename TYPE>
  struct CHOPCONF_i {
    #pragma pack(push, 1)
    struct CHOPCONF_t {
      constexpr static uint8_t address = 0x6C;
      union {
        uint32_t sr;
        struct {
          bool enable_drv : 4;  // 0
          uint16_t : 14;
          uint8_t
            tbl : 2,            // 15
            : 7,
            mres : 4;           // 24
          bool
            intpol : 1,         // 28
            dedge : 1,          // 29
            diss2g : 1,         // 30
            diss2vs : 1;        // 31
        };
      };
    };
    #pragma pack(pop)

    void CHOPCONF(uint32_t input) {
      static_cast<TYPE*>(this)->write(CHOPCONF_t::address, input);
    }
    uint32_t CHOPCONF() {
      return static_cast<TYPE*>(this)->read(CHOPCONF_t::address);
    }

    void enable_drv ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.enable_drv = B; CHOPCONF(r.sr); }
    void tbl        ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.tbl = B;        CHOPCONF(r.sr); }
    void mres       ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.mres = B;       CHOPCONF(r.sr); }
    void intpol     ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.intpol = B;     CHOPCONF(r.sr); }
    void dedge      ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.dedge = B;      CHOPCONF(r.sr); }
    void diss2g     ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.diss2g = B;     CHOPCONF(r.sr); }
    void diss2vs    ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.diss2vs = B;    CHOPCONF(r.sr); }

    bool    enable_drv() { return CHOPCONF_t{ CHOPCONF() }.enable_drv; }
    uint8_t tbl()        { return CHOPCONF_t{ CHOPCONF() }.tbl;        }
    uint8_t mres()       { return CHOPCONF_t{ CHOPCONF() }.mres;       }
    bool    intpol()     { return CHOPCONF_t{ CHOPCONF() }.intpol;     }
    bool    dedge()      { return CHOPCONF_t{ CHOPCONF() }.dedge;      }
    bool    diss2g()     { return CHOPCONF_t{ CHOPCONF() }.diss2g;     }
    bool    diss2vs()    { return CHOPCONF_t{ CHOPCONF() }.diss2vs;    }
  };

  // 0x6F R: DRV_STATUS
  template<typename TYPE>
  struct DRV_STATUS_i {
    #pragma pack(push, 1)
    struct DRV_STATUS_t {
      constexpr static uint8_t address = 0x6F;
      union {
        uint32_t sr;
        struct {
          bool
            otpw : 1,       // 0
            ot : 1,         // 1
            s2ga : 1,       // 2
            s2gb : 1,       // 3
            s2vsa : 1,      // 4
            s2vsb : 1,      // 5
            ola : 1,        // 6
            olb : 1,        // 7
            t120 : 1,       // 8
            t150 : 1;       // 9
          uint8_t           // 
            : 6,            // 
            cs_actual : 5;  // 16
          uint16_t : 10;    // 
          bool stst : 1;    // 31
        };
      };
    };
    #pragma pack(pop)

    uint32_t DRV_STATUS() {
      return static_cast<TYPE*>(this)->read(DRV_STATUS_t::address);
    }

    bool        otpw()      { return DRV_STATUS_t{ DRV_STATUS() }.otpw;      }
    bool        ot()        { return DRV_STATUS_t{ DRV_STATUS() }.ot;        }
    bool        s2ga()      { return DRV_STATUS_t{ DRV_STATUS() }.s2ga;      }
    bool        s2gb()      { return DRV_STATUS_t{ DRV_STATUS() }.s2gb;      }
    bool        s2vsa()     { return DRV_STATUS_t{ DRV_STATUS() }.s2vsa;     }
    bool        s2vsb()     { return DRV_STATUS_t{ DRV_STATUS() }.s2vsb;     }
    bool        ola()       { return DRV_STATUS_t{ DRV_STATUS() }.ola;       }
    bool        olb()       { return DRV_STATUS_t{ DRV_STATUS() }.olb;       }
    bool        t120()      { return DRV_STATUS_t{ DRV_STATUS() }.t120;      }
    bool        t150()      { return DRV_STATUS_t{ DRV_STATUS() }.t150;      }
    uint16_t    cs_actual() { return DRV_STATUS_t{ DRV_STATUS() }.cs_actual; }
    bool        stst()      { return DRV_STATUS_t{ DRV_STATUS() }.stst;      }
  };

  using TMC2208_n::PWMCONF_i;
  using TMC2208_n::PWM_SCALE_i;
  using TMC2208_n::PWM_AUTO_i;
}
