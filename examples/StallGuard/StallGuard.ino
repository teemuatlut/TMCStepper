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

#define MAX_SPEED  40 // In timer value
#define MIN_SPEED  1000

#define STALL_VALUE 15 // [-64..63]

// Note: You also have to connect GND, 5V and VM.
//       A connection diagram can be found in the schematics.
#define EN_PIN        38    // Enable
#define DIR_PIN       55    // Direction
#define STEP_PIN      54    // Step
#define STEP_PORT     PORTF // Match with STEP_PIN
#define STEP_BIT_POS  0     // Match with STEP_PIN
#define CS_PIN        38    // Chip select
#define SW_MOSI       66    // Software Master Out Slave In (MOSI)
#define SW_MISO       44    // Software Master In Slave Out (MISO)
#define SW_SCK        64    // Software Slave Clock (SCK)

#define R_SENSE 0.11 // Match to your driver
                     // SilentStepStick series use 0.11
                     // UltiMachine Einsy and Archim2 boards use 0.2
                     // Panucatt BSD2660 uses 0.1

// Select your stepper driver type
//#define USING_TMC2660 // Uncomment if you are using TMC2660 driver
//TMC2130Stepper driver = TMC2130Stepper(CS_PIN, R_SENSE); // Hardware SPI
//TMC2130Stepper driver = TMC2130Stepper(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK); // Software SPI
//TMC2660Stepper driver = TMC2660Stepper(EN_PIN, R_SENSE); // Hardware SPI
//TMC2660Stepper driver = TMC2660Stepper(EN_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK); // Software SPI

bool vsense;

uint16_t rms_current(uint8_t CS) {
  return (float)(CS+1)/32.0 * (vsense?0.180:0.325)/(R_SENSE+0.02) / 1.41421 * 1000;
}

void setup() {
  SPI.begin();
  Serial.begin(250000);         // Init serial port and set baudrate
  while(!Serial);               // Wait for serial port to connect
  Serial.println("\nStart...");

  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(MISO, INPUT_PULLUP);
  digitalWrite(EN_PIN, LOW);

  driver.begin();
  driver.toff(4);
  driver.blank_time(24);
  driver.rms_current(400); // mA
  driver.microsteps(16);
  driver.sfilt(true); // Improves TMC2660 SG readout
  #ifdef USING_TMC2660
    driver.rdsel(0b01);
  #else
    driver.TCOOLTHRS(0xFFFFF); // 20bit max
    driver.THIGH(0);
  #endif
  driver.semin(5);
  driver.semax(2);
  driver.sedn(0b01);
  driver.sgt(STALL_VALUE);

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

ISR(TIMER1_COMPA_vect){
  STEP_PORT |= 1 << STEP_BIT_POS;
  STEP_PORT &= ~(1 << STEP_BIT_POS);
}

void loop()
{
  static uint32_t last_time=0;
  uint32_t ms = millis();

  while(Serial.available() > 0) {
    int8_t read_byte = Serial.read();
    #ifdef USING_TMC2660
      if (read_byte == '0')      { TIMSK1 &= ~(1 << OCIE1A); driver.toff(0); }
      else if (read_byte == '1') { TIMSK1 |=  (1 << OCIE1A); driver.toff(driver.savedToff()); }
    #else
      if (read_byte == '0')      { TIMSK1 &= ~(1 << OCIE1A); digitalWrite( EN_PIN, HIGH ); }
      else if (read_byte == '1') { TIMSK1 |=  (1 << OCIE1A); digitalWrite( EN_PIN,  LOW ); }
    #endif
    else if (read_byte == '+') { if (OCR1A > MAX_SPEED) OCR1A -= 20; }
    else if (read_byte == '-') { if (OCR1A < MIN_SPEED) OCR1A += 20; }
  }

  if((ms-last_time) > 100) { //run every 0.1s
    last_time = ms;
    uint32_t drv_status = driver.DRV_STATUS();
    Serial.print("0 ");
    Serial.print((drv_status & SG_RESULT_bm)>>SG_RESULT_bp , DEC);
    Serial.print(" ");
    Serial.println(rms_current((drv_status & CS_ACTUAL_bm)>>CS_ACTUAL_bp), DEC);
  }
}

