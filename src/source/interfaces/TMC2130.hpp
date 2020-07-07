
#pragma once

#include "TMCStepper.h"
#include "source/TMC2130_bitfields.h"

namespace TMC2130_n {
    // 0x00 RW: GCONF
    template<typename TYPE>
    struct GCONF_i {
        uint32_t GCONF() {
            return static_cast<TYPE*>(this)->read(GCONF_t::address);
        }
        void GCONF(uint32_t input) {
            static_cast<TYPE*>(this)->write(GCONF_t::address, input);
        }

        void I_scale_analog(bool B)         { auto r=GCONF_t{ GCONF() }; r.i_scale_analog = B;         GCONF(r.sr); }
        void internal_Rsense(bool B)        { auto r=GCONF_t{ GCONF() }; r.internal_rsense = B;        GCONF(r.sr); }
        void en_pwm_mode(bool B)            { auto r=GCONF_t{ GCONF() }; r.en_pwm_mode = B;            GCONF(r.sr); }
        void enc_commutation(bool B)        { auto r=GCONF_t{ GCONF() }; r.enc_commutation = B;        GCONF(r.sr); }
        void shaft(bool B)                  { auto r=GCONF_t{ GCONF() }; r.shaft = B;                  GCONF(r.sr); }
        void diag0_error(bool B)            { auto r=GCONF_t{ GCONF() }; r.diag0_error = B;            GCONF(r.sr); }
        void diag0_otpw(bool B)             { auto r=GCONF_t{ GCONF() }; r.diag0_otpw = B;             GCONF(r.sr); }
        void diag0_stall(bool B)            { auto r=GCONF_t{ GCONF() }; r.diag0_stall = B;            GCONF(r.sr); }
        void diag1_stall(bool B)            { auto r=GCONF_t{ GCONF() }; r.diag1_stall = B;            GCONF(r.sr); }
        void diag1_index(bool B)            { auto r=GCONF_t{ GCONF() }; r.diag1_index = B;            GCONF(r.sr); }
        void diag1_onstate(bool B)          { auto r=GCONF_t{ GCONF() }; r.diag1_onstate = B;          GCONF(r.sr); }
        void diag1_steps_skipped(bool B)    { auto r=GCONF_t{ GCONF() }; r.diag1_steps_skipped = B;    GCONF(r.sr); }
        void diag0_int_pushpull(bool B)     { auto r=GCONF_t{ GCONF() }; r.diag0_int_pushpull = B;     GCONF(r.sr); }
        void diag1_pushpull(bool B)         { auto r=GCONF_t{ GCONF() }; r.diag1_poscomp_pushpull = B; GCONF(r.sr); }
        void small_hysteresis(bool B)       { auto r=GCONF_t{ GCONF() }; r.small_hysteresis = B;       GCONF(r.sr); }
        void stop_enable(bool B)            { auto r=GCONF_t{ GCONF() }; r.stop_enable = B;            GCONF(r.sr); }
        void direct_mode(bool B)            { auto r=GCONF_t{ GCONF() }; r.direct_mode = B;            GCONF(r.sr); }

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
        bool diag1_pushpull()               { return GCONF_t{ GCONF() }.diag1_poscomp_pushpull; }
        bool small_hysteresis()             { return GCONF_t{ GCONF() }.small_hysteresis;       }
        bool stop_enable()                  { return GCONF_t{ GCONF() }.stop_enable;            }
        bool direct_mode()                  { return GCONF_t{ GCONF() }.direct_mode;            }
    };

    // 0x01 R+C: GSTAT
    template<typename TYPE>
    struct GSTAT_i {
        uint8_t GSTAT()     { return static_cast<TYPE*>(this)->read(GSTAT_t::address); }
        void GSTAT(uint8_t) { static_cast<TYPE*>(this)->write(GSTAT_t::address, 0b111); }
        bool reset()        { GSTAT_t r; r.sr = GSTAT(); return r.reset; }
        bool drv_err()      { GSTAT_t r; r.sr = GSTAT(); return r.drv_err; }
        bool uv_cp()        { GSTAT_t r; r.sr = GSTAT(); return r.uv_cp; }
    };

