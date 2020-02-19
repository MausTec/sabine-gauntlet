#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

#include "assets/Phoenix.h"
#include "RTC.h"

class PMainPage : public Pages {
  uint32_t lastRender = millis();

  void Enter() override {
    UI.AddMenuItem(0, F("Thermal Detonators"));
    UI.AddMenuItem(1, F("Settings"));

    Btn.OK->attachClick(handleOKClick);
  }

	void Render() override {
    UI.RenderMenu(8);
    // LCD.DrawGraphic(0, 0, 64, 64, PHOENIX);
    renderDate();
	}

  void Loop() override {
    if ((millis() - lastRender) > 1000) {
      renderDate();
    }
  }

private:

  static void handleOKClick() {
    UIMenuItem* c = UI.GetCurrentMenuItem();
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

    const uint8_t dx = 0;
    const uint8_t dy = 3;

    // 08 34 19
    char time[9];
    // 2019 02 31
    char date[11];

    sprintf_P(time, PSTR("%02d:%02d:%02d"), RTC.Hour(), RTC.Minute(), RTC.Second());
    sprintf_P(date, PSTR("%02d/%02d"), RTC.Month(), RTC.Day());

    Str.Puts(0, 0, time, false);
    Str.Puts(80, 0, date, false);
  }
};

#endif