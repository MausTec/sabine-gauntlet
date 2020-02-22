#include "lcd.h"

void lcd::Setup() {
  pinMode(LCD_EN, OUTPUT);
  pinMode(LCD_BL, OUTPUT);

  digitalWrite(LCD_EN, HIGH);
  analogWrite(LCD_BL, 0);

  // Initialize:
  this->sendCommand(LCD_ON, 0, 1);
  this->sendCommand(LCD_ON, 0, 2);

  this->sendCommand(LCD_DISP_START, 0, 1);
  this->sendCommand(LCD_DISP_START, 0, 2);

  this->Clear(PIXEL_OFF);

  // Setup Backlight Dimming
  blThread = Thread();
  blThread.enabled = false;
  blThread.onRun(runThread);
}

void lcd::Clear(uint8_t pattern) {
  long start = millis();

  for (int p = 0; p < 8; p++) {
    for (int x = 0; x < 128; x++) {
      this->SetByte(x, p, pattern);
    }
  }

  float duration = millis() - start;

  if (false) {
    Serial.print("Clear took ");
    Serial.print(duration);
    Serial.print("ms (");
    Serial.print(duration / (64 * 128));
    Serial.print(" ms/px, ");
    Serial.print(1.0 / (duration / 1000));
    Serial.println(" FPS)");
  }
}

void lcd::SetDot(uint8_t x, uint8_t y, uint8_t color) {
  uint8_t page = y / 8;
  uint8_t data;
  uint8_t chip;

  if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT)) {
    return;
  }

#ifdef LCD_READ_CACHE
  data = this->readCache[x][page];
#else
  chip = this->goTo(x, y);
  data = this->readData(chip);
#endif

  if(color & 1) {
    data |= 0x01 << (y%8);
  } else {
    data &= ~(0x01 << (y%8));
  } 

#ifdef LCD_READ_CACHE
  this->readCache[x][page] = data;
#endif

  chip = this->goTo(x, y);
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

void lcd::MaskByte(uint8_t x, uint8_t page, uint8_t mask, uint8_t data) {
  uint8_t y = page * 8;
  uint8_t chip;
  uint8_t color, prevColor;

  if((x >= DISPLAY_WIDTH) || (y >= DISPLAY_HEIGHT)) {
    return;
  }

#ifdef LCD_READ_CACHE
  color = this->readCache[x][page];
#else
  chip = this->goTo(x, y);
  color = this->readData(chip);
#endif

  prevColor = color;

  data  &= mask;
  color &= ~mask;
  color |= data;

  if (false) {
    Serial.print(" C: ");
    Serial.println(color, BIN);
  }

  if (prevColor == color) {
    return;
  }

  this->SetByte(x, page, color);
}

// Drawing

void lcd::DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
  uint8_t xend = x + width;
  uint8_t yend = y + height;

  for (int ypos = y; ypos <= yend; ypos++) {
    for (int xpos = x; xpos <= xend; xpos++) {
      if (xpos == x || ypos == y || xpos == xend || ypos == yend) {
        this->SetDot(xpos, ypos, color >> (xpos + ypos) % 8);
      }
    }
  }
}

void lcd::FillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color) {
  uint8_t xend = x + width;
  uint8_t yend = y + height;
  uint8_t page, pageStart, pageEnd, mask;
  int8_t  bitStart, bitEnd;

  // Iterate over rows in pages:
  for (page = y / 8; page <= (yend / 8); page++) {

    pageStart = page * 8;
    pageEnd   = pageStart + 8;
    bitStart  = max(y - pageStart, 0);
    bitEnd    = 8 - max(pageEnd - yend, 0);

    mask = (((1 << (bitStart)) - 1) ^ ((1 << (bitEnd)) - 1));

    // Iterate over each column in this row, read data, and mask shape:
    for (int xpos = x; xpos <= xend; xpos++) {
      this->MaskByte(xpos, page, mask, color);
    }
  }
}

#define _swap(a,b) \
do { \
  uint8_t t; \
  t=a;\
  a=b;\
  b=t;\
} while(0)

void lcd::DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color) {
  uint8_t dx, dy, x, y, slope;
  int8_t error, ystep;

  slope = abs(y1 - y0) / abs(x1 - x0);

  if (slope > 1) {
    _swap(x0, y0);
    _swap(x1, y1);
  }

  if (x0 > x1) {
    _swap(x0, x1);
    _swap(y0, y1);
  }

  dx = x1 - x0;
  dy = abs(y1 - y0);
  error = dx / 2;

  y = y0;
  ystep = y0 < y1 ? 1 : -1;

  for (x = x0; x <= x1; x++) {
    if (slope > 1) {
      this->SetDot(y, x, color);
    } else {
      this->SetDot(x, y, color);
    }

    error = error - dy;

    if (error < 0) {
      y = y + ystep;
      error = error + dx;
    }
  }
}

// This code functions similar to FillRect only the actual data being
// written is copied from memory. This might also be duplicated logic
// from Aurebesh library, which uses similar code to mask in an "image".
//
void lcd::DrawGraphic(uint8_t posX, uint8_t posY, uint8_t scaleWidth, uint8_t scaleHeight, uint8_t* data, bool invert) {
  long start = millis();
  uint8_t page, chip, pageStart, pageEnd, mask, xpos, xend, yend;
  int8_t  bitStart, bitEnd, yPos;

  // Graphic Specific
  size_t idx, p = 0;
  uint8_t i, j, imgByte, colOffset, colByte, frame, startX, 
          startY, width, height, frameCount, x, y;

  double colSkip;
  double rowSkip;

  // Load header
  frameCount = pgm_read_byte(&(data[p++]));

  for (j = 0; j < frameCount; j++) {
    frame  = pgm_read_byte(&(data[p++]));
    startX = pgm_read_byte(&(data[p++]));
    startY = pgm_read_byte(&(data[p++]));
    width  = pgm_read_byte(&(data[p++]));
    height = pgm_read_byte(&(data[p++]));

    colSkip = (double)width / scaleWidth;
    rowSkip = (double)height / scaleHeight;

    if (false) {
      Serial.print("pass=");
      Serial.print(j);
      Serial.print(" frame=");
      Serial.print(frame, HEX);
      Serial.print(" startX=");
      Serial.print(startX, HEX);
      Serial.print(" startY=");
      Serial.print(startY, HEX);
      Serial.print(" width=");
      Serial.print(width, HEX);
      Serial.print(" height=");
      Serial.println(height, HEX);
    }

    x = posX + startX;
    y = posY + startY;

    xend = x + scaleWidth;
    yend = y + scaleHeight;

    // Iterate over rows in pages:
    for (page = y / 8; page < (yend / 8); page++) {
      pageStart = page * 8;
      pageEnd   = pageStart + 8;
      bitStart  = max(y - pageStart, 0);
      bitEnd    = 8 - max(pageEnd - yend, 0);

      mask = (((1 << (bitStart)) - 1) ^ ((1 << (bitEnd)) - 1)); 

      // Iterate over each column in this row, read data, and mask shape:
      for (xpos = x; xpos <= xend; xpos += 1) {
        uint8_t eXpos = ((xpos - x) * colSkip);
        colByte = 0;
        yPos = pageStart - bitStart;

        for (i = 0; i < 8; i++) {
          colByte >>= 1;

          // Shift off rows that we're not writing.
          if (i < bitStart || i > bitEnd) continue;

          // Calculate current image byte
          idx = (
            // Start Byte
            ((yPos + i) - y) * ceil((double)width / 8) * rowSkip
          ) + (
            // X position
            eXpos / 8
          );

          colOffset = (eXpos - 1) % 8;
          imgByte = pgm_read_byte(&(data[p + idx])) << colOffset;
          colByte |= imgByte & B10000000;
        }

        if (invert) {
          colByte = ~colByte;
        }

        MaskByte(xpos, page, mask, colByte);
      }
    }

    // Increment pointer to next frame
    p += ((size_t) ceil((float)width / 8) * height);
  }

  Serial.print("Rendered graphic in ");
  Serial.print(millis() - start);
  Serial.println("ms");
}

void lcd::DrawGraphic(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t* data) {
  lcd::DrawGraphic(x, y, width, height, data, false);
}

void lcd::BacklightSet(long duration, uint8_t level) {
  uint8_t distance = abs(blLevel - level);

  blTargetLevel = level;
  blThread.setInterval(min(duration / distance, 1));
  blThread.enabled = true;

  if (false) {
    Serial.print("BL Set: ");
    Serial.print(level);
    Serial.print(" (");
    Serial.print(duration);
    Serial.println("ms)");
  }
}

void lcd::BacklightOn(long duration) {
  BacklightSet(duration, 255);
}

void lcd::BacklightOff(long duration) {
  BacklightSet(duration, 0);
}

void lcd::DoLoop(void) {
  if (blThread.shouldRun()) {
    blThread.run();
  }
}

static void lcd::runThread(void) {
  LCD.doBacklightDim();
}

// Private

void lcd::doBacklightDim(void) {
  if (blTargetLevel > blLevel) {
    blLevel += 1;
  } else if(blTargetLevel < blLevel) {
    blLevel -= 1;
  } else {
    blThread.enabled = false;
  }

  if (false) {
    Serial.print("BL: ");
    Serial.println(blLevel);
  }

  analogWrite(LCD_BL, blLevel);
}

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

#ifdef LCD_POS_CACHE
  // Invalidate cache
  if (lastChip != chip) {
    gxPos = 255;
    gyPos = 255;
  }

  if (gxPos != addr) {
#endif
    this->sendCommand(LCD_SET_ADD, addr, chip);
#ifdef LCD_POS_CACHE
    gxPos = addr;
  }

  if (gyPos / 8 != page) {
#endif
    this->sendCommand(LCD_SET_PAGE, page, chip);
#ifdef LCD_POS_CACHE
    gyPos = y;
  }

  lastChip = chip;
#endif

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
  // this->waitReady(chip);

  SR.SetChip(chip);
  SR.SetRWDI(LOW, HIGH);
  SR.SetData(data);
  SR.Flush();

  disable();
  enable();
  gxPos++;
}

uint8_t lcd::readData(uint8_t chip) {
  uint8_t data;

  // this->waitReady(chip);

  SR.SetChip(chip);
  SR.SetRWDI(HIGH, HIGH);
  SR.SetData(0);
  SR.Flush();

  // Fake read to latch the data:
  disable();
  enable();
  gxPos++;

  // Actual read to get the data:
  disable();
  delayMicroseconds(LCD_tDDR);
  SR.LatchData();
  enable();
  gxPos++;

  data = SR.ReadData(false);

  return data;
}

void lcd::waitReady(uint8_t chip) {
  // HACK - Make sure we don't neglect our lööp:
  DoLoop();

  SR.SetChip(chip);
  SR.SetRWDI(HIGH, LOW); // Read Instruction
  SR.SetData(0);
  SR.Flush();

  disable();
  delayMicroseconds(LCD_tDDR);
  SR.LatchData();
  enable();

  uint8_t status = SR.ReadData(false);

  while(status & LCD_BUSY_FLAG) {
//    Serial.print(F("Not ready: "));
//    Serial.println(status, HEX);
    disable();
    delayMicroseconds(LCD_tDDR);
    SR.LatchData();
    enable();
    status = SR.ReadData(false);
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