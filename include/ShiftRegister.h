#ifndef ShiftRegister_h
#define ShiftRegister_h

#include "Arduino.h"
#include "../config.h"

#define SR_TGAP 0
#define SR_TSTR 0

// For LCD Control:
#define SR_LCD_CS1 0
#define SR_LCD_CS2 1
#define SR_LCD_RW  2
#define SR_LCD_DI  3
#define SR_LCD_CS  B00000011

// Shift Register contains all the parallel input and some
// control channels for the LCD in a 16 bit array:
/*
   | 7 | 6 | 5 | 4 |  3  |  2  |  1  |  0  |7 6 5 4 3 2 1 0|
   |---+---+---+---+-----+-----+-----+-----+-+-+-+-+-+-+-+-|
   |   |   |   |   | D/I | R/W | CS2 | CS1 |      DATA     |
 */

class ShiftRegister {
  public:
    void Setup();
    void Write(uint8_t sr0_data, uint8_t sr1_data);
    void Write(uint16_t data);
    static void LatchData();
    uint8_t ReadData();
    uint8_t ReadData(bool latch);
    void SetRWDI(bool rw, bool di);
    void SetChip(uint8_t chip);
    void SetData(uint8_t data);
    void Flush();
    
    static uint8_t reverseBits(uint8_t data);

  private:
    static void StrobeHigh(int pin);
    //void StrobeLow(int pin);
    static uint16_t reverseBits(uint16_t data);

    uint8_t dataBuf = 0;
    uint8_t controlBuf = 0;
    bool configured = false;
};

extern ShiftRegister SR;
#endif
