
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

    // 0x04 R: IOIN
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

    using TMC2130_n::IHOLD_IRUN_i;
    using TMC2130_n::TPOWERDOWN_i;
    using TMC2130_n::TSTEP_i;
    using TMC2130_n::TPWMTHRS_i;
    using TMC2130_n::MSCNT_i;
    using TMC2130_n::MSCURACT_i;
}
