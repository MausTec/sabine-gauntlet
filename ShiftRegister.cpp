#include "Arduino.h"
#include "ShiftRegister.h"

void enableSr() {
  digitalWrite(SR_E, LOW);
  delay(10);
}

void disableSr() {
  digitalWrite(SR_E, HIGH);
  delay(10);
}

void ShiftRegister::Setup() {
  pinMode(SR_RW, OUTPUT);
  pinMode(SR_DS, OUTPUT);
  pinMode(SR_DC, OUTPUT);
  pinMode(SR_DR, INPUT);
  pinMode(SR_RW2, OUTPUT);
  pinMode(SR_E, OUTPUT);

  digitalWrite(SR_E, LOW);
  digitalWrite(SR_RW2, LOW);
  digitalWrite(SR_RW, LOW);
  configured = true;
}

void ShiftRegister::Write(uint8_t sr0_data, uint8_t sr1_data) {
  uint16_t upper = sr0_data;
  uint16_t lower = sr1_data;
  Write((upper << 8) | lower);
}

void ShiftRegister::Write(uint16_t data) {
  if(!configured) return;

  disableSr();
  digitalWrite(SR_RW, LOW);

  for(int i = 0; i < 16; i++) {
    digitalWrite(SR_DS, data & 1);
    StrobeHigh(SR_DC);
    // Serial.print(data & 1);

    // if (i == 7)
      // Serial.print (" - ");

    data >>= 1;
  }

  enableSr();

  // Serial.println(" -- Written.");
}

void ShiftRegister::StrobeHigh(int pin) {
  if(!configured) return;

  digitalWrite(pin, HIGH);
  delay(SR_TSTR);
  digitalWrite(pin, LOW);
  delay(SR_TGAP);
}

void ShiftRegister::Flush() {
  Write(reverseBits(dataBuf), reverseBits(controlBuf));
}

void ShiftRegister::SetData(uint8_t data) {
  dataBuf = data;
  Flush();
}

/* Control Bits:
 *
 *  7   6   5   4   3   2   1   0
 * Bsy  L  On  Rst  L   L   L   L
 *
 * Busy / On:    10100000
 * Busy / Reset: 10110000
 * Getting:      00101000
 */
uint8_t ShiftRegister::ReadData() {
  // Load the shift registers in parallel
  digitalWrite(SR_RW, HIGH);
  StrobeHigh(SR_DC);
  digitalWrite(SR_RW, LOW);
  // StrobeHigh(SR_DC);

  uint16_t data = 0;

  // Shift off the data blocks
  for(int i = 0; i < 16; i++) {
    data <<= 1;
    data |= digitalRead(SR_DR) & 1;
    digitalWrite(SR_DS, data & 1);
    // Serial.print(data & 1);
    // if (i == 7) Serial.print(" - ");
    StrobeHigh(SR_DC);
  }

  // data = reverseBits(data);

  uint8_t dataChan = data & 255;
  uint8_t addressChan = data >> 8;

  if (false) {
    Serial.print(" -- Read: ");
    Serial.print(data);
    Serial.print(", Data: ");
    Serial.print(dataChan);
    Serial.print(", Address: ");
    Serial.println(addressChan);
  }

  return dataChan;
}

// LCD SPECIFIC

void ShiftRegister::SetRWDI(bool rw, bool di) {
  // Serial.print("Set RW: ");
  // Serial.println(rw);
  // Serial.print("Set DI: ");
  // Serial.println(di);
  // controlBuf ^= (-rw ^ controlBuf) & SR_LCD_RW;
  // controlBuf ^= (-di ^ controlBuf) & SR_LCD_DI;
  controlBuf = (controlBuf & ~(1UL << SR_LCD_RW)) | (rw << SR_LCD_RW);
  controlBuf = (controlBuf & ~(1UL << SR_LCD_DI)) | (di << SR_LCD_DI);
  Flush();
}

void ShiftRegister::SetChip(uint8_t chip) {
  // controlBuf ^= (-chip ^ controlBuf) & SR_LCD_CS;
  // Serial.print("Set chip: ");
  // Serial.println(chip);

  bool cs1 = chip == 0;
  bool cs2 = chip == 1;

  controlBuf = (controlBuf & ~(1UL << SR_LCD_CS1)) | (cs1 << SR_LCD_CS1);
  controlBuf = (controlBuf & ~(1UL << SR_LCD_CS2)) | (cs2 << SR_LCD_CS2);
  Flush();
}

uint8_t ShiftRegister::reverseBits(uint8_t data) {
  uint8_t tmp = data;
  uint8_t out = 0;

  for (int i = 0; i < 8; i++) {
    out <<= 1;
    out |= (tmp & 1);
    tmp >>= 1;
  }

  return out;
}

uint16_t ShiftRegister::reverseBits(uint16_t data) {
  uint8_t tmp = data;
  uint8_t out = 0;

  for (int i = 0; i < 16; i++) {
    out <<= 1;
    out |= (tmp & 1);
    tmp >>= 1;
  }

  return out;
}

ShiftRegister SR = ShiftRegister();
