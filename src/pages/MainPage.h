#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

#include "../RTC/RTC.h"

class PMainPage : public Pages {
  uint32_t lastRender = millis();

  void RenderDate() {
    lastRender = millis();

    const uint8_t dx = 0;
    const uint8_t dy = 3;

    // 08 34 19
    char time[9];
    // 2019 02 31
    char date[11];

    sprintf(time, "%02d %02d %02d", RTC.Hour(), RTC.Minute(), RTC.Second());
    sprintf(date, "%04d %02d %02d", RTC.Year(), RTC.Month(), RTC.Day());

    Str.PutsCenter(24, time, false);
    Str.PutsCenter(32, date, false);

    // Hour Colon
    LCD.SetDot((64 - 13), 25, PIXEL_ON);
    LCD.SetDot((64 - 13), 27, PIXEL_ON);

    // Seconds Colon
    LCD.SetDot((64 + 11), 25, PIXEL_ON);
    LCD.SetDot((64 + 11), 27, PIXEL_ON);

    // Year Hyphen
    LCD.DrawLine((64 - 6), 34, (64 - 4), 34, PIXEL_ON);
    LCD.DrawLine((64 + 18), 34, (64 + 20), 34, PIXEL_ON);
  }

	void Render() {
    UI.Title("Hello Sabine");

    RenderDate();

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

    if ((millis() - lastRender) > 1000) {
      RenderDate();
    }

    // UI.Clear();
    // Serial.print(RTC.Year());
    // Serial.print("-");
    // Serial.print(RTC.Month());
    // Serial.print("-");
    // Serial.print(RTC.Day());
    // Serial.print("T");
    // Serial.print(RTC.Hour());
    // Serial.print("-");
    // Serial.print(RTC.Minute());
    // Serial.print("-");
    // Serial.println(RTC.Second());
  }  
};

#endif