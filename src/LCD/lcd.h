#ifndef LCD_h
#define LCD_h

// Dimensions

#define DISPLAY_WIDTH  128
#define DISPLAY_HEIGHT 64
#define DISPLAY_CHIP_WIDTH 64

// Color Constants

#define PIXEL_ON  255
#define PIXEL_OFF 0

// Pin Config

#define LCD_EN 4
#define LCD_BL 6

// Timing Info

#define LCD_tDDR   1    /* Data Delay time (E high to valid read data)        */
#define LCD_tAS    1    /* Address setup time (ctrl line changes to E HIGH   */
#define LCD_tDSW   1    /* Data setup time (data lines setup to dropping E)   */
#define LCD_tWH    1    /* E hi level width (minimum E hi pulse width)        */
#define LCD_tWL    1   /* E lo level width (minimum E lo pulse width)        */

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

// Configuration

#define LCD_READ_CACHE  // Use to bypass reading the chip.

// Main Class

class lcd {
  public:
    void Setup(void);
    void Clear(uint8_t pattern);
    void SetDot(uint8_t x, uint8_t y, uint8_t color);
    void SetByte(uint8_t x, uint8_t page, uint8_t color);

    // Higher Level Drawing
    void DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
    void FillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);
    void DrawLine(uint8_t x, uint8_t y, uint8_t xend, uint8_t yend, uint8_t color);

  private:
    void sendCommand(uint8_t command, uint8_t args, uint8_t chip);
    void sendData(uint8_t command, uint8_t chip);
    uint8_t readData(uint8_t chip);
    uint8_t goTo(uint8_t x, uint8_t y);
    void waitReady(uint8_t chip);
    void enable();
    void disable();

    // Drawing Helpers
    

#ifdef LCD_READ_CACHE
    uint8_t readCache[DISPLAY_WIDTH][DISPLAY_HEIGHT / 8];
#endif

};

extern lcd LCD;
#endif