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
	SW_SCK   = 64; // Software Slave Clock (SCK)

constexpr float R_SENSE = 0.11; // Match to your driver

// Software SPI is bitbanged by the library without artificial delays
SW_SPIClass SW_SPI(SW_MOSI, SW_MISO, SW_SCK);

// Select your stepper driver type
//TMC2130Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC2160Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC2660Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC5160Stepper driver(SW_SPI, CS_PIN, R_SENSE);

bool dir = true;

void setup() {
	Serial.begin(9600);
	while(!Serial);
	Serial.println("Start...");
	driver.begin(); 			// Initiate pins and registeries
	driver.rms_current(600); 	// Set stepper current to 600mA
	driver.en_pwm_mode(1);  	// Enable extremely quiet stepping

	pinMode(EN_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	digitalWrite(EN_PIN, LOW); 	// Enable driver in hardware

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
