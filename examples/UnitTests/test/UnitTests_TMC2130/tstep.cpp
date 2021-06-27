
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x12;

struct test_fixture_get_tstep {
    test_fixture_get_tstep(const uint32_t responseValue) {
        SPI.responses.emplace_back(0);
        SPI.responses.emplace_back(responseValue);
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_get_tstep() {
    test_fixture_get_tstep test{10000};

    auto tstep = test.driver.TSTEP();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_UINT32(10000, tstep);
}
