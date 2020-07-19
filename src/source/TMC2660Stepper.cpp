#include "TMCStepper.h"
#include "SW_SPI.h"

using namespace TMCStepper_n;

TMC2660Stepper::TMC2660Stepper(SPIClass &spi, PinDef cs, float RS) :
  pinCS(cs),
  Rsense(RS),
  TMC_HW_SPI(&spi)
  {}

TMC2660Stepper::TMC2660Stepper(SW_SPIClass &spi, PinDef cs, float RS) :
  pinCS(cs),
  Rsense(RS),
  TMC_SW_SPI(&spi)
  {}

// |    3b   |       17b     |
// | Address | Register data |
// |     24b data buffer     |
namespace TMC2660_n {
  union TransferData {
    uint32_t data : 24;
    char buffer[3];
  };
}
using namespace TMC2660_n;

uint32_t TMC2660Stepper::read() {
  TransferData data;
  OutputPin cs(pinCS);

  data.data = ((uint32_t)DRVCONF_register.address<<17) | DRVCONF_register.sr;

  beginTransaction();
  cs.write(LOW);

  transfer(data.buffer, 3);

  endTransaction();
  cs.write(HIGH);

  return data.data >> 4;
}

void TMC2660Stepper::write(uint8_t addressByte, uint32_t config) {
  TransferData data;
  OutputPin cs(pinCS);

  data.data = (uint32_t)addressByte<<17 | config;

  beginTransaction();
  cs.write(LOW);

  transfer(data.buffer, 3);

  endTransaction();
  cs.write(HIGH);
}

void TMC2660Stepper::begin() {
  //set pins
  OutputPin cs(pinCS);
  cs.mode(OUTPUT);
  cs.write(HIGH);

  //TODO: Push shadow registers

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);
}

bool TMC2660Stepper::isEnabled() { return toff() > 0; }

uint8_t TMC2660Stepper::test_connection() {
  uint32_t drv_status = DRVSTATUS();
  switch (drv_status) {
      case 0xFFCFF: return 1;
      case 0: return 2;
      default: return 0;
  }
}

/*
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = (CS+1)/32 * V_fs/R_sense * 1/sqrt(2)
  Solve for CS ->
  CS = 32*sqrt(2)*I_rms*R_sense/V_fs - 1

  Example:
  vsense = 0b0 -> V_fs = 0.310V //Typical
  mA = 1650mA = I_rms/1000 = 1.65A
  R_sense = 0.100 Ohm
  ->
  CS = 32*sqrt(2)*1.65*0.100/0.310 - 1 = 24,09
  CS = 24
*/

uint16_t TMC2660Stepper::cs2rms(uint8_t CS) {
  return (float)(CS+1)/32.0 * (vsense() ? 0.165 : 0.310)/(Rsense+0.02) / 1.41421 * 1000;
}

uint16_t TMC2660Stepper::rms_current() {
  return cs2rms(cs());
}
void TMC2660Stepper::rms_current(uint16_t mA) {
  uint8_t CS = 32.0*1.41421*mA/1000.0*Rsense/0.310 - 1;
  // If Current Scale is too low, turn on high sensitivity R_sense and calculate again
  if (CS < 16) {
    vsense(true);
    CS = 32.0*1.41421*mA/1000.0*Rsense/0.165 - 1;
  } else { // If CS >= 16, turn off high_sense_r
    vsense(false);
  }

  if (CS > 31)
    CS = 31;

  cs(CS);
  //val_mA = mA;
}

void TMC2660Stepper::push() {
  DRVCTRL( sdoff() ? DRVCTRL_1_register.sr : DRVCTRL_0_register.sr);
  CHOPCONF(CHOPCONF_register.sr);
  SMARTEN(SMARTEN_register.sr);
  SGCSCONF(SGCSCONF_register.sr);
  DRVCONF(DRVCONF_register.sr);
}

void TMC2660Stepper::hysteresis_end(int8_t value) { hend(value+3); }
int8_t TMC2660Stepper::hysteresis_end() { return hend()-3; };

void TMC2660Stepper::hysteresis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMC2660Stepper::hysteresis_start() { return hstrt()+1; }

void TMC2660Stepper::microsteps(uint16_t ms) {
  switch(ms) {
    case 256: mres(0); break;
    case 128: mres(1); break;
    case  64: mres(2); break;
    case  32: mres(3); break;
    case  16: mres(4); break;
    case   8: mres(5); break;
    case   4: mres(6); break;
    case   2: mres(7); break;
    case   0: mres(8); break;
    default: break;
  }
}

uint16_t TMC2660Stepper::microsteps() {
  switch(mres()) {
    case 0: return 256;
    case 1: return 128;
    case 2: return  64;
    case 3: return  32;
    case 4: return  16;
    case 5: return   8;
    case 6: return   4;
    case 7: return   2;
    case 8: return   0;
  }
  return 0;
}

void TMC2660Stepper::blank_time(uint8_t value) {
  switch (value) {
    case 16: tbl(0b00); break;
    case 24: tbl(0b01); break;
    case 36: tbl(0b10); break;
    case 54: tbl(0b11); break;
  }
}

uint8_t TMC2660Stepper::blank_time() {
  switch (tbl()) {
    case 0b00: return 16;
    case 0b01: return 24;
    case 0b10: return 36;
    case 0b11: return 54;
  }
  return 0;
}
