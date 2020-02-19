#ifndef Aurebesh_h
#define Aurebesh_h

#define AUREBESH_CHR_WIDTH 7
#define AUREBESH_CHR_HEIGHT 5
#define AUREBESH_CHR_SPACE (AUREBESH_CHR_WIDTH + 1)

#include "Arduino.h"

#include "LCD/lcd.h"

class Aurebesh {
  public:
    void Puts(int x, int y, const char *str);
    void Puts(int x, int y, const char *str, bool invert);
    void Puts(int y, const char *str);
    void PutsCenter(int y, const char *str, bool invert);
    
    void Puts(int x, int y, const String &str);
    void Puts(int x, int y, const String &str, bool invert);
    void Puts(int x, int y, int str, bool invert);
    void Puts(int x, int y, int str);
    void Puts(int y, int str);
    
    void Puts(int x, int y, const __FlashStringHelper *str);
    void Puts(int x, int y, const __FlashStringHelper *str, bool invert);
    void PutsCenter(int y, const __FlashStringHelper *str, bool invert);
    
    void Puts_P(int x, int y, PGM_P str);
    void Puts_P(int x, int y, PGM_P str, bool invert);
    
    void PutChar(int x, int y, unsigned char c);
    void PutChar(int x, int y, unsigned char c, bool invert);
  
  private:
    unsigned char asciiToAruebesh(unsigned char ascii);
    size_t strw(const __FlashStringHelper *str);
    size_t strw(const char *str);
};

const unsigned char AUREBESH_FONT[][5] PROGMEM = {
  { B00000000, B00000000, B00000000, B00000000, B00000000 }, // 0

  // 0x21 "!"
  { B00011000, B00011000, B00011000, B00000000, B00011000 }, // !
  { B01100110, 
    B01100110, 
    B00100010, 
    B00000000, 
    B00000000 }, // "
  { B00110110, 
    B01111111, 
    B00110110, 
    B01111111, 
    B00110110 }, // #
  { B00101000, 
    B01111111, 
    B00101011, 
    B00000110, 
    B00001100 }, // $
  { B01100011, 
    B01001110, 
    B00011100, 
    B00111001, 
    B01100011 }, // %
  { B00111100, 
    B01100110, 
    B00111101, 
    B01100110, 
    B00111111 }, // &
  { B00011000, 
    B00011000, 
    B00001000, 
    B00000000, 
    B00000000 }, // '
  { B00001100, 
    B00011000, 
    B00110000, 
    B00011000, 
    B00001100 }, // (
  { B00110000, 
    B00011000, 
    B00001100, 
    B00011000, 
    B00110000 }, // )
  { B00101010, 
    B00011100, 
    B00011100, 
    B00101010, 
    B00000000 }, // *
  { B00001000, 
    B00001000, 
    B00111110, 
    B00001000, 
    B00001000 }, // +
  { B00000000, 
    B00000000, 
    B00011000, 
    B00011000, 
    B00110000 }, // ,
  { B00000000, 
    B00000000, 
    B00111100, 
    B00000000, 
    B00000000 }, // -
  { B00000000, 
    B00000000, 
    B00111100, 
    B00100100, 
    B00111100 }, // .
  { B00000110, 
    B00001100, 
    B00011000, 
    B00110000, 
    B01100000 }, // /

  // 0x30 - "0"
  { B01111111, B01100011, B01101011, B01100011, B01111111 }, // 0
  { B01111100, B00001100, B00001100, B00001100, B01111111 }, // 1
  { B01111111, B00000000, B01111111, B01100000, B01111111 }, // 2
  { B01111111, B00000011, B01110011, B00000011, B01111111 }, // 3
  { B00011011, B00110000, B01111111, B00000011, B00000011 }, // 4
  { B01111111, B00000000, B01111111, B00000011, B01111111 }, // 5
  { B01111111, B00000000, B01111111, B01100011, B01111111 }, // 6
  { B01111111, B00000011, B00000011, B00000011, B00000011 }, // 7
  { B01111111, B01100011, B00111111, B01100011, B01111111 }, // 8
  { B01111111, B01100011, B01111111, B00000000, B01111111 }, // 9

  // 0x3A - ":"
  { B00111100, 
    B00011000, 
    B00000000, 
    B00011000, 
    B00111100 }, // :
  { B00011000, 
    B00000000, 
    B00011000, 
    B00011000, 
    B00110000 }, // ;
  { B00001100, 
    B00011000, 
    B00110000, 
    B00011000, 
    B00001100 }, // <
  { B01100000, 
    B00111110, 
    B00000000, 
    B00111110, 
    B01100000 }, // =
  { B00110000, 
    B00011000, 
    B00001100, 
    B00011000, 
    B00110000 }, // >
  { B01111110, 
    B00000011, 
    B00011110, 
    B00000000, 
    B00011000 }, // ?
  { B01111110, 
    B01101011, 
    B01101110, 
    B01100000, 
    B01111111 }, // @

  // 0x41 - "A"
  { B00001000, B00011100, B00110110, B01100011, B01111111 }, // A
  { B01111111, B01100001, B01101111, B01100001, B01111111 }, // B
  { B00001111, B00011000, B00110000, B01100000, B01111111 }, // C
  { B01111000, B01001100, B01000110, B01010011, B01011111 }, // D
  { B01111111, B00000000, B00111110, B00000000, B01111111 }, // E
  { B01111111, B00000011, B00111110, B00001100, B00011000 }, // F
  { B01111110, B01100000, B01100110, B01100001, B01111111 }, // G
  { B01100011, B01101011, B01101011, B01101011, B01100011 }, // H
  { B00001110, B00011110, B00110110, B00000110, B00000110 }, // I
  { B00000011, B01100011, B00110011, B00011011, B00001111 }, // J
  { B01100011, B01111110, B00000000, B01111110, B01100011 }, // K
  { B01100000, B01100011, B01100110, B01101100, B01111000 }, // L
  { B01100010, B01110111, B01111101, B01101001, B01100010 }, // M
  { B01100010, B01110001, B01111001, B01101101, B01100110 }, // N
  { B00001000, B00011100, B00110110, B01100011, B01111111 }, // 0
  { B01111111, B01100001, B01101100, B01111000, B01100000 }, // P
  { B00111111, B01100001, B01100001, B01101101, B00111001 }, // Q
  { B00111111, B01110010, B01101100, B01100110, B01100011 }, // R
  { B00111110, B01100001, B01111100, B00000111, B01111110 }, // S
  { B00011100, B00111110, B01101011, B00001000, B00001000 }, // T
  { B01101111, B01101001, B01100010, B01100100, B01111000 }, // U
  { B01000111, B01000110, B00101010, B00101010, B00010010 }, // V
  { B00100011, B01001011, B01011111, B01110111, B00100011 }, // W
  { B01100011, B00110110, B00011000, B01001100, B01100110 }, // X
  { B01100011, B00110110, B00011100, B00001100, B00000110 }, // Y
  { B00111110, B01000111, B00011100, B01110001, B00111110 }, // Z

  // 0x5B - "["
  { B00111100, 
    B00110000, 
    B00110000, 
    B00110000, 
    B00111100 }, // [
  { B00110000, 
    B00011000, 
    B00001100, 
    B00000110, 
    B00000011 }, // "\"
  { B00011110, 
    B00000110, 
    B00000110, 
    B00000110, 
    B00011110 }, // ]
  { B00001000, 
    B00011100, 
    B00110110, 
    B00100010, 
    B00000000 }, // ^
  { B00000000, 
    B00000000, 
    B00000000, 
    B01000001, 
    B01111111 }, // _
  { B00000000, 
    B00100010, 
    B00110110, 
    B00011100, 
    B00001000 }, // `

  // 0x7B - "{"
  { B00000000, 
    B00000000, 
    B00000000, 
    B00000000, 
    B00000000 }, // {
  { B00011000, 
    B00011000, 
    B00011000, 
    B00011000, 
    B00011000 }, // |
  { B00000000, 
    B00000000, 
    B00000000, 
    B00000000, 
    B00000000 }, // }
  { B00000000, 
    B00000000, 
    B00110010, 
    B01001100, 
    B00000000 }, // ~

  { B01111111, B01111111, B01111111, B01111111, B01111111 }  // TOFU
};

extern Aurebesh Str;
#endif
