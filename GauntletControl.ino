#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#include "ShiftRegister.h"
#include "src/openGLCD/openGLCD.h"
#include "Aurebesh.h"

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");

  // Configure the shift register:
  SR.Setup();

  // Configure LCD library:
  int status = GLCD.Init();

  if (status != GLCD_ENOERR) {
    Serial.print("ERROR: Init not ready. Code: ");
    Serial.println(status);
    Serial.println(digitalRead(3));
    return;
  }
  
  GLCD.FillRect(0, 0, 128, 9);
  Serial.println("Initialized.");
  Str.PutsCenter(2, "New Bounty", true);
  Str.Puts(0, 10, F("Vector Unit 1072"));
}

uint8_t counter = 0;

void loop() {
  DrawBattery();
  SR.Write(counter++);
  delay(5000);
}
