#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

class PMainPage : public Pages {
	void Render() {
    LCD.FillRect(10, 10, 108, 44, PIXEL_ON);
    LCD.FillRect(15, 15, 103, 17, PIXEL_OFF);

    for (int i = 5; i <= 30; i += 5) {
      LCD.DrawLine(0, i, 5, i, PIXEL_ON);
      LCD.DrawLine(0, 63-i, 5, 63-i, PIXEL_ON);
    }

    if(false) {
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
    }
	}

  void Loop() {
    if (Btn.Pressed(1)) {
      Pages::Go(&ThermalPage);
      return;
    }
  }  
};

#endif