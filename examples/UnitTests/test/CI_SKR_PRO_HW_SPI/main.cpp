
#include <Arduino.h>
extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>

constexpr uint8_t StepPin = PE9;
// Disabled because the actual 144pin chip is not supported by the framework
// constexpr uint8_t DirPin = PF1;
// constexpr uint8_t EnablePin = PF2;

constexpr uint8_t ChipSelectPin = PA15;

SW_SPIClass sw_spi(PC12, PC11, PC10);
TMC2130Stepper driver{sw_spi, ChipSelectPin, 0.11};

void TestCommunication() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x11, version, "Communication error");
}

void TestVersion() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x11, version);
}

void TestStepPinIsHigh() {
    digitalWrite(StepPin, HIGH);
    TEST_ASSERT_TRUE(driver.step());
}

void TestStepPinIsLow() {
    digitalWrite(StepPin, LOW);
    TEST_ASSERT_FALSE(driver.step());
}

void setup() {
    delay(2000);

    pinMode(StepPin, OUTPUT);
    pinMode(ChipSelectPin, OUTPUT);
    digitalWrite(ChipSelectPin, HIGH);

    SPI.begin();

    UNITY_BEGIN();

    RUN_TEST(TestCommunication);
    RUN_TEST(TestVersion);
    RUN_TEST(TestStepPinIsHigh);
    RUN_TEST(TestStepPinIsLow);

    UNITY_END();
}

void loop() {}
