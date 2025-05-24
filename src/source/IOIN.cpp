/**
 * TMCStepper library by @teemuatlut
 * IOIN.cpp - Driver Control
 * TMC2130 (TMC5160, TMC5161), TMC2160, TMC5130, TMC2208, TMC2209, TMC2224, TMC2240
 */
#include "TMCStepper.h"
#include "TMC_MACROS.h"

#define GET_REG_NS(NS, SETTING) NS::IOIN_t r{0}; r.sr = IOIN(); return r.SETTING

//
// TMC2130
//
#define GET_REG(SETTING) IOIN_t r{0}; r.sr = IOIN(); return r.SETTING

uint32_t TMC2130Stepper::IOIN()			{ return read(IOIN_t::address); }
bool	TMC2130Stepper::step()			{ GET_REG(step);		}
bool	TMC2130Stepper::dir()			{ GET_REG(dir);			}
bool	TMC2130Stepper::dcen_cfg4()		{ GET_REG(dcen_cfg4);	}
bool	TMC2130Stepper::dcin_cfg5()		{ GET_REG(dcin_cfg5);	}
bool	TMC2130Stepper::drv_enn_cfg6()	{ GET_REG(drv_enn_cfg6);}
bool	TMC2130Stepper::dco()			{ GET_REG(dco);			}
uint8_t TMC2130Stepper::version()		{ GET_REG(version);		}

//
// TMC2160
//
#define GET_REG_2160(SETTING) GET_REG_NS(TMC2160_n, SETTING)

uint32_t TMC2160Stepper::IOIN()				{ return read(TMC2160_n::IOIN_t::address); }
bool	TMC2160Stepper::refl_step()			{ GET_REG_2160(refl_step);		}
bool	TMC2160Stepper::refr_dir()			{ GET_REG_2160(refr_dir);		}
bool	TMC2160Stepper::encb_dcen_cfg4()	{ GET_REG_2160(encb_dcen_cfg4);	}
bool	TMC2160Stepper::enca_dcin_cfg5()	{ GET_REG_2160(enca_dcin_cfg5);	}
bool	TMC2160Stepper::drv_enn()			{ GET_REG_2160(drv_enn);		}
bool	TMC2160Stepper::dco_cfg6()			{ GET_REG_2160(dco_cfg6);		}
uint8_t	TMC2160Stepper::version()			{ GET_REG_2160(version);		}

//
// TMC2208
//
#define GET_REG_2208(SETTING) GET_REG_NS(TMC2208_n, SETTING)

uint32_t TMC2208Stepper::IOIN()		{ return read(TMC2208_n::IOIN_t::address); }
bool	TMC2208Stepper::enn()		{ GET_REG_2208(enn);		}
bool	TMC2208Stepper::ms1()		{ GET_REG_2208(ms1);		}
bool	TMC2208Stepper::ms2()		{ GET_REG_2208(ms2);		}
bool	TMC2208Stepper::diag()		{ GET_REG_2208(diag);		}
bool	TMC2208Stepper::pdn_uart()	{ GET_REG_2208(pdn_uart);	}
bool	TMC2208Stepper::step()		{ GET_REG_2208(step);		}
bool	TMC2208Stepper::sel_a()		{ GET_REG_2208(sel_a);		}
bool	TMC2208Stepper::dir()		{ GET_REG_2208(dir);		}
uint8_t	TMC2208Stepper::version() 	{ GET_REG_2208(version);	}

//
// TMC2209
//
#define GET_REG_2209(SETTING) GET_REG_NS(TMC2209_n, SETTING)

uint32_t TMC2209Stepper::IOIN()		{ return read(TMC2209_n::IOIN_t::address); }
bool	TMC2209Stepper::enn()		{ GET_REG_2209(enn);		}
bool	TMC2209Stepper::ms1()		{ GET_REG_2209(ms1);		}
bool	TMC2209Stepper::ms2()		{ GET_REG_2209(ms2);		}
bool	TMC2209Stepper::diag()		{ GET_REG_2209(diag);		}
bool	TMC2209Stepper::pdn_uart()	{ GET_REG_2209(pdn_uart);	}
bool	TMC2209Stepper::step()		{ GET_REG_2209(step);		}
bool	TMC2209Stepper::spread_en()	{ GET_REG_2209(spread_en);	}
bool	TMC2209Stepper::dir()		{ GET_REG_2209(dir);		}
uint8_t	TMC2209Stepper::version() 	{ GET_REG_2209(version);	}

