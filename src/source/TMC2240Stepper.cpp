#include "TMCStepper.h"
#include "TMC_MACROS.h"

int8_t TMC2240Stepper::chain_length = 0;
uint32_t TMC2240Stepper::spi_speed = 16000000/8;

TMC2240Stepper::TMC2240Stepper(uint16_t pinCS, int8_t link) :
  _pinCS(pinCS),
  link_index(link)
  {
    defaults();

    if (link > chain_length)
      chain_length = link;
  }

TMC2240Stepper::TMC2240Stepper(uint16_t pinCS, uint16_t pinMOSI, uint16_t pinMISO, uint16_t pinSCK, int8_t link) :
  _pinCS(pinCS),
  link_index(link)
  {
    SW_SPIClass *SW_SPI_Obj = new SW_SPIClass(pinMOSI, pinMISO, pinSCK);
    TMC_SW_SPI = SW_SPI_Obj;
    defaults();

    if (link > chain_length)
      chain_length = link;
  }

void TMC2240Stepper::defaults() {
  //GCONF_register.sr = 0x0000;
  //CHOPCONF_register.sr = 0x10000053;
  //PWMCONF_register.sr = 0xC10D0024;
}

__attribute__((weak))
void TMC2240Stepper::setSPISpeed(uint32_t speed) {
  spi_speed = speed;
}

__attribute__((weak))
void TMC2240Stepper::switchCSpin(bool state) {
  digitalWrite(_pinCS, state);
}

__attribute__((weak))
void TMC2240Stepper::beginTransaction() {
  if (TMC_SW_SPI == nullptr) {
    SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE3));
  }
}
__attribute__((weak))
void TMC2240Stepper::endTransaction() {
  if (TMC_SW_SPI == nullptr) {
    SPI.endTransaction();
  }
}

__attribute__((weak))
uint8_t TMC2240Stepper::transfer(const uint8_t data) {
  uint8_t out = 0;
  if (TMC_SW_SPI != nullptr) {
    out = TMC_SW_SPI->transfer(data);
  }
  else {
    out = SPI.transfer(data);
  }
  return out;
}

void TMC2240Stepper::transferEmptyBytes(const uint8_t n) {
  for (uint8_t i = 0; i < n; i++) {
    transfer(0x00);
  }
}

__attribute__((weak))
uint32_t TMC2240Stepper::read(uint8_t addressByte) {
  uint32_t out = 0UL;
  int8_t i = 1;

  beginTransaction();
  switchCSpin(LOW);
  transfer(addressByte);
  // Clear SPI
  transferEmptyBytes(4);

  // Shift the written data to the correct driver in chain
  // Default link_index = -1 and no shifting happens
  while(i < link_index) {
    transferEmptyBytes(5);
    i++;
  }

  switchCSpin(HIGH);
  switchCSpin(LOW);

  // Shift data from target link into the last one...
  while(i < chain_length) {
    transferEmptyBytes(5);
    i++;
  }

  // ...and once more to MCU
  status_response = transfer(addressByte); // Send the address byte again
  out  = transfer(0x00);
  out <<= 8;
  out |= transfer(0x00);
  out <<= 8;
  out |= transfer(0x00);
  out <<= 8;
  out |= transfer(0x00);

  endTransaction();
  switchCSpin(HIGH);
  return out;
}

__attribute__((weak))
void TMC2240Stepper::write(uint8_t addressByte, uint32_t config) {
  addressByte |= TMC_WRITE;
  int8_t i = 1;

  beginTransaction();
  switchCSpin(LOW);
  status_response = transfer(addressByte);
  transfer(config>>24);
  transfer(config>>16);
  transfer(config>>8);
  transfer(config);

  // Shift the written data to the correct driver in chain
  // Default link_index = -1 and no shifting happens
  while(i < link_index) {
    transferEmptyBytes(5);
    i++;
  }

  endTransaction();
  switchCSpin(HIGH);
}

void TMC2240Stepper::begin() {
  // Set pins
  pinMode(_pinCS, OUTPUT);
  switchCSpin(HIGH);

  if (TMC_SW_SPI != nullptr) TMC_SW_SPI->init();

  //GCONF(GCONF_register.sr);
  //CHOPCONF(CHOPCONF_register.sr);
  //COOLCONF(COOLCONF_register.sr);
  //PWMCONF(PWMCONF_register.sr);
  //IHOLD_IRUN(IHOLD_IRUN_register.sr);

  //toff(8); //off_time(8);
  //tbl(1); //blank_time(24);
}

