//// Drawing Commands
//
//void lcdBufferSet(int x, int y, bool value) {
//  GLCD.SetDot(x + 1, y + 1, value ? PIXEL_ON : PIXEL_OFF);
//}
//
//void lcdDrawPoint(int x, int y, bool invert) {
//  lcdBufferSet(x - 1, y - 1, !invert);
//}
//void lcdDrawPoint(int x, int y) {
//  lcdDrawPoint(x, y, false);
//}
//
//void lcdDrawRect(int x, int y, int width, int height, bool invert) {
//  for(int row = y; row < (y + height); row++) {
//    for(int col = x; col < (x + width); col++) {
//      lcdBufferSet(col - 1, row - 1, !invert);
//    }
//  }
//}
//void lcdDrawRect(int x, int y, int width, int height) {
//  lcdDrawRect(x, y, width, height, false);
//}
//
//
//void lcdDrawChar(int x, int y, unsigned char chr, bool invert) {
//  // Chars are 7x5. It is up to you to provide proper spacing.
//  unsigned char idx = asciiToAruebesh(chr);
//  const unsigned char *data = AUREBESH_FONT[idx];
//  
//  for(int row = 0; row < 5; row++) {
//    unsigned char row_data = data[row];
//
//    // Count backwards from 6..0
//    for(int col = 6; col >= 0; col--) {
//      bool pixel = !(row_data & 1);
//      lcdDrawPoint(x + col, y + row, pixel ^ invert);
//      row_data = row_data >> 1;
//    }
//  }
//}
//void lcdDrawChar(int x, int y, unsigned char idx) {
//  lcdDrawChar(x, y, idx, false);
//}
//
//void lcdDrawString(int x, int y, const char *idx, size_t len, bool invert) {
//  for(int pos = 0; pos < len; pos++) {
//    // pos * 8 = Character width + 1px gap
//    lcdDrawChar(x + (pos * 8), y, idx[pos], invert);
//  }
//}
//void lcdDrawString(int x, int y, const char *idx, size_t len) {
//  lcdDrawString(x, y, idx, len, false);
//}
//void lcdDrawStringI(int x, int y, const char *idx, size_t len) {
//  lcdDrawString(x, y, idx, len, true);
//}
//void lcdDrawStringCenter(int y, const char *idx, size_t len, bool invert) {
//  int x = (LCD_SCREEN_WIDTH - (len * 8)) / 2;
//  lcdDrawString(x, y, idx, len, invert);
//}
//void lcdDrawStringCenter(int y, const char *idx, size_t len) {
//  lcdDrawStringCenter(y, idx, len, false);
//}
