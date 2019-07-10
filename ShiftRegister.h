#ifndef ShiftRegister_h
#define ShiftRegister_h

// Wire 3 for SR and LCD Enable

#define SR_RW 5
#define SR_RW2 9
#define SR_DS 2
#define SR_DC 3
#define SR_DR 8
#define SR_TGAP 0
#define SR_TSTR 0
#define SR_E 10

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
    void LatchData(void);
    uint8_t ReadData(void);
    uint8_t ReadData(bool latch);
    // WriteCommand(uint8_t cmd, uint8_t chip);
    // WriteByte(uint8_t);
    void SetRWDI(bool rw, bool di);
    void SetChip(uint8_t chip);
    void SetData(uint8_t data);
    // WaitReady(uint8_t chip);
    // SerialIn();
    // SerialOut();
    void Flush();
    // Read();
    
    uint8_t reverseBits(uint8_t data);

  private:
    void StrobeHigh(int pin);
    //void StrobeLow(int pin);
    uint16_t reverseBits(uint16_t data);

    uint8_t dataBuf;
    uint8_t controlBuf;
    bool configured = false;
};

extern ShiftRegister SR;
#endif