void TMC2240Stepper::push() {
  GCONF(GCONF_register.sr);
  DRV_CONF(DRV_CONF_register.sr);
  IHOLD_IRUN(IHOLD_IRUN_register.sr);
  CHOPCONF(CHOPCONF_register.sr);
  PWMCONF(PWMCONF_register.sr);
}

bool TMC2240Stepper::isEnabled() { return !drv_enn() && toff(); }

uint8_t TMC2240Stepper::IFCNT() {
  return read(IFCNT_t::address);
}

void TMC2240Stepper::SLAVECONF(uint16_t input) {
  SLAVECONF_register.sr = input&0xF00;
  write(SLAVECONF_register.address, SLAVECONF_register.sr);
}

uint16_t TMC2240Stepper::SLAVECONF() {
  return SLAVECONF_register.sr;
}

void TMC2240Stepper::senddelay(uint8_t B)   { SLAVECONF_register.SENDDELAY = B; write(SLAVECONF_register.address, SLAVECONF_register.sr); }
uint8_t TMC2240Stepper::senddelay()     { return SLAVECONF_register.SENDDELAY; }

uint32_t TMC2240Stepper::IOIN() {
  return read(TMC2240_n::IOIN_t::address);
}

bool TMC2240Stepper::step()         { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.step;   }
bool TMC2240Stepper::dir()          { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.dir;    }
bool TMC2240Stepper::encb()         { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.encb;   }
bool TMC2240Stepper::enca()         { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.enca;   }
bool TMC2240Stepper::drv_enn()        { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.drv_enn;  }
bool TMC2240Stepper::encn()         { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.encn;   }
bool TMC2240Stepper::uart_en()        { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.uart_en;  }
bool TMC2240Stepper::comp_a()       { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.comp_a; }
bool TMC2240Stepper::comp_b()       { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.comp_b; }
bool TMC2240Stepper::comp_a1_a2()     { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.comp_a1_a2; }
bool TMC2240Stepper::comp_b1_b2()     { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.comp_b1_b2; }
bool TMC2240Stepper::output()       { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.output; }
bool TMC2240Stepper::ext_res_det()      { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.ext_res_det;  }
bool TMC2240Stepper::ext_clk()          { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.ext_clk;  }
bool TMC2240Stepper::adc_err()        { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.adc_err;  }
uint8_t TMC2240Stepper::silicon_rv()  { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.silicon_rv; }
uint8_t TMC2240Stepper::version()       { TMC2240_n::IOIN_t r{0}; r.sr = IOIN(); return r.version;  }

uint32_t TMC2240Stepper::PWM_SCALE() {
  return read(TMC2240_n::PWM_SCALE_t::address);
}
uint8_t TMC2240Stepper::pwm_scale_sum() {
  TMC2240_n::PWM_SCALE_t r{0};
  r.sr = PWM_SCALE();
  return r.pwm_scale_sum;
}

int16_t TMC2240Stepper::pwm_scale_auto() {
  TMC2240_n::PWM_SCALE_t r{0};
  r.sr = PWM_SCALE();
  return r.pwm_scale_auto;
  // Not two's complement? 9nth bit determines sign
  /*
  uint32_t d = PWM_SCALE();
  int16_t response = (d>>PWM_SCALE_AUTO_bp)&0xFF;
  if (((d&PWM_SCALE_AUTO_bm) >> 24) & 0x1) return -response;
  else return response;
  */
}

// R: PWM_AUTO
uint32_t TMC2240Stepper::PWM_AUTO() {
  return read(PWM_AUTO_t::address);
}
uint8_t TMC2240Stepper::pwm_ofs_auto()  { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_ofs_auto; }
uint8_t TMC2240Stepper::pwm_grad_auto() { PWM_AUTO_t r{0}; r.sr = PWM_AUTO(); return r.pwm_grad_auto; }

/**
 * 0:1A  1:2A  2:3A  3:3A
 */
#define TMC2240_CURRENT_RANGE   2

/**
 * ('rref', 12000, minval=12000, maxval=60000)
 */
