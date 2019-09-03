#include "Arduino.h"
#include "Aurebesh.h"

/**
 * output a character string
 *
 * @param str pointer to a null terminated character string.
 *
 * Outputs all the characters in the string to the text area. 
 *
 * @b Examples:
 * @code
 * Aurebesh.Puts(0, 0, "Hello World");
 * @endcode
 */
void Aurebesh::Puts(int x, int y, const char *str, bool invert) {
  uint8_t i = 0;
  
  while(*str) {
    this->PutChar(x + (i++ * AUREBESH_CHR_SPACE), y, (uint8_t)*str, invert);
    str++;
  }
}

void Aurebesh::Puts(int x, int y, const char *str) {
  Puts(x, y, str, false);
}

void Aurebesh::Puts(int y, const char *str) {
  Puts(0, y, str, false);
}

void Aurebesh::Puts(int x, int y, int str, bool invert) {
  Puts(x, y, String(str), invert);
}

void Aurebesh::Puts(int x, int y, int str) {
  Puts(x, y, str, false);
}

void Aurebesh::Puts(int y, int str) {
  Puts(0, y, String(str));
}

void Aurebesh::PutsCenter(int y, const char *str, bool invert) {
  size_t str_w = strw(str);
  uint8_t x = 0;

  if (str_w * AUREBESH_CHR_SPACE <= DISPLAY_WIDTH)
    x = (DISPLAY_WIDTH - (str_w * AUREBESH_CHR_SPACE)) / 2;

  Puts(x, y, str, invert);
}

void Aurebesh::PutsCenter(int y, const __FlashStringHelper *str, bool invert) {
  size_t str_w = strw(str);
  uint8_t x = 0;

  if (str_w * AUREBESH_CHR_SPACE <= DISPLAY_WIDTH)
    x = (DISPLAY_WIDTH - (str_w * AUREBESH_CHR_SPACE)) / 2;

  Puts_P(x, y, (PGM_P)str, invert);
}


/**
 * output a String class string
 *
 * @param str String class string
 */
void Aurebesh::Puts(int x, int y, const String &str, bool invert) {
  for(unsigned int i = 0; i < str.length(); i++) {
    this->PutChar(x + (i * AUREBESH_CHR_SPACE), y, str[i], invert);
  }
}

void Aurebesh::Puts(int x, int y, const String &str) {
  Puts(x, y, str, false);
}

/**
 * output an Arduino Flash program memory character string
 *
 * @param str pointer to a null terminated character string stored in program memory declared using F() macro
 *
 * Outputs all the characters in the string to the text area. 
 *
 * @b Examples:
 * @code
 * Aurebesh.Puts(F("Hello World"));
 * @endcode
 */
void Aurebesh::Puts(int x, int y, const __FlashStringHelper *str, bool invert) {
  Puts_P(x, y, (PGM_P)str, invert);
}

void Aurebesh::Puts(int x, int y, const __FlashStringHelper *str) {
  Puts(x, y, str, false);
}

/**
 * output a program memory character string
 *
 * @param str pointer to a null terminated character string stored in program memory
 *
 * @b Examples:
 * @code
 * Aurebesh.Puts_P(PSTR("Hello World"));
 * @endcode
 */

void Aurebesh::Puts_P(int x, int y, PGM_P str, bool invert) {
  uint8_t c;
  uint8_t i = 0;
  
  while((c = pgm_read_byte(str)) != 0) {
    this->PutChar(x + (i++ * AUREBESH_CHR_SPACE), y, c, invert);
    str++;
  }
}

void Aurebesh::Puts_P(int x, int y, PGM_P str) {
  Puts_P(x, y, str, false);
}

/**
 * 
 */
void Aurebesh::PutChar(int x, int y, unsigned char chr, bool invert) {
  // Chars are 7x5. It is up to you to provide proper spacing.
  unsigned char idx = asciiToAruebesh(chr);
  uint8_t charData[AUREBESH_CHR_HEIGHT];

  uint8_t pageStart = y/8;
  uint8_t pageOffset = y%8;
  uint8_t pageEnd = pageStart + ((AUREBESH_CHR_HEIGHT + pageOffset) / 8);
  uint8_t mask, data, xPos, tmp;

  if (false) {
    Serial.print("Y: ");
    Serial.print(y);
    Serial.print(" PS: ");
    Serial.print(pageStart);
    Serial.print(" PO: ");
    Serial.print(pageOffset);
    Serial.print(" PE: ");
    Serial.println(pageEnd);
  }

  // Load char into mem
  for(int i = 0; i < AUREBESH_CHR_HEIGHT; i++) {
    charData[i] = pgm_read_byte(&(AUREBESH_FONT[idx][i]));
  }

  for(int page = pageStart; page <= pageEnd; page++) {
    mask = 255 << 8 - AUREBESH_CHR_HEIGHT;

    if (page == pageStart) {
      mask >>= pageOffset;
    } else {
      mask <<= 8 - pageOffset;
    }

    for(int col = 0; col <= AUREBESH_CHR_WIDTH; col++) {
      xPos = x + col;
      data = 0;

      for(int row = AUREBESH_CHR_HEIGHT - 1; row >= 0; row--) {
        data >>= 1;
        tmp = charData[row];
        tmp <<= col;
        data |= tmp & B10000000;
      }

      if (page == pageStart) {
        data >>= pageOffset;
      } else {
        data <<= 8 - pageOffset;
      }

      if (false) {
        Serial.print("P: ");
        Serial.print(page);
        Serial.print(" D: ");
        Serial.print(data, BIN);
        Serial.print(" M: ");
        Serial.print(mask, BIN);
      }

      if (invert) {
        data = (~data) & mask;
      }

      // TODO - Why the heck is this all coming out upside down?
      LCD.MaskByte(xPos - 1, page, SR.reverseBits(mask), SR.reverseBits(data));
    }
  }
}

void Aurebesh::PutChar(int x, int y, unsigned char chr) {
  PutChar(x, y, chr, false);
}

// Private Things

unsigned char Aurebesh::asciiToAruebesh(unsigned char ascii) {
  unsigned char idx = ascii;

  if(idx <= 32) {
    // Non printing through space:
    return 0;
  } else if(idx <= 47) {
    // Symbols 1
    return idx - 32;
  } else if(idx <= 57) {
    // Numbers
    return idx - 32;
  } else if(idx <= 64) {
    // Symbols 2
    return idx - 32;
  } else if(idx <= 90) {
    // Upper case
    return idx - 32;
  } else if(idx <= 96) {
    // Symbols 3
    return idx - 32;
  } else if(idx <= 122) {
    // Lower case
    return idx - 64;
  } else if(idx <= 126) {
    // Symbols 4
    return idx - 64;
  } else {
    return 0;
  }
}

size_t Aurebesh::strw(const __FlashStringHelper *str) {
  size_t str_w = 0;
  PGM_P p = (PGM_P)str;
  
  // Read to null terminator:
  while(pgm_read_byte(p) != NULL) {
    str_w++;
    p++;
  }

  return str_w;
}

size_t Aurebesh::strw(const char *str) {
  size_t str_w = 0;
  const char *n = str;

  // Read to null terminator:
  while(*n) {
    str_w++;
    n++;
  }

  return str_w;
}

Aurebesh Str = Aurebesh();