    // 0x04 R: IOIN
    template<typename TYPE>
    struct IOIN_i {
        uint32_t IOIN()     { return static_cast<TYPE*>(this)->read(IOIN_t::address); }
        bool step()         { IOIN_t r{0}; r.sr = IOIN(); return r.step; }
        bool dir()          { IOIN_t r{0}; r.sr = IOIN(); return r.dir; }
        bool dcen_cfg4()    { IOIN_t r{0}; r.sr = IOIN(); return r.dcen_cfg4; }
        bool dcin_cfg5()    { IOIN_t r{0}; r.sr = IOIN(); return r.dcin_cfg5; }
        bool drv_enn_cfg6() { IOIN_t r{0}; r.sr = IOIN(); return r.drv_enn_cfg6; }
        bool dco()          { IOIN_t r{0}; r.sr = IOIN(); return r.dco; }
        uint8_t version()   { IOIN_t r{0}; r.sr = IOIN(); return r.version; }
    };

    // 0x10 W: IHOLD_IRUN
    template<typename TYPE>
    struct IHOLD_IRUN_i {
        uint32_t IHOLD_IRUN() {
            return r.sr;
        }
        void IHOLD_IRUN(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void ihold(uint8_t B) {
            r.ihold = B;
            IHOLD_IRUN(r.sr);
        }
        void irun(uint8_t B) {
            r.irun = B;
            IHOLD_IRUN(r.sr);
        }
        void iholddelay(uint8_t B) {
            r.iholddelay = B;
            IHOLD_IRUN(r.sr);
        }

        uint8_t ihold() {
            return r.ihold;
        }
        uint8_t irun() {
            return r.irun;
        }
        uint8_t iholddelay() {
            return r.iholddelay;
        }

        protected:
            IHOLD_IRUN_t r{};
    };

    // 0x11 W: TPOWERDOWN
    template<typename TYPE>
    struct TPOWERDOWN_i {
        uint8_t TPOWERDOWN() { return r.sr; }
        void TPOWERDOWN(uint8_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        TPOWERDOWN_t r{};
    };

    // 0x12 R: TSTEP
    template<typename TYPE>
    struct TSTEP_i {
        uint32_t TSTEP() {
            return static_cast<TYPE*>(this)->read(TSTEP_t::address);
        }
    };

    // 0x13 W: TPWMTHRS
    template<typename TYPE>
    struct TPWMTHRS_i {
        uint8_t TPWMTHRS() { return r.sr; }
        void TPWMTHRS(uint8_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        TPWMTHRS_t r{};
    };

    // 0x14 W: TCOOLTHRS
    template<typename TYPE>
    struct TCOOLTHRS_i {
        uint32_t TCOOLTHRS() { return r.sr; }
        void TCOOLTHRS(uint32_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        TCOOLTHRS_t r{};
    };

    // 0x15 W: THIGH
    template<typename TYPE>
    struct THIGH_i {
        uint32_t THIGH() { return r.sr; }
        void THIGH(uint32_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        THIGH_t r{};
    };

    // 0x2D RW: XDIRECT
    template<typename TYPE>
    struct XDIRECT_i {
        uint32_t XDIRECT() {
            return static_cast<TYPE*>(this)->read(XDIRECT_t::address);
        }
        void XDIRECT(uint32_t input) {
            static_cast<TYPE*>(this)->write(XDIRECT_t::address, input);
        }
        void coil_A(int16_t B)  { XDIRECT_t r{ XDIRECT() }; r.coil_A = B; XDIRECT(r.address, r.sr); }
        void coil_B(int16_t B)  { XDIRECT_t r{ XDIRECT() }; r.coil_B = B; XDIRECT(r.address, r.sr); }
        int16_t coil_A()        { return XDIRECT_t{ XDIRECT() }.coil_A; }
        int16_t coil_B()        { return XDIRECT_t{ XDIRECT() }.coil_B; }
    };

    // 0x15 W: VDCMIN
    template<typename TYPE>
    struct VDCMIN_i {
        uint32_t VDCMIN() { return r.sr; }
        void VDCMIN(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

    protected:
        VDCMIN_t r{};
    };

    // 0x6A R: MSCNT
    template<typename TYPE>
    struct MSCNT_i {
        uint16_t MSCNT() {
            return static_cast<TYPE*>(this)->read(MSCNT_t::address);
        }
    };

    // 0x6B R: MSCURACT
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
    template<typename TYPE>
    struct CHOPCONF_i {
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

    // 0x6D W: COOLCONF
    template<typename TYPE>
    struct COOLCONF_i {
        uint32_t COOLCONF() { return r.sr; }
        void COOLCONF(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void semin( uint8_t B ) { r.semin = B;  COOLCONF(r.sr); }
        void seup(  uint8_t B ) { r.seup = B;   COOLCONF(r.sr); }
        void semax( uint8_t B ) { r.semax = B;  COOLCONF(r.sr); }
        void sedn(  uint8_t B ) { r.sedn = B;   COOLCONF(r.sr); }
        void seimin(bool    B ) { r.seimin = B; COOLCONF(r.sr); }
        void sgt(   int8_t  B ) { r.sgt = B;    COOLCONF(r.sr); }
        void sfilt( bool    B ) { r.sfilt = B;  COOLCONF(r.sr); }

        uint8_t semin() { return r.semin;   }
        uint8_t seup()  { return r.seup;    }
        uint8_t semax() { return r.semax;   }
        uint8_t sedn()  { return r.sedn;    }
        bool    seimin(){ return r.seimin;  }
        bool    sfilt() { return r.sfilt;   }

        int8_t sgt() {
            // Two's complement in a 7bit value
            int8_t val = (r.sgt &  0x40) << 1; // Isolate sign bit
            val |= r.sgt & 0x7F;
            return val;
        }

    protected:
        COOLCONF_t r{};
    };

    // 0x6E W: DCCTRL
    template<typename TYPE>
    struct DCCTRL_i {
        void DCCTRL(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
        void dc_time(uint16_t input) {
            r.dc_time = input;
            DCCTRL(r.sr);
        }
        void dc_sg(uint8_t input) {
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
    template<typename TYPE>
    struct DRV_STATUS_i {
        uint32_t DRV_STATUS() {
            return static_cast<TYPE*>(this)->read(DRV_STATUS_t::address);
        }

        uint16_t sg_result(){ return DRV_STATUS_t{ DRV_STATUS() }.sg_result; }
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

    // 0x70 W: PWMCONF
    template<typename TYPE>
    struct PWMCONF_i {
        uint32_t PWMCONF() { return r.sr; }
        void PWMCONF(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void pwm_ampl(      uint8_t B ) { r.pwm_ampl = B;        PWMCONF(r.sr); }
        void pwm_grad(      uint8_t B ) { r.pwm_grad = B;        PWMCONF(r.sr); }
        void pwm_freq(      uint8_t B ) { r.pwm_freq = B;        PWMCONF(r.sr); }
        void pwm_autoscale( bool    B ) { r.pwm_autoscale = B;   PWMCONF(r.sr); }
        void pwm_symmetric( bool    B ) { r.pwm_symmetric = B;   PWMCONF(r.sr); }
        void freewheel(     uint8_t B ) { r.freewheel = B;       PWMCONF(r.sr); }

        uint8_t pwm_ampl()      { return r.pwm_ampl;     }
        uint8_t pwm_grad()      { return r.pwm_grad;     }
        uint8_t pwm_freq()      { return r.pwm_freq;     }
        bool    pwm_autoscale() { return r.pwm_autoscale;}
        bool    pwm_symmetric() { return r.pwm_symmetric;}
        uint8_t freewheel()     { return r.freewheel;    }

    protected:
        PWMCONF_t r{{0x00050480}};
    };

    // 0x71 R: PWM_SCALE
    template<typename TYPE>
    struct PWM_SCALE_i {
        uint8_t PWM_SCALE() { return static_cast<TYPE*>(this)->read(PWM_SCALE_t::address); }
    };

    // 0x72 W: ENCM_CTRL
    template<typename TYPE>
    struct ENCM_CTRL_i {
        uint8_t ENCM_CTRL() { return r.sr; }
        void ENCM_CTRL(uint8_t input) {
          r.sr = input;
          static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
        void inv(bool B)      { r.inv = B;       ENCM_CTRL(r.sr); }
        void maxspeed(bool B) { r.maxspeed  = B; ENCM_CTRL(r.sr); }
        bool inv()            { return r.inv; }
        bool maxspeed()       { return r.maxspeed; }

    protected:
        ENCM_CTRL_t r{};
    };

    // 0x73 R: LOST_STEPS
    template<typename TYPE>
    struct LOST_STEPS_i {
        uint32_t LOST_STEPS() {
            return static_cast<TYPE*>(this)->read(LOST_STEPS_t::address);
        }
    };
}
