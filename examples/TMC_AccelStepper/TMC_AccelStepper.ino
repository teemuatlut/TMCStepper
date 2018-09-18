/**
 * Author Teemu Mäntykallio
 * Initializes the library and turns the motor in alternating directions.
 */

#define EN_PIN    38  // Nano v3:   16 Mega:    38  //enable (CFG6)
#define DIR_PIN   55  //            19          55  //direction
#define STEP_PIN  54  //            18          54  //step
#define CS_PIN    40  //            17          40  //chip select
#define R_SENSE    0.11 // Match to your driver

constexpr uint32_t steps_per_mm = 80;

#include <TMCStepper.h>
TMC2130Stepper driver = TMC2130Stepper(CS_PIN, R_SENSE);

#include <AccelStepper.h>
AccelStepper stepper = AccelStepper(stepper.DRIVER, STEP_PIN, DIR_PIN);

void setup() {
    SPI.begin();
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Start...");
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(CS_PIN, HIGH);
    driver.begin();             // Initiate pins and registeries
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
