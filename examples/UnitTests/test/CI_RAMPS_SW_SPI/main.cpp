
#include <Arduino.h>
extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>

constexpr uint8_t DirPin = 55;
constexpr uint8_t StepPin = 54;
constexpr uint8_t EnablePin = 38;
constexpr uint8_t ChipSelectPin = 40;
constexpr uint8_t MosiPin = 66;
constexpr uint8_t MisoPin = 44;
constexpr uint8_t SckPin = 63;

SW_SPIClass swSPI{MosiPin, MisoPin, SckPin};
TMC5160Stepper driver{swSPI, ChipSelectPin, 0.11};

void TestCommunication() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x30, version, "Communication error");
}

void TestVersion() {
    auto version = driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x30, version);
}

void TestDirPinIsHigh() {
    digitalWrite(DirPin, HIGH);
    TEST_ASSERT_TRUE(driver.refr_dir());
}

void TestDirPinIsLow() {
    digitalWrite(DirPin, LOW);
    TEST_ASSERT_FALSE(driver.refr_dir());
}

void TestStepPinIsHigh() {
    digitalWrite(StepPin, HIGH);
    TEST_ASSERT_TRUE(driver.refl_step());
}

void TestStepPinIsLow() {
    digitalWrite(StepPin, LOW);
    TEST_ASSERT_FALSE(driver.refl_step());
}

void TestEnablePinIsHigh() {
    digitalWrite(EnablePin, HIGH);
    TEST_ASSERT_TRUE(driver.drv_enn());
}

void TestEnablePinIsLow() {
    digitalWrite(EnablePin, LOW);
    TEST_ASSERT_FALSE(driver.drv_enn());
}

void setup() {
    delay(2000);

    pinMode(EnablePin, OUTPUT);
    pinMode(DirPin, OUTPUT);
    pinMode(StepPin, OUTPUT);

    SPI.begin();

    driver.begin();

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
