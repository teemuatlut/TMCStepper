#pragma once

#if defined(bcm2835)
  #include "source/rpi_bcm2835.h"
  #include "source/bcm2835_spi.h"
  #include "source/bcm2835_stream.h"
#endif

#include <stdint.h>
#include "TMC_HAL.h"

class SSwitch {
  public:
    SSwitch(const TMCStepper_n::PinDef pin1, const TMCStepper_n::PinDef pin2, const uint8_t address);
    void active();
  private:
    TMCStepper_n::PinDef p1;
    TMCStepper_n::PinDef p2;
    const uint8_t addr;
};
