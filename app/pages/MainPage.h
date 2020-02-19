#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

#include "assets/Phoenix.h"
#include "RTC.h"

class PMainPage : public Pages {
  uint32_t lastRender = millis();

  void Enter() override {
    UI.AddMenuItem(0, F("Props"));
    UI.AddMenuItem(2, F("Calendar"));
    UI.AddMenuItem(1, F("Config"));

    UI.onMenuClick(select);
  }

	void Render() override {
    UI.RenderControls();
    UI.Title();
    UI.RenderMenu(16, 16);
//    LCD.DrawGraphic(8, 16, 32, 32, PHOENIX);
    renderDate();
	}

  void Loop() override {
    if ((millis() - lastRender) > 1000) {
      renderDate();
    }
  }

private:

  static void select(UIMenuItem *c) {
    switch(c->value) {
      case 0:
        Pages::Go(&ThermalPage);
        break;
      case 1:
        Pages::Go(&SettingsPage);
        break;
    }
  }

  void renderDate() {
    lastRender = millis();

    // 08 34 19
    char time[9];
    // 2019 02 31
    char date[11];

    sprintf_P(time, PSTR("%02d:%02d:%02d"), RTC.Hour(), RTC.Minute(), RTC.Second());
    sprintf_P(date, PSTR("%02d/%02d"), RTC.Month(), RTC.Day());

    Str.Puts(2, 2, time, true);
    Str.Puts(78, 2, date, true);
  }
};

#endif