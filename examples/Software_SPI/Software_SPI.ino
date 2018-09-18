/**
 * Author Teemu Mäntykallio
 * Initializes the library and turns the motor in alternating directions.
 */

#define EN_PIN    7  // Nano v3:	16 Mega:	38	//enable (CFG6)
#define DIR_PIN   6  //			19			55	//direction
#define STEP_PIN  5  //			18			54	//step
#define CS_PIN    8  //			17			64	//chip select
#define MOSI_PIN  9
#define MISO_PIN 10
#define SCK_PIN  11
#define R_SENSE   0.11 // Match to your driver

bool dir = true;

#include <TMCStepper.h>
TMC2130Stepper driver = TMC2130Stepper(CS_PIN, R_SENSE, MOSI_PIN, MISO_PIN, SCK_PIN);

void setup() {
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Start...");
	driver.begin(); 			// Initiate pins and registeries
	driver.rms_current(600); 	// Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
	driver.en_pwm_mode(1); 	// Enable extremely quiet stepping

	digitalWrite(EN_PIN, LOW);

	Serial.print("DRV_STATUS=0b");
	Serial.println(driver.DRV_STATUS(), BIN);
}

void loop() {
	digitalWrite(STEP_PIN, HIGH);
	delayMicroseconds(10);
	digitalWrite(STEP_PIN, LOW);
	delayMicroseconds(10);
	uint32_t ms = millis();
	static uint32_t last_time = 0;
	if ((ms - last_time) > 2000) {
		if (dir) {
			Serial.println("Dir -> 0");
			driver.shaft(0);
		} else {
			Serial.println("Dir -> 1");
			driver.shaft(1);
		}
		dir = !dir;
		last_time = ms;
	}
}
