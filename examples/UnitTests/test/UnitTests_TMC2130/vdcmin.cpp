
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x33;

struct test_fixture_set_vdcmin {
    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_get_vdcmin {
    SPIClass SPI{};
    MockInterface<TMC2130Stepper, TMC2130Stepper::VDCMIN_i> driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

void test_TMC2130_set_vdcmin() {
    test_fixture_set_vdcmin test{};
    test.expectedCommands.emplace_back(registerAddress | 0x80, 150); // Write

    test.driver.VDCMIN(150);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_vdcmin() {
    test_fixture_get_vdcmin test{};
    test.driver.set_register(20000);

    auto val = test.driver.VDCMIN();

    TEST_ASSERT_EQUAL_UINT32(20000, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}
