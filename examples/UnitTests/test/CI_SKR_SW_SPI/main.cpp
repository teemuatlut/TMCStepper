
#include <Arduino.h>

#include <usb/usb.h>
#include <usb/usbcfg.h>
#include <usb/usbhw.h>
#include <usb/usbcore.h>
#include <usb/cdc.h>
#include <usb/cdcuser.h>
#include <usb/mscuser.h>
#include <CDCSerial.h>
#include <usb/mscuser.h>

extern "C" {
    #include <unity.h>
}
#include <TMCStepper.h>

constexpr uint8_t MosiPin = P1_17;
constexpr uint8_t MisoPin = P0_05;
constexpr uint8_t SckPin = P0_04;

constexpr uint8_t X_DirPin = P2_06;
constexpr uint8_t X_StepPin = P2_02;
constexpr uint8_t X_EnablePin = P2_01;
constexpr uint8_t X_ChipSelectPin = P1_10;

constexpr uint8_t Y_DirPin = P0_20;
constexpr uint8_t Y_StepPin = P0_19;
constexpr uint8_t Y_EnablePin = P2_01;
constexpr uint8_t Y_ChipSelectPin = P1_15;

SW_SPIClass swSPI{MosiPin, MisoPin, SckPin};
TMC2130Stepper x_driver{swSPI, X_ChipSelectPin, 0.11};
TMC2130Stepper y_driver{swSPI, Y_ChipSelectPin, 0.11};

void TestCommunication() {
    auto version = x_driver.version();
    TEST_ASSERT_EQUAL_HEX8_MESSAGE(0x30, version, "Communication error");
}

void TestVersion() {
    auto version = x_driver.version();
    TEST_ASSERT_EQUAL_UINT8(0x30, version);
}

void TestDirPinIsHigh() {
    digitalWrite(X_DirPin, HIGH);
    TEST_ASSERT_TRUE(x_driver.dir());
}

void TestDirPinIsLow() {
    digitalWrite(X_DirPin, LOW);
    TEST_ASSERT_FALSE(x_driver.dir());
}

void TestStepPinIsHigh() {
    digitalWrite(X_StepPin, HIGH);
    TEST_ASSERT_TRUE(x_driver.step());
}

void TestStepPinIsLow() {
    digitalWrite(X_StepPin, LOW);
    TEST_ASSERT_FALSE(x_driver.step());
}

void TestEnablePinIsHigh() {
    digitalWrite(X_EnablePin, HIGH);
    TEST_ASSERT_TRUE(x_driver.drv_enn_cfg6());
}

void TestEnablePinIsLow() {
    digitalWrite(X_EnablePin, LOW);
    TEST_ASSERT_FALSE(x_driver.drv_enn_cfg6());
}

void setup() {
    UsbSerial.begin(115200);
    //while(!UsbSerial.host_connected);

    pinMode(X_EnablePin, OUTPUT);
    pinMode(X_DirPin, OUTPUT);
    pinMode(X_StepPin, OUTPUT);

    x_driver.begin();
    y_driver.begin();

    UsbSerial.println("Start " __TIMESTAMP__);

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

void loop() {
    MSC_RunDeferredCommands();
}

