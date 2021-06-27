
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x10;

struct test_fixture_set_ihold_irun {
    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_get_ihold_irun {
    SPIClass SPI{};

    struct Mock_TMC2130 : TMC2130Stepper {
        using TMC2130Stepper::TMC2130Stepper;

        void set_register(const uint32_t new_value) {
            TMC2130Stepper::IHOLD_IRUN_i::r.sr = new_value;
        }
    } driver{SPI, 0, 1.0};

    std::deque<SPIClass::Payload> expectedCommands{};
};

void test_TMC2130_set_ihold() {
    test_fixture_set_ihold_irun test{};
    test.expectedCommands.emplace_back(registerAddress | 0x80, 19); // Write

    test.driver.ihold(19);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_irun() {
    test_fixture_set_ihold_irun test{};
    test.expectedCommands.emplace_back(registerAddress | 0x80, 25<<8); // Write

    test.driver.irun(25);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_iholddelay() {
    test_fixture_set_ihold_irun test{};
    test.expectedCommands.emplace_back(registerAddress | 0x80, 15<<16); // Write

    test.driver.iholddelay(15);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_ihold() {
    test_fixture_get_ihold_irun test{};
    test.driver.set_register(15<<16 | 10<<8 | 7);

    auto val = test.driver.ihold();

    TEST_ASSERT_EQUAL_UINT8(7, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}

void test_TMC2130_get_irun() {
    test_fixture_get_ihold_irun test{};
    test.driver.set_register(15<<16 | 10<<8 | 7);

    auto val = test.driver.irun();

    TEST_ASSERT_EQUAL_UINT8(10, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}

void test_TMC2130_get_iholddelay() {
    test_fixture_get_ihold_irun test{};
    test.driver.set_register(15<<16 | 10<<8 | 7);

    auto val = test.driver.iholddelay();

    TEST_ASSERT_EQUAL_UINT8(15, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}
