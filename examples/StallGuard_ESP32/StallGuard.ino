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
#include "esp32-hal-timer.h"

#define MAX_SPEED        10 // In timer value
#define MIN_SPEED      1000

#define STALL_VALUE      7 // [-64..63]

#define EN_PIN           17 // Enable
#define DIR_PIN          16 // Direction
#define STEP_PIN         21 // Step
#define CS_PIN           5 // Chip select
#define SW_MOSI          23 // Software Master Out Slave In (MOSI)
#define SW_MISO          19 // Software Master In Slave Out (MISO)
#define SW_SCK           18 // Software Slave Clock (SCK)

#define R_SENSE 0.11f // Match to your driver
                      // SilentStepStick series use 0.11
                      // UltiMachine Einsy and Archim2 boards use 0.2
                      // Panucatt BSD2660 uses 0.1
                      // Watterott TMC5160 uses 0.075

// Select your stepper driver type
TMC2130Stepper driver(CS_PIN, R_SENSE); // Hardware SPI
//TMC2130Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK); // Software SPI
//TMC5160Stepper driver(CS_PIN, R_SENSE);
//TMC5160Stepper driver(CS_PIN, R_SENSE, SW_MOSI, SW_MISO, SW_SCK);

using namespace TMC2130_n;

hw_timer_t * timer = NULL;

uint32_t currentSpeed = 100; // Initial speed, corresponding to the timer alarm value

void IRAM_ATTR onTimer() {
  digitalWrite(STEP_PIN, !digitalRead(STEP_PIN)); // Toggle the step pin
}

void setup() {
  SPI.begin();
  Serial.begin(115200);         // Init serial port and set baudrate
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
  driver.rms_current(1500); // mA
  driver.microsteps(16);
  driver.TCOOLTHRS(0xFFFFF); // 20bit max
  driver.THIGH(0);
  driver.semin(5);
  driver.semax(2);
  driver.sedn(0b01);
  driver.sgt(STALL_VALUE);

   // Use the first timer, set the frequency to 1kHz, and specify that it is counting up
  timer = timerBegin(0, 80, true); // 0 - timer number, 80 - prescaler (80MHz / 80 = 1MHz), true - count up
  timerAttachInterrupt(timer, &onTimer, true); // Attach the interrupt function
  timerAlarmWrite(timer, 1000, true); // Set the alarm to trigger every 1000 ticks (1MHz / 1000 = 1kHz)
  timerAlarmEnable(timer); // Enable the alarm
}

void loop() {
  static uint32_t last_time = 0;
  uint32_t ms = millis();

  while (Serial.available() > 0) {
    int8_t read_byte = Serial.read();
    if (read_byte == '0') {
      timerAlarmDisable(timer);
      digitalWrite(EN_PIN, HIGH); // Disable the driver
    } else if (read_byte == '1') {
      timerAlarmEnable(timer);
      digitalWrite(EN_PIN, LOW); // Enable the driver
    } else if (read_byte == '+') { //9 clicks is fastest and good speed
      // Increase speed
      if (currentSpeed > MAX_SPEED) {
        currentSpeed -= 10; // Decrease the alarm value to increase speed
        timerAlarmWrite(timer, currentSpeed, true);
      }
    } else if (read_byte == '-') {
      // Decrease speed
      if (currentSpeed < MIN_SPEED) {
        currentSpeed += 10; // Increase the alarm value to decrease speed
        timerAlarmWrite(timer, currentSpeed, true);
      }
    }
  }

  if((ms-last_time) > 100) { //run every 0.1s
    last_time = ms;

    DRV_STATUS_t drv_status{0};
    drv_status.sr = driver.DRV_STATUS();

    Serial.print("0 ");
    Serial.print(drv_status.sg_result, DEC);
    Serial.print(" ");
    Serial.print(currentSpeed, DEC);
    Serial.print(" ");
    Serial.println(driver.cs2rms(drv_status.cs_actual), DEC);
  }
}
