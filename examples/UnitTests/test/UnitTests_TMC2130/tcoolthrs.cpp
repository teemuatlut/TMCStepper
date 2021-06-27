
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x14;

struct test_fixture_set_tcoolthrs {
    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_get_tcoolthrs {
    SPIClass SPI{};
    MockInterface<TMC2130Stepper, TMC2130Stepper::TCOOLTHRS_i> driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

void test_TMC2130_set_tcoolthrs() {
    test_fixture_set_tcoolthrs test{};
    test.expectedCommands.emplace_back(registerAddress | 0x80, 150); // Write

    test.driver.TCOOLTHRS(150);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_tcoolthrs() {
    test_fixture_get_tcoolthrs test{};
    test.driver.set_register(200);

    auto val = test.driver.TCOOLTHRS();

    TEST_ASSERT_EQUAL_UINT8(200, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}
