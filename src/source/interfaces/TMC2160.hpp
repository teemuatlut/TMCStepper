#pragma once

#include "../../TMCStepper.h"

namespace TMC2160_n {
    using TMC2130_n::GCONF_t;
    using TMC2130_n::GSTAT_t;
    using TMC2130_n::IHOLD_IRUN_t;
    using TMC2130_n::TPOWERDOWN_t;
    using TMC2130_n::TSTEP_t;
    using TMC2130_n::TPWMTHRS_t;
    using TMC2130_n::TCOOLTHRS_t;
    using TMC2130_n::THIGH_t;
    using TMC2130_n::XDIRECT_t;
    using TMC2130_n::VDCMIN_t;
    using TMC2130_n::MSLUTSEL_t;
    using TMC2130_n::MSLUTSTART_t;
    using TMC2130_n::MSCNT_t;
    using TMC2130_n::MSCURACT_t;

    using TMC2130_n::GCONF_i;
    using TMC2130_n::GSTAT_i;
    using TMC2130_n::IHOLD_IRUN_i;
    using TMC2130_n::TPOWERDOWN_i;
    using TMC2130_n::TSTEP_i;
    using TMC2130_n::TPWMTHRS_i;
    using TMC2130_n::TCOOLTHRS_i;
    using TMC2130_n::THIGH_i;
    using TMC2130_n::XDIRECT_i;
    using TMC2130_n::VDCMIN_i;
    using TMC2130_n::MSLUTSEL_i;
    using TMC2130_n::MSLUTSTART_i;
    using TMC2130_n::MSCNT_i;
    using TMC2130_n::MSCURACT_i;

    // 0x6C RW: CHOPCONF
    #pragma pack(push, 1)
    struct CHOPCONF_t {
        constexpr static uint8_t address = 0x6C;
        union {
            uint32_t sr : 32;
            struct {
                uint8_t toff : 4,     // 0..3
                        hstrt : 3,    // 4..6
                        hend : 4;     // 7..10
                bool fd3 : 1,         // 11
                    disfdcc : 1,      // 12
                    : 1,              // 13
                    chm : 1;          // 14
                uint8_t tbl : 2;      // 15..16
                bool    : 1,          // 17
                        vhighfs : 1,  // 18
                        vhighchm : 1; // 19
                uint8_t tpfd : 4,     // 20..23
                        mres : 4;     // 24..27
                bool    intpol : 1,   // 28
                        dedge : 1,    // 29
                        diss2g : 1,   // 30
                        diss2vs : 1;  // 31
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct CHOPCONF_i {
        uint32_t CHOPCONF() {
            return static_cast<TYPE*>(this)->read(CHOPCONF_t::address);
        }
        void CHOPCONF(uint32_t input) {
            static_cast<TYPE*>(this)->write(CHOPCONF_t::address, input);
        }

        void toff(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.toff = B;       CHOPCONF(r.sr); }
        void hstrt(     const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.hstrt = B;      CHOPCONF(r.sr); }
        void hend(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.hend = B;       CHOPCONF(r.sr); }
        //void fd(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.fd = B;         CHOPCONF(r.sr); }
        void disfdcc(   const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.disfdcc = B;    CHOPCONF(r.sr); }
        void chm(       const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.chm = B;        CHOPCONF(r.sr); }
        void tbl(       const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.tbl = B;        CHOPCONF(r.sr); }
        void vhighfs(   const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vhighfs = B;    CHOPCONF(r.sr); }
        void vhighchm(  const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vhighchm = B;   CHOPCONF(r.sr); }
        void tpfd(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.tpfd = B;       CHOPCONF(r.sr); }
        void mres(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.mres = B;       CHOPCONF(r.sr); }
        void intpol(    const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.intpol = B;     CHOPCONF(r.sr); }
        void dedge(     const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.dedge = B;      CHOPCONF(r.sr); }
        void diss2g(    const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.diss2g = B;     CHOPCONF(r.sr); }
        void diss2vs(   const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.diss2vs = B;    CHOPCONF(r.sr); }

        uint8_t toff    () { return CHOPCONF_t{ CHOPCONF() }.toff;     }
        uint8_t hstrt   () { return CHOPCONF_t{ CHOPCONF() }.hstrt;    }
        uint8_t hend    () { return CHOPCONF_t{ CHOPCONF() }.hend;     }
        //uint8_t fd    () { return CHOPCONF_t{ CHOPCONF() }.fd;       }
        bool disfdcc    () { return CHOPCONF_t{ CHOPCONF() }.disfdcc;  }
        bool chm        () { return CHOPCONF_t{ CHOPCONF() }.chm;      }
        uint8_t tbl     () { return CHOPCONF_t{ CHOPCONF() }.tbl;      }
        bool vhighfs    () { return CHOPCONF_t{ CHOPCONF() }.vhighfs;  }
        bool vhighchm   () { return CHOPCONF_t{ CHOPCONF() }.vhighchm; }
        uint8_t tpfd    () { return CHOPCONF_t{ CHOPCONF() }.tpfd;     }
        uint8_t mres    () { return CHOPCONF_t{ CHOPCONF() }.mres;     }
        bool intpol     () { return CHOPCONF_t{ CHOPCONF() }.intpol;   }
        bool dedge      () { return CHOPCONF_t{ CHOPCONF() }.dedge;    }
        bool diss2g     () { return CHOPCONF_t{ CHOPCONF() }.diss2g;   }
        bool diss2vs    () { return CHOPCONF_t{ CHOPCONF() }.diss2vs;  }
    };

