#include "TMCStepper.h"

inline void TMCStepper::switchCSpin(bool state) {
  // Allows for overriding in child class to make use of fast io
  digitalWrite(_pinCS, state);
}

void TMCStepper::read(uint8_t addressByte, uint32_t *config) {
  //uint8_t s;
  SPI.begin();
  SPI.beginTransaction(SPISettings(16000000/8, MSBFIRST, SPI_MODE3));
  //digitalWrite(_pinCS, LOW);
  switchCSpin(LOW);

  SPI.transfer(addressByte & 0xFF); // s = 
  #ifdef TMCDEBUG
    Serial.print("READ");
    Serial.print("\t| A=");
    Serial.print(addressByte&0x7F, HEX);
    Serial.print("\t| ");
    Serial.print(*config, HEX);
    Serial.print("\t| s=");
    Serial.print(status_response, HEX);
  #endif

  SPI.transfer16(0x0000); // Clear SPI
  SPI.transfer16(0x0000);
  //digitalWrite(_pinCS, HIGH);
  //digitalWrite(_pinCS, LOW);
  switchCSpin(HIGH);
  switchCSpin(LOW);

  SPI.transfer(addressByte & 0xFF); // Send the address byte again
  *config  = SPI.transfer(0x00);
  *config <<= 8;
  *config |= SPI.transfer(0x00);
  *config <<= 8;
  *config |= SPI.transfer(0x00);
  *config <<= 8;
  *config |= SPI.transfer(0x00);
  #ifdef TMCDEBUG
    Serial.print("\t| R=");
    Serial.print(*config, HEX);
    Serial.println();
  #endif

  //digitalWrite(_pinCS, HIGH);
  switchCSpin(HIGH);
  SPI.endTransaction();

  //return s;
}

void TMCStepper::setSPISpeed(uint32_t speed) {
  spi_speed = speed;
}

uint32_t TMCStepper::setBits(uint32_t sr, uint32_t bitmask, uint8_t bitpos, uint8_t B) {
  /*
  Serial.print("setBits(0b");
  Serial.print(sr, BIN);
  Serial.print(", 0x");
  Serial.print(bitmask, HEX);
  Serial.print(", ");
  Serial.print(bitpos);
  Serial.print(", 0b");
  Serial.print(B, BIN);
  Serial.println(')');
  ^*/
  sr &= ~bitmask; // Clear config area
  /*
  Serial.print("sr=");
  Serial.println(sr);
  */
  sr |= ((uint32_t)B<<bitpos)&bitmask; // Set bits
  /*
  Serial.print("sr=");
  Serial.println(sr);
  */
  return sr;
}

uint32_t TMCStepper::getBits(uint32_t sr, uint32_t bitmask, uint8_t bitpos) {
  return (sr&bitmask) >> bitpos;
}

bool TMC5130Stepper::checkOT() {
  uint32_t response = DRV_STATUS();
  if (response & cfg.OTPW_bm) {
    flag_otpw = 1;
    return true; // bit 26 for overtemperature warning flag
  }
  return false;
}

bool TMC5130Stepper::getOTPW() { return flag_otpw; }

void TMC5130Stepper::clear_otpw() { flag_otpw = 0; }

/*  
  Requested current = mA = I_rms/1000
  Equation for current:
  I_rms = (CS+1)/32 * V_fs/(R_sense+0.02ohm) * 1/sqrt(2)
  Solve for CS ->
  CS = 32*sqrt(2)*I_rms*(R_sense+0.02)/V_fs - 1
  
  Example:
  vsense = 0b0 -> V_fs = 0.325V
  mA = 1640mA = I_rms/1000 = 1.64A
  R_sense = 0.10 Ohm
  ->
  CS = 32*sqrt(2)*1.64*(0.10+0.02)/0.325 - 1 = 26.4
  CS = 26
*/  
void TMC5130Stepper::rms_current(uint16_t mA, float multiplier, float RS) {
  Rsense = RS;
  uint8_t CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.325 - 1;
  // If Current Scale is too low, turn on high sensitivity R_sense and calculate again
  if (CS < 16) {
    vsense(true);
    CS = 32.0*1.41421*mA/1000.0*(Rsense+0.02)/0.180 - 1;
  } else if(vsense()) { // If CS >= 16, turn off high_sense_r if it's currently ON
    vsense(false);
  }
  irun(CS);
  ihold(CS*multiplier);
  val_mA = mA;
}

uint16_t TMC5130Stepper::rms_current() {
  return (float)(irun()+1)/32.0 * (vsense()?0.180:0.325)/(Rsense+0.02) / 1.41421 * 1000;
}

void TMC5130Stepper::setCurrent(uint16_t mA, float R, float multiplier) { rms_current(mA, multiplier, R); }
uint16_t TMC5130Stepper::getCurrent() { return val_mA; }