#define TMC2240_Rref            12000

uint16_t TMC2240Stepper::cs2rms(uint8_t CS) {
  uint32_t globalscaler = 0;
  float MA, IFS_current_RMS = 0;
  IFS_current_RMS = calc_IFS_current_RMS(TMC2240_CURRENT_RANGE,TMC2240_Rref);
  globalscaler = global_scaler();
  return (float)(CS + 0.5f) * (globalscaler * IFS_current_RMS) / 256 / 32 * 1000;
}

float TMC2240Stepper::calc_IFS_current_RMS(int8_t range, uint32_t Rref) {
  uint32_t Kifs_values[] = { 11750, 24000, 36000, 36000 };
  float IFS_current_RMS = 0;

  IFS_current_RMS=(float)(((float)(Kifs_values[range]) /Rref) /sqrt(2));

  return IFS_current_RMS;
}

uint32_t TMC2240Stepper::set_globalscaler(float current, float IFS_current_RMS) {
  uint32_t globalscaler = 0;
  current /= 1000;
  globalscaler = (int)(((current * 256) / IFS_current_RMS) + 0.5f);

  if (globalscaler < 32) globalscaler = 32;
  if (globalscaler >= 256) globalscaler = 0;
  global_scaler(globalscaler);
  return globalscaler;
}

void TMC2240Stepper::rms_current(uint16_t mA) {
  uint32_t globalscaler, CS = 0;
  float MA, IFS_current_RMS = 0;
  IFS_current_RMS = calc_IFS_current_RMS(TMC2240_CURRENT_RANGE,TMC2240_Rref);
  globalscaler  = set_globalscaler(mA,IFS_current_RMS);
  MA = (float)mA / 1000;
  //globalscaler = global_scaler();
  CS = (int)(((MA * 256 * 32) / (globalscaler * IFS_current_RMS)) - 1 + 0.5f);
  //MA=(float)mA/1000;
  //CS = (int)(((float)(32* MA))/IFS_current_RMS )-0.5;
  if (CS >= 31) CS = 31;
  if (CS <= 0) CS = 0;
  //CS = 30;
  //SERIAL_ECHOLNPGM("CS=", CS);
  irun(CS);
  ihold(CS * holdMultiplier);
}

void TMC2240Stepper::rms_current(uint16_t mA, float mult) {
  holdMultiplier = mult;
  rms_current(mA);
}

uint16_t TMC2240Stepper::rms_current() {
  return cs2rms(irun());
}

void TMC2240Stepper::microsteps(uint16_t ms) {
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

uint16_t TMC2240Stepper::microsteps() {
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

// R+C: GSTAT
uint8_t TMC2240Stepper::GSTAT()        { return read(TMC2240_n::GSTAT_t::address); }
void  TMC2240Stepper::GSTAT(uint8_t)   { write(TMC2240_n::GSTAT_t::address, 0b111); }
bool  TMC2240Stepper::reset()          { TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.reset; }
bool  TMC2240Stepper::drv_err()        { TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.drv_err; }
bool  TMC2240Stepper::uv_cp()          { TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.uv_cp; }
bool  TMC2240Stepper::register_reset() { TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.register_reset; }
bool  TMC2240Stepper::vm_uvlo()        { TMC2240_n::GSTAT_t r; r.sr = GSTAT(); return r.vm_uvlo; }

uint8_t TMC2240Stepper::test_connection() {
  uint32_t drv_status = DRV_STATUS();
  switch (drv_status) {
      case 0xFFFFFFFF: return 1;
      case 0: return 2;
      default: return 0;
  }
}

// W: TPOWERDOWN
uint8_t TMC2240Stepper::TPOWERDOWN() { return TPOWERDOWN_register.sr; }
void TMC2240Stepper::TPOWERDOWN(uint8_t input) {
  TPOWERDOWN_register.sr = input;
  write(TPOWERDOWN_register.address, TPOWERDOWN_register.sr);
}

void TMC2240Stepper::hysteresis_end(int8_t value) { hend(value+3); }
int8_t TMC2240Stepper::hysteresis_end() { return hend()-3; };

void TMC2240Stepper::hysteresis_start(uint8_t value) { hstrt(value-1); }
uint8_t TMC2240Stepper::hysteresis_start() { return hstrt()+1; }
