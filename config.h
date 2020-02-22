#ifndef __CONFIG_h
#define __CONFIG_h

//== Pin Configuration

// LCD
#define LCD_EN 9//PB1
#define LCD_BL 6 

// Shift Register
#define SR_RW A2//12//PB4
#define SR_DS 11//PB3
#define SR_DC 13//PB5
#define SR_DR 10//PB2

// Transmitter
#define TX_EN_PIN 8//PB0

// Buttons
#define BTN_1_PIN 7
#define BTN_2_PIN 3
#define BTN_3_PIN 4
#define BTN_4_PIN 5

// Status
// #define STAT_PIN 7

// Bodge Wires
#define SD_CS_PIN A1  // 15
#define VBAT_PIN A3   // 17
#define KB_DAT_PIN A0 // or 14 // or 19?
#define KB_IRQ_PIN PD2


#endif