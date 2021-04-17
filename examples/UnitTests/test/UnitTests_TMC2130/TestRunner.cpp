
#include <unity.h>
#include "gconf.h"
#include "gstat.h"

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

    RUN_TEST(test_TMC2130_get_reset);
    RUN_TEST(test_TMC2130_get_drv_err);

    UNITY_END();
    return 0;
}
