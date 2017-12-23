/**
 * Author Teemu Mäntykallio
 * Initializes the library and turns the motor in alternating directions.
*/

#include <TMCStepper.h>

#define EN_PIN    38  // Nano v3:	16 Mega:	38	//enable (CFG6)
#define DIR_PIN   55  //			19			55	//direction
#define STEP_PIN  54  //			18			54	//step
#define CS_PIN    38  //			17			64	//chip select

bool dir = true;
TMC2660Stepper driver = TMC2660Stepper(CS_PIN);

void setup() {
	Serial.begin(9600);
	pinMode(CS_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
	driver.toff(4);
	driver.cs(10);
	//driver.begin(); 			// Initiate pins and registeries
	//driver.rms_current(600); 	// Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
	//driver.stealthChop(1); 	// Enable extremely quiet stepping
	//driver.cs(10);
	//driver.toff(10);

	Serial.print("SPI_response=0b");
	Serial.println(driver.SPI_response, BIN);
	Serial.print("_pinCS=");
	Serial.println(driver._pinCS);
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
			//driver.shaft(0);
		} else {
			Serial.println("Dir -> 1");
			//driver.shaft(1);
		}
		dir = !dir;
		last_time = ms;
	}
}