    using TMC2130_n::COOLCONF_t;
    using TMC2130_n::DCCTRL_t;
    using TMC2130_n::DRV_STATUS_t;
    using TMC2130_n::ENCM_CTRL_t;
    using TMC2130_n::LOST_STEPS_t;
    using TMC2130_n::COOLCONF_i;
    using TMC2130_n::DCCTRL_i;
    using TMC2130_n::DRV_STATUS_i;
    using TMC2130_n::ENCM_CTRL_i;
    using TMC2130_n::LOST_STEPS_i;

    // 0x04 R: IOIN
    #pragma pack(push, 1)
    struct IOIN_t {
        constexpr static uint8_t address = 0x04;
        union {
            uint32_t sr;
            struct {
                bool refl_step : 1,
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
    #pragma pack(pop)

    template<typename TYPE>
    struct IOIN_i {
        uint32_t  IOIN() {
            return static_cast<TYPE*>(this)->read(IOIN_t::address);
        }
        bool    refl_step()      { return IOIN_t{ IOIN() }.refl_step; }
        bool    refr_dir()       { return IOIN_t{ IOIN() }.refr_dir; }
        bool    encb_dcen_cfg4() { return IOIN_t{ IOIN() }.encb_dcen_cfg4; }
        bool    enca_dcin_cfg5() { return IOIN_t{ IOIN() }.enca_dcin_cfg5; }
        bool    drv_enn()        { return IOIN_t{ IOIN() }.drv_enn; }
        bool    dco_cfg6()       { return IOIN_t{ IOIN() }.dco_cfg6; }
        uint8_t version()        { return IOIN_t{ IOIN() }.version; }
    };

    // 0x0B W: GLOBAL_SCALER
    struct GLOBAL_SCALER_t {
        constexpr static uint8_t address = 0x0B;
        uint8_t sr;
    };

    template<typename TYPE>
    struct GLOBAL_SCALER_i {
        uint8_t GLOBAL_SCALER() const {
            return r.sr;
        }
        void GLOBAL_SCALER(const uint8_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
    protected:
        GLOBAL_SCALER_t r{};
    };

    // 0x0C R: OFFSET_READ
    struct OFFSET_READ_t {
        constexpr static uint8_t address = 0x0C;
    };

    template<typename TYPE>
    struct OFFSET_READ_i {
        uint16_t OFFSET_READ() {
            return static_cast<TYPE*>(this)->read(OFFSET_READ_t::address);
        }
    };

    // 0x71 R: PWM_SCALE
    #pragma pack(push, 1)
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
    #pragma pack(pop)

    template<typename TYPE>
    struct PWM_SCALE_i {
        uint32_t PWM_SCALE() {
            return static_cast<TYPE*>(this)->read(PWM_SCALE_t::address);
        }
        uint8_t pwm_scale_sum()   { return PWM_SCALE_t{ PWM_SCALE() }.pwm_scale_sum; }
        uint16_t pwm_scale_auto() { return PWM_SCALE_t{ PWM_SCALE() }.pwm_scale_auto; }
    };

    // 0x09 W: SHORT_CONF
    #pragma pack(push, 1)
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
    #pragma pack(pop)

    template<typename TYPE>
    struct SHORT_CONF_i {
        uint32_t SHORT_CONF() const { return r.sr; }
        void SHORT_CONF(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void s2vs_level(const uint8_t B)  { r.s2vs_level;  SHORT_CONF(r.sr); }
        void s2g_level(const uint8_t B)   { r.s2g_level;   SHORT_CONF(r.sr); }
        void shortfilter(const uint8_t B) { r.shortfilter; SHORT_CONF(r.sr); }
        void shortdelay(const bool B)     { r.shortdelay;  SHORT_CONF(r.sr); }
        uint8_t s2vs_level()  const { return r.s2vs_level;  }
        uint8_t s2g_level()   const { return r.s2g_level;   }
        uint8_t shortfilter() const { return r.shortfilter; }
        bool shortdelay()     const { return r.shortdelay;  }
    protected:
        SHORT_CONF_t r{};
    };

    // 0x0A W: DRV_CONF
    #pragma pack(push, 1)
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
    #pragma pack(pop)

    template<typename TYPE>
    struct DRV_CONF_i {
        uint32_t DRV_CONF() const { return r.sr; }
        void DRV_CONF(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void bbmtime(const uint8_t B)     { r.bbmtime = B;        DRV_CONF(r.sr); }
        void bbmclks(const uint8_t B)     { r.bbmclks = B;        DRV_CONF(r.sr); }
        void otselect(const uint8_t B)    { r.otselect = B;       DRV_CONF(r.sr); }
        void drvstrength(const uint8_t B) { r.drvstrength = B;    DRV_CONF(r.sr); }
        void filt_isense(const uint8_t B) { r.filt_isense = B;    DRV_CONF(r.sr); }
        uint8_t bbmtime()     const { return r.bbmtime;     }
        uint8_t bbmclks()     const { return r.bbmclks;     }
        uint8_t otselect()    const { return r.otselect;    }
        uint8_t drvstrength() const { return r.drvstrength; }
        uint8_t filt_isense() const { return r.filt_isense; }
    protected:
        DRV_CONF_t r{};
    };

    // 0x70 W: PWMCONF
    #pragma pack(push, 1)
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
    #pragma pack(pop)

    template<typename TYPE>
    struct PWMCONF_i {
        uint32_t PWMCONF() const {
            return r.sr;
        }
        void PWMCONF(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void pwm_ofs        ( const uint8_t B ) { r.pwm_ofs = B;       PWMCONF(r.sr); }
        void pwm_grad       ( const uint8_t B ) { r.pwm_grad = B;      PWMCONF(r.sr); }
        void pwm_freq       ( const uint8_t B ) { r.pwm_freq = B;      PWMCONF(r.sr); }
        void pwm_autoscale  ( const bool    B ) { r.pwm_autoscale = B; PWMCONF(r.sr); }
        void pwm_autograd   ( const bool    B ) { r.pwm_autograd = B;  PWMCONF(r.sr); }
        void freewheel      ( const uint8_t B ) { r.freewheel = B;     PWMCONF(r.sr); }
        void pwm_reg        ( const uint8_t B ) { r.pwm_reg = B;       PWMCONF(r.sr); }
        void pwm_lim        ( const uint8_t B ) { r.pwm_lim = B;       PWMCONF(r.sr); }

        uint8_t pwm_ofs()       const { return r.pwm_ofs;      }
        uint8_t pwm_grad()      const { return r.pwm_grad;     }
        uint8_t pwm_freq()      const { return r.pwm_freq;     }
        bool    pwm_autoscale() const { return r.pwm_autoscale;}
        bool    pwm_autograd()  const { return r.pwm_autograd; }
        uint8_t freewheel()     const { return r.freewheel;    }
        uint8_t pwm_reg()       const { return r.pwm_reg;      }
        uint8_t pwm_lim()       const { return r.pwm_lim;      }
    protected:
        PWMCONF_t r{};
    };
}
