
#include <Arduino.h>
extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>

constexpr uint8_t DirPin = 48;
constexpr uint8_t StepPin = 46;
constexpr uint8_t EnablePin = 62;
constexpr uint8_t ChipSelectPin = 53;

TMC2130Stepper driver{SPI, ChipSelectPin, 0.11};

void TestCommunication() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x11, version, "Communication error");
}

void TestVersion() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x11, version);
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
    TEST_ASSERT_TRUE(driver.drv_enn_cfg6());
}

void TestEnablePinIsLow() {
    digitalWrite(EnablePin, LOW);
    TEST_ASSERT_FALSE(driver.drv_enn_cfg6());
}

void setup() {
    delay(2000);

    pinMode(EnablePin, OUTPUT);
    pinMode(DirPin, OUTPUT);
    pinMode(StepPin, OUTPUT);
    pinMode(ChipSelectPin, OUTPUT);
    digitalWrite(ChipSelectPin, HIGH);

    SPI.begin();

    UNITY_BEGIN();

    RUN_TEST(TestCommunication);
    RUN_TEST(TestVersion);
    RUN_TEST(TestDirPinIsHigh);
    RUN_TEST(TestDirPinIsLow);
    RUN_TEST(TestStepPinIsHigh);
    RUN_TEST(TestStepPinIsLow);
    RUN_TEST(TestEnablePinIsHigh);
    RUN_TEST(TestEnablePinIsLow);

    UNITY_END();
}

void loop() {}
