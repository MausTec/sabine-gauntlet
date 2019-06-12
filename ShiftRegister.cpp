#include "Arduino.h"
#include "ShiftRegister.h"

void ShiftRegister::Setup() {
  pinMode(SR_EN, OUTPUT);
  pinMode(SR_DS, OUTPUT);
  pinMode(SR_DC, OUTPUT);
  configured = true;
}

void ShiftRegister::Write(uint8_t data) {
  if(!configured) return;

  for(int i = 0; i < 8; i++) {
    digitalWrite(SR_DS, data & 1);
    delay(SR_TGAP);
    StrobeHigh(SR_DC);
    data >>= 1;
  }

  StrobeHigh(SR_EN);
}

void ShiftRegister::StrobeHigh(int pin) {
  if(!configured) return;

  digitalWrite(pin, HIGH);
  delay(SR_TSTR);
  digitalWrite(pin, LOW);
  delay(SR_TGAP);
}

void ShiftRegister::Flush() {
  Write(dataBuf);
  Write(controlBuf);
}

void ShiftRegister::SetData(uint8_t data) {
  dataBuf = data;
}

// LCD SPECIFIC

void ShiftRegister::SetRWDI(bool rw, bool di) {
  controlBuf ^= (-rw ^ controlBuf) & SR_LCD_RW;
  controlBuf ^= (-di ^ controlBuf) & SR_LCD_DI;
}

void ShiftRegister::SetChip(uint8_t chip) {
  controlBuf ^= (-chip ^ controlBuf) & SR_LCD_CS;
}

ShiftRegister SR = ShiftRegister();
