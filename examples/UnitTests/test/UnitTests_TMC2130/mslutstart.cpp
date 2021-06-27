
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x69;

struct test_fixture_set_mslutstart {
    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_get_mslutstart {
    SPIClass SPI{};
    MockInterface<TMC2130Stepper, TMC2130Stepper::MSLUTSTART_i> driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

void test_TMC2130_set_mslutstart() {
    test_fixture_set_mslutstart test{};
    test.expectedCommands.emplace_back(registerAddress | 0x80, 180 << 16 | 75); // Write

    test.driver.MSLUTSTART(180 << 16 | 75);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_mslutstart() {
    test_fixture_get_mslutstart test{};
    test.driver.set_register(0x00FF00FF);

    auto val = test.driver.MSLUTSTART();

    TEST_ASSERT_EQUAL_UINT32(0x00FF00FF, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}
