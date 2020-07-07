#include "TMCStepper.h"

using namespace TMCStepper_n;

int8_t TMC_SPI::chain_length = 0;
uint32_t TMC_SPI::spi_speed = 16000000/8;

TMC_SPI::TMC_SPI(SPIClass &spi, PinDef cs, int8_t link) :
  pinCS(cs),
  TMC_HW_SPI(&spi),
  link_index(link)
  {
    if (link > chain_length)
      chain_length = link;
  }

TMC_SPI::TMC_SPI(SW_SPIClass &spi, PinDef cs, int8_t link) :
  pinCS(cs),
  TMC_SW_SPI(&spi),
  link_index(link)
  {
    if (link > chain_length)
      chain_length = link;
  }

TMC2130Stepper::TMC2130Stepper(SPIClass &spi, PinDef cs, float RS, int8_t link) :
  TMC_SPI(spi, cs, link),
  TMCStepper<TMC2130Stepper>(RS)
  {
    defaults();
  }

TMC2130Stepper::TMC2130Stepper(SW_SPIClass &spi, PinDef cs, float RS, int8_t link) :
  TMC_SPI(spi, cs, link),
  TMCStepper<TMC2130Stepper>(RS)
  {
    defaults();
  }

void TMC2130Stepper::defaults() {
  //MSLUT0_register.sr = ???;
  //MSLUT1_register.sr = ???;
  //MSLUT2_register.sr = ???;
  //MSLUT3_register.sr = ???;
  //MSLUT4_register.sr = ???;
  //MSLUT5_register.sr = ???;
  //MSLUT6_register.sr = ???;
  //MSLUT7_register.sr = ???;
  //MSLUTSTART_register.start_sin90 = 247;
  PWMCONF_i::r.sr = 0x00050480;
}

__attribute__((weak))
void TMC_SPI::setSPISpeed(uint32_t speed) {
  spi_speed = speed;
}

__attribute__((weak))
uint32_t TMC_SPI::read(uint8_t addressByte) {
  TransferData data;
  OutputPin cs(pinCS);

  beginTransaction();
  cs.write(LOW);
  data.address = addressByte;
  transfer(data.buffer, 5);

  // Shift the written data to the correct driver in chain
  // Default link_index = -1 and no shifting happens
  int8_t i = 1;
  for (data.data = 0; i < link_index; i++) {
    transfer(data.buffer, 5);
  }

  cs.write(HIGH);
  cs.write(LOW);

  // Shift data from target link into the last one...
  for (data.data = 0; i < chain_length; i++) {
    transfer(data.buffer, 5);
  }

  // ...and once more to MCU
  data.address = addressByte;
  transfer(data.buffer, 5);
  status_response = data.status;

  endTransaction();
  cs.write(HIGH);
  return data.data;
}

__attribute__((weak))
void TMC_SPI::write(uint8_t addressByte, uint32_t config) {
  OutputPin cs(pinCS);
  TransferData data;
  addressByte |= TMC_WRITE;

  beginTransaction();
  cs.write(LOW);

  data.address = addressByte;
  data.data = config;
  transfer(data.buffer, 5);
  status_response = data.status;

  // Shift the written data to the correct driver in chain
  // Default link_index = -1 and no shifting happens
  data.data = 0;
  for (int8_t i = 1; i < chain_length; i++) {
    transfer(data.buffer, 5);
  }

  endTransaction();
  cs.write(HIGH);
}

void TMC2130Stepper::begin() {
  //set pins
  OutputPin cs(pinCS);
  cs.mode(OUTPUT);
  cs.write(HIGH);

  if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();

  COOLCONF(COOLCONF_i::r.sr);
  PWMCONF(PWMCONF_i::r.sr);
  IHOLD_IRUN(IHOLD_IRUN_i::r.sr);

  toff(8); //off_time(8);
  tbl(1); //blank_time(24);
}

/**
 *  Helper functions
 */

bool TMC2130Stepper::isEnabled() { return !drv_enn_cfg6() && toff(); }

void TMC2130Stepper::push() {
  IHOLD_IRUN(IHOLD_IRUN_i::r.sr);
  TPOWERDOWN(TPOWERDOWN_i::r.sr);
  TPWMTHRS(TPWMTHRS_i::r.sr);
  TCOOLTHRS(TCOOLTHRS_i::r.sr);
  THIGH(THIGH_i::r.sr);
  VDCMIN(VDCMIN_i::r.sr);
  COOLCONF(COOLCONF_i::r.sr);
  DCCTRL(DCCTRL_i::r.sr);
  PWMCONF(PWMCONF_i::r.sr);
  ENCM_CTRL(ENCM_CTRL_i::r.sr);
}

void TMC2130Stepper::sg_current_decrease(uint8_t value) {
  switch(value) {
    case 32: sedn(0b00); break;
    case  8: sedn(0b01); break;
    case  2: sedn(0b10); break;
    case  1: sedn(0b11); break;
  }
}
uint8_t TMC2130Stepper::sg_current_decrease() {
  switch(sedn()) {
    case 0b00: return 32;
    case 0b01: return  8;
    case 0b10: return  2;
    case 0b11: return  1;
  }
  return 0;
}
