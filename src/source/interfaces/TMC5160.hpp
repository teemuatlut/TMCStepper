
#pragma once

namespace TMC5160_n {

    // 0x00 RW: GCONF
    template<typename TYPE>
    struct GCONF_i {
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
                struct { // TMC5160
                bool recalibrate : 1,
                    faststandstill : 1,
                    : 1,
                    multistep_filt : 1,
                    : 3,
                    diag0_step : 1,
                    diag1_dir : 1,
                    : 4,
                    diag1_poscomp_pushpull : 1;
                };
            };
        };

        // 0x6C RW: CHOPCONF
        template<typename TYPE>
        struct CHOPCONF_i {
            struct CHOPCONF_t {
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
                    struct { // TMC5160
                        uint32_t     : 20;
                        uint8_t tpfd : 4; // 5160
                        uint16_t     : 7;
                        bool diss2vs : 1; // TMC5160 only
                    };
                };
            };

            uint32_t CHOPCONF() {
                return static_cast<TYPE*>(this)->read(CHOPCONF_t::address);
            }
            void CHOPCONF(uint32_t input) {
                static_cast<TYPE*>(this)->write(CHOPCONF_t::address, input);
            }

            void toff(      uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.toff = B;       CHOPCONF(r.sr); }
            void hstrt(     uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.hstrt = B;      CHOPCONF(r.sr); }
            void hend(      uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.hend = B;       CHOPCONF(r.sr); }
            //void fd(      uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.fd = B;         CHOPCONF(r.sr); }
            void disfdcc(   bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.disfdcc = B;    CHOPCONF(r.sr); }
            void rndtf(     bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.rndtf = B;      CHOPCONF(r.sr); }
            void chm(       bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.chm = B;        CHOPCONF(r.sr); }
            void tbl(       uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.tbl = B;        CHOPCONF(r.sr); }
            void vsense(    bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vsense = B;     CHOPCONF(r.sr); }
            void vhighfs(   bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vhighfs = B;    CHOPCONF(r.sr); }
            void vhighchm(  bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.vhighchm = B;   CHOPCONF(r.sr); }
            void sync(      uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.sync = B;       CHOPCONF(r.sr); }
            void mres(      uint8_t B ) { CHOPCONF_t r{ CHOPCONF() }; r.mres = B;       CHOPCONF(r.sr); }
            void intpol(    bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.intpol = B;     CHOPCONF(r.sr); }
            void dedge(     bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.dedge = B;      CHOPCONF(r.sr); }
            void diss2g(    bool    B ) { CHOPCONF_t r{ CHOPCONF() }; r.diss2g = B;     CHOPCONF(r.sr); }

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

}
