#ifndef ShiftRegister_h
#define ShiftRegister_h

// Wire 3 for SR and LCD Enable

#define SR_RW 5
#define SR_DS 2
#define SR_DC 3
#define SR_DR 8
#define SR_TGAP 0
#define SR_TSTR 0

// For LCD Control:
#define SR_LCD_DI  B0001000
#define SR_LCD_RW  B0000100
#define SR_LCD_CS  B0000011
#define SR_LDC_CS1 B0000010
#define SR_LCD_CS2 B0000001

// Shift Register contains all the parallel input and some
// control channels for the LCD in a 16 bit array:
/*
   | 0 | 1 | 2 | 3 |  4  |  5  |  6  |  7  |0 1 2 3 4 5 6 7|
   |---+---+---+---+-----+-----+-----+-----+-+-+-+-+-+-+-+-|
   |   |   |   |   | D/I | R/W | CS1 | CS2 |      DATA     |
 */

class ShiftRegister {
  public:
    void Setup();
    void Write(uint8_t sr0_data, uint8_t sr1_data);
    void Write(uint16_t data);
    // WriteData(uint8_t);
    // ReadData(void);
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

  private:
    void StrobeHigh(int pin);
    //void StrobeLow(int pin);

    uint8_t dataBuf;
    uint8_t controlBuf;
    bool configured = false;
};

extern ShiftRegister SR;
#endif
