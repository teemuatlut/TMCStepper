#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x04;

struct test_fixture_get_ioin {
    test_fixture_get_ioin(const uint32_t responseValue) {
        SPI.responses.emplace_back(0);
        SPI.responses.emplace_back(responseValue);
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_get_step() {
    test_fixture_get_ioin test{0x1};

    auto bit = test.driver.step();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_dir() {
    test_fixture_get_ioin test{0x2};

    auto bit = test.driver.dir();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_dcen_cfg4() {
    test_fixture_get_ioin test{0x4};

    auto bit = test.driver.dcen_cfg4();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_dcin_cfg5() {
    test_fixture_get_ioin test{0x8};

    auto bit = test.driver.dcin_cfg5();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_drv_enn_cfg6() {
    test_fixture_get_ioin test{0x10};

    auto bit = test.driver.drv_enn_cfg6();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_dco() {
    test_fixture_get_ioin test{0x20};

    auto bit = test.driver.dco();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_TRUE(bit);
}

void test_TMC2130_get_version() {
    test_fixture_get_ioin test{0x11 << 24};

    auto version = test.driver.version();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_UINT8(0x11, version);
}
