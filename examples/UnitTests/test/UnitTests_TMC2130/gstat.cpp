#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint32_t MAX_17bit = 0x1FFFF;
static constexpr uint8_t registerAddress = 0x01;

struct test_fixture_get_gstat {
    test_fixture_get_gstat() {
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, initValue); // Read
    }

    const uint8_t initValue = 0x3;
    SPIClass SPI{initValue};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_get_reset() {
    test_fixture_get_gstat test{};

    auto bit = test.driver.reset();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_drv_err() {
    test_fixture_get_gstat test{};

    auto bit = test.driver.drv_err();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}
