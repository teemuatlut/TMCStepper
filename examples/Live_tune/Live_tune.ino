/**
 * Author Teemu Mäntykallio
 * Initializes the library and runs the stepper motor.
 */

#include <TMCStepper.h>

constexpr TMC_HAL::PinDef
	EN_PIN            = 38, // Enable
	DIR_PIN           = 55, // Direction
	STEP_PIN          = 54, // Step
	CS_PIN            = 42, // Chip select
	SW_MOSI           = 66, // Software Master Out Slave In (MOSI)
	SW_MISO           = 44, // Software Master In Slave Out (MISO)
	SW_SCK            = 64, // Software Slave Clock (SCK)
	SW_RX             = 63, // TMC2208/TMC2224 SoftwareSerial receive pin
	SW_TX             = 40; // TMC2208/TMC2224 SoftwareSerial transmit pin

auto SERIAL_PORT = Serial1; // TMC2208/TMC2224 HardwareSerial port
constexpr uint8_t DRIVER_ADDRESS = 0b00; // TMC2209 Driver address according to MS1 and MS2

constexpr float R_SENSE = 0.11f; // Match to your driver

//SW_SPIClass SW_SPI(SW_MOSI, SW_MISO, SW_SCK);

// Select your stepper driver type
//TMC2130Stepper driver(   SPI, CS_PIN, R_SENSE); // Hardware SPI
//TMC2130Stepper driver(SW_SPI, CS_PIN, R_SENSE); // Software SPI
//TMC2660Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC2660Stepper driver(SW_SPI, CS_PIN, R_SENSE);
//TMC5160Stepper driver(   SPI, CS_PIN, R_SENSE);
//TMC5160Stepper driver(SW_SPI, CS_PIN, R_SENSE);

// On AVR the SWSerial class enables half duplex serial communication
// On other platforms it only redirects to SoftwareSerial if possible
//TMC_HAL::SWSerial SW_SERIAL(SW_RX, SW_TX);

//TMC2208Stepper driver(SERIAL_PORT, R_SENSE);   // Hardware Serial
//TMC2208Stepper driver(  SW_SERIAL, R_SENSE);   // Software serial
//TMC2209Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);

int speed = 10;
bool running = false;
float Rsense = 0.11;
float hold_x = 0.5;
boolean toggle1 = 0;
uint8_t stall_value = 9;
volatile uint32_t step_counter = 0;
const uint32_t steps_per_mm = 80 * 16; // @ 256 microsteps
const uint16_t fsteps_per_rotation = 200;
const uint32_t MHz = 16000000>>8; // Scaled by 256
const uint16_t acceleration = 2000;

// Using direct register manipulation can reach faster stepping times
auto STEP_PORT = PORTF; // Match with STEP_PIN
auto STEP_BIT_POS = 0;  // Match with STEP_PIN

ISR(TIMER1_COMPA_vect){
	//STEP_PORT ^= 1 << STEP_BIT_POS;
	digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
	step_counter++;
}

void initTimer() {
	cli();//stop interrupts
	//set timer1 interrupt at 10kHz => 10000 steps/s => ~ 20 fullsteps/s
	TCCR1A = 0; // set entire TCCR1A register to 0
	TCCR1B = 0; // same for TCCR1B
	TCNT1  = 0; //initialize counter value to 0
	// set compare match register for 2kHz increments
	OCR1A = 61;// = (16*10^6) / (8*2000) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS01 bit for no prescaler
	TCCR1B |= (1 << CS10);
	// enable/disable timer compare interrupt on start
	//TIMSK1 |= (1 << OCIE1A);
	TIMSK1 &= ~(1 << OCIE1A);
	sei();//allow interrupts
}

uint16_t calculateMMSTimer(uint8_t mms) {
	uint32_t steps_per_second = mms * steps_per_mm;
	steps_per_second >>= 8;
	uint32_t tmr = MHz / steps_per_second - 1;
	return tmr;
}
uint16_t calculateFSPSTimer(uint16_t fsps) {
	return MHz / fsps - 1;
}
uint16_t calculateRPSTimer(uint8_t rps) {
	return MHz / (rps * fsteps_per_rotation) - 1;
}

void accelerationRamp(uint16_t maxMMS = 100) {
	TIMSK1 &= ~(1 << OCIE1A);
	while (driver.cur_a() != 0) { // Use cur_b if measuring from B coil
		digitalWrite(STEP_PIN, HIGH);
		digitalWrite(STEP_PIN, LOW);
		delay(1);
	}
	delay(100);
	digitalWrite(EN_PIN, HIGH);
	uint16_t mms = 2;
	uint16_t maxOCR1A = calculateMMSTimer(maxMMS);
	uint16_t _OCR1A = calculateMMSTimer(mms);
	digitalWrite(EN_PIN, LOW);
	OCR1A = _OCR1A;
	TIMSK1 |= 1 << OCIE1A;
	for (; mms <= maxMMS; mms += acceleration) {
		delay(1);
		OCR1A = calculateMMSTimer(mms);
	}
	cli();
	step_counter = 0;
	sei();
	while (step_counter <= 100*steps_per_mm);
	for (; mms >= 2; mms -= acceleration) {
		delay(1);
		OCR1A = calculateMMSTimer(mms);
	}
}

void serialTuple(String cmd, int arg) {
	Serial.print("Received command: ");
	Serial.print(cmd);
	Serial.print("(");
	Serial.print(arg);
	Serial.println(")");
}

void setup() {
	initTimer();
	Serial.begin(500000);

	pinMode(EN_PIN, OUTPUT);
	pinMode(DIR_PIN, OUTPUT);
	pinMode(STEP_PIN, OUTPUT);
	digitalWrite(EN_PIN, HIGH); //deactivate driver (LOW active)
	digitalWrite(DIR_PIN, LOW); //LOW or HIGH
	digitalWrite(STEP_PIN, LOW);

	driver.push();
    driver.tbl(1); //blank_time(24);
    driver.TPOWERDOWN(255);
	driver.toff(4);

	// Effective hysteresis = 0
	driver.hstrt(0);
	driver.hend(2);

	driver.en_pwm_mode(true);
	driver.pwm_freq(1);
	driver.pwm_autoscale(true);
	driver.pwm_ampl(180);
	driver.pwm_grad(1);

    driver.rms_current(600); // mA
    driver.microsteps(256);
    driver.diag1_stall(1);
    driver.diag1_pushpull(1);
	digitalWrite(EN_PIN, LOW);

	while (driver.cur_a() < 240) { // Use cur_b if measuring from B coil
		digitalWrite(STEP_PIN, HIGH);
		digitalWrite(STEP_PIN, LOW);
		delay(3);
	}
	Serial.print("cur_a = ");
	Serial.println(driver.cur_a(), DEC);
	Serial.print("cur_b = ");
	Serial.println(driver.cur_b(), DEC);
}

void loop() {
	if (Serial.available() > 0) {
		String cmd = Serial.readStringUntil(' ');
		String strArg = Serial.readStringUntil('\n');

		int arg = strArg.toInt();

		if (cmd == "run") {
			serialTuple("run", arg);
			running = arg;
			arg ? TIMSK1 |= 1 << OCIE1A : TIMSK1 &= ~(1 << OCIE1A);
			//arg ? digitalWrite(EN_PIN, LOW) : digitalWrite(EN_PIN, HIGH);
		}

		else if (cmd == "mms") {
			serialTuple("mms", arg);
			cli();
			TCNT1 = 0;
			OCR1A = calculateMMSTimer(arg);
			Serial.print("Set OCR1A to ");
			Serial.println(OCR1A);
			sei();
		}
		else if (cmd == "fsps") {
			serialTuple("fsps", arg);
			cli();
			OCR1A = calculateFSPSTimer(arg);
			Serial.print("Set OCR1A to ");
			Serial.println(OCR1A);
			sei();
		}
		else if (cmd == "rps") {
			serialTuple("rps", arg);
			cli();
			OCR1A = calculateRPSTimer(arg);
			Serial.print("Set OCR1A to ");
			Serial.println(OCR1A);
			sei();
		}
		else if (cmd == "rms_current") {
			serialTuple("rms_current", arg);
			driver.rms_current(arg, hold_x);
		}
		else if (cmd == "find_pos") {
			serialTuple("find_pos", arg);
			TIMSK1 &= ~(1 << OCIE1A);
			while (driver.cur_a() != arg) { // Use cur_b if measuring from B coil
				digitalWrite(STEP_PIN, HIGH);
				digitalWrite(STEP_PIN, LOW);
				delay(1);
			}
		}
		else if (cmd == "rampTo") {
			serialTuple("rampTo", arg);
			accelerationRamp(arg);
		}
		else if (cmd == "Rsense") {
			Serial.print("Setting R sense value to: ");
			Serial.println(arg);
			Rsense = arg;
		}
		else if (cmd == "hold_multiplier") {
			Serial.print("Setting hold multiplier to: ");
			Serial.println(arg);
			hold_x = arg;
		}
		else if (cmd == "GCONF") {
			Serial.print("GCONF: 0b");
			Serial.println(driver.GCONF(), BIN);
		}
		else if (cmd == "I_scale_analog") {
			serialTuple("I_scale_analog", arg);
			driver.I_scale_analog(arg);
		}
		else if (cmd == "internal_Rsense") {
			serialTuple("internal_Rsense", arg);
			driver.internal_Rsense(arg);
		}
		else if (cmd == "en_pwm_mode") {
			serialTuple("en_pwm_mode", arg);
			driver.en_pwm_mode(arg);
		}
		else if (cmd == "enc_commutation") {
			serialTuple("enc_commutation", arg);
			driver.enc_commutation(arg);
		}
		else if (cmd == "shaft") {
			serialTuple("shaft", arg);
			driver.shaft(arg);
		}
		else if (cmd == "diag0_error") {
			serialTuple("diag0_error", arg);
			driver.diag0_error(arg);
		}
		else if (cmd == "diag0_otpw") {
			serialTuple("diag0_otpw", arg);
			driver.diag0_otpw(arg);
		}
		else if (cmd == "diag0_stall") {
			serialTuple("diag0_stall", arg);
			driver.diag0_stall(arg);
		}
		else if (cmd == "diag1_stall") {
			serialTuple("diag1_stall", arg);
			driver.diag1_stall(arg);
		}
		else if (cmd == "diag1_index") {
			serialTuple("diag1_index", arg);
			driver.diag1_index(arg);
		}
		else if (cmd == "diag1_onstate") {
			serialTuple("diag1_onstate", arg);
			driver.diag1_onstate(arg);
		}
		else if (cmd == "diag0_int_pushpull") {
			serialTuple("diag0_int_pushpull", arg);
			driver.diag0_int_pushpull(arg);
		}
		else if (cmd == "diag1_pushpull") {
			serialTuple("diag1_pushpull", arg);
			driver.diag1_pushpull(arg);
		}
		else if (cmd == "small_hysteresis") {
			serialTuple("small_hysteresis", arg);
			driver.small_hysteresis(arg);
		}
		else if (cmd == "stop_enable") {
			serialTuple("stop_enable", arg);
			driver.stop_enable(arg);
		}
		else if (cmd == "direct_mode") {
			serialTuple("direct_mode", arg);
			driver.direct_mode(arg);
		}
		// IHOLD_IRUN
		else if (cmd == "ihold") {
			serialTuple("ihold", arg);
			driver.ihold(arg);
		}
		else if (cmd == "irun") {
			serialTuple("irun", arg);
			driver.irun(arg);
		}
		else if (cmd == "iholddelay") {
			serialTuple("iholddelay", arg);
			driver.iholddelay(arg);
		}

		else if (cmd == "TSTEP") {
			Serial.print("TSTEP: ");
			Serial.println(driver.TSTEP());
		}

		else if (cmd == "TPWMTHRS") {
			serialTuple("TPWMTHRS", arg);
			driver.TPWMTHRS(arg);
		}
		else if (cmd == "TCOOLTHRS") {
			serialTuple("TCOOLTHRS", arg);
			driver.TCOOLTHRS(arg);
		}
		else if (cmd == "THIGH") {
			serialTuple("THIGH", arg);
			driver.THIGH(arg);
		}
		// XDIRECT
		else if (cmd == "coil_A") {
			serialTuple("coil_A", arg);
			driver.coil_A(arg);
		}
		else if (cmd == "coil_B") {
			serialTuple("coil_B", arg);
			driver.coil_B(arg);
		}

		else if (cmd == "VDCMIN") {
			serialTuple("VDCMIN", arg);
			driver.VDCMIN(arg);
		}

		else if (cmd == "CHOPCONF") {
			Serial.print("CHOPCONF: 0b");
			Serial.println(driver.CHOPCONF(), BIN);
		}
		else if (cmd == "toff") {
			serialTuple("toff", arg);
			driver.toff(arg);
		}
		else if (cmd == "hstrt") {
			serialTuple("hstrt", arg);
			driver.hstrt(arg);
		}
		else if (cmd == "hend") {
			serialTuple("hend", arg);
			driver.hend(arg);
		}
		/*
		else if (cmd == "fd") {
			serialTuple("fd", arg);
			driver.fd(arg);
		}
		*/
		else if (cmd == "disfdcc") {
			serialTuple("disfdcc", arg);
			driver.disfdcc(arg);
		}
		else if (cmd == "rndtf") {
			serialTuple("rndtf", arg);
			driver.rndtf(arg);
		}
		else if (cmd == "chm") {
			serialTuple("chm", arg);
			driver.chm(arg);
		}
		else if (cmd == "tbl") {
			serialTuple("tbl", arg);
			driver.tbl(arg);
		}
		else if (cmd == "vsense") {
			serialTuple("vsense", arg);
			driver.vsense(arg);
		}
		else if (cmd == "vhighfs") {
			serialTuple("vhighfs", arg);
			driver.vhighfs(arg);
		}
		else if (cmd == "vhighchm") {
			serialTuple("vhighchm", arg);
			driver.vhighchm(arg);
		}
		else if (cmd == "sync") {
			serialTuple("sync", arg);
			driver.sync(arg);
		}
		else if (cmd == "mres") {
			serialTuple("mres", arg);
			driver.mres(arg);
		}
		else if (cmd == "intpol") {
			serialTuple("intpol", arg);
			driver.intpol(arg);
		}
		else if (cmd == "dedge") {
			serialTuple("dedge", arg);
			driver.dedge(arg);
		}
		else if (cmd == "diss2g") {
			serialTuple("diss2g", arg);
			driver.diss2g(arg);
		}
		// COOLCONF
		else if (cmd == "semin") {
			serialTuple("semin", arg);
			driver.semin(arg);
		}
		else if (cmd == "seup") {
			serialTuple("seup", arg);
			driver.seup(arg);
		}
		else if (cmd == "semax") {
			serialTuple("semax", arg);
			driver.semax(arg);
		}
		else if (cmd == "sedn") {
			serialTuple("sedn", arg);
			driver.sedn(arg);
		}
		else if (cmd == "seimin") {
			serialTuple("seimin", arg);
			driver.seimin(arg);
		}
		else if (cmd == "sgt") {
			serialTuple("sgt", arg);
			driver.sgt(arg);
		}
		else if (cmd == "sfilt") {
			serialTuple("sfilt", arg);
			driver.sfilt(arg);
		}
		// PWMCONF
		else if (cmd == "pwm_ampl") {
			serialTuple("pwm_ampl", arg);
			driver.pwm_ampl(arg);
		}
		else if (cmd == "pwm_grad") {
			serialTuple("pwm_grad", arg);
			driver.pwm_grad(arg);
		}
		else if (cmd == "pwm_freq") {
			serialTuple("pwm_freq", arg);
			driver.pwm_freq(arg);
		}
		else if (cmd == "pwm_autoscale") {
			serialTuple("pwm_autoscale", arg);
			driver.pwm_autoscale(arg);
		}
		else if (cmd == "pwm_symmetric") {
			serialTuple("pwm_symmetric", arg);
			driver.pwm_symmetric(arg);
		}
		else if (cmd == "freewheel") {
			serialTuple("freewheel", arg);
			driver.freewheel(arg);
		}
		// ENCM_CTRL
		else if (cmd == "inv") {
			serialTuple("inv", arg);
			driver.inv(arg);
		}
		else if (cmd == "maxspeed") {
			serialTuple("maxspeed", arg);
			driver.maxspeed(arg);
		}

		else if (cmd == "DRVSTATUS") {
			Serial.print("DRVSTATUS: 0b");
			Serial.println(driver.DRV_STATUS(), BIN);
		}
		else if (cmd == "PWM_SCALE") {
			Serial.print("PWM_SCALE: 0b");
			Serial.println(driver.PWM_SCALE(), DEC);
		}
		else if (cmd == "LOST_STEPS") {
			Serial.print("LOST_STEPS: 0b");
			Serial.println(driver.LOST_STEPS(), DEC);
		}
		else {
			Serial.println("Invalid command!");
		}
	}
}
