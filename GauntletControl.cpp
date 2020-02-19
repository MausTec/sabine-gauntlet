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

PS2Keyboard KB;

bool error = false;

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
  KB.begin(KB_DAT_PIN, KB_IRQ_PIN);

  Serial.println(F("Initialized."));

  // Load initial page:
  Pages::Go(&MainPage);
}

uint8_t dx = 0;

void loop() {
  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }

  if (KB.available()) {

    // read the next key
    char c = KB.read();

    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {

      // otherwise, just print all normal characters
      Str.PutChar(dx, 9, c);
      dx += 8;
      if (dx >= 120) dx = 0;
    }
  }

  // Delegate this loop cycle to our current page.
  Pages::DoLoop();

  // Schedule Threads
  LCD.DoLoop();
  TX.DoLoop();
}