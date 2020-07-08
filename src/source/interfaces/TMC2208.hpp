
#pragma once

#include "TMCStepper.h"
#include "TMC2130.hpp"
#include "../TMC2208_bitfields.h"

namespace TMC2208_n {
    // 0x00 RW: GCONF
    template<typename TYPE>
    struct GCONF_i {
        uint16_t GCONF() {
            return static_cast<TYPE*>(this)->read(GCONF_t::address);
        }
        void GCONF(uint16_t input) {
            static_cast<TYPE*>(this)->write(GCONF_t::address, input);
        }

        void I_scale_analog(bool B)     { GCONF_t r{ GCONF() }; r.i_scale_analog = B;    GCONF(r.sr); }
        void internal_Rsense(bool B)    { GCONF_t r{ GCONF() }; r.internal_rsense = B;   GCONF(r.sr); }
        void en_spreadCycle(bool B)     { GCONF_t r{ GCONF() }; r.en_spreadcycle = B;    GCONF(r.sr); }
        void shaft(bool B)              { GCONF_t r{ GCONF() }; r.shaft = B;             GCONF(r.sr); }
        void index_otpw(bool B)         { GCONF_t r{ GCONF() }; r.index_otpw = B;        GCONF(r.sr); }
        void index_step(bool B)         { GCONF_t r{ GCONF() }; r.index_step = B;        GCONF(r.sr); }
        void pdn_disable(bool B)        { GCONF_t r{ GCONF() }; r.pdn_disable = B;       GCONF(r.sr); }
        void mstep_reg_select(bool B)   { GCONF_t r{ GCONF() }; r.mstep_reg_select = B;  GCONF(r.sr); }
        void multistep_filt(bool B)     { GCONF_t r{ GCONF() }; r.multistep_filt = B;    GCONF(r.sr); }

        bool I_scale_analog()   { return GCONF_t{ GCONF() }.i_scale_analog;  }
        bool internal_Rsense()  { return GCONF_t{ GCONF() }.internal_rsense; }
        bool en_spreadCycle()   { return GCONF_t{ GCONF() }.en_spreadcycle;  }
        bool shaft()            { return GCONF_t{ GCONF() }.shaft;           }
        bool index_otpw()       { return GCONF_t{ GCONF() }.index_otpw;      }
        bool index_step()       { return GCONF_t{ GCONF() }.index_step;      }
        bool pdn_disable()      { return GCONF_t{ GCONF() }.pdn_disable;     }
        bool mstep_reg_select() { return GCONF_t{ GCONF() }.mstep_reg_select;}
        bool multistep_filt()   { return GCONF_t{ GCONF() }.multistep_filt;  }
    };

    using TMC2130_n::GSTAT_i;

    // 0x02 R: IFCNT
    template<typename TYPE>
    struct IFCNT_i {
        uint8_t IFCNT() {
            return static_cast<TYPE*>(this)->read(IFCNT_t::address);
        }
    };

    // 0x03 W: SLAVECONF
    template<typename TYPE>
    struct SLAVECONF_i {
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

    // 0x04 W: OTP_PROG
    template<typename TYPE>
    struct OTP_PROG_i {
        void OTP_PROG(uint16_t input) {
            static_cast<TYPE*>(this)->write(OTP_PROG_t::address, input);
        }
    };

    // 0x05 R: OTP_READ
    template<typename TYPE>
    struct OTP_READ_i {
        uint32_t OTP_READ() {
            return static_cast<TYPE*>(this)->read(OTP_READ_t::address);
        }
    };
    
    // 0x06 R: IOIN
    template<typename TYPE>
    struct IOIN_i {
        uint32_t IOIN()     { return static_cast<TYPE*>(this)->read(IOIN_t::address); }
        bool enn()          { return IOIN_t{ IOIN() }.enn;       }
        bool ms1()          { return IOIN_t{ IOIN() }.ms1;       }
        bool ms2()          { return IOIN_t{ IOIN() }.ms2;       }
        bool diag()         { return IOIN_t{ IOIN() }.diag;      }
        bool pdn_uart()     { return IOIN_t{ IOIN() }.pdn_uart;  }
        bool step()         { return IOIN_t{ IOIN() }.step;      }
        bool sel_a()        { return IOIN_t{ IOIN() }.sel_a;     }
        bool dir()          { return IOIN_t{ IOIN() }.dir;       }
        uint8_t version()   { return IOIN_t{ IOIN() }.version;   }
    };

    // 0x07 RW: FACTORY_CONF
    template<typename TYPE>
    struct FACTORY_CONF_i {
        uint16_t FACTORY_CONF() {
            return static_cast<TYPE*>(this)->read(FACTORY_CONF_t::address);
        }
        void FACTORY_CONF(uint16_t input) {
            static_cast<TYPE*>(this)->write(FACTORY_CONF_t::address, input);
        }
        void fclktrim(uint8_t B){ FACTORY_CONF_t r{ FACTORY_CONF() }; r.fclktrim = B;   FACTORY_CONF(r.sr); }
        void ottrim(uint8_t B)  { FACTORY_CONF_t r{ FACTORY_CONF() }; r.ottrim = B;     FACTORY_CONF(r.sr); }
        uint8_t fclktrim()      { return FACTORY_CONF_t{ FACTORY_CONF() }.fclktrim; }
        uint8_t ottrim()        { return FACTORY_CONF_t{ FACTORY_CONF() }.ottrim; }
    };

    using TMC2130_n::IHOLD_IRUN_i;
    using TMC2130_n::TPOWERDOWN_i;
    using TMC2130_n::TSTEP_i;
    using TMC2130_n::TPWMTHRS_i;

    // 0x22 W: VACTUAL
    template<typename TYPE>
    struct VACTUAL_i {
        void VACTUAL(uint32_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, input);
        }
        uint32_t VACTUAL() {
            return r.sr;
        }
    protected:
        VACTUAL_t r{};
    };

    using TMC2130_n::MSCNT_i;
    using TMC2130_n::MSCURACT_i;

    // 0x6C RW: CHOPCONF
    template<typename TYPE>
    struct CHOPCONF_i {
        void CHOPCONF(uint32_t input) {
            static_cast<TYPE*>(this)->write(CHOPCONF_t::address, input);
        }
        uint32_t CHOPCONF() {
            return static_cast<TYPE*>(this)->read(CHOPCONF_t::address);
        }
        void toff   ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.toff = B;    CHOPCONF(r.sr); }
        void hstrt  ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.hstrt = B;   CHOPCONF(r.sr); }
        void hend   ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.hend = B;    CHOPCONF(r.sr); }
        void tbl    ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.tbl = B;     CHOPCONF(r.sr); }
        void vsense ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.vsense = B;  CHOPCONF(r.sr); }
        void mres   ( uint8_t  B )  { CHOPCONF_t r{ CHOPCONF() }; r.mres = B;    CHOPCONF(r.sr); }
        void intpol ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.intpol = B;  CHOPCONF(r.sr); }
        void dedge  ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.dedge = B;   CHOPCONF(r.sr); }
        void diss2g ( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.diss2g = B;  CHOPCONF(r.sr); }
        void diss2vs( bool     B )  { CHOPCONF_t r{ CHOPCONF() }; r.diss2vs = B; CHOPCONF(r.sr); }

        uint8_t toff()      { return CHOPCONF_t{ CHOPCONF() }.toff;      }
        uint8_t hstrt()     { return CHOPCONF_t{ CHOPCONF() }.hstrt;     }
        uint8_t hend()      { return CHOPCONF_t{ CHOPCONF() }.hend;      }
        uint8_t tbl()       { return CHOPCONF_t{ CHOPCONF() }.tbl;       }
        bool    vsense()    { return CHOPCONF_t{ CHOPCONF() }.vsense;    }
        uint8_t mres()      { return CHOPCONF_t{ CHOPCONF() }.mres;      }
        bool    intpol()    { return CHOPCONF_t{ CHOPCONF() }.intpol;    }
        bool    dedge()     { return CHOPCONF_t{ CHOPCONF() }.dedge;     }
        bool    diss2g()    { return CHOPCONF_t{ CHOPCONF() }.diss2g;    }
        bool    diss2vs()   { return CHOPCONF_t{ CHOPCONF() }.diss2vs;   }
    };

    // 0x6F R: DRV_STATUS
    template<typename TYPE>
    struct DRV_STATUS_i {
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
        bool        t143()      { return DRV_STATUS_t{ DRV_STATUS() }.t143;      }
        bool        t150()      { return DRV_STATUS_t{ DRV_STATUS() }.t150;      }
        bool        t157()      { return DRV_STATUS_t{ DRV_STATUS() }.t157;      }
        uint16_t    cs_actual() { return DRV_STATUS_t{ DRV_STATUS() }.cs_actual; }
        bool        stealth()   { return DRV_STATUS_t{ DRV_STATUS() }.stealth;   }
        bool        stst()      { return DRV_STATUS_t{ DRV_STATUS() }.stst;      }
    };

    // 0x70 RW: PWMCONF
    template<typename TYPE>
    struct PWMCONF_i {
        uint32_t PWMCONF() {
            return static_cast<TYPE*>(this)->read(PWMCONF_t::address);
        }
        void PWMCONF(uint32_t input) {
            static_cast<TYPE*>(this)->write(PWMCONF_t::address, input);
        }

        void pwm_ofs        ( uint8_t B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_ofs = B;        PWMCONF(r.sr); }
        void pwm_grad       ( uint8_t B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_grad = B;       PWMCONF(r.sr); }
        void pwm_freq       ( uint8_t B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_freq = B;       PWMCONF(r.sr); }
        void pwm_autoscale  ( bool    B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_autoscale = B;  PWMCONF(r.sr); }
        void pwm_autograd   ( bool    B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_autograd = B;   PWMCONF(r.sr); }
        void freewheel      ( uint8_t B ) { PWMCONF_t r{ PWMCONF() }; r.freewheel = B;      PWMCONF(r.sr); }
        void pwm_reg        ( uint8_t B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_reg = B;        PWMCONF(r.sr); }
        void pwm_lim        ( uint8_t B ) { PWMCONF_t r{ PWMCONF() }; r.pwm_lim = B;        PWMCONF(r.sr); }

        uint8_t pwm_ofs()       { return PWMCONF_t{ PWMCONF() }.pwm_ofs;         }
        uint8_t pwm_grad()      { return PWMCONF_t{ PWMCONF() }.pwm_grad;        }
        uint8_t pwm_freq()      { return PWMCONF_t{ PWMCONF() }.pwm_freq;        }
        bool    pwm_autoscale() { return PWMCONF_t{ PWMCONF() }.pwm_autoscale;   }
        bool    pwm_autograd()  { return PWMCONF_t{ PWMCONF() }.pwm_autograd;    }
        uint8_t freewheel()     { return PWMCONF_t{ PWMCONF() }.freewheel;       }
        uint8_t pwm_reg()       { return PWMCONF_t{ PWMCONF() }.pwm_reg;         }
        uint8_t pwm_lim()       { return PWMCONF_t{ PWMCONF() }.pwm_lim;         }
    };

    // 0x71 R: PWM_SCALE
    template<typename TYPE>
    struct PWM_SCALE_i {
        uint32_t PWM_SCALE() {
            return static_cast<TYPE*>(this)->read(PWM_SCALE_t::address);
        }
        uint8_t pwm_scale_sum() {
            return PWM_SCALE_t{ PWM_SCALE() }.pwm_scale_sum;
        }

        int16_t pwm_scale_auto() {
            return PWM_SCALE_t{ PWM_SCALE() }.pwm_scale_auto;
            // Not two's complement? 9nth bit determines sign
            /*
            uint32_t d = PWM_SCALE();
            int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
            if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
            else return response;
            */
        }
    };

    // 0x72 R: PWM_AUTO
    template<typename TYPE>
    struct PWM_AUTO_i {
        uint32_t PWM_AUTO() {
            return static_cast<TYPE*>(this)->read(PWM_AUTO_t::address);
        }
        uint8_t pwm_ofs_auto()  { return PWM_AUTO_t{ PWM_AUTO() }.pwm_ofs_auto; }
        uint8_t pwm_grad_auto() { return PWM_AUTO_t{ PWM_AUTO() }.pwm_grad_auto; }
    };
}
