#pragma once

#define SELF this->self()
#define TT template<typename T>

#define REG(R) this->R##_register
#define ADR(R) this->R##_address
//#define WRITE_REG(R) SELF.write(REG(R).address, REG(R).sr)
//#define READ_REG(R) SELF.read(REG(R).address)

#define DEBUG_PRINT(CFG, VAL) do{ Serial.print(CFG); Serial.print('('); Serial.print(VAL, HEX); Serial.println(')'); }while(0)
