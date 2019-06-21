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
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Configure the shift register and other components:
  SR.Setup();
  Btn.Setup();
  TX.Setup();

  // Configure LCD library:
  LCD.Setup();
  
  Serial.println("Initialized.");

  // Load initial page:
  // Pages::Go(&MainPage);
  // Serial.println("Main page rendered.");
}

uint8_t counter = 0;

void loop() {
  // if (error) {
  //   delay(1000);
  //   return;
  // }
  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }

  // Str.Puts(10, 10, counter, false);
  // Str.Puts(64, 20, counter, false);
  // UI.Title(counter++);


  LCD.Clear(counter++);

  delay(1000);


  // Delegate this loop cycle to our current page.
  // Pages::DoLoop();
}