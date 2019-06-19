#include "Arduino.h"
#include "ShiftRegister.h"

void ShiftRegister::Setup() {
  pinMode(SR_RW, OUTPUT);
  pinMode(SR_DS, OUTPUT);
  pinMode(SR_DC, OUTPUT);
  pinMode(SR_DR, INPUT);

  digitalWrite(SR_RW, LOW);
  configured = true;
}

void ShiftRegister::Write(uint8_t sr0_data, uint8_t sr1_data) {
  uint16_t upper = sr0_data;
  uint16_t lower = sr1_data;
  Serial.print("SR::Write(");
  Serial.print(upper);
  Serial.print(", ");
  Serial.print(lower);
  Serial.print("); -> ");
  Write((upper << 8) | lower);
}

void ShiftRegister::Write(uint16_t data) {
  if(!configured) return;

  Serial.print("SR::Write(");
  Serial.print(data);

  for(int i = 0; i < 16; i++) {
    digitalWrite(SR_DS, data & 1);
    delay(SR_TGAP);
    StrobeHigh(SR_DC);

    Serial.print(", ");
    Serial.print(data & 1);

    data >>= 1;
  }

  Serial.println(");");
}

void ShiftRegister::StrobeHigh(int pin) {
  if(!configured) return;

  digitalWrite(pin, HIGH);
  delay(SR_TSTR);
  digitalWrite(pin, LOW);
  delay(SR_TGAP);
}

void ShiftRegister::Flush() {
  Write(controlBuf, dataBuf);
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
