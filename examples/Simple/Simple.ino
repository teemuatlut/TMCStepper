/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper
 * motor in alternating directions.
 */

#include <TMCStepper.h>

#define EN_PIN           38 // Enable
#define DIR_PIN          55 // Direction
#define STEP_PIN         54 // Step
#define CS_PIN           42 // Chip select
#define SW_MOSI          66 // Software Master Out Slave In (MOSI)
#define SW_MISO          44 // Software Master In Slave Out (MISO)
#define SW_SCK           64 // Software Slave Clock (SCK)
#define SW_RX            63 // SoftwareSerial receive pin
#define SW_TX            40 // SoftwareSerial transmit pin
#define SERIAL_PORT Serial1 // HardwareSerial port
#define DRIVER_ADDRESS 0b00 // Driver address according to MS1 and MS2

#define R_SENSE 0.11f // Match to your driver
                      // SilentStepStick series use 0.11
                      // UltiMachine Einsy and Archim2 boards use 0.2
                      // Panucatt BSD2660 uses 0.1
                      // Watterott TMC5160 uses 0.075

//SW_SPIClass SW_SPI(SW_MOSI, SW_MISO, SW_SCK);

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

// On TMC2208 you can use a serial mux to communicate with
// multiple driver using a single serial port
//TMC_HAL::SSwitch uart_switch(0, 0);

//TMC2208Stepper driver(SERIAL_PORT, R_SENSE);   // Hardware Serial
//TMC2208Stepper driver(  SW_SERIAL, R_SENSE);   // Software serial
//TMC2208Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS, uart_switch); // Hardware UART mux
//TMC2209Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);

void setup() {
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware

  driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
                                  // UART: Init SW UART (if selected) with default 19200 baudrate
  driver.rms_current(600);        // Set motor RMS current
  driver.microsteps(16);          // Set microsteps to 1/16th

//driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
}

bool shaft = false;

void loop() {
  // Run 5000 steps and switch direction in software
  for (uint16_t i = 5000; i>0; i--) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(160);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(160);
  }
  shaft = !shaft;
  driver.shaft(shaft);
}
