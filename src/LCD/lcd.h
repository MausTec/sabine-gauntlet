#ifndef LCD_h
#define LCD_h

// Pin Config

#define LCD_EN 4
#define LCD_BL 6

// Timing Info

#define LCD_tDDR   30    /* Data Delay time (E high to valid read data)        */
#define LCD_tAS    150    /* Address setup time (ctrl line changes to E HIGH   */
#define LCD_tDSW   20    /* Data setup time (data lines setup to dropping E)   */
#define LCD_tWH    500    /* E hi level width (minimum E hi pulse width)        */
#define LCD_tWL    500   /* E lo level width (minimum E lo pulse width)        */

// Commands

#define LCD_ON        0x3F // ok
#define LCD_OFF       0x3E // ok
#define LCD_SET_ADD     0x40 
#define LCD_DISP_START    0xC0
#define LCD_SET_PAGE    0xB8

#define LCD_BUSY_BIT    7
#define LCD_BUSY_FLAG   0x80 

#define LCD_RESET_BIT   4
#define LCD_RESET_FLAG    0x10

// Main Class

class lcd {
  public:
    void Setup(void);
    void Clear(uint8_t pattern);
    void SetDot(uint8_t x, uint8_t y, uint8_t color);

  private:
    void sendCommand(uint8_t command, uint8_t args, uint8_t chip);
    void sendData(uint8_t command, uint8_t chip);
    void waitReady(uint8_t chip);
    void enable();
    void disable();
};

extern lcd LCD;
#endif