#ifndef SETTINGS_PAGE_h
#define SETTINGS_PAGE_h

#include "Settings.h"

class PSettingsPage : public Pages {
  void Enter() override {
    UI.AddMenuItem(1, F("Backlight"));
    UI.AddMenuItem(2, F("TX Address"));
    UI.AddMenuItem(3, F("Date & Time"));
    UI.AddMenuItem(98, F("Save"), save);
    UI.AddMenuItem(99, F("Exit"));

    UI.onMenuClick(select);
  }

  void Render() override {
    UI.RenderControls();
    UI.Title(F("Settings"));
    UI.RenderMenu();
  }

private:

  static void save(UIMenuItem *c) {
    UI.Modal(F("Saving"));
    Settings.Save();
    UI.Flash(F("Saved."));
  }

  static void select(UIMenuItem *c) {
    switch(c->value) {
      case 1:
        if (Settings.BacklightBrightness < (255 - 51))
          Settings.BacklightBrightness += 51;
        else
          Settings.BacklightBrightness = 255;
        LCD.BacklightSet(0, Settings.BacklightBrightness);
        break;

      case 2:
        if (Settings.BacklightBrightness > 51)
          Settings.BacklightBrightness -= 51;
        else
          Settings.BacklightBrightness = 0;
        LCD.BacklightSet(0, Settings.BacklightBrightness);
        break;

      case 99:
        Pages::GoBack();
        break;
    }
  }
};

#endif