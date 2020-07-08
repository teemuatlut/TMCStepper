#pragma once

#include "TMCStepper.h"
#include "TMC2130.hpp"
#include "../TMC2208_bitfields.h"

namespace TMC2209_n {

    using namespace TMC2208_n;
    using TMC2130_n::TCOOLTHRS_i;

    // 0x06 R: IOIN
    template<typename TYPE>
    struct IOIN_i {
        uint32_t IOIN() {
            return static_cast<TYPE*>(this)->read(IOIN_t::address);
        }
        bool enn()          { return IOIN_t{ IOIN() }.enn;         }
        bool ms1()          { return IOIN_t{ IOIN() }.ms1;         }
        bool ms2()          { return IOIN_t{ IOIN() }.ms2;         }
        bool diag()         { return IOIN_t{ IOIN() }.diag;        }
        bool pdn_uart()     { return IOIN_t{ IOIN() }.pdn_uart;    }
        bool step()         { return IOIN_t{ IOIN() }.step;        }
        bool spread_en()    { return IOIN_t{ IOIN() }.spread_en;   }
        bool dir()          { return IOIN_t{ IOIN() }.dir;         }
        uint8_t version()   { return IOIN_t{ IOIN() }.version;     }
    };

    // 0x40 W: SGTHRS
    template<typename TYPE>
    struct SGTHRS_i {
        void SGTHRS(uint8_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }
        uint8_t SGTHRS() {
            return r.sr;
        }
    protected:
        SGTHRS_t r{};
    };

    // 0x41 R: SG_RESULT
    template<typename TYPE>
    struct SG_RESULT_i {
        uint16_t SG_RESULT() {
            return static_cast<TYPE*>(this)->read(TMC2209_n::SG_RESULT_t::address);
        }
    };

    // 0x42 W: COOLCONF
    template<typename TYPE>
    struct COOLCONF_i {
        uint16_t COOLCONF() { return r.sr; }
        void COOLCONF(uint16_t input) {
            r.sr = input;
            static_cast<TYPE*>(this)->write(r.address, r.sr);
        }

        void semin( uint8_t B ) { r.semin = B;  COOLCONF(r.sr); }
        void seup(  uint8_t B ) { r.seup = B;   COOLCONF(r.sr); }
        void semax( uint8_t B ) { r.semax = B;  COOLCONF(r.sr); }
        void sedn(  uint8_t B ) { r.sedn = B;   COOLCONF(r.sr); }
        void seimin(bool    B ) { r.seimin = B; COOLCONF(r.sr); }

        uint8_t semin() { return r.semin;   }
        uint8_t seup()  { return r.seup;    }
        uint8_t semax() { return r.semax;   }
        uint8_t sedn()  { return r.sedn;    }
        bool    seimin(){ return r.seimin;  }

    protected:
        COOLCONF_t r{};
    };

}