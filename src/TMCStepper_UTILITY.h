#ifndef TMCStepper_UTILITY_h
#define TMCStepper_UTILITY_h

void print_HEX(uint32_t data) {
  for (uint8_t digits = 8; digits--;) {
    Serial.print((data >> 28) & 0xFUL, HEX);
    data <<= 4;
  }
}

void print_BIN(uint32_t data) {
  for (uint8_t digits = 32; digits--;) {
    Serial.print((data & 0x8000UL) ? '1' : '0');
    data <<= 1;
    if ((digits & 0x7) == 0x7 && digits < 24) Serial.print('.');
  }
}

#endif
