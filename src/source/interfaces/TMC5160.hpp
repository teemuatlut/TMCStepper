
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
                    bool    recalibrate : 1, // 2130, 5130
                            faststandstill : 1, // 2130, 5130
                            en_pwm_mode : 1,
                            multistep_filt : 1, // 2130, 5130
                            shaft : 1,
                            diag0_error : 1,
                            diag0_otpw : 1;
                    union {
                        bool diag0_stall : 1,
                             diag0_step :1;
                    };
                    union {
                        bool diag1_stall : 1,
                             diag1_dir : 1;
                    };
                    bool    diag1_index : 1,
                            diag1_onstate : 1,
                            diag1_steps_skipped : 1,
                            diag0_int_pushpull : 1,
                            diag1_poscomp_pushpull : 1,
                            small_hysteresis : 1,
                            stop_enable : 1,
                            direct_mode : 1;
                };
            };
        };

        void GCONF(uint32_t input) {
            static_cast<TYPE*>(this)->write(GCONF_t::address, input);
        }
        void recalibrate(bool B)            { GCONF_t r{ GCONF() }; r.recalibrate = B;            GCONF(r.sr); }
        void faststandstill(bool B)         { GCONF_t r{ GCONF() }; r.faststandstill = B;         GCONF(r.sr); }
        void en_pwm_mode(bool B)            { GCONF_t r{ GCONF() }; r.en_pwm_mode = B;            GCONF(r.sr); }
        void multistep_filt(bool B)         { GCONF_t r{ GCONF() }; r.multistep_filt = B;         GCONF(r.sr); }
        void shaft(bool B)                  { GCONF_t r{ GCONF() }; r.shaft = B;                  GCONF(r.sr); }
        void diag0_error(bool B)            { GCONF_t r{ GCONF() }; r.diag0_error = B;            GCONF(r.sr); }
        void diag0_otpw(bool B)             { GCONF_t r{ GCONF() }; r.diag0_otpw = B;             GCONF(r.sr); }
        void diag0_stall(bool B)            { GCONF_t r{ GCONF() }; r.diag0_stall = B;            GCONF(r.sr); }
        void diag1_stall(bool B)            { GCONF_t r{ GCONF() }; r.diag1_stall = B;            GCONF(r.sr); }
        void diag1_index(bool B)            { GCONF_t r{ GCONF() }; r.diag1_index = B;            GCONF(r.sr); }
        void diag1_onstate(bool B)          { GCONF_t r{ GCONF() }; r.diag1_onstate = B;          GCONF(r.sr); }
        void diag1_steps_skipped(bool B)    { GCONF_t r{ GCONF() }; r.diag1_steps_skipped = B;    GCONF(r.sr); }
        void diag0_int_pushpull(bool B)     { GCONF_t r{ GCONF() }; r.diag0_int_pushpull = B;     GCONF(r.sr); }
        void diag1_pushpull(bool B)         { GCONF_t r{ GCONF() }; r.diag1_poscomp_pushpull = B; GCONF(r.sr); }
        void small_hysteresis(bool B)       { GCONF_t r{ GCONF() }; r.small_hysteresis = B;       GCONF(r.sr); }
        void stop_enable(bool B)            { GCONF_t r{ GCONF() }; r.stop_enable = B;            GCONF(r.sr); }
        void direct_mode(bool B)            { GCONF_t r{ GCONF() }; r.direct_mode = B;            GCONF(r.sr); }

        uint32_t GCONF() {
            return static_cast<TYPE*>(this)->read(GCONF_t::address);
        }
        bool recalibrate()                  { return GCONF_t{ GCONF() }.recalibrate;            }
        bool faststandstill()               { return GCONF_t{ GCONF() }.faststandstill;         }
        bool en_pwm_mode()                  { return GCONF_t{ GCONF() }.en_pwm_mode;            }
        bool multistep_filt()               { return GCONF_t{ GCONF() }.multistep_filt;         }
        bool shaft()                        { return GCONF_t{ GCONF() }.shaft;                  }
        bool diag0_error()                  { return GCONF_t{ GCONF() }.diag0_error;            }
        bool diag0_otpw()                   { return GCONF_t{ GCONF() }.diag0_otpw;             }
        bool diag0_stall()                  { return GCONF_t{ GCONF() }.diag0_stall;            }
        bool diag1_stall()                  { return GCONF_t{ GCONF() }.diag1_stall;            }
        bool diag1_index()                  { return GCONF_t{ GCONF() }.diag1_index;            }
        bool diag1_onstate()                { return GCONF_t{ GCONF() }.diag1_onstate;          }
        bool diag1_steps_skipped()          { return GCONF_t{ GCONF() }.diag1_steps_skipped;    }
        bool diag0_int_pushpull()           { return GCONF_t{ GCONF() }.diag0_int_pushpull;     }
        bool diag1_pushpull()               { return GCONF_t{ GCONF() }.diag1_poscomp_pushpull; }
        bool small_hysteresis()             { return GCONF_t{ GCONF() }.small_hysteresis;       }
        bool stop_enable()                  { return GCONF_t{ GCONF() }.stop_enable;            }
        bool direct_mode()                  { return GCONF_t{ GCONF() }.direct_mode;            }
    };

    using TMC2130_n::GSTAT_i;
    using TMC2208_n::IFCNT_i;

    // 0x03 W: SLAVECONF
    template<typename TYPE>
    struct SLAVECONF_i {
        #pragma pack(push, 1)
        struct SLAVECONF_t {
            constexpr static uint8_t address = 0x03;
            union {
                uint16_t sr : 12;
                struct {
                    uint8_t slaveaddr : 8;
                    uint8_t senddelay : 4;
                };
            };
        };
        #pragma pack(pop)

        void SLAVECONF(uint16_t input) {
            r.sr = input&0xF00;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
        uint16_t SLAVECONF() {
            return r.sr;
        }
        void senddelay(uint8_t B) {
            r.senddelay = B; SLAVECONF(r.sr);
        }
        uint8_t senddelay() {
            return r.senddelay;
        }
    protected:
        SLAVECONF_t r;
    };
    
    template<typename TYPE>
    struct IOIN_i {
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
                         enc_n_dco_cfg6 : 1,
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
        bool    drv_enn()        { return IOIN_t{ IOIN() }.drv_enn; }
        bool    enc_n_dco_cfg6() { return IOIN_t{ IOIN() }.enc_n_dco_cfg6; }
        bool    sd_mode()        { return IOIN_t{ IOIN() }.sd_mode; }
        bool    swcomp_in()      { return IOIN_t{ IOIN() }.swcomp_in; }
        uint8_t version()        { return IOIN_t{ IOIN() }.version; }
    };

    using TMC5130_n::OUTPUT_i;
    using TMC5130_n::X_COMPARE_i;
    using TMC2208_n::OTP_PROG_i;
    using TMC2208_n::OTP_READ_i;
    using TMC2208_n::FACTORY_CONF_i;
    using TMC2160_n::SHORT_CONF_i;
    using TMC2160_n::DRV_CONF_i;
    using TMC2160_n::GLOBAL_SCALER_i;
    using TMC2160_n::OFFSET_READ_i;
    using TMC2130_n::IHOLD_IRUN_i;
    using TMC2130_n::TPOWERDOWN_i;
    using TMC2130_n::TSTEP_i;
    using TMC2130_n::TPWMTHRS_i;
    using TMC2130_n::TCOOLTHRS_i;
    using TMC2130_n::THIGH_i;
    using TMC5130_n::RAMPMODE_i;
    using TMC5130_n::XACTUAL_i;
    using TMC5130_n::VACTUAL_i;
    using TMC5130_n::VSTART_i;
    using TMC5130_n::A1_i;
    using TMC5130_n::V1_i;
    using TMC5130_n::AMAX_i;
    using TMC5130_n::VMAX_i;
    using TMC5130_n::DMAX_i;
    using TMC5130_n::D1_i;
    using TMC5130_n::VSTOP_i;
    using TMC5130_n::TZEROWAIT_i;
    using TMC5130_n::XTARGET_i;
    using TMC2130_n::VDCMIN_i;
    using TMC5130_n::SW_MODE_i;
    using TMC5130_n::RAMP_STAT_i;
    using TMC5130_n::XLATCH_i;
    using TMC5130_n::ENCMODE_i;
    using TMC5130_n::X_ENC_i;
    using TMC5130_n::ENC_CONST_i;
    using TMC5130_n::ENC_STATUS_i;
    using TMC5130_n::ENC_LATCH_i;
    
    template<typename TYPE>
    struct ENC_DEVIATION_i {
        #pragma pack(push, 1)
        struct ENC_DEVIATION_t {
            constexpr static uint8_t address = 0x3D;
            uint32_t sr : 20;
        };
        #pragma pack(pop)
    
        uint32_t ENC_DEVIATION() {
            return r.sr;
        }
        void ENC_DEVIATION(uint32_t input) {
            static_cast<TYPE*>(this)->write(ENC_DEVIATION_t::address, input);
        }
        protected:
            ENC_DEVIATION_t r{};
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
    using TMC2160_n::CHOPCONF_i;
    using TMC2130_n::COOLCONF_i;
    using TMC2130_n::DCCTRL_i;

    // 0x6F R: DRV_STATUS
    template<typename TYPE>
    struct DRV_STATUS_i {
        #pragma pack(push, 1)
        struct DRV_STATUS_t {
            constexpr static uint8_t address = 0x6F;
            union {
                uint32_t sr;
                struct {
                    uint16_t sg_result : 10;
                    bool : 2,
                         s2vsa : 1,
                         s2vsb : 1,
                         stealth : 1;
                    bool fsactive : 1;
                    uint8_t cs_actual : 5,
                            : 3;
                    bool    stallGuard : 1,
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

        uint32_t DRV_STATUS() {
            return static_cast<TYPE*>(this)->read(DRV_STATUS_t::address);
        }

        uint16_t sg_result(){ return DRV_STATUS_t{ DRV_STATUS() }.sg_result; }
        bool s2vsa()        { return DRV_STATUS_t{ DRV_STATUS() }.s2vsa;     }
        bool s2vsb()        { return DRV_STATUS_t{ DRV_STATUS() }.s2vsb;     }
        bool stealth()      { return DRV_STATUS_t{ DRV_STATUS() }.stealth;   }
        bool fsactive()     { return DRV_STATUS_t{ DRV_STATUS() }.fsactive;  }
        uint8_t cs_actual() { return DRV_STATUS_t{ DRV_STATUS() }.cs_actual; }
        bool stallguard()   { return DRV_STATUS_t{ DRV_STATUS() }.stallGuard;}
        bool ot()           { return DRV_STATUS_t{ DRV_STATUS() }.ot;        }
        bool otpw()         { return DRV_STATUS_t{ DRV_STATUS() }.otpw;      }
        bool s2ga()         { return DRV_STATUS_t{ DRV_STATUS() }.s2ga;      }
        bool s2gb()         { return DRV_STATUS_t{ DRV_STATUS() }.s2gb;      }
        bool ola()          { return DRV_STATUS_t{ DRV_STATUS() }.ola;       }
        bool olb()          { return DRV_STATUS_t{ DRV_STATUS() }.olb;       }
        bool stst()         { return DRV_STATUS_t{ DRV_STATUS() }.stst;      }    
    };

    using TMC2160_n::PWMCONF_i;
    using TMC2160_n::PWM_SCALE_i;
    using TMC2208_n::PWM_AUTO_i;
    using TMC2130_n::LOST_STEPS_i;

}
