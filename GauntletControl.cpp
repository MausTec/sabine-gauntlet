#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define SLEEP_AFTER_MS 10000

#define KB_DAT_PIN 14 // or 19?
#define KB_IRQ_PIN PD2

#include "Arduino.h"

#include "config.h"
#include "include/RTC.h"
#include "include/ShiftRegister.h"
#include "include/lcd.h"
#include "include/Aurebesh.h"
#include "include/Buttons.h"
#include "include/Pages.h"
#include "include/digitalWriteFast.h"
#include "include/Settings.h"

#include "include/PS2Keyboard.h"

void setup() {
  Serial.begin(57600);
  Serial.println(F("Initializing..."));

  // Configure the shift register and other components:
  Settings.Load();

  RTC.Setup();
  SR.Setup();
  Btn.Setup();
  TX.Setup();

  // Configure LCD library:
  LCD.Setup();
  LCD.BacklightSet(1000, Settings.BacklightBrightness);

  // Init keyboard
  PS2Keyboard::begin(KB_DAT_PIN, KB_IRQ_PIN);

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
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }

  Btn.tick();
  PS2Keyboard::tick();

  // Delegate this loop cycle to our current page.
  Pages::DoLoop();

  // Schedule Threads
  LCD.DoLoop();
}