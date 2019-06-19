#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define SLEEP_AFTER_MS 10000

#include "ShiftRegister.h"
#include "src/openGLCD/openGLCD.h"
#include "Aurebesh.h"
#include "Buttons.h"
#include "src/Pages.h"

bool error = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Configure the shift register:
  // Which we should do after we have free pins. :|
  SR.Setup();
  Btn.Setup();
  TX.Setup();

  // Configure LCD library:
  // int status = GLCD.Init();

  // if (status != GLCD_ENOERR) {
  //   Serial.print("ERROR: Init not ready. Code: ");
  //   Serial.println(status);
  //   error = true;
  //   return;
  // }
  
  Serial.println("Initialized.");

  analogWrite(6, 255);

  // Load initial page:
  // Pages::Go(&MainPage);
}

uint8_t counter = 0;

void loop() {
  Serial.println();
  TX.Send(1, 1);
  TX.Send(1, 3);
  TX.Send(1, 0);

  delay(1000);

  // Activate Standby after 5000s
  // This will re-enter but Pages::Go is idempotent.
  // if (Btn.LastPress() > SLEEP_AFTER_MS) {
  //   Pages::Go(&StandbyPage);
  // }

  // Delegate this loop cycle to our current page.
  // Pages::DoLoop();
}