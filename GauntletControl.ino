#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define SLEEP_AFTER_MS 10000

#include "src/digitalWriteFast.h"
#include "ShiftRegister.h"
#include "src/LCD/lcd.h"
#include "Aurebesh.h"
#include "Buttons.h"
#include "src/Pages.h"

bool error = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Configure the shift register and other components:
  SR.Setup();
  Btn.Setup();
  TX.Setup();

  // Configure LCD library:
  LCD.Setup();
  
  Serial.println("Initialized.");

  // Load initial page:
  Pages::Go(&MainPage);
  Serial.println("Main page rendered.");
}

void loop() {
  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }

  // Delegate this loop cycle to our current page.
  Pages::DoLoop();
}