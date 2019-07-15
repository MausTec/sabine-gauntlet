#include "Arduino.h"
#include "src/digitalWriteFast.h"
#include "ShiftRegister.h"

void ShiftRegister::Setup() {
  pinModeFast(SR_RW, OUTPUT);
  pinModeFast(SR_DS, OUTPUT);
  pinModeFast(SR_DC, OUTPUT);
  pinModeFast(SR_DR, INPUT);

  digitalWrite(SR_RW, LOW);
  configured = true;
}

void ShiftRegister::Write(uint8_t sr0_data, uint8_t sr1_data) {
  uint16_t upper = sr0_data;
  uint16_t lower = sr1_data;
  Write((upper << 8) | lower);
}

void ShiftRegister::Write(uint16_t data) {
  for(int i = 0; i < 16; i++) {
    if (data & 1) {
      digitalWriteFast(SR_DS, HIGH);
    } else {
      digitalWriteFast(SR_DS, LOW);
    }

    StrobeHigh(SR_DC);
    data >>= 1;
  }
}

void ShiftRegister::StrobeHigh(int pin) {
  delayMicroseconds(SR_TGAP);
  digitalWriteFast(pin, HIGH);
  delayMicroseconds(SR_TSTR);
  digitalWriteFast(pin, LOW);
}

void ShiftRegister::Flush() {
  Write(reverseBits(dataBuf), reverseBits(controlBuf));
}

void ShiftRegister::SetData(uint8_t data) {
  dataBuf = data;
}

void ShiftRegister::LatchData(void) {
  digitalWriteFast(SR_DS, LOW);
  digitalWriteFast(SR_RW, HIGH);
  digitalWriteFast(SR_DC, HIGH);
  digitalWriteFast(SR_DC, LOW);
  digitalWriteFast(SR_RW, LOW);
}

uint8_t ShiftRegister::ReadData(void) {
  return ReadData(true);
}

/* Control Bits:
 *
 *  7   6   5   4   3   2   1   0
 * Bsy  L  On  Rst  L   L   L   L
 */
uint8_t ShiftRegister::ReadData(bool latch) {
  // Load in the new data:
  if (latch) {
    LatchData();
  }

  uint16_t data = 0;
  uint16_t addr = 0;

  // Shift address or skip
  if (false) {
    for(int i = 0; i < 8; i++) {
      addr <<= 1;
      addr |= digitalReadFast(SR_DR) != 0;

      StrobeHigh(SR_DC);
    }
  } else {
    // Just shift away the Address bits.
    for(int i = 0; i < 8; i++) {
      StrobeHigh(SR_DC);
    }
  }

  for(int i = 0; i < 8; i++) {
    data <<= 1;
    data |= digitalReadFast(SR_DR) != 0;

    StrobeHigh(SR_DC);
  }

  if (false) {
    Serial.print("-- R - D: ");
    Serial.print(data, BIN);
    Serial.print(" A: ");
    Serial.println(addr, BIN);
  }

  return data;
}

// LCD SPECIFIC

void ShiftRegister::SetRWDI(bool rw, bool di) {
  controlBuf = (controlBuf & ~(1UL << SR_LCD_RW)) | (rw << SR_LCD_RW);
  controlBuf = (controlBuf & ~(1UL << SR_LCD_DI)) | (di << SR_LCD_DI);
}

void ShiftRegister::SetChip(uint8_t chip) {
  bool cs1 = !!(chip & 1);
  bool cs2 = !!(chip & 2);

  controlBuf = (controlBuf & ~(1UL << SR_LCD_CS1)) | (cs1 << SR_LCD_CS1);
  controlBuf = (controlBuf & ~(1UL << SR_LCD_CS2)) | (cs2 << SR_LCD_CS2);
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
  uint16_t tmp = data;
  uint16_t out = 0;

  for (int i = 0; i < 16; i++) {
    out <<= 1;
    out |= (tmp & 1);
    tmp >>= 1;
  }

  return out;
}

ShiftRegister SR = ShiftRegister();
