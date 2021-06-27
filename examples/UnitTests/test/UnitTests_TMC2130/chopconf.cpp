
#include <algorithm>
#include <unity.h>
#include <TMCStepper.h>
#include "Mocks.h"

static constexpr uint8_t registerAddress = 0x6C;

struct test_fixture_set_chopconf {
    test_fixture_set_chopconf() {
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
    }

    SPIClass SPI{};
    TMC2130Stepper driver{SPI, 0, 1.0};
    std::deque<SPIClass::Payload> expectedCommands{};
};

struct test_fixture_reset_chopconf {
    test_fixture_reset_chopconf() : driver(SPI, 0, 1.0) {
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
        SPI.responses.emplace_back(0);
        SPI.responses.emplace_back(0xFFFFFFFF);
    }

    SPIClass SPI;
    TMC2130Stepper driver;
    std::deque<SPIClass::Payload> expectedCommands;
};

struct test_fixture_get_chopconf {
    test_fixture_get_chopconf() : driver(SPI, 0, 1.0) {
        expectedCommands.emplace_back(registerAddress, 0); // Read
        expectedCommands.emplace_back(registerAddress, 0); // Read
        SPI.responses.emplace_back(0);
    }

    SPIClass SPI;
    TMC2130Stepper driver;
    std::deque<SPIClass::Payload> expectedCommands;
};

void test_TMC2130_set_toff() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 15); // Write

    test.driver.toff(15);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_hstrt() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 7<<4); // Write

    test.driver.hstrt(7);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_hend() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 15<<7); // Write

    test.driver.hend(15);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_disfdcc() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<12); // Write

    test.driver.disfdcc(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_rndtf() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<13); // Write

    test.driver.rndtf(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_chm() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<14); // Write

    test.driver.chm(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_tbl() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 3<<15); // Write

    test.driver.tbl(3);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_vsense() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<17); // Write

    test.driver.vsense(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_vhighfs() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<18); // Write

    test.driver.vhighfs(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_vhighchm() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<19); // Write

    test.driver.vhighchm(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_sync() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 15<<20); // Write

    test.driver.sync(15);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_mres() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 8<<24); // Write

    test.driver.mres(8);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_intpol() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<28); // Write

    test.driver.intpol(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_dedge() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<29); // Write

    test.driver.dedge(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_set_diss2g() {
    test_fixture_set_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, 1<<30); // Write

    test.driver.diss2g(true);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_toff() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(15<<0) & 0xFFFFFFFF); // Write

    test.driver.toff(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_hstrt() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(7<<4) & 0xFFFFFFFF); // Write

    test.driver.hstrt(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_hend() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(15<<7) & 0xFFFFFFFF); // Write

    test.driver.hend(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_disfdcc() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<12) & 0xFFFFFFFF); // Write

    test.driver.disfdcc(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_rndtf() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<13) & 0xFFFFFFFF); // Write

    test.driver.rndtf(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_chm() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<14) & 0xFFFFFFFF); // Write

    test.driver.chm(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_tbl() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(3<<15) & 0xFFFFFFFF); // Write

    test.driver.tbl(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_vsense() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<17) & 0xFFFFFFFF); // Write

    test.driver.vsense(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_vhighfs() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<18) & 0xFFFFFFFF); // Write

    test.driver.vhighfs(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_vhighchm() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<19) & 0xFFFFFFFF); // Write

    test.driver.vhighchm(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_sync() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(15<<20) & 0xFFFFFFFF); // Write

    test.driver.sync(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_mres() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(15<<24) & 0xFFFFFFFF); // Write

    test.driver.mres(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_intpol() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<28) & 0xFFFFFFFF); // Write

    test.driver.intpol(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_dedge() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<29) & 0xFFFFFFFF); // Write

    test.driver.dedge(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_reset_diss2g() {
    test_fixture_reset_chopconf test{};
    test.expectedCommands.emplace_back(0x80 | registerAddress, ~(1<<30) & 0xFFFFFFFF); // Write

    test.driver.diss2g(0);

    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_toff() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(3); // Read

    const auto val = test.driver.toff();

    TEST_ASSERT_EQUAL_UINT8(3, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_hstrt() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(6<<4); // Read

    const auto val = test.driver.hstrt();

    TEST_ASSERT_EQUAL_UINT8(6, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_hend() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(15<<7); // Read

    const auto val = test.driver.hend();

    TEST_ASSERT_EQUAL_UINT8(15, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_disfdcc() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<12); // Read

    const auto val = test.driver.disfdcc();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_rndtf() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<13); // Read

    const auto val = test.driver.rndtf();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_chm() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<14); // Read

    const auto val = test.driver.chm();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_tbl() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(3<<15); // Read

    const auto val = test.driver.tbl();

    TEST_ASSERT_EQUAL_UINT8(3, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_vsense() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<17); // Read

    const auto val = test.driver.vsense();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_vhighfs() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<18); // Read

    const auto val = test.driver.vhighfs();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_vhighchm() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<19); // Read

    const auto val = test.driver.vhighchm();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_sync() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(15<<20); // Read

    const auto val = test.driver.sync();

    TEST_ASSERT_EQUAL_UINT8(15, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_mres() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(4<<24); // Read

    const auto val = test.driver.mres();

    TEST_ASSERT_EQUAL_UINT8(4, val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_intol() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<28); // Read

    const auto val = test.driver.intpol();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_dedge() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<29); // Read

    const auto val = test.driver.dedge();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}

void test_TMC2130_get_diss2g() {
    test_fixture_get_chopconf test{};
    test.SPI.responses.emplace_back(1<<30); // Read

    const auto val = test.driver.diss2g();

    TEST_ASSERT_TRUE(val);
    TEST_ASSERT_TRUE_MESSAGE(test.expectedCommands == test.SPI.sentCommands, test.SPI);
}
