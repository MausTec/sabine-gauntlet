#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define SLEEP_AFTER_MS 10000
#define STAT_PIN 10

#include "src/RTC/RTC.h"
#include "ShiftRegister.h"
#include "src/LCD/lcd.h"
#include "Aurebesh.h"
#include "Buttons.h"
#include "src/Pages.h"
#include "src/digitalWriteFast.h"

bool error = false;

void setup() {
  Serial.begin(57600);
  Serial.println(F("Initializing..."));

  // Configure the shift register and other components:
  RTC.Setup();
  SR.Setup();
  Btn.Setup();
  TX.Setup();

  // Configure LCD library:
  LCD.Setup();
  LCD.BacklightOn(1000);
  
  Serial.println(F("Initialized."));

  // Load initial page:
  Pages::Go(&MainPage);
  Serial.println(F("Main page rendered."));

  // Status Ind
  pinMode(STAT_PIN, OUTPUT);
}

bool statusBit = false;

void loop() {
  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  if (Btn.LastPress() > SLEEP_AFTER_MS) {
    Pages::Go(&StandbyPage);
  }

  // Delegate this loop cycle to our current page.
  Pages::DoLoop();

  // Schedule Threads
  LCD.DoLoop();
  TX.DoLoop();

  // Activity LED
  if (statusBit) {
    digitalWriteFast(STAT_PIN, HIGH);
  } else {
    digitalWriteFast(STAT_PIN, LOW);
  }

  statusBit = !statusBit;
}