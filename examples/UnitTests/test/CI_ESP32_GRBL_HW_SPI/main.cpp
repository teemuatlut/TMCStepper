
#include <Arduino.h>
extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>

constexpr uint8_t X_StepPin = GPIO_NUM_12;
constexpr uint8_t X_DirPin  = GPIO_NUM_14;
constexpr uint8_t X_CS_Pin  = GPIO_NUM_17;

constexpr uint8_t Y_StepPin = GPIO_NUM_27;
constexpr uint8_t Y_DirPin  = GPIO_NUM_26;
constexpr uint8_t Y_CS_Pin  = GPIO_NUM_17;

constexpr uint8_t Z_StepPin = GPIO_NUM_15;
constexpr uint8_t Z_DirPin  = GPIO_NUM_2;
constexpr uint8_t Z_CS_Pin  = GPIO_NUM_17;

TMC5160Stepper X_driver{SPI, X_CS_Pin, 0.075, 1};
TMC2130Stepper Y_driver{SPI, Y_CS_Pin, 0.110, 2};
TMC5160Stepper Z_driver{SPI, Z_CS_Pin, 0.075, 3};

// X: TMC5160

void X_TestCommunication() {
    auto version = X_driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x30, version, "Communication error");
}

void X_TestVersion() {
    auto version = X_driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x30, version);
}

void X_TestStepPinIsHigh() {
    digitalWrite(X_StepPin, HIGH);
    TEST_ASSERT_TRUE(X_driver.refl_step());
}

void X_TestStepPinIsLow() {
    digitalWrite(X_StepPin, LOW);
    TEST_ASSERT_FALSE(X_driver.refl_step());
}

void X_TestDirPinIsHigh() {
    digitalWrite(X_DirPin, HIGH);
    TEST_ASSERT_TRUE(X_driver.refr_dir());
}

void X_TestDirPinIsLow() {
    digitalWrite(X_DirPin, LOW);
    TEST_ASSERT_FALSE(X_driver.refr_dir());
}

// Y: TMC2130

void Y_TestCommunication() {
    auto version = Y_driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x11, version, "Communication error");
}

void Y_TestVersion() {
    auto version = Y_driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x11, version);
}

void Y_TestStepPinIsHigh() {
    digitalWrite(Y_StepPin, HIGH);
    TEST_ASSERT_TRUE(Y_driver.step());
}

void Y_TestStepPinIsLow() {
    digitalWrite(Y_StepPin, LOW);
    TEST_ASSERT_FALSE(Y_driver.step());
}

void Y_TestDirPinIsHigh() {
    digitalWrite(Y_DirPin, HIGH);
    TEST_ASSERT_TRUE(Y_driver.dir());
}

void Y_TestDirPinIsLow() {
    digitalWrite(Y_DirPin, LOW);
    TEST_ASSERT_FALSE(Y_driver.dir());
}

// Z: TMC5160

void Z_TestCommunication() {
    auto version = Z_driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x30, version, "Communication error");
}

void Z_TestVersion() {
    auto version = Z_driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x30, version);
}

void Z_TestStepPinIsHigh() {
    digitalWrite(Z_StepPin, HIGH);
    TEST_ASSERT_TRUE(Z_driver.refl_step());
}

void Z_TestStepPinIsLow() {
    digitalWrite(Z_StepPin, LOW);
    TEST_ASSERT_FALSE(Z_driver.refl_step());
}

void Z_TestDirPinIsHigh() {
    digitalWrite(Z_DirPin, HIGH);
    TEST_ASSERT_TRUE(Z_driver.refr_dir());
}

void Z_TestDirPinIsLow() {
    digitalWrite(Z_DirPin, LOW);
    TEST_ASSERT_FALSE(Z_driver.refr_dir());
}

void setup() {
    delay(2000);

    pinMode(X_StepPin, OUTPUT);
    pinMode(Y_StepPin, OUTPUT);
    pinMode(Z_StepPin, OUTPUT);
    pinMode(X_DirPin, OUTPUT);
    pinMode(Y_DirPin, OUTPUT);
    pinMode(Z_DirPin, OUTPUT);

    pinMode(X_CS_Pin, OUTPUT);
    digitalWrite(X_CS_Pin, HIGH);

    SPI.begin();

    UNITY_BEGIN();

    RUN_TEST(X_TestCommunication);
    RUN_TEST(X_TestVersion);
    RUN_TEST(X_TestStepPinIsHigh);
    RUN_TEST(X_TestStepPinIsLow);
    RUN_TEST(X_TestDirPinIsHigh);
    RUN_TEST(X_TestDirPinIsLow);

    RUN_TEST(Y_TestCommunication);
    RUN_TEST(Y_TestVersion);
    RUN_TEST(Y_TestStepPinIsHigh);
    RUN_TEST(Y_TestStepPinIsLow);
    RUN_TEST(Y_TestDirPinIsHigh);
    RUN_TEST(Y_TestDirPinIsLow);

    RUN_TEST(Z_TestCommunication);
    RUN_TEST(Z_TestVersion);
    RUN_TEST(Z_TestStepPinIsHigh);
    RUN_TEST(Z_TestStepPinIsLow);
    RUN_TEST(Z_TestDirPinIsHigh);
    RUN_TEST(Z_TestDirPinIsLow);

    UNITY_END();
}

void loop() {}
