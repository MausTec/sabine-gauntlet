#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

#include "../assets/Phoenix.h"
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

    sprintf_P(time, PSTR("%02d:%02d"), RTC.Hour(), RTC.Minute());
    sprintf_P(date, PSTR("%02d/%02d"), RTC.Month(), RTC.Day());

    Str.PutsCenter(24, time, false);
    Str.PutsCenter(32, date, false);

    // Hour Colon
    LCD.SetDot((64 - 13), 25, PIXEL_ON);
    LCD.SetDot((64 - 13), 27, PIXEL_ON);

    // Year Hyphen
    LCD.DrawLine((64 - 6), 34, (64 - 4), 34, PIXEL_ON);
  }

	void Render() {
    LCD.DrawGraphic(0, 0, 64, 64, PHOENIX);
    // RenderDate();
	}

  void Loop() {
    if (Btn.Pressed(1)) {
      Pages::Go(&ThermalPage);
      return;
    }

    if ((millis() - lastRender) > 1000) {
      // RenderDate();
    }
  }  
};

#endif