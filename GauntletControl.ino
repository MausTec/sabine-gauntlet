#include <openGLCD.h>
#include "ShiftRegister.h"

#define INVERT true
#define LCD_SCREEN_WIDTH 128
#define LCD_SCREEN_HEIGHT 64

#define LCD_DATA_PIN 12
#define LCD_CLK_PIN 13
#define LCD_ENABLE_PIN 11
#define LCD_CHIP_SELECT_PIN 10
#define LCD_INSTRUCTION_PIN 8
#define LCD_RESET_PIN 7

#define C_DISPLAY_ON B00111111
#define C_DISPLAY_OFF B00111110
#define C_SET_Y_ADDRESS B01000000
#define C_SET_X_ADDRESS B10111000
#define C_SET_START_LINE B11000000

unsigned char LCD_BUFFER[128][8];

ShiftRegister SR;

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
  lcdDrawStringCenter(2, "New Bounty", 10, true);
  lcdDrawString(0, 12, "Vector Unit 1072", 16);
  lcdDrawString(0, 19, "Assassin Class", 14);
  lcdDrawString(0, 27, "Bounty 600 cred", 15);
  lcdDrawString(0, 35, "Highly dangerous", 16);
  lcdDrawString(0, 43, "Likes cats", 10);
  GLCD.FillRect(0, 56, 128, 9);
  lcdDrawStringI(4, 57, "Accept   Reject", 16);
}

uint8_t counter = 0;

void loop() {
  SR.Write(counter++);
  delay(5000);
}
