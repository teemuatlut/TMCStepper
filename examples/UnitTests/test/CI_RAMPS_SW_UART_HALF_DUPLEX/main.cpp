
#include <Arduino.h>
extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>
#include <SoftwareSerial.h>

constexpr uint8_t DirPin = 61;
constexpr uint8_t StepPin = 60;
constexpr uint8_t EnablePin = 56;
constexpr uint8_t RxPin = 64;
constexpr uint8_t TxPin = 64;

TMC_HAL::SWSerial swSerial{RxPin, TxPin};
TMC2209Stepper driver{swSerial, 0.11, 0};

void TestCommunication() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x21, version, "Communication error");
}

void TestVersion() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x21, version);
}

void TestDirPinIsHigh() {
    digitalWrite(DirPin, HIGH);
    TEST_ASSERT_TRUE(driver.dir());
}

void TestDirPinIsLow() {
    digitalWrite(DirPin, LOW);
    TEST_ASSERT_FALSE(driver.dir());
}

void TestStepPinIsHigh() {
    digitalWrite(StepPin, HIGH);
    TEST_ASSERT_TRUE(driver.step());
}

void TestStepPinIsLow() {
    digitalWrite(StepPin, LOW);
    TEST_ASSERT_FALSE(driver.step());
}

void TestEnablePinIsHigh() {
    digitalWrite(EnablePin, HIGH);
    TEST_ASSERT_TRUE(driver.enn());
}

void TestEnablePinIsLow() {
    digitalWrite(EnablePin, LOW);
    TEST_ASSERT_FALSE(driver.enn());
}

void TestGconfWrite() {
    driver.GCONF(0x44);
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x44, driver.GCONF(), "Failed to modify gconf register");

    decltype(driver)::GCONF_t gconf = 0;
    gconf.mstep_reg_select = true;

    driver.GCONF(gconf.sr); // Reset to just mstep_reg_select enabled
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(1u<<7, driver.GCONF(), "Failed to reset gconf register");
}

void TestChopconfWrite() {
    driver.CHOPCONF(8);
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(8, driver.CHOPCONF(), "Failed to modify chopconf register");

    driver.CHOPCONF(0x10000053); // Reset to default
    TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x10000053, driver.CHOPCONF(), "Failed to reset chopconf register");
}

void setup() {
    delay(2000);

    pinMode(EnablePin, OUTPUT);
    pinMode(DirPin, OUTPUT);
    pinMode(StepPin, OUTPUT);

    driver.begin(19200);

    UNITY_BEGIN();

    RUN_TEST(TestCommunication);
    RUN_TEST(TestVersion);
    RUN_TEST(TestDirPinIsHigh);
    RUN_TEST(TestDirPinIsLow);
    RUN_TEST(TestStepPinIsHigh);
    RUN_TEST(TestStepPinIsLow);
    RUN_TEST(TestEnablePinIsHigh);
    RUN_TEST(TestEnablePinIsLow);
    RUN_TEST(TestGconfWrite);
    RUN_TEST(TestChopconfWrite);

    UNITY_END();
}

void loop() {}
