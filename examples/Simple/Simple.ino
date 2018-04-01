/**
 * Author Teemu Mäntykallio
 * Initializes the library and turns the motor in alternating directions.
*/

//#include <TMC2130Stepper.h>
#include <TMCStepper.h>

#define EN_PIN    38  // Nano v3:	16 Mega:	38	//enable (CFG6)
#define DIR_PIN   55  //			19			55	//direction
#define STEP_PIN  54  //			18			54	//step
#define CS_PIN    38  //			17			64	//chip select

bool dir = true;
//TMC2660Stepper driver2660 = TMC2660Stepper(CS_PIN);
//TMC5130Stepper driver5130 = TMC5130Stepper(CS_PIN);
TMC2130Stepper driver2130 = TMC2130Stepper(CS_PIN, 66, 44, 64);
TMC2660Stepper driver2660 = TMC2660Stepper(CS_PIN, 66, 44, 64);

void setup() {
	Serial.begin(9600);
	pinMode(CS_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);

	//driver2660.toff(2);
	//driver5130.toff(2);
	driver2130.pwm_ampl(255);
	driver2130.pwm_grad(15);
	driver2130.pwm_freq(0b10);

/*
	driver2660.toff(4);
	driver2660.cs(10);

	driver5130.begin(); 			// Initiate pins and registeries
	driver5130.rms_current(600); 	// Set stepper current to 600mA. The command is the same as command TMC2130.setCurrent(600, 0.11, 0.5);
	driver5130.en_pwm_mode(true); 	// Enable extremely quiet stepping
	driver5130.irun(10);
	driver5130.toff(10);
*/	/*
	Serial.print("SPI_response=0b");
	Serial.println(driver2660.SPI_response, BIN);
	Serial.print("_pinCS=");
	Serial.println(driver2660._pinCS);
	*/
/*
	Serial.print("SPI_response=0b");
	Serial.println(driver5130.status_response, BIN);
	Serial.print("_pinCS=");
	Serial.println(driver5130._pinCS);
	*/
}

void loop() {}
