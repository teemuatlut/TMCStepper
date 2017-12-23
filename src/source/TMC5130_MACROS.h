#pragma once

#include "TMCStepper.h"

#define WRITE_REG(R) 	write(cfg.TMC_WRITE|cfg.REG_##R, R##_sr);

#define READ_REG(R)   	read(cfg.TMC_READ|cfg.REG_##R, &R##_sr); return R##_sr

#define READ_REG_R(R)   tmp_sr=0; read(cfg.TMC_READ|cfg.REG_##R, &tmp_sr); return tmp_sr;

#define MOD_REG(REG, SETTING) 	REG##_sr &= ~cfg.SETTING##_bm; \
								REG##_sr |= ((uint32_t)B<<cfg.SETTING##_bp)&cfg.SETTING##_bm; \
								WRITE_REG(REG);

#define GET_BYTE(REG, SETTING) 	return (REG()&cfg.SETTING##_bm) >> cfg.SETTING##_bp;

#define GET_BYTE_R(REG, SETTING) return (REG()&cfg.SETTING##_bm) >> cfg.SETTING##_bp;

#define GET_BIT(REG, SETTING) 	return (bool)((REG()&cfg.SETTING##_bm) >> cfg.SETTING##_bp);
