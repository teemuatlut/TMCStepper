
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x6D;

struct test_fixture_set_coolconf {
    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_reset_coolconf {
    test_fixture_reset_coolconf() : driver(SPI, 0, 1.0) {
        driver.COOLCONF(0xFFFFFFFF);
        SPI.sentCommands.clear();
    }

    SPIClass SPI;
    TMC2130Stepper driver;
    std::deque<SPIClass::Payload> expectedCommands;
};

struct test_fixture_get_coolconf {
    SPIClass SPI{};

    struct Mock_TMC2130 : TMC2130Stepper {
        using TMC2130Stepper::TMC2130Stepper;

        void set_register(const uint32_t new_value) {
            TMC2130Stepper::COOLCONF_i::r.sr = new_value;
        }
    } driver{SPI, 0, 1.0};

    std::deque<SPIClass::Payload> expectedCommands{};
};

void test_TMC2130_set_semin() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 15); // Write

    test.driver.semin(15);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_seup() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 3<<5); // Write

    test.driver.seup(3);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_semax() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 15<<8); // Write

    test.driver.semax(15);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_sedn() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 3<<13); // Write

    test.driver.sedn(3);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_seimin() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<15); // Write

    test.driver.seimin(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_sgt_max() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 63<<16); // Write

    test.driver.sgt(63);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_sgt_min() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, (-64&0x7F)<<16); // Write

    test.driver.sgt(-64);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_sfilt() {
    test_fixture_set_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<24); // Write

    test.driver.sfilt(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_TMC2130_reset_semin() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(15<<0) & 0x01FFFFFF); // Write

    test.driver.semin(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_seup() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(3<<5) & 0x01FFFFFF); // Write

    test.driver.seup(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_semax() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(15<<8) & 0x01FFFFFF); // Write

    test.driver.semax(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_sedn() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(3<<13) & 0x01FFFFFF); // Write

    test.driver.sedn(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_seimin() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<15) & 0x01FFFFFF); // Write

    test.driver.seimin(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_sgt() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(0x7F<<16) & 0x01FFFFFF); // Write

    test.driver.sgt(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_sfilt() {
    test_fixture_reset_coolconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<24) & 0x01FFFFFF); // Write

    test.driver.sfilt(false);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void test_TMC2130_get_semin() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(15); // Read

    const auto val = test.driver.semin();

    TEST_ASSERT_EQUAL_UINT8(15, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_seup() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(3<<5); // Read

    const auto val = test.driver.seup();

    TEST_ASSERT_EQUAL_UINT8(3, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_semax() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(15<<8); // Read

    const auto val = test.driver.semax();

    TEST_ASSERT_EQUAL_UINT8(15, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_sedn() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(3<<13); // Read

    const auto val = test.driver.sedn();

    TEST_ASSERT_EQUAL_UINT8(3, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_seimin() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(1<<15); // Read

    const auto val = test.driver.seimin();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_sgt_max() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(63<<16); // Read

    const auto val = test.driver.sgt();

    TEST_ASSERT_EQUAL_UINT8(63, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_sgt_min() {
    test_fixture_get_coolconf test{};
    test.driver.set_register((-64&0x7F)<<16); // Read

    const auto val = test.driver.sgt();

    TEST_ASSERT_EQUAL_INT8(-64, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_sfilt() {
    test_fixture_get_coolconf test{};
    test.driver.set_register(1<<24); // Read

    const auto val = test.driver.sfilt();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

