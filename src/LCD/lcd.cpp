#include "Arduino.h"
#include "../../ShiftRegister.h"
#include "lcd.h"

void lcd::Setup() {
  pinMode(LCD_EN, OUTPUT);
  pinMode(LCD_BL, OUTPUT);

  digitalWrite(LCD_EN, HIGH);
  analogWrite(LCD_BL, 255);

  // Initialize:
  this->sendCommand(LCD_ON, 0, 1);
  this->sendCommand(LCD_ON, 0, 2);

  this->sendCommand(LCD_DISP_START, 0, 1);
  this->sendCommand(LCD_DISP_START, 0, 2);

  Serial.println("Clearing with 255");
  this->Clear(B11110000);
  // this->Clear(0);
}

void lcd::Clear(uint8_t pattern) {
  for (int c = 1; c <= 2; c++) {
    for (int i = 0; i < 64; i++) {
      for (int p = 0; p < 8; p++) {
        this->sendCommand(LCD_SET_ADD, i, c);
        this->sendCommand(LCD_SET_PAGE, p, c);
        this->sendData(pattern, c);
      }
    }
  }
}

void lcd::SetDot(uint8_t x, uint8_t y, uint8_t color) {
  // uint8_t data;

  // if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT))
  //   return;
  
  // this->GotoXY(x, y-y%8);         // read data from display memory
    
  // data = this->ReadData();
  // if(color == PIXEL_ON)
  // {
  //   data |= 0x01 << (y%8);        // set dot
  // }
  // else
  // {
  //   data &= ~(0x01 << (y%8));     // clear dot
  // } 
  // this->WriteData(data);          // write data back to display
}

// Private

// Low-level command sending:
void lcd::sendCommand(uint8_t command, uint8_t args, uint8_t chip) {
  this->waitReady(chip);

  uint8_t final = command | args;

  SR.SetChip(chip);
  SR.SetRWDI(LOW, LOW);
  SR.SetData(final);
  SR.Flush();
  delay(1);

  disable();

  // SR.SetData(final);
  // SR.Flush();

  enable();
}

void lcd::sendData(uint8_t data, uint8_t chip) {
  this->waitReady(chip);

  SR.SetChip(chip);
  SR.SetRWDI(LOW, HIGH);
  SR.SetData(data);
  SR.Flush();

  disable();

  SR.SetData(data);
  SR.Flush();

  enable();
  delay(10);
}

// Higher level command wrappers:

void lcd::waitReady(uint8_t chip) {
  return;

  SR.SetChip(chip);
  SR.SetRWDI(HIGH, LOW); // Read Instruction
  SR.Flush();

  disable();

  SR.SetData(255);
  SR.Flush();

  uint8_t status = 255;

  do {
    status = SR.ReadData();
    // Serial.print("Status: ");
    // Serial.println(status, BIN);
  } while(status & LCD_BUSY_FLAG);
  
  enable();
}

void lcd::enable() {
  delayMicroseconds(LCD_tDSW);
  digitalWrite(LCD_EN, LOW);
  delayMicroseconds(LCD_tWL);
}

void lcd::disable() {
  delayMicroseconds(LCD_tAS);
  digitalWrite(LCD_EN, HIGH);
  delayMicroseconds(LCD_tWH);
}

lcd LCD = lcd();