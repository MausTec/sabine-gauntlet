#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

class PMainPage : public Pages {
	void Render() {
    bool animate = true;

    if (!animate) {
      // Full Diag
    	LCD.DrawLine(0, 0, 128, 64, PIXEL_ON);
      LCD.DrawLine(128, 0, 0, 64, PIXEL_ON);

      // Cross
      LCD.DrawLine(64, 0, 64, 64, PIXEL_ON);
      LCD.DrawLine(0, 32, 128, 32, PIXEL_ON);

      // 1:1 Diag
      LCD.DrawLine(32, 0, 96, 64, PIXEL_ON);
      LCD.DrawLine(96, 0, 32, 64, PIXEL_ON);

      // Narrow Diag
      LCD.DrawLine(54, 0, 74, 64, PIXEL_ON);
      LCD.DrawLine(74, 0, 54, 64, PIXEL_ON);

      // Narrow Horiz Diag
      LCD.DrawLine(0, 22, 128, 42, PIXEL_ON);
      LCD.DrawLine(128, 22, 0, 42, PIXEL_ON);
    } else {
      LCD.DrawLine(x1, y1, x2, y2, PIXEL_ON);
    }
	}

  void Loop() {
    if (Btn.Pressed(1)) {
      Pages::Go(&ThermalPage);
      return;
    }

    if (x2 > 0) {
      x1 += 4;
      x2 -= 4;
      y1 = 0;
      y2 = 64;
    } else if (y2 > 0) {
      x1 = 128;
      x2 = 0;
      y1 += 2;
      y2 -= 2;
    }

    // y1 += 1;
    // t2 -= 2;
    // t3 -= 1;

    UI.Clear();
    Render();
  }  

  uint8_t x1 = 0;
  uint8_t y1 = 0;
  uint8_t x2 = 128;
  uint8_t y2 = 64;
};

#endif