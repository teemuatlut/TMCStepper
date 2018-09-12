#include "TMCStepper.h"
#include "TMC_DECL.h"

#define SET_REG(SETTING) do{ REG(SGCSCONF).SETTING = B; SELF.write(ADR(SGCSCONF), REG(SGCSCONF).sr);; }while(0)
#define GET_REG(SETTING) return REG(SGCSCONF).SETTING

uint32_t TMC2660Stepper::SGCSCONF() { return REG(SGCSCONF).sr; }
void TMC2660Stepper::SGCSCONF(uint32_t data) {
  REG(SGCSCONF).sr = data;
  SELF.write(ADR(SGCSCONF), REG(SGCSCONF).sr);
}

void TMC2660Stepper::sfilt(bool B) 	{ SET_REG(sfilt); }
void TMC2660Stepper::sgt(uint8_t B) { SET_REG(sgt); }
void TMC2660Stepper::cs(uint8_t B) 	{ SET_REG(cs); }

bool TMC2660Stepper::sfilt() { GET_REG(sfilt); }
uint8_t TMC2660Stepper::sgt(){ GET_REG(sgt); }
uint8_t TMC2660Stepper::cs() { GET_REG(cs); }
