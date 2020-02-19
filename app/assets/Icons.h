#ifndef _ICONS_h
#define _ICONS_h

const PROGMEM uint8_t IconUp[] = {
  1   , // frameCount

  // FRAME 0
  0   , // frame
  0   , // startX
  0   , // startY
  8   , // width
  8   , // height

  0b00010000,
  0b00111000,
  0b01111100,
  0b11111110,
  0b00111000,
  0b00111000,
  0b00111000,
  0b00111000
};

const PROGMEM uint8_t IconDown[] = {
  1   , // frameCount

  // FRAME 0
  0   , // frame
  0   , // startX
  0   , // startY
  8   , // width
  8   , // height

  0b00111000,
  0b00111000,
  0b00111000,
  0b00111000,
  0b11111110,
  0b01111100,
  0b00111000,
  0b00010000
};

const PROGMEM uint8_t IconOK[] = {
  1   , // frameCount

  // FRAME 0
  0   , // frame
  0   , // startX
  0   , // startY
  8   , // width
  8   , // height

  0b00000000,
  0b00000001,
  0b00000011,
  0b00000111,
  0b11001110,
  0b01111100,
  0b00111000,
  0b00010000
};

const PROGMEM uint8_t IconBack[] = {
  1   , // frameCount

  // FRAME 0
  0   , // frame
  0   , // startX
  0   , // startY
  8   , // width
  8   , // height

  0b00000000,
  0b00010000,
  0b00110000,
  0b01111110,
  0b11111110,
  0b01111110,
  0b00110000,
  0b00010000
};

#endif