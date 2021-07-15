/**
 * Author Teemu Mäntykallio
 *
 * Plot TMC2130 or TMC2660 motor load using the stallGuard value.
 * You can finetune the reading by changing the STALL_VALUE.
 * This will let you control at which load the value will read 0
 * and the stall flag will be triggered. This will also set pin DIAG1 high.
 * A higher STALL_VALUE will make the reading less sensitive and
 * a lower STALL_VALUE will make it more sensitive.
 *
 * You can control the rotation speed with
 * 0 Stop
 * 1 Resume
 * + Speed up
 * - Slow down
 */
#include <TMCStepper.h>

constexpr uint32_t MAX_SPEED = 40; // In timer value
constexpr uint32_t MIN_SPEED = 1000;

constexpr int16_t STALL_VALUE = 15; // [-64..63]

constexpr TMC_HAL::PinDef
  EN_PIN   = 38, // Enable
  DIR_PIN  = 55, // Direction
  STEP_PIN = 54, // Step
  SW_RX    = 63, // SoftwareSerial receive pin
  SW_TX    = 40; // SoftwareSerial transmit pin

auto SERIAL_PORT = Serial1;              // HardwareSerial port
constexpr uint8_t DRIVER_ADDRESS = 0b00; // Driver address according to MS1 and MS2

constexpr float R_SENSE = 0.11; // Match to your driver

TMC_HAL::SWSerial SW_SERIAL(SW_RX, SW_TX);

// Select your stepper driver type
//TMC2209Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2209Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(SERIAL_PORT, R_SENSE, DRIVER_ADDRESS);
//TMC2300Stepper driver(  SW_SERIAL, R_SENSE, DRIVER_ADDRESS);

// Using direct register manipulation can reach faster stepping times
auto STEP_PORT = PORTF; // Match with STEP_PIN
auto STEP_BIT_POS = 0;  // Match with STEP_PIN

ISR(TIMER1_COMPA_vect){
  //STEP_PORT ^= 1 << STEP_BIT_POS;
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
}

void setup() {
  Serial.begin(250000);         // Init serial port and set baudrate
  while(!Serial);               // Wait for serial port to connect
  Serial.println("\nStart...");

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW);

  driver.begin();
  driver.toff(4);
  driver.blank_time(24);
  driver.rms_current(400); // mA
  driver.microsteps(16);
  driver.TCOOLTHRS(0xFFFFF); // 20bit max
  driver.semin(5);
  driver.semax(2);
  driver.sedn(0b01);
  driver.SGTHRS(STALL_VALUE);

  // Set stepper interrupt
  {
    cli();//stop interrupts
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B
    TCNT1  = 0;//initialize counter value to 0
    OCR1A = 256;// = (16*10^6) / (1*1024) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS11 bits for 8 prescaler
    TCCR1B |= (1 << CS11);// | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei();//allow interrupts
  }
}

void loop() {
  static uint32_t last_time=0;
  uint32_t ms = millis();

  while(Serial.available() > 0) {
    int8_t read_byte = Serial.read();
    if (read_byte == '0')      { TIMSK1 &= ~(1 << OCIE1A); digitalWrite( EN_PIN, HIGH ); }
    else if (read_byte == '1') { TIMSK1 |=  (1 << OCIE1A); digitalWrite( EN_PIN,  LOW ); }
    else if (read_byte == '+') { if (OCR1A > MAX_SPEED) OCR1A -= 20; }
    else if (read_byte == '-') { if (OCR1A < MIN_SPEED) OCR1A += 20; }
  }

  if((ms-last_time) > 100) { //run every 0.1s
    last_time = ms;

    Serial.print("0 ");
    Serial.print(driver.SG_RESULT(), DEC);
    Serial.print(" ");
    Serial.println(driver.cs2rms(driver.cs_actual()), DEC);
  }
}

