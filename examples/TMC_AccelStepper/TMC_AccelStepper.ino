/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper motor.
 */

#include <TMCStepper.h>

constexpr TMC_HAL::PinDef
    EN_PIN   = 38, // Enable
    DIR_PIN  = 55, // Direction
    STEP_PIN = 54, // Step
    CS_PIN   = 42, // Chip select
    SW_MOSI  = 66, // Software Master Out Slave In (MOSI)
    SW_MISO  = 44, // Software Master In Slave Out (MISO)
    SW_SCK   = 64, // Software Slave Clock (SCK)
    SW_RX    = 63, // SoftwareSerial receive pin
    SW_TX    = 40; // SoftwareSerial transmit pin

auto SERIAL_PORT = Serial1;              // TMC2209 HardwareSerial port
constexpr uint8_t DRIVER_ADDRESS = 0b00; // TMC2209 Driver address according to MS1 and MS2

constexpr float R_SENSE = 0.11; // Match to your driver

SW_SPIClass SW_SPI(SW_MOSI, SW_MISO, SW_SCK);

// Select your stepper driver type
//TMC2130Stepper driver(   SPI, CS_PIN, R_SENSE); // Hardware SPI
//TMC2130Stepper driver(SW_SPI, CS_PIN, R_SENSE); // Software SPI
//TMC2160Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC2160Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC2660Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC2660Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC5130Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC5130Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC5160Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC5160Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC5161Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC5161Stepper driver(SW_SPI, CS_PIN, R_SENSE);

// On AVR the SWSerial class enables single wire serial communication
// On other platforms it only redirects to SoftwareSerial if possible
//TMC_HAL::SWSerial SW_SERIAL(SW_RX, SW_TX);

//TMC2208Stepper driver(SERIAL_PORT, R_SENSE);   // Hardware Serial
//TMC2208Stepper driver(  SW_SERIAL, R_SENSE);   // Software serial
//TMC2209Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);

constexpr uint32_t steps_per_mm = 80;

#include <AccelStepper.h>
AccelStepper stepper = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);

void setup() {
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Start...");

    driver.begin();             // Initiate driver and communication
    driver.rms_current(600);    // Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
    driver.en_pwm_mode(1);      // Enable extremely quiet stepping
    driver.pwm_autoscale(1);
    driver.microsteps(16);

    stepper.setMaxSpeed(50*steps_per_mm); // 100mm/s @ 80 steps/mm
    stepper.setAcceleration(1000*steps_per_mm); // 2000mm/s^2
    stepper.setEnablePin(EN_PIN);
    stepper.setPinsInverted(false, false, true);
    stepper.enableOutputs();
}

void loop() {
    if (stepper.distanceToGo() == 0) {
        stepper.disableOutputs();
        delay(100);
        stepper.move(100*steps_per_mm); // Move 100mm
        stepper.enableOutputs();
    }
    stepper.run();
}
