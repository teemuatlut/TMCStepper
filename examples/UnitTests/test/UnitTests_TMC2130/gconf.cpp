
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint32_t MAX_17bit = 0x1FFFF;

struct test_fixture_set_gconf {
    test_fixture_set_gconf() {
        expectedCommands.emplace_back(0x00, 0); // Read
        expectedCommands.emplace_back(0x00, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_reset_gconf {
    test_fixture_reset_gconf() : driver(SPI, 0, 1.0) {
        expectedCommands.emplace_back(0x00, 0); // Read
        expectedCommands.emplace_back(0x00, 0); // Read
        SPI.responses.emplace_back(0);
        SPI.responses.emplace_back(MAX_17bit);
    }

    SPIClass SPI;
    TMC2130Stepper driver;
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_set_I_scale_analog() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<0); // Write

    test.driver.I_scale_analog(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_internal_Rsense() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<1); // Write

    test.driver.internal_Rsense(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_stealthChop() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<2); // Write

    test.driver.en_pwm_mode(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_enc_commutation() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<3); // Write

    test.driver.enc_commutation(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_shaft() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<4); // Write

    test.driver.shaft(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag0_error() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<5); // Write

    test.driver.diag0_error(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag0_otpw() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<6); // Write

    test.driver.diag0_otpw(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag0_stall() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<7); // Write

    test.driver.diag0_stall(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag1_stall() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<8); // Write

    test.driver.diag1_stall(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag1_index() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<9); // Write

    test.driver.diag1_index(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag1_onstate() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<10); // Write

    test.driver.diag1_onstate(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag1_steps_skipped() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<11); // Write

    test.driver.diag1_steps_skipped(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag0_int_pushpull() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<12); // Write

    test.driver.diag0_int_pushpull(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diag1_pushpull() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<13); // Write

    test.driver.diag1_pushpull(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_small_hysteresis() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<14); // Write

    test.driver.small_hysteresis(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_stop_enable() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<15); // Write

    test.driver.stop_enable(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_direct_mode() {
    test_fixture_set_gconf test{};
    test.expectedCommands.emplace_back(0x80, 1<<16); // Write

    test.driver.direct_mode(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

// test_mode configuration option is not part of the libary

void test_TMC2130_reset_I_scale_analog() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<0) & MAX_17bit); // Write

    test.driver.I_scale_analog(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_internal_Rsense() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<1) & MAX_17bit); // Write

    test.driver.internal_Rsense(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_stealthChop() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<2) & MAX_17bit); // Write

    test.driver.en_pwm_mode(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_enc_commutation() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<3) & MAX_17bit); // Write

    test.driver.enc_commutation(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_shaft() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<4) & MAX_17bit); // Write

    test.driver.shaft(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag0_error() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<5) & MAX_17bit); // Write

    test.driver.diag0_error(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag0_otpw() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<6) & MAX_17bit); // Write

    test.driver.diag0_otpw(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag0_stall() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<7) & MAX_17bit); // Write

    test.driver.diag0_stall(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag1_stall() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<8) & MAX_17bit); // Write

    test.driver.diag1_stall(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag1_index() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<9) & MAX_17bit); // Write

    test.driver.diag1_index(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag1_onstate() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<10) & MAX_17bit); // Write

    test.driver.diag1_onstate(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag1_steps_skipped() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<11) & MAX_17bit); // Write

    test.driver.diag1_steps_skipped(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag0_int_pushpull() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<12) & MAX_17bit); // Write

    test.driver.diag0_int_pushpull(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diag1_pushpull() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<13) & MAX_17bit); // Write

    test.driver.diag1_pushpull(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_small_hysteresis() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<14) & MAX_17bit); // Write

    test.driver.small_hysteresis(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_stop_enable() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<15) & MAX_17bit); // Write

    test.driver.stop_enable(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_direct_mode() {
    test_fixture_reset_gconf test{};
    test.expectedCommands.emplace_back(0x80, ~(1<<16) & MAX_17bit); // Write

    test.driver.direct_mode(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

// test_mode configuration option is not part of the libary
