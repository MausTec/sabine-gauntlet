#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define SLEEP_AFTER_MS 10000

#include "Arduino.h"

#include "config.h"
#include "src/RTC/RTC.h"
#include "src/ShiftRegister.h"
#include "src/LCD/lcd.h"
#include "src/Aurebesh.h"
#include "src/Buttons.h"
#include "src/Pages.h"
#include "src/digitalWriteFast.h"
#include "src/Settings.h"

bool error = false;

void setup() {
  Serial.begin(57600);
  Serial.println(F("Initializing..."));

  // Configure the shift register and other components:
  Settings.Load();

  // RTC.Setup();
  SR.Setup();
  Btn.Setup();
  TX.Setup();

  // Configure LCD library:
  LCD.Setup();
  LCD.BacklightSet(1000, Settings.BacklightBrightness);
  
  Serial.println(F("Initialized."));

  // Load initial page:
  Pages::Go(&MainPage);
}

void loop() {
  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }

  // Delegate this loop cycle to our current page.
  Pages::DoLoop();

  // Schedule Threads
  LCD.DoLoop();
  TX.DoLoop();
}