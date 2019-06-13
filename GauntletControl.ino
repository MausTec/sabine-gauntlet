#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define SLEEP_AFTER_MS 10000

#include "ShiftRegister.h"
#include "src/openGLCD/openGLCD.h"
#include "Aurebesh.h"
#include "Buttons.h"
#include "src/Pages.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Configure the shift register:
  // Which we should do after we have free pins. :|
  // SR.Setup();

  // Configure LCD library:
  int status = GLCD.Init();

  if (status != GLCD_ENOERR) {
    Serial.print("ERROR: Init not ready. Code: ");
    Serial.println(status);
    Serial.println(digitalRead(3));
    return;
  }

  // Configure Input
  Btn.Setup();
  
  Serial.println("Initialized.");

  // Load initial page:
  Pages::Go(&MainPage);

  // Doorbell! :D
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
}

void loop() {
  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  if (Btn.LastPress() > SLEEP_AFTER_MS) {
    Pages::Go(&StandbyPage);
  }

  // Delegate this loop cycle to our current page.
  Pages::DoLoop();
}