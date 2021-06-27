
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x68;

struct test_fixture_set_mslutsel {
    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_get_mslutsel {
    SPIClass SPI{};
    MockInterface<TMC2130Stepper, TMC2130Stepper::MSLUTSEL_i> driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

void test_TMC2130_set_mslutsel() {
    test_fixture_set_mslutsel test{};
    uint32_t sr = 7<<24 | 6<<16 | 5<<8 | 3<<6 | 2<<4 | 1<<2 | 3;
    test.expectedCommands.emplace_back(registerAddress | 0x80, sr); // Write

    TMC2130Stepper::MSLUTSEL_t r{};
    r.x3 = 7;
    r.x2 = 6;
    r.x1 = 5;
    r.w3 = 3;
    r.w2 = 2;
    r.w1 = 1;
    r.w0 = 3;

    test.driver.MSLUTSEL(r.sr);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_mslutsel() {
    test_fixture_get_mslutsel test{};
    test.driver.set_register(0x70605E7);

    auto val = test.driver.MSLUTSEL();

    TEST_ASSERT_EQUAL_UINT32(0x70605E7, val);
    TEST_ASSERT_EQUAL_INT(0, test.SPI.transferCalls);
}
