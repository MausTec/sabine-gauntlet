#include <openGLCD.h>
#include "ShiftRegister.h"
#include "Aurebesh.h"

#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

ShiftRegister SR;
Aurebesh Str;

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
//  lcdDrawStringCenter(2, "New Bounty", 10, true);
//  lcdDrawString(0, 12, "Vector Unit 1072", 16);
//  lcdDrawString(0, 19, "Assassin Class", 14);
//  lcdDrawString(0, 27, "Bounty 600 cred", 15);
//  lcdDrawString(0, 35, "Highly dangerous", 16);
//  lcdDrawString(0, 43, "Likes cats", 10);
//  GLCD.FillRect(0, 56, 128, 9);
//  lcdDrawStringI(4, 57, "Accept   Reject", 16);
}

uint8_t counter = 0;

void loop() {
  SR.Write(counter++);
  delay(5000);
}
