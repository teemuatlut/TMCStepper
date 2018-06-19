/*
 * Author: Teemu Mäntykallio
 */

#include <TMCStepper.h>

#define EN_PIN       38  // Nano v3:   16 Mega:    38  //enable (CFG6)
#define DIR_PIN      55  //            19          55  //direction
#define STEP_PIN     54  //            18          54  //step
#define CS_PIN       40  //            17          64  //chip select
#define STEP_PORT PORTF  // Register to match with STEP_PIN
#define STEP_BIT      0  // Bit in register to match STEP_PIN
#define R_SENSE       0.11 // Match to your driver

TMC2130Stepper driver = TMC2130Stepper(CS_PIN, R_SENSE);

// You can define starting values here:
struct {
    uint8_t blank_time = 24;        // [16, 24, 36, 54]
    uint8_t off_time = 3;           // [1..15]
    uint8_t hysteresis_start = 1;   // [1..8]
    int8_t hysteresis_end = 12;     // [-3..12]
} config;

void initPins();

ISR(TIMER1_COMPA_vect){
    STEP_PORT |= 1 << STEP_BIT;
    STEP_PORT &= ~(1 << STEP_BIT);
}

void reportCurrentSettings() {
    Serial.print("Off time = ");
    Serial.print(config.off_time);
    Serial.print(" Hysteresis end = ");
    Serial.print(config.hysteresis_end);
    Serial.print(" Hysteresis start = ");
    Serial.println(config.hysteresis_start);
}

void setup() {
    initPins();
    Serial.begin(250000);
    Serial.println(F("Starting calibration of TMC spreadCycle parameters."));
    Serial.println(F("This example by default uses X axis driver on a RAMPS1.4."));
    Serial.println(F("First make sure your serial terminal sends newline ending only!"));
    for (uint8_t i = 0; i < 60; i++) { Serial.print('.'); delay(100); }
    Serial.println(F("\nThen make sure the belt is disconnected"));
    Serial.println(F("as we will not respect endstops or physical limits"));
    while(1) {
        Serial.println(F("Is the belt disconnected? Send 'yes' to confirm."));
        while(!Serial.available());
        String yn = Serial.readStringUntil('\n');
        Serial.println(yn);
        if (yn == "yes") {
            break;
        } else {
            Serial.println(F("Belt still connected."));
            Serial.println(F("Please disconnect belt."));
        };
    }

    Serial.println(F("\nNow make sure the driver has 12V (or greater) power turned on."));
    while(1) {
        Serial.println(F("Is VMOT power on? Send 'yes' to confirm"));
        while(!Serial.available());
        String yn = Serial.readStringUntil('\n');
        Serial.println(yn);
        if (yn == "yes") {
            break;
        } else {
            Serial.println(F("Please turn on power to the driver."));
        };
    }

    Serial.print(F("\nTesting connection..."));
    uint8_t result = driver.test_connection();
    if (result) {
        Serial.println(F("failed!"));
        Serial.print(F("Likely cause: "));
        switch(result) {
            case 1: Serial.println(F("loose connection")); break;
            case 2: Serial.println(F("Likely cause: no power")); break;
        }
        Serial.println(F("Fix the problem and reset board."));
        abort();
    }
    Serial.println(F("OK"));

    driver.push();
    driver.microsteps(256);
    driver.irun(10);
    driver.ihold(10);

    Serial.print(F("Setting driver blank time to "));
    Serial.print(config.blank_time);
    Serial.println(F(" cycles."));
    driver.blank_time(config.blank_time);

    Serial.print(F("Setting driver off time to "));
    Serial.println(config.off_time);
    driver.toff(config.off_time);

    Serial.print(F("Setting hysteresis end value to "));
    Serial.println(config.hysteresis_end);
    driver.hysteresis_end(config.hysteresis_end);

    Serial.print(F("Setting hysteresis start value to "));
    Serial.println(config.hysteresis_start);
    driver.hysteresis_start(config.hysteresis_start);

    Serial.print(F("Effective hysteresis = "));
    Serial.print(config.hysteresis_end);
    Serial.print(F(" + "));
    Serial.print(config.hysteresis_start);
    Serial.print(F(" = "));
    Serial.println(config.hysteresis_end + config.hysteresis_start);

    Serial.println(F("\nNow we start decreasing the hysteresis end setting."));
    Serial.println(F("You should first hear your motor making clearly audible noise."));
    Serial.println(F("As we tune the timings the noise will get higher pitched."));
    Serial.println(F("When the noise is no longer audible we have reached a good setting."));
    Serial.println(F("You can tune the setting by sending - (minus) character"));
    Serial.println(F("or you can go back to previous parameter by sending + (plus) character."));
    Serial.println(F("Sending = (equal) character move to the next phase."));

    digitalWrite(EN_PIN, LOW);
    while (driver.cur_a() < 240) { // Use cur_b if measuring from B coil
        digitalWrite(STEP_PIN, HIGH);
        digitalWrite(STEP_PIN, LOW);
        delay(3);
    }

    while(1) {
        if (Serial.available() > 0) {
            uint8_t c = Serial.read();
            if (c == '+') {
                if (config.hysteresis_end == 12) Serial.println(F("Reached MAX setting already!"));
                else {
                    config.hysteresis_end++;
                    reportCurrentSettings();
                    driver.hysteresis_end(config.hysteresis_end);
                }
            } else if (c == '-') {
                if (config.hysteresis_end == -3) Serial.println(F("Reached MIN setting already!"));
                else {
                    config.hysteresis_end--;
                    reportCurrentSettings();
                    driver.hysteresis_end(config.hysteresis_end);
                }
            }
            else if (c == '=') break;
        }
    }

    Serial.print(F("Final effective hysteresis = "));
    Serial.print(config.hysteresis_end);
    Serial.print(F(" + "));
    Serial.print(config.hysteresis_start);
    Serial.print(F(" = "));
    Serial.println(config.hysteresis_end + config.hysteresis_start);
    Serial.println(F("Your configuration parameters in Marlin are:"));
    Serial.print(F("#define CHOPPER_TIMING "));
    Serial.print(config.off_time);
    Serial.print(F(" "));
    Serial.print(config.hysteresis_end);
    Serial.print(F(" "));
    Serial.print(config.hysteresis_start);
}

void initPins() {
    pinMode(EN_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);
    pinMode(STEP_PIN, OUTPUT);
    pinMode(CS_PIN, OUTPUT);
    digitalWrite(EN_PIN, HIGH); //deactivate driver (LOW active)
    digitalWrite(DIR_PIN, LOW); //LOW or HIGH
    digitalWrite(STEP_PIN, LOW);
    digitalWrite(CS_PIN, HIGH);
    SPI.begin();
    pinMode(MISO, INPUT_PULLUP);
}

void loop() {}