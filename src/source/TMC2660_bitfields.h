#pragma once

struct DRVCTRL_1_t {
  uint8_t address;
  union {
    uint32_t sr;
    struct {
      uint8_t cb : 8;
      bool phb : 1;
      uint8_t ca : 8;
      bool pha : 1; 
    };
  };
};

struct DRVCTRL_0_t {
  uint8_t address;
  union {
    uint32_t sr;
    struct {
      uint8_t mres : 4;
      uint8_t : 4;
      bool dedge : 1;
      bool intpol : 1;
    };
  };
};

namespace TMC2660 {
  struct CHOPCONF_t {
    uint8_t address;
    union {
      uint32_t sr;
      struct {
        uint8_t toff : 4;
        uint8_t hstrt : 3;
        uint8_t hend : 4;
        uint8_t hdec : 2;
        bool rndtf : 1;
        bool chm : 1;
        uint8_t tbl : 2;
      };
    };
  };
}

struct SMARTEN_t {
  uint8_t address;
  union {
    uint32_t sr;
    struct {
      uint8_t semin : 4,
                    : 1,
              seup  : 2,
                    : 1,
              semax : 4,
                    : 1,
              sedn : 2;
      bool seimin : 1;
    };
  };
};

struct SGCSCONF_t {
  uint8_t address;
  union {
    uint32_t sr;
    struct {
      uint8_t cs : 5;
      uint8_t    : 3;
      uint8_t sgt : 7;
      uint8_t : 1;
      bool sfilt : 1;
    };
  };
};

struct DRVCONF_t {
  uint8_t address;
  union {
    uint32_t sr;
    struct {
      uint8_t : 4;
      uint8_t rdsel : 2;
      bool vsense : 1;
      bool sdoff : 1;
      uint8_t ts2g : 2;
      bool diss2g : 1;
      uint8_t : 1;
      uint8_t slpl : 2;
      uint8_t slph : 2;
      bool tst : 1; 
    };
  };
};

struct READ_RDSEL00_t {
  union {
    uint32_t sr;
    struct {
      bool  sg_value : 1,
            ot : 1,
            otpw : 1,
            s2ga : 1,
            s2gb : 1,
            ola : 1,
            olb : 1,
            stst : 1;
      uint8_t : 2;
      uint16_t mstep : 10;
    };
  };
};

struct READ_RDSEL01_t {
  union {
    uint32_t sr;
    struct {
      bool  sg_value : 1,
            ot : 1,
            otpw : 1,
            s2ga : 1,
            s2gb : 1,
            ola : 1,
            olb : 1,
            stst : 1;
      uint8_t : 2;
      uint16_t sg_result : 10;
    };
  };
};

struct READ_RDSEL10_t {
  union {
    uint32_t sr;
    struct {
      bool  sg_value : 1,
            ot : 1,
            otpw : 1,
            s2ga : 1,
            s2gb : 1,
            ola : 1,
            olb : 1,
            stst : 1;
      uint8_t : 2;
      uint8_t se : 5;
      uint8_t sg_result : 5;
    };
  };
};