//
// TMC2224
//
#define GET_REG_2224(SETTING) GET_REG_NS(TMC2224_n, SETTING)

uint32_t TMC2224Stepper::IOIN()		{ return read(TMC2224_n::IOIN_t::address); }
bool TMC2224Stepper::enn()			{ GET_REG_2224(enn);		}
bool TMC2224Stepper::ms1()			{ GET_REG_2224(ms1);		}
bool TMC2224Stepper::ms2()			{ GET_REG_2224(ms2);		}
bool TMC2224Stepper::pdn_uart()		{ GET_REG_2224(pdn_uart);	}
bool TMC2224Stepper::spread()		{ GET_REG_2224(spread);		}
bool TMC2224Stepper::step()			{ GET_REG_2224(step);		}
bool TMC2224Stepper::sel_a()		{ GET_REG_2224(sel_a);		}
bool TMC2224Stepper::dir()			{ GET_REG_2224(dir);		}
uint8_t TMC2224Stepper::version() 	{ GET_REG_2224(version);	}

//
// TMC2240
//
#define GET_REG_2240(SETTING) GET_REG_NS(TMC2240_n, SETTING)

uint32_t TMC2240Stepper::IOIN()			{ return read(TMC2240_n::IOIN_t::address); }
bool	TMC2240Stepper::step()			{ GET_REG_2240(step);		}
bool	TMC2240Stepper::dir()			{ GET_REG_2240(dir);		}
bool	TMC2240Stepper::encb()			{ GET_REG_2240(encb);		}
bool	TMC2240Stepper::enca()			{ GET_REG_2240(enca);		}
bool	TMC2240Stepper::drv_enn()		{ GET_REG_2240(drv_enn);	}
bool	TMC2240Stepper::encn()			{ GET_REG_2240(encn);		}
bool	TMC2240Stepper::uart_en()		{ GET_REG_2240(uart_en);	}
bool	TMC2240Stepper::comp_a()		{ GET_REG_2240(comp_a);		}
bool	TMC2240Stepper::comp_b()		{ GET_REG_2240(comp_b);		}
bool	TMC2240Stepper::comp_a1_a2()	{ GET_REG_2240(comp_a1_a2);	}
bool	TMC2240Stepper::comp_b1_b2()	{ GET_REG_2240(comp_b1_b2);	}
bool	TMC2240Stepper::output()		{ GET_REG_2240(output);		}
bool	TMC2240Stepper::ext_res_det()	{ GET_REG_2240(ext_res_det);}
bool	TMC2240Stepper::ext_clk()		{ GET_REG_2240(ext_clk);	}
bool	TMC2240Stepper::adc_err()		{ GET_REG_2240(adc_err);	}
uint8_t	TMC2240Stepper::silicon_rv()	{ GET_REG_2240(silicon_rv);	}
uint8_t	TMC2240Stepper::version()		{ GET_REG_2240(version);	}

//
// TMC5130
//
#define GET_REG_5130(SETTING) GET_REG_NS(TMC5130_n, SETTING)

uint32_t TMC5130Stepper::IOIN()			{ return read(TMC5130_n::IOIN_t::address); }
bool	TMC5130Stepper::refl_step()		{ GET_REG_5130(refl_step);		}
bool	TMC5130Stepper::refr_dir()		{ GET_REG_5130(refr_dir);		}
bool	TMC5130Stepper::encb_dcen_cfg4(){ GET_REG_5130(encb_dcen_cfg4);	}
bool	TMC5130Stepper::enca_dcin_cfg5(){ GET_REG_5130(enca_dcin_cfg5);	}
bool	TMC5130Stepper::drv_enn_cfg6()	{ GET_REG_5130(drv_enn_cfg6);	}
bool	TMC5130Stepper::enc_n_dco()		{ GET_REG_5130(enc_n_dco);		}
bool	TMC5130Stepper::sd_mode()		{ GET_REG_5130(sd_mode);		}
bool	TMC5130Stepper::swcomp_in()		{ GET_REG_5130(swcomp_in);		}
uint8_t	TMC5130Stepper::version()		{ GET_REG_5130(version);		}
