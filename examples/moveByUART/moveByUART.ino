/**
 * Author Konstantin Kalinskiy
 * Initializes the library and runs the stepper
 * motor only by UART (don't need to connect step dir pins)
 * I test this setup on arduino nano
 * i use potenciometr to change speed and direction
 * and i use button to run\stop motor
 */
#include <TMCStepper.h>
// #include <CaptureTimer.h>

#define FWD_BUTTON_PIN 8

#define KNOB_PIN A0  // connect potenciometr
#define EN_PIN 5     // Enable
// #define DIR_PIN 6            // Direction (not need for UART control)
// #define STEP_PIN 7           // Step (not need for UART control)
#define INDEX_PIN 2  // INDEX pin on TMC driver. Must connect to arduino interrupt pin
// #define CS_PIN 42            // Chip select
// #define SW_MOSI 66           // Software Master Out Slave In (MOSI)
// #define SW_MISO 44           // Software Master In Slave Out (MISO)
// #define SW_SCK 64            // Software Slave Clock (SCK)
#define SW_RX 9   // TMC2208/TMC2224 SoftwareSerial receive pin
#define SW_TX 10  // TMC2208/TMC2224 SoftwareSerial transmit pin
// #define SERIAL_PORT Serial1  // TMC2208/TMC2224 HardwareSerial port
#define DRIVER_ADDRESS 0b00  // TMC2209 Driver address according to MS1 and MS2

#define MICROSTEPS 2  //microsteps 1/2, 1/4, 1/8, 1/16, 1/32, 1/64, 1/128 1/256
#define samplingPer 500

#define R_SENSE 0.11f  // Match to your driver \
                       // SilentStepStick series use 0.11 \
                       // UltiMachine Einsy and Archim2 boards use 0.2 \
                       // Panucatt BSD2660 uses 0.1 \
                       // Watterott TMC5160 uses 0.075

// Select your stepper driver type
//TMC2130Stepper driver(CS_PIN, R_SENSE);                           // Hardware SPI
//TMC2130Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK); // Software SPI
//TMC2660Stepper driver(CS_PIN, R_SENSE);                           // Hardware SPI
//TMC2660Stepper driver(CS_PIN, _SENSE, SW_MOSI, SW_MISO, SW_SCK);
//TMC5160Stepper driver(CS_PIN, R_SENSE);
//TMC5160Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

// TMC2208Stepper driver(&SERIAL_PORT, R_SENSE);                     // Hardware Serial
//TMC2208Stepper driver(SW_RX, SW_TX, R_SENSE);                     // Software serial
//TMC2209Stepper driver(&SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);

TMC2209Stepper driver(SW_RX, SW_TX, R_SENSE, DRIVER_ADDRESS);

void print_param(String param_name, float param_value) {
  Serial.print(param_name);
  Serial.print(": ");
  Serial.println(param_value, 2);
}

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("Serial port started");


  pinMode(KNOB_PIN, INPUT);
  pinMode(EN_PIN, OUTPUT);
  // pinMode(STEP_PIN, OUTPUT);
  // pinMode(DIR_PIN, OUTPUT);
  // pinMode(INDEX_PIN, INPUT);
  pinMode(FWD_BUTTON_PIN, INPUT);
  digitalWrite(EN_PIN, LOW);  // Enable driver in hardware

  // Enable one according to your setup
  //SPI.begin();                    // SPI drivers
  //SERIAL_PORT.begin(115200);      // HW UART drivers
  driver.beginSerial(115200);  // SW UART drivers

  driver.begin();                 //  SPI: Init CS pins and possible SW SPI pins
                                  // UART: Init SW UART (if selected) with default 115200 baudrate
  driver.toff(1);                 // Enables driver in software
  driver.rms_current(1500);       // Set motor RMS current
  driver.microsteps(MICROSTEPS);  //microsteps 1/2, 1/4, 1/8, 1/16, 1/32, 1/64, 1/128 1/256

  // driver.en_pwm_mode(true);    // Toggle stealthChop on TMC2130/2160/5130/5160
  driver.en_spreadCycle(false);  // Toggle spreadCycle on TMC2208/2209/2224
  // driver.VACTUAL(0);           // 0 - set rotor speed from STEP input, !=0 - from internal generator (12Mhz max)

  driver.pwm_autoscale(true);  // stealthChop auto configuration
  driver.pwm_autograd(true);   // stealthChop auto configuration. Automatic tuning (only with pwm_autoscale=1)



  // stealhChop autoconf phase 1 (PWM_ OFS_AUTO)
  // Conditions:
  // - Motor in standstill and actual current scale (CS) is identical to run current (IRUN).
  // - If standstill reduction is enabled (pin PDN_UART=0), an initial step pulse switches the drive back to run current.
  // - Pins VS and VREF at operating level.
  print_param("IRUN", driver.irun());
  print_param("CS_ACTUAL", driver.cs_actual());

  Serial.println("Start delay for autoconf");
  delay(200);  // delay at least 130 milliseconds to stealhChop autoconfig phase 1
  Serial.println("End delay for autoconf");

  print_param("IRUN", driver.irun());
  print_param("CS_ACTUAL", driver.cs_actual());

  Serial.println("Starting phase 2 of stealhChop autoconfig");

  // Motor must move at a velocity, where a significant amount of back EMF is generated and where the full run current can be reached. Conditions:
  // - 1.5 * PWM_OFS_AUTO < PWM_SCALE_SUM < 4 * PWM_OFS_AUTO
  // - PWM_SCALE_SUM < 255.
  // Hint: A typical range is 60-300 RPM. Determine best conditions with the evaluation board and monitor PWM_SCALE_AUTO going down to zero during tuning.

  float percent_rotation_per_tick = (float)((float)(1.8 / MICROSTEPS) / 360);

  int32_t vactual = (float)(1 / percent_rotation_per_tick);  //start from 1 RPS (60 RPM)
  uint32_t calibration_time;                                 // how many time need to calibrate
  int16_t pwm_scale_auto;

  // stealhChop autoconf phase 2
  // need some inpection. I'm not sure if this is correct

  do {
    print_param("rotation speed", vactual);
    print_param("microsteps", MICROSTEPS);
    calibration_time = (float)(500 / (float)(abs(vactual) / MICROSTEPS)) * 1000;  // how many time need to 1000 full steps
    print_param("calibration time ms", calibration_time);
    driver.VACTUAL(vactual);  // steps per second
    vactual *= -1.05; // increase 5% and change direction
    if (abs(vactual) > 3 / percent_rotation_per_tick) {
      vactual = (float)(1.00 / percent_rotation_per_tick);
    }
    delay(calibration_time);
    pwm_scale_auto = driver.pwm_scale_auto();
    print_param("pwm_scale_auto", pwm_scale_auto);
  } while (pwm_scale_auto != 0);

  driver.VACTUAL(0);
  Serial.println("stealhChop autoconfig finished...");


  driver.index_step(1);  // 1 - output steps to UART

  // initialize the capture timer pin & period
  // CaptureTimer::initCapTicks(samplingPer, INDEX_PIN);
}


bool shaft = false;
int fwd_button_state;
int knob_pin_value = 0;
int32_t rotation_speed = 0;
uint16_t ticks;
float percent_rotation_per_tick = 1.8 / MICROSTEPS / 360;

void loop() {
  fwd_button_state = digitalRead(FWD_BUTTON_PIN);


  if (fwd_button_state == HIGH) {
    knob_pin_value = analogRead(KNOB_PIN);
    rotation_speed = (long)(knob_pin_value - 512) * 2 * MICROSTEPS;

    driver.VACTUAL(rotation_speed);  // set rotor speed

    while (fwd_button_state == HIGH) {
      print_param("pwm_scale_auto: ", driver.pwm_scale_auto());
      delay(100);
      knob_pin_value = analogRead(KNOB_PIN);
      rotation_speed = (long)(knob_pin_value - 512) * 2 * MICROSTEPS;
      driver.VACTUAL(rotation_speed);


      // if (CaptureTimer::getTicks(&ticks) == true) {  // Only print on serial if new data is available
      //   Serial.print("Ticks: ");
      //   Serial.print(ticks);
      //   Serial.print("\tFreq: ");
      //   (void)CaptureTimer::getFreq(&ticks);
      //   Serial.print(ticks);
      //   Serial.print("Hz");
      //   Serial.print("\tRotation speed: ");
      //   Serial.println(rotation_speed);
      //   print_param("IRUN", driver.irun());
      //   print_param("CS_ACTUAL", driver.cs_actual());
      // }


      fwd_button_state = digitalRead(FWD_BUTTON_PIN);
    }
    driver.VACTUAL(0);

    print_param("RPS: ", (float)rotation_speed * percent_rotation_per_tick);
    print_param("MicroStep counter: ", driver.MSCNT());
  }
  // shaft = !shaft;
  // driver.shaft(shaft);
}
