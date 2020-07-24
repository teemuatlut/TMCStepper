
#include <TMCStepper.h>
#include <source/TMC_HAL.h>

extern "C" {
	#include "main.h"
}

TMCStepper_n::OutputPin enPin(ENABLE_GPIO_Port, ENABLE_Pin);
TMCStepper_n::OutputPin step(STEP_GPIO_Port, STEP_Pin);

SPIClass SPI(&hspi1);
SW_SPIClass SWSPI({SW_SPI_MOSI_GPIO_Port, SW_SPI_MOSI_Pin}, {SW_SPI_MISO_GPIO_Port, SW_SPI_MISO_Pin}, {SW_SPI_SCK_GPIO_Port, SW_SPI_SCK_Pin});

//TMC2130Stepper driver(SPI, {CS_GPIO_Port, CS_Pin}, 0.11);
TMC2130Stepper driver(SWSPI, {CS_GPIO_Port, CS_Pin}, 0.11);

//HardwareSerial SerialInstance(&huart2);
//TMC2209Stepper driver_serial(&SerialInstance, 0.5, 0);

extern "C"
void initDriver() {
	enPin = LOW;					// Enable driver in hardware

									// Enable one according to your setup
	driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
							  // UART: Init SW UART (if selected) with default 115200 baudrate
	driver.toff(5);                 // Enables driver in software
	driver.rms_current(600);        // Set motor RMS current
	driver.microsteps(16);          // Set microsteps to 1/16th

	driver.en_pwm_mode(true);       // Toggle stealthChop on TMC2130/2160/5130/5160
	//driver.en_spreadCycle(false);   // Toggle spreadCycle on TMC2208/2209/2224
	driver.pwm_autoscale(true);     // Needed for stealthChop

	auto drv_status = driver.DRV_STATUS();
	(void)drv_status;

	auto ioin = driver.IOIN();
	(void)ioin;
}

bool shaft = false;

extern "C"
void runMotor() {
	// Run 5000 steps and switch direction in software
	for (uint16_t i = 1000; i>0; i--) {
		step = HIGH;
		delay(1);
		step = LOW;
		delay(1);
	}
	shaft = !shaft;
	driver.shaft(shaft);

	step.toggle();

	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
}
