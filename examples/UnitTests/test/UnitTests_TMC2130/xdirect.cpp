
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x2D;

struct test_fixture_set_xdirect {
    test_fixture_set_xdirect() {
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_get_xdirect {
    test_fixture_get_xdirect(const uint32_t responseValue) {
        SPI.responses.emplace_back(0);
        SPI.responses.emplace_back(responseValue);
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_set_coil_a_max() {
    test_fixture_set_xdirect test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 255); // Write

    test.driver.coil_A(255);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_coil_a_min() {
    test_fixture_set_xdirect test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 0x106); // Write

    test.driver.coil_A(-250);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_coil_b_max() {
    test_fixture_set_xdirect test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 255<<16); // Write

    test.driver.coil_B(255);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_coil_b_min() {
    test_fixture_set_xdirect test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, (-245 & 0x1FF)<<16); // Write

    test.driver.coil_B(-245);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_coil_a() {
    test_fixture_get_xdirect test{255};

    auto coil_a = test.driver.coil_A();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_INT16(255, coil_a);
}

void test_TMC2130_get_coil_a_min() {
    test_fixture_get_xdirect test{0x10F};

    auto coil_a = test.driver.coil_A();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_INT16(-241, coil_a);
}

void test_TMC2130_get_coil_b() {
    test_fixture_get_xdirect test{255<<16};

    auto coil_b = test.driver.coil_B();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_INT16(255, coil_b);
}

void test_TMC2130_get_coil_b_min() {
    test_fixture_get_xdirect test{0x10F<<16};

    auto coil_b = test.driver.coil_B();

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
    TEST_ASSERT_EQUAL_INT16(-241, coil_b);
}
