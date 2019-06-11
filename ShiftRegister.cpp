#include "Arduino.h"
#include "ShiftRegister.h"

void ShiftRegister::Setup() {
  pinMode(SR_EN, OUTPUT);
  pinMode(SR_DS, OUTPUT);
  pinMode(SR_DC, OUTPUT);
}

void ShiftRegister::Write(uint8_t data) {
  for(int i = 0; i < 8; i++) {
    digitalWrite(SR_DS, data & 1);
    delay(SR_TGAP);
    StrobeHigh(SR_DC);
    data >>= 1;
  }

  StrobeHigh(SR_EN);
}

void ShiftRegister::StrobeHigh(int pin) {
  digitalWrite(pin, HIGH);
  delay(SR_TSTR);
  digitalWrite(pin, LOW);
  delay(SR_TGAP);
}

ShiftRegister SR = ShiftRegister();
