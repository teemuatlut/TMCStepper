#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x6B;

struct test_fixture_get_mscuract {
    test_fixture_get_mscuract(const uint32_t responseValue) {
        SPI.responses.emplace_back(0);
        SPI.responses.emplace_back(responseValue);
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_get_cur_a() {
    test_fixture_get_mscuract test{ 0x106 };

    auto val = test.driver.cur_a();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_INT8(-250, val);
}

void test_TMC2130_get_cur_b() {
    test_fixture_get_mscuract test{ (-250 & 0x1FF)<<16 };

    auto val = test.driver.cur_b();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_INT8(-250, val);
}
