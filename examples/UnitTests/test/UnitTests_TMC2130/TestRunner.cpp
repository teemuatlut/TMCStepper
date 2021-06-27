
#include <unity.h>
#include "TestRunner.h"


int main(int argc, char **argv) {
    UNITY_BEGIN();

    // GCONF unit tests
    RUN_TEST(test_TMC2130_set_I_scale_analog);
    RUN_TEST(test_TMC2130_set_internal_Rsense);
    RUN_TEST(test_TMC2130_set_stealthChop);
    RUN_TEST(test_TMC2130_set_enc_commutation);
    RUN_TEST(test_TMC2130_set_shaft);
    RUN_TEST(test_TMC2130_set_diag0_error);
    RUN_TEST(test_TMC2130_set_diag0_otpw);
    RUN_TEST(test_TMC2130_set_diag0_stall);
    RUN_TEST(test_TMC2130_set_diag1_stall);
    RUN_TEST(test_TMC2130_set_diag1_index);
    RUN_TEST(test_TMC2130_set_diag1_onstate);
    RUN_TEST(test_TMC2130_set_diag1_steps_skipped);
    RUN_TEST(test_TMC2130_set_diag0_int_pushpull);
    RUN_TEST(test_TMC2130_set_diag1_pushpull);
    RUN_TEST(test_TMC2130_set_small_hysteresis);
    RUN_TEST(test_TMC2130_set_stop_enable);
    RUN_TEST(test_TMC2130_set_direct_mode);

    RUN_TEST(test_TMC2130_reset_I_scale_analog);
    RUN_TEST(test_TMC2130_reset_internal_Rsense);
    RUN_TEST(test_TMC2130_reset_stealthChop);
    RUN_TEST(test_TMC2130_reset_enc_commutation);
    RUN_TEST(test_TMC2130_reset_shaft);
    RUN_TEST(test_TMC2130_reset_diag0_error);
    RUN_TEST(test_TMC2130_reset_diag0_otpw);
    RUN_TEST(test_TMC2130_reset_diag0_stall);
    RUN_TEST(test_TMC2130_reset_diag1_stall);
    RUN_TEST(test_TMC2130_reset_diag1_index);
    RUN_TEST(test_TMC2130_reset_diag1_onstate);
    RUN_TEST(test_TMC2130_reset_diag1_steps_skipped);
    RUN_TEST(test_TMC2130_reset_diag0_int_pushpull);
    RUN_TEST(test_TMC2130_reset_diag1_pushpull);
    RUN_TEST(test_TMC2130_reset_small_hysteresis);
    RUN_TEST(test_TMC2130_reset_stop_enable);
    RUN_TEST(test_TMC2130_reset_direct_mode);

    // GSTAT
    RUN_TEST(test_TMC2130_get_reset);
    RUN_TEST(test_TMC2130_get_drv_err);

    // IOIN
    RUN_TEST(test_TMC2130_get_step);
    RUN_TEST(test_TMC2130_get_dir);
    RUN_TEST(test_TMC2130_get_dcen_cfg4);
    RUN_TEST(test_TMC2130_get_dcin_cfg5);
    RUN_TEST(test_TMC2130_get_drv_enn_cfg6);
    RUN_TEST(test_TMC2130_get_dco);
    RUN_TEST(test_TMC2130_get_version);

    // IHOLD_IRUN
    RUN_TEST(test_TMC2130_set_ihold);
    RUN_TEST(test_TMC2130_set_irun);
    RUN_TEST(test_TMC2130_set_iholddelay);
    RUN_TEST(test_TMC2130_get_ihold);
    RUN_TEST(test_TMC2130_get_irun);
    RUN_TEST(test_TMC2130_get_iholddelay);

    // TPOWERDOWN
    RUN_TEST(test_TMC2130_set_tpowerdown);
    RUN_TEST(test_TMC2130_get_tpowerdown);

    // TSTEP
    RUN_TEST(test_TMC2130_get_tstep);

    // TPWMTHRS
    RUN_TEST(test_TMC2130_set_tpwmthrs);
    RUN_TEST(test_TMC2130_get_tpwmthrs);

    // TCOOLTHRS
    RUN_TEST(test_TMC2130_set_tcoolthrs);
    RUN_TEST(test_TMC2130_get_tcoolthrs);

    // THIGH
    RUN_TEST(test_TMC2130_set_thigh);
    RUN_TEST(test_TMC2130_get_thigh);

    // XDIRECT
    RUN_TEST(test_TMC2130_set_coil_a_max);
    RUN_TEST(test_TMC2130_set_coil_a_min);
    RUN_TEST(test_TMC2130_set_coil_b_max);
    RUN_TEST(test_TMC2130_set_coil_b_min);
    RUN_TEST(test_TMC2130_get_coil_a);
    RUN_TEST(test_TMC2130_get_coil_a_min);
    RUN_TEST(test_TMC2130_get_coil_b);
    RUN_TEST(test_TMC2130_get_coil_b_min);

    // VDCMIN
    RUN_TEST(test_TMC2130_set_vdcmin);
    RUN_TEST(test_TMC2130_get_vdcmin);

    // MSLUT

    // MSLUTSEL
    RUN_TEST(test_TMC2130_set_mslutsel);
    RUN_TEST(test_TMC2130_get_mslutsel);

    // MSLUTSTART
    RUN_TEST(test_TMC2130_set_mslutstart);
    RUN_TEST(test_TMC2130_get_mslutstart);

    // MSCNT
    RUN_TEST(test_TMC2130_get_mscnt);

    // MSCURACT
    RUN_TEST(test_TMC2130_get_cur_a);
    RUN_TEST(test_TMC2130_get_cur_b);

    // CHOPCONF
    RUN_TEST(test_TMC2130_set_toff);
    RUN_TEST(test_TMC2130_set_hstrt);
    RUN_TEST(test_TMC2130_set_hend);
    RUN_TEST(test_TMC2130_set_disfdcc);
    RUN_TEST(test_TMC2130_set_rndtf);
    RUN_TEST(test_TMC2130_set_chm);
    RUN_TEST(test_TMC2130_set_tbl);
    RUN_TEST(test_TMC2130_set_vsense);
    RUN_TEST(test_TMC2130_set_vhighfs);
    RUN_TEST(test_TMC2130_set_vhighchm);
    RUN_TEST(test_TMC2130_set_sync);
    RUN_TEST(test_TMC2130_set_mres);
    RUN_TEST(test_TMC2130_set_intpol);
    RUN_TEST(test_TMC2130_set_dedge);
    RUN_TEST(test_TMC2130_set_diss2g);
    RUN_TEST(test_TMC2130_reset_toff);
    RUN_TEST(test_TMC2130_reset_hstrt);
    RUN_TEST(test_TMC2130_reset_hend);
    RUN_TEST(test_TMC2130_reset_disfdcc);
    RUN_TEST(test_TMC2130_reset_rndtf);
    RUN_TEST(test_TMC2130_reset_chm);
    RUN_TEST(test_TMC2130_reset_tbl);
    RUN_TEST(test_TMC2130_reset_vsense);
    RUN_TEST(test_TMC2130_reset_vhighfs);
    RUN_TEST(test_TMC2130_reset_vhighchm);
    RUN_TEST(test_TMC2130_reset_sync);
    RUN_TEST(test_TMC2130_reset_mres);
    RUN_TEST(test_TMC2130_reset_intpol);
    RUN_TEST(test_TMC2130_reset_dedge);
    RUN_TEST(test_TMC2130_reset_diss2g);
    RUN_TEST(test_TMC2130_get_toff);
    RUN_TEST(test_TMC2130_get_hstrt);
    RUN_TEST(test_TMC2130_get_hend);
    RUN_TEST(test_TMC2130_get_disfdcc);
    RUN_TEST(test_TMC2130_get_rndtf);
    RUN_TEST(test_TMC2130_get_chm);
    RUN_TEST(test_TMC2130_get_tbl);
    RUN_TEST(test_TMC2130_get_vsense);
    RUN_TEST(test_TMC2130_get_vhighfs);
    RUN_TEST(test_TMC2130_get_vhighchm);
    RUN_TEST(test_TMC2130_get_sync);
    RUN_TEST(test_TMC2130_get_mres);
    RUN_TEST(test_TMC2130_get_intol);
    RUN_TEST(test_TMC2130_get_dedge);
    RUN_TEST(test_TMC2130_get_diss2g);

    // COOLCONF
    RUN_TEST(test_TMC2130_set_semin);
    RUN_TEST(test_TMC2130_set_seup);
    RUN_TEST(test_TMC2130_set_semax);
    RUN_TEST(test_TMC2130_set_sedn);
    RUN_TEST(test_TMC2130_set_seimin);
    RUN_TEST(test_TMC2130_set_sgt_max);
    RUN_TEST(test_TMC2130_set_sgt_min);
    RUN_TEST(test_TMC2130_set_sfilt);
    RUN_TEST(test_TMC2130_reset_semin);
    RUN_TEST(test_TMC2130_reset_seup);
    RUN_TEST(test_TMC2130_reset_semax);
    RUN_TEST(test_TMC2130_reset_sedn);
    RUN_TEST(test_TMC2130_reset_seimin);
    RUN_TEST(test_TMC2130_reset_sgt);
    RUN_TEST(test_TMC2130_reset_sfilt);
    RUN_TEST(test_TMC2130_get_semin);
    RUN_TEST(test_TMC2130_get_seup);
    RUN_TEST(test_TMC2130_get_semax);
    RUN_TEST(test_TMC2130_get_sedn);
    RUN_TEST(test_TMC2130_get_seimin);
    RUN_TEST(test_TMC2130_get_sgt_max);
    RUN_TEST(test_TMC2130_get_sgt_min);
    RUN_TEST(test_TMC2130_get_sfilt);

    UNITY_END();
    return 0;
}
