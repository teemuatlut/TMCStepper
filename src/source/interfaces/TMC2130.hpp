
#pragma once

#include "../../TMCStepper.h"

namespace TMC2130_n {
    // 0x00 RW: GCONF
    #pragma pack(push, 1)
    struct GCONF_t {
        GCONF_t(const uint32_t data) : sr(data) {};
        constexpr static uint8_t address = 0x00;
        union {
            uint32_t sr : 18;
            struct {
                bool  i_scale_analog : 1, // 2130, 5130
                internal_rsense : 1, // 2130, 5130
                en_pwm_mode : 1,
                enc_commutation : 1, // 2130, 5130
                shaft : 1,
                diag0_error : 1,
                diag0_otpw : 1,
                diag0_stall : 1,
                diag1_stall : 1,
                diag1_index : 1,
                diag1_onstate : 1,
                diag1_steps_skipped : 1,
                diag0_int_pushpull : 1,
                diag1_pushpull : 1,
                small_hysteresis : 1,
                stop_enable : 1,
                direct_mode : 1;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct GCONF_i {
        uint32_t GCONF() {
            return static_cast<TYPE*>(this)->read(GCONF_t::address);
        }
        void GCONF(const uint32_t input) {
            static_cast<TYPE*>(this)->write(GCONF_t::address, input);
        }

        void I_scale_analog(const bool B)         { GCONF_t r{ GCONF() }; r.i_scale_analog = B;         GCONF(r.sr); }
        void internal_Rsense(const bool B)        { GCONF_t r{ GCONF() }; r.internal_rsense = B;        GCONF(r.sr); }
        void en_pwm_mode(const bool B)            { GCONF_t r{ GCONF() }; r.en_pwm_mode = B;            GCONF(r.sr); }
        void enc_commutation(const bool B)        { GCONF_t r{ GCONF() }; r.enc_commutation = B;        GCONF(r.sr); }
        void shaft(const bool B)                  { GCONF_t r{ GCONF() }; r.shaft = B;                  GCONF(r.sr); }
        void diag0_error(const bool B)            { GCONF_t r{ GCONF() }; r.diag0_error = B;            GCONF(r.sr); }
        void diag0_otpw(const bool B)             { GCONF_t r{ GCONF() }; r.diag0_otpw = B;             GCONF(r.sr); }
        void diag0_stall(const bool B)            { GCONF_t r{ GCONF() }; r.diag0_stall = B;            GCONF(r.sr); }
        void diag1_stall(const bool B)            { GCONF_t r{ GCONF() }; r.diag1_stall = B;            GCONF(r.sr); }
        void diag1_index(const bool B)            { GCONF_t r{ GCONF() }; r.diag1_index = B;            GCONF(r.sr); }
        void diag1_onstate(const bool B)          { GCONF_t r{ GCONF() }; r.diag1_onstate = B;          GCONF(r.sr); }
        void diag1_steps_skipped(const bool B)    { GCONF_t r{ GCONF() }; r.diag1_steps_skipped = B;    GCONF(r.sr); }
        void diag0_int_pushpull(const bool B)     { GCONF_t r{ GCONF() }; r.diag0_int_pushpull = B;     GCONF(r.sr); }
        void diag1_pushpull(const bool B)         { GCONF_t r{ GCONF() }; r.diag1_pushpull = B;         GCONF(r.sr); }
        void small_hysteresis(const bool B)       { GCONF_t r{ GCONF() }; r.small_hysteresis = B;       GCONF(r.sr); }
        void stop_enable(const bool B)            { GCONF_t r{ GCONF() }; r.stop_enable = B;            GCONF(r.sr); }
        void direct_mode(const bool B)            { GCONF_t r{ GCONF() }; r.direct_mode = B;            GCONF(r.sr); }

        bool I_scale_analog()               { return GCONF_t{ GCONF() }.i_scale_analog;         }
        bool internal_Rsense()              { return GCONF_t{ GCONF() }.internal_rsense;        }
        bool en_pwm_mode()                  { return GCONF_t{ GCONF() }.en_pwm_mode;            }
        bool enc_commutation()              { return GCONF_t{ GCONF() }.enc_commutation;        }
        bool shaft()                        { return GCONF_t{ GCONF() }.shaft;                  }
        bool diag0_error()                  { return GCONF_t{ GCONF() }.diag0_error;            }
        bool diag0_otpw()                   { return GCONF_t{ GCONF() }.diag0_otpw;             }
        bool diag0_stall()                  { return GCONF_t{ GCONF() }.diag0_stall;            }
        bool diag1_stall()                  { return GCONF_t{ GCONF() }.diag1_stall;            }
        bool diag1_index()                  { return GCONF_t{ GCONF() }.diag1_index;            }
        bool diag1_onstate()                { return GCONF_t{ GCONF() }.diag1_onstate;          }
        bool diag1_steps_skipped()          { return GCONF_t{ GCONF() }.diag1_steps_skipped;    }
        bool diag0_int_pushpull()           { return GCONF_t{ GCONF() }.diag0_int_pushpull;     }
        bool diag1_pushpull()               { return GCONF_t{ GCONF() }.diag1_pushpull;         }
        bool small_hysteresis()             { return GCONF_t{ GCONF() }.small_hysteresis;       }
        bool stop_enable()                  { return GCONF_t{ GCONF() }.stop_enable;            }
        bool direct_mode()                  { return GCONF_t{ GCONF() }.direct_mode;            }
    };

    // 0x01 R+C: GSTAT
    #pragma pack(push, 1)
    struct GSTAT_t {
        constexpr static uint8_t address = 0x01;
        union {
            uint8_t sr : 3;
            struct {
                bool reset : 1,
                        drv_err : 1,
                        uv_cp : 1;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct GSTAT_i {
        uint8_t GSTAT()     { return static_cast<TYPE*>(this)->read(GSTAT_t::address); }
        void GSTAT(uint8_t) { static_cast<TYPE*>(this)->write(GSTAT_t::address, 0b111); }
        bool reset()        { GSTAT_t r{ GSTAT() }; return r.reset; }
        bool drv_err()      { GSTAT_t r{ GSTAT() }; return r.drv_err; }
        bool uv_cp()        { GSTAT_t r{ GSTAT() }; return r.uv_cp; }
    };

    // 0x04 R: IOIN
    #pragma pack(push, 1)
    struct IOIN_t {
        constexpr static uint8_t address = 0x04;
        union {
            uint32_t sr;
            struct {
                bool    step : 1,
                        dir : 1,
                        dcen_cfg4 : 1,
                        dcin_cfg5 : 1,
                        drv_enn_cfg6 : 1,
                        dco : 1,
                            : 2;
                uint16_t : 16;
                uint8_t version : 8;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct IOIN_i {
        uint32_t IOIN()     { return static_cast<TYPE*>(this)->read(IOIN_t::address); }
        bool step()         { IOIN_t r{ IOIN() }; return r.step; }
        bool dir()          { IOIN_t r{ IOIN() }; return r.dir; }
        bool dcen_cfg4()    { IOIN_t r{ IOIN() }; return r.dcen_cfg4; }
        bool dcin_cfg5()    { IOIN_t r{ IOIN() }; return r.dcin_cfg5; }
        bool drv_enn_cfg6() { IOIN_t r{ IOIN() }; return r.drv_enn_cfg6; }
        bool dco()          { IOIN_t r{ IOIN() }; return r.dco; }
        uint8_t version()   { IOIN_t r{ IOIN() }; return r.version; }
    };

    // 0x10 W: IHOLD_IRUN
    #pragma pack(push, 1)
    struct IHOLD_IRUN_t {
        constexpr static uint8_t address = 0x10;
        union {
            uint32_t sr : 20;
            struct {
                uint8_t ihold : 5,
                        : 3,
                        irun : 5,
                        : 3,
                        iholddelay : 4;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct IHOLD_IRUN_i {
        uint32_t IHOLD_IRUN() const {
            return r.sr;
        }
        void IHOLD_IRUN(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void ihold(const uint8_t B) {
            r.ihold = B;
            IHOLD_IRUN(r.sr);
        }
        void irun(const uint8_t B) {
            r.irun = B;
            IHOLD_IRUN(r.sr);
        }
        void iholddelay(const uint8_t B) {
            r.iholddelay = B;
            IHOLD_IRUN(r.sr);
        }

        uint8_t ihold() const {
            return r.ihold;
        }
        uint8_t irun() const {
            return r.irun;
        }
        uint8_t iholddelay() const {
            return r.iholddelay;
        }

        protected:
            IHOLD_IRUN_t r{};
    };

    // 0x11 W: TPOWERDOWN
    struct TPOWERDOWN_t {
        constexpr static uint8_t address = 0x11;
        uint8_t sr : 8;
    };

    template<typename TYPE>
    struct TPOWERDOWN_i {
        uint8_t TPOWERDOWN() const { return r.sr; }
        void TPOWERDOWN(const uint8_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        TPOWERDOWN_t r{};
    };

    // 0x12 R: TSTEP
    struct TSTEP_t {
        constexpr static uint8_t address = 0x12;
    };

    template<typename TYPE>
    struct TSTEP_i {
        uint32_t TSTEP() {
            return static_cast<TYPE*>(this)->read(TSTEP_t::address);
        }
    };

    // 0x13 W: TPWMTHRS
    struct TPWMTHRS_t {
        constexpr static uint8_t address = 0x13;
        uint32_t sr : 20;
    };

    template<typename TYPE>
    struct TPWMTHRS_i {
        uint8_t TPWMTHRS() const { return r.sr; }
        void TPWMTHRS(const uint8_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        TPWMTHRS_t r{};
    };

    // 0x14 W: TCOOLTHRS
    struct TCOOLTHRS_t {
        constexpr static uint8_t address = 0x14;
        uint32_t sr : 20;
    };

    template<typename TYPE>
    struct TCOOLTHRS_i  {
        uint32_t TCOOLTHRS() const { return r.sr; }
        void TCOOLTHRS(const uint32_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        TCOOLTHRS_t r{};
    };

    // 0x15 W: THIGH
    struct THIGH_t {
        constexpr static uint8_t address = 0x15;
        uint32_t sr : 20;
    };

    template<typename TYPE>
    struct THIGH_i {
        uint32_t THIGH() const { return r.sr; }
        void THIGH(const uint32_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        THIGH_t r{};
    };

    // 0x2D RW: XDIRECT
    #pragma pack(push, 1)
    struct XDIRECT_t {
        XDIRECT_t(const uint32_t data) : sr(data) {};
        constexpr static uint8_t address = 0x2D;
        union {
            uint32_t sr : 25;
            struct {
                int16_t coil_A : 9,
                                : 7;
                int16_t coil_B : 9;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct XDIRECT_i {
        uint32_t XDIRECT() {
            return static_cast<TYPE*>(this)->read(XDIRECT_t::address);
        }
        void XDIRECT(const uint32_t input) {
            static_cast<TYPE*>(this)->write(XDIRECT_t::address, input);
        }
        void coil_A(const int16_t B)  { XDIRECT_t r{ XDIRECT() }; r.coil_A = B; XDIRECT(r.sr); }
        void coil_B(const int16_t B)  { XDIRECT_t r{ XDIRECT() }; r.coil_B = B; XDIRECT(r.sr); }
        int16_t coil_A()        { return XDIRECT_t{ XDIRECT() }.coil_A; }
        int16_t coil_B()        { return XDIRECT_t{ XDIRECT() }.coil_B; }
    };

    // 0x15 W: VDCMIN
    struct VDCMIN_t {
        constexpr static uint8_t address = 0x33;
        uint32_t sr : 23;
    };

    template<typename TYPE>
    struct VDCMIN_i {
        uint32_t VDCMIN() const { return r.sr; }
        void VDCMIN(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        VDCMIN_t r{};
    };

    struct MSLUT0_t {
        constexpr static uint8_t address = 0x60;
    };
    template<typename TYPE>
    struct MSLUT0_i {
        void MSLUT0(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT0_t::address, input);
        }
    };

    struct MSLUT1_t {
        constexpr static uint8_t address = 0x61;
    };
    template<typename TYPE>
    struct MSLUT1_i {
        void MSLUT1(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT1_t::address, input);
        }
    };

    struct MSLUT2_t {
        constexpr static uint8_t address = 0x62;
    };
    template<typename TYPE>
    struct MSLUT2_i {
        void MSLUT2(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT2_t::address, input);
        }
    };

    struct MSLUT3_t {
        constexpr static uint8_t address = 0x63;
    };
    template<typename TYPE>
    struct MSLUT3_i {
        void MSLUT3(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT3_t::address, input);
        }
    };

    struct MSLUT4_t {
        constexpr static uint8_t address = 0x64;
    };
    template<typename TYPE>
    struct MSLUT4_i {
        void MSLUT4(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT4_t::address, input);
        }
    };

    struct MSLUT5_t {
        constexpr static uint8_t address = 0x65;
    };
    template<typename TYPE>
    struct MSLUT5_i {
        void MSLUT5(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT5_t::address, input);
        }
    };

    struct MSLUT6_t {
        constexpr static uint8_t address = 0x66;
    };
    template<typename TYPE>
    struct MSLUT6_i {
        void MSLUT6(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT6_t::address, input);
        }
    };

    struct MSLUT7_t {
        constexpr static uint8_t address = 0x67;
    };
    template<typename TYPE>
    struct MSLUT7_i {
        void MSLUT7(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUT7_t::address, input);
        }
    };

    // 0x68 W: MSLUTSEL
    #pragma pack(push, 1)
    struct MSLUTSEL_t {
        constexpr static uint8_t address = 0x68;
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
    #pragma pack(pop)

    template<typename TYPE>
    struct MSLUTSEL_i {
        uint32_t MSLUTSEL() const {
            return r.sr;
        }
        void MSLUTSEL(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUTSEL_t::address, input);
        }
        protected:
            MSLUTSEL_t r{};
    };

    // 0x69 W: MSLUTSTART
    #pragma pack(push, 1)
    struct MSLUTSTART_t {
        constexpr static uint8_t address = 0x69;
        union {
            uint32_t sr : 24;
            struct {
                uint8_t start_sin : 8,
                                    : 8,
                        start_sin90 : 8;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct MSLUTSTART_i {
        uint32_t MSLUTSTART() const {
            return r.sr;
        }
        void MSLUTSTART(const uint32_t input) {
            static_cast<TYPE*>(this)->write(MSLUTSTART_t::address, input);
        }
        protected:
            MSLUTSTART_t r{{247ul<<16 | 0}};
    };

    // 0x6A R: MSCNT
    struct MSCNT_t { constexpr static uint8_t address = 0x6A; };

    template<typename TYPE>
    struct MSCNT_i {
        uint16_t MSCNT() {
            return static_cast<TYPE*>(this)->read(MSCNT_t::address);
        }
    };

    // 0x6B R: MSCURACT
    #pragma pack(push, 1)
    struct MSCURACT_t {
        MSCURACT_t(const uint32_t initValue) : sr(initValue) {}
        constexpr static uint8_t address = 0x6B;
        union {
            uint32_t sr : 25;
            struct {
                int16_t cur_a : 9,
                        : 7,
                        cur_b : 9;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct MSCURACT_i {
        uint32_t MSCURACT() {
            return static_cast<TYPE*>(this)->read(MSCURACT_t::address);
        }
        int16_t cur_a() {
            MSCURACT_t r{ MSCURACT() };
            int16_t value = r.cur_a;
            if (value > 255) value -= 512;
            return value;
        }
        int16_t cur_b() {
            MSCURACT_t r{ MSCURACT() };
            int16_t value = r.cur_b;
            if (value > 255) value -= 512;
            return value;
        }
    };

    // 0x6C RW: CHOPCONF
    #pragma pack(push, 1)
    struct CHOPCONF_t {
        CHOPCONF_t(const uint32_t initValue) : sr(initValue) {}
        constexpr static uint8_t address = 0x6C;
        union {
            uint32_t sr : 32;
            struct {
                uint8_t toff : 4,
                        hstrt : 3,
                        hend : 4,
                        : 1;
                bool    disfdcc : 1,
                        rndtf : 1,
                        chm : 1;
                uint8_t tbl : 2;
                bool    vsense : 1,
                        vhighfs : 1,
                        vhighchm : 1;
                uint8_t sync : 4,
                        mres : 4;
                bool    intpol : 1,
                        dedge : 1,
                        diss2g : 1;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct CHOPCONF_i {
        uint32_t CHOPCONF() {
            return static_cast<TYPE*>(this)->read(CHOPCONF_t::address);
        }
        void CHOPCONF(const uint32_t input) {
            static_cast<TYPE*>(this)->write(CHOPCONF_t::address, input);
        }

        /**
         * @brief Enable driver and set off time for spreadcycle
         * @param B Off time value
         */
        void toff(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.toff = B;       CHOPCONF(r.sr); }
        void hstrt(     const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.hstrt = B;      CHOPCONF(r.sr); }
        void hend(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.hend = B;       CHOPCONF(r.sr); }
        //void fd(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.fd = B;         CHOPCONF(r.sr); }
        void disfdcc(   const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.disfdcc = B;    CHOPCONF(r.sr); }
        void rndtf(     const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.rndtf = B;      CHOPCONF(r.sr); }
        void chm(       const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.chm = B;        CHOPCONF(r.sr); }
        void tbl(       const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.tbl = B;        CHOPCONF(r.sr); }
        void vsense(    const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vsense = B;     CHOPCONF(r.sr); }
        void vhighfs(   const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vhighfs = B;    CHOPCONF(r.sr); }
        void vhighchm(  const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vhighchm = B;   CHOPCONF(r.sr); }
        void sync(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.sync = B;       CHOPCONF(r.sr); }
        void mres(      const uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.mres = B;       CHOPCONF(r.sr); }
        void intpol(    const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.intpol = B;     CHOPCONF(r.sr); }
        void dedge(     const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.dedge = B;      CHOPCONF(r.sr); }
        void diss2g(    const bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.diss2g = B;     CHOPCONF(r.sr); }

        /**
         * @brief Get off time value
         * @returns Off time value
         */
        uint8_t toff()      { return CHOPCONF_t{ CHOPCONF() }.toff;     }
        uint8_t hstrt()     { return CHOPCONF_t{ CHOPCONF() }.hstrt;    }
        uint8_t hend()      { return CHOPCONF_t{ CHOPCONF() }.hend;     }
        //uint8_t fd()      { return CHOPCONF_t{ CHOPCONF() }.fd;       }
        bool    disfdcc()   { return CHOPCONF_t{ CHOPCONF() }.disfdcc;  }
        bool    rndtf()     { return CHOPCONF_t{ CHOPCONF() }.rndtf;    }
        bool    chm()       { return CHOPCONF_t{ CHOPCONF() }.chm;      }
        uint8_t tbl()       { return CHOPCONF_t{ CHOPCONF() }.tbl;      }
        bool    vsense()    { return CHOPCONF_t{ CHOPCONF() }.vsense;   }
        bool    vhighfs()   { return CHOPCONF_t{ CHOPCONF() }.vhighfs;  }
        bool    vhighchm()  { return CHOPCONF_t{ CHOPCONF() }.vhighchm; }
        uint8_t sync()      { return CHOPCONF_t{ CHOPCONF() }.sync;     }
        uint8_t mres()      { return CHOPCONF_t{ CHOPCONF() }.mres;     }
        bool    intpol()    { return CHOPCONF_t{ CHOPCONF() }.intpol;   }
        bool    dedge()     { return CHOPCONF_t{ CHOPCONF() }.dedge;    }
        bool    diss2g()    { return CHOPCONF_t{ CHOPCONF() }.diss2g;   }
    };

    // 0x6D W: COOLCONF
    #pragma pack(push, 1)
    struct COOLCONF_t {
        constexpr static uint8_t address = 0x6D;
        union {
            uint32_t sr : 25;
            struct {
                uint8_t semin : 4,
                        : 1,
                        seup : 2,
                        : 1,
                        semax : 4,
                        : 1,
                        sedn : 2;
                bool    seimin : 1;
                int8_t  sgt : 7,
                        : 1;
                bool    sfilt : 1;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct COOLCONF_i {
        uint32_t COOLCONF() const { return r.sr; }
        void COOLCONF(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void semin( const uint8_t B ) { r.semin = B;  COOLCONF(r.sr); }
        void seup(  const uint8_t B ) { r.seup = B;   COOLCONF(r.sr); }
        void semax( const uint8_t B ) { r.semax = B;  COOLCONF(r.sr); }
        void sedn(  const uint8_t B ) { r.sedn = B;   COOLCONF(r.sr); }
        void seimin(const bool    B ) { r.seimin = B; COOLCONF(r.sr); }
        void sgt(   const int8_t  B ) { r.sgt = B;    COOLCONF(r.sr); }
        void sfilt( const bool    B ) { r.sfilt = B;  COOLCONF(r.sr); }

        uint8_t semin()  const { return r.semin;   }
        uint8_t seup()   const { return r.seup;    }
        uint8_t semax()  const { return r.semax;   }
        uint8_t sedn()   const { return r.sedn;    }
        bool    seimin() const { return r.seimin;  }
        bool    sfilt()  const { return r.sfilt;   }

        int8_t sgt() const {
            // Two's complement in a 7bit value
            int8_t val = (r.sgt &  0x40) << 1; // Isolate sign bit
            val |= r.sgt & 0x7F;
            return val;
        }

    protected:
        COOLCONF_t r{};
    };

    // 0x6E W: DCCTRL
    #pragma pack(push, 1)
    struct DCCTRL_t {
        constexpr static uint8_t address = 0x6E;
        union {
            uint32_t sr : 24;
            struct {
                uint16_t dc_time : 10,
                : 6;
                uint8_t dc_sg : 8;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct DCCTRL_i {
        void DCCTRL(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
        void dc_time(const uint16_t input) {
            r.dc_time = input;
            DCCTRL(r.sr);
        }
        void dc_sg(const uint8_t input) {
            r.dc_sg = input;
            DCCTRL(r.sr);
        }

        uint32_t DCCTRL() {
            return static_cast<TYPE*>(this)->read(r.address);
        }
        uint16_t dc_time() {
            return DCCTRL_t{ DCCTRL() }.dc_time;
        }
        uint8_t dc_sg() {
            return DCCTRL_t{ DCCTRL() }.dc_sg;
        }

    protected:
        DCCTRL_t r{};
    };

    // 0x6F R: DRV_STATUS
    #pragma pack(push, 1)
    struct DRV_STATUS_t {
        constexpr static uint8_t address = 0x6F;
        union {
            uint32_t sr;
            struct {
                uint16_t sg_result : 10;
                uint8_t            : 5;
                bool fsactive : 1;
                uint8_t cs_actual : 5,
                        : 3;
                bool    stallguard : 1,
                        ot : 1,
                        otpw : 1,
                        s2ga : 1,
                        s2gb : 1,
                        ola : 1,
                        olb : 1,
                        stst : 1;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct DRV_STATUS_i {
        uint32_t DRV_STATUS() {
            return static_cast<TYPE*>(this)->read(DRV_STATUS_t::address);
        }

        uint16_t sg_result(){ return DRV_STATUS_t{ DRV_STATUS() }.sg_result; }
        bool fsactive()     { return DRV_STATUS_t{ DRV_STATUS() }.fsactive;  }
        uint8_t cs_actual() { return DRV_STATUS_t{ DRV_STATUS() }.cs_actual; }
        bool stallguard()   { return DRV_STATUS_t{ DRV_STATUS() }.stallguard;}
        bool ot()           { return DRV_STATUS_t{ DRV_STATUS() }.ot;        }
        bool otpw()         { return DRV_STATUS_t{ DRV_STATUS() }.otpw;      }
        bool s2ga()         { return DRV_STATUS_t{ DRV_STATUS() }.s2ga;      }
        bool s2gb()         { return DRV_STATUS_t{ DRV_STATUS() }.s2gb;      }
        bool ola()          { return DRV_STATUS_t{ DRV_STATUS() }.ola;       }
        bool olb()          { return DRV_STATUS_t{ DRV_STATUS() }.olb;       }
        bool stst()         { return DRV_STATUS_t{ DRV_STATUS() }.stst;      }    
    };

    // 0x70 W: PWMCONF
    #pragma pack(push, 1)
    struct PWMCONF_t {
        constexpr static uint8_t address = 0x70;
        union {
            uint32_t sr : 22;
            struct {
                uint8_t pwm_ampl : 8,
                        pwm_grad : 8,
                        pwm_freq : 2;
                bool pwm_autoscale : 1,
                        pwm_symmetric : 1;
                uint8_t freewheel : 2;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct PWMCONF_i {
        uint32_t PWMCONF() const { return r.sr; }
        void PWMCONF(const uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void pwm_ampl(      const uint8_t B ) { r.pwm_ampl = B;        PWMCONF(r.sr); }
        void pwm_grad(      const uint8_t B ) { r.pwm_grad = B;        PWMCONF(r.sr); }
        void pwm_freq(      const uint8_t B ) { r.pwm_freq = B;        PWMCONF(r.sr); }
        void pwm_autoscale( const bool    B ) { r.pwm_autoscale = B;   PWMCONF(r.sr); }
        void pwm_symmetric( const bool    B ) { r.pwm_symmetric = B;   PWMCONF(r.sr); }
        void freewheel(     const uint8_t B ) { r.freewheel = B;       PWMCONF(r.sr); }

        uint8_t pwm_ampl()      const { return r.pwm_ampl;     }
        uint8_t pwm_grad()      const { return r.pwm_grad;     }
        uint8_t pwm_freq()      const { return r.pwm_freq;     }
        bool    pwm_autoscale() const { return r.pwm_autoscale;}
        bool    pwm_symmetric() const { return r.pwm_symmetric;}
        uint8_t freewheel()     const { return r.freewheel;    }

    protected:
        PWMCONF_t r{{0x00050480}};
    };

    // 0x71 R: PWM_SCALE
    struct PWM_SCALE_t  { constexpr static uint8_t address = 0x71; };

    template<typename TYPE>
    struct PWM_SCALE_i {
        uint8_t PWM_SCALE() { return static_cast<TYPE*>(this)->read(PWM_SCALE_t::address); }
    };

    // 0x72 W: ENCM_CTRL
    #pragma pack(push, 1)
    struct ENCM_CTRL_t {
        constexpr static uint8_t address = 0x72;
        union {
            uint8_t sr : 2;
            struct {
                bool inv : 1,
                        maxspeed : 1;
            };
        };
    };
    #pragma pack(pop)

    template<typename TYPE>
    struct ENCM_CTRL_i {
        uint8_t ENCM_CTRL() const { return r.sr; }
        void ENCM_CTRL(uint8_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
        void inv(const bool B)      { r.inv = B;       ENCM_CTRL(r.sr); }
        void maxspeed(const bool B) { r.maxspeed  = B; ENCM_CTRL(r.sr); }
        bool inv()            const { return r.inv; }
        bool maxspeed()       const { return r.maxspeed; }

    protected:
        ENCM_CTRL_t r{};
    };

    // 0x73 R: LOST_STEPS
    struct LOST_STEPS_t { constexpr static uint8_t address = 0x73; };

    template<typename TYPE>
    struct LOST_STEPS_i {
        uint32_t LOST_STEPS() {
            return static_cast<TYPE*>(this)->read(LOST_STEPS_t::address);
        }
    };
}
