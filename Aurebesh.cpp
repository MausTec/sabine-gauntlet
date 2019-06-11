#include "Arduino.h"
#include "Aurebesh.h"
#include <openGlcd.h>

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

void Aurebesh::PutsCenter(int y, const char *str, bool invert) {
  const char *n;
  size_t str_w = 0;

  n = str;
  while(*n) {
    str_w++;
    n++;
  }
  
  uint8_t x = (GLCD.Width - (str_w * AUREBESH_CHR_SPACE)) / 2;

  Puts(x, y, str, invert);
}


/**
 * output a String class string
 *
 * @param str String class string
 */
void Aurebesh::Puts(int x, int y, const String &str, bool invert) {
  for(unsigned int i = 0; i < str.length(); i++) {
    this->PutChar(x + (i++ * AUREBESH_CHR_SPACE), y, str[i], invert);
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
  const unsigned char *data = AUREBESH_FONT[idx];
  
  for(int row = 0; row < AUREBESH_CHR_HEIGHT; row++) {
    unsigned char row_data = data[row];

    // Count backwards from 6..0
    for(int col = AUREBESH_CHR_WIDTH - 1; col >= 0; col--) {
      bool value = (row_data & 1) ^ invert;
      GLCD.SetDot(x + col, y + row, value ? PIXEL_ON : PIXEL_OFF);
      row_data = row_data >> 1;
    }
  }
}

// Private Things

unsigned char Aurebesh::asciiToAruebesh(unsigned char ascii) {
  unsigned char idx = ascii;

  // Check if non-printing and return 0:
  if(idx <= 32) return 0;
  
  // First subtract 32, putting SPACE at 0
  idx -= 32;

  // Check if we're in the extended char set (< 0):
  if(idx <= 15) return 0; // TOFU

  // Shift again to offset punctuation 1
  idx -= 15;

  // Return numbers:
  if(idx <= 10) return idx;

  // Return TOFU take 2, the semicolon boogaloo
  if(idx <= 17) return 0; // This ends at @ btw

  // Shift off punctuation 2
  idx -= 7;

  // A quick recap, A should now be 11 and we're (32+15+7 = 54) off from ASCII
  // at this point we only care about alphanumerics, so let's return those.
  if(idx <= 36) return idx;
  if(idx >= 43 && idx <= 68) return idx - 32; // Lower case conversion

  // Return the universal tofu:
  return 0;
}
