void strobeHigh(int pin) {
  delay(10);
  digitalWrite(pin, HIGH);
  delay(10);
  digitalWrite(pin, LOW);
  delay(10);
}

void strobeLow(int pin) {
  delay(10);
  digitalWrite(pin, LOW);
  delay(10);
  digitalWrite(pin, HIGH);
  delay(10);
}

// Initialize the LCD Buffer and send setup commands
//
void lcdSetup() {
  // Initialize Pins
  pinMode(LCD_DATA_PIN, OUTPUT);
  pinMode(LCD_CLK_PIN, OUTPUT);
  pinMode(LCD_ENABLE_PIN, OUTPUT);
  pinMode(LCD_CHIP_SELECT_PIN, OUTPUT);
  pinMode(LCD_INSTRUCTION_PIN, OUTPUT);
  pinMode(LCD_RESET_PIN, OUTPUT);
  pinMode(2, OUTPUT);
  
  // Initialize Buffer
  for(int i = 0; i < 128; i++) {
    for(int j = 0; j < 8; j++) {
      LCD_BUFFER[i][j] = 0;
    }
  }

  Serial.println("Buffer initialized.");
}

// Write the buffer contents to the LCD
//
void lcdFlushBuffer() {
  for(int i = 0; i < 128; i++) {
    for(int j = 0; j < 8; j++) {
      lcdWrite(LCD_BUFFER[i][j]);
      return;
    }
  }

  lcdDebugBuffer();
  Serial.println("Buffer flushed.");
}

void lcdDebugBuffer() {
  Serial.println("BUFFER CONTENTS:");
  for(int row = 0; row < 64; row++) {
    int row_byte = row / 8;
    int row_bit = row % 8;

    if(row > 32) return;
     
    for(int col = 0; col < 128; col++) {
      // print row,col
      unsigned char data = LCD_BUFFER[col][row_byte];
      unsigned char bitval = data >> row_bit;

      if(bitval & 1) {
        Serial.print("X");
      } else {
        Serial.print(".");
      }
    }
    Serial.print("\n");
  }
}

// Write a single byte to the LCD, serialized
//
void lcdWrite(unsigned char val) {
  unsigned char tmp = val;

  // Write out 8 bits to shift register:
  for(int i = 0; i < 8; i++) {
    bool level = tmp & 1 ? HIGH : LOW;
    tmp >>= 1;
    
    digitalWrite(LCD_DATA_PIN, level);
    delay(10);

    // Pulse Clock
    strobeHigh(LCD_CLK_PIN);
  }

  // Pulse Enable
  strobeHigh(LCD_ENABLE_PIN);
  strobeLow(LCD_CHIP_SELECT_PIN);
}

void lcdBufferSet(int x, int y, bool value) {
//  if(x < 0 || y < 0) return;
//  if(x >= LCD_SCREEN_WIDTH || y >= LCD_SCREEN_HEIGHT) return;
//  
//    int row_byte = y / 8;
//    int row_bit = y % 8;
//    unsigned char data = LCD_BUFFER[x][row_byte];
//    unsigned char mask = (-value ^ data) & ((unsigned char)1 << row_bit);
//    LCD_BUFFER[x][row_byte] = data ^ mask;
  GLCD.SetDot(x + 1, y + 1, value ? PIXEL_ON : PIXEL_OFF);
}
