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

  this->Clear(PIXEL_OFF);
}

void lcd::Clear(uint8_t pattern) {
  long start = millis();

  for (int x = 0; x < 128; x++) {
    for (int p = 0; p < 8; p++) {
      this->SetByte(x, p, pattern);
    }
  }

  float duration = millis() - start;

  Serial.print("Clear took ");
  Serial.print(duration);
  Serial.print("ms (");
  Serial.print(duration / (64 * 128));
  Serial.print(" ms/px, ");
  Serial.print(1.0 / (duration / 1000));
  Serial.println(" FPS)");
}

void lcd::SetDot(uint8_t x, uint8_t y, uint8_t color) {
  uint8_t page = y / 8;
  uint8_t data;
  uint8_t chip;

  if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT)) {
    return;
  }
  
  chip = this->goTo(x, y);

#ifdef LCD_READ_CACHE
  data = this->readCache[x][page];
#else
  data = this->readData(chip);
#endif

  if(color == PIXEL_ON) {
    data |= 0x01 << (y%8);
  } else {
    data &= ~(0x01 << (y%8));
  } 

#ifdef LCD_READ_CACHE
  this->readCache[x][page] = data;
#endif

  this->sendData(data, chip);
}

void lcd::SetByte(uint8_t x, uint8_t page, uint8_t color) {
  uint8_t y = page * 8;
  uint8_t chip;

  if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT)) {
    return;
  }

#ifdef LCD_READ_CACHE
  this->readCache[x][page] = color;
#endif

  chip = this->goTo(x, y);
  this->sendData(color, chip);
}

// Private

uint8_t lcd::goTo(uint8_t x, uint8_t y) {
  uint8_t chip = (x / DISPLAY_CHIP_WIDTH) + 1;
  uint8_t page = y / 8;
  uint8_t addr = x % DISPLAY_CHIP_WIDTH;

  if (false) {
    Serial.print("Addr: ");
    Serial.print(addr);
    Serial.print(" Page: ");
    Serial.print(page);
    Serial.print(" Chip: ");
    Serial.println(chip);
  }

  this->sendCommand(LCD_SET_ADD, addr, chip);
  this->sendCommand(LCD_SET_PAGE, page, chip);

  return chip;
}

// Low-level command sending:
void lcd::sendCommand(uint8_t command, uint8_t args, uint8_t chip) {
  this->waitReady(chip);

  uint8_t final = command | args;

  SR.SetChip(chip);
  SR.SetRWDI(LOW, LOW);
  SR.SetData(final);
  SR.Flush();

  disable();
  enable();
}

void lcd::sendData(uint8_t data, uint8_t chip) {
  this->waitReady(chip);

  SR.SetChip(chip);
  SR.SetRWDI(LOW, HIGH);
  SR.SetData(data);
  SR.Flush();

  disable();
  enable();
}

uint8_t lcd::readData(uint8_t chip) {
  this->waitReady(chip);

  SR.SetChip(chip);
  SR.SetRWDI(HIGH, HIGH);
  SR.SetData(0);
  SR.Flush();

  disable();
  enable();
  delayMicroseconds(LCD_tDDR);

  return SR.ReadData();
}

void lcd::waitReady(uint8_t chip) {
  SR.SetChip(chip);
  SR.SetRWDI(HIGH, LOW); // Read Instruction
  SR.SetData(0);
  SR.Flush();

  disable();
  enable();
  delayMicroseconds(LCD_tDDR);

  uint8_t status = SR.ReadData();

  while(status & LCD_BUSY_FLAG) {
    Serial.print("Not ready: ");
    Serial.println(status, HEX);
    status = SR.ReadData();
  };
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