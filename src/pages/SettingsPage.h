#ifndef SETTINGS_PAGE_h
#define SETTINGS_PAGE_h

#include "../Settings.h"

class PSettingsPage : public Pages {
  void Enter() {
    UI.ClearMenu();
    UI.AddMenuItem(1, F("Backlight Up"));
    UI.AddMenuItem(2, F("Backlight Down"));
    UI.AddMenuItem(3, F("Save"));
    UI.AddMenuItem(99, F("Back"));
  }

  void Render() {
    long start = millis();
    UI.Title(F("Settings"));
    UI.RenderMenu();
  }

  void Loop() {
    if (Btn.Pressed(BTN_UP)) {
      UI.SelectPreviousMenuItem();
      return;
    }

    if (Btn.Pressed(BTN_DOWN)) {
      UI.SelectNextMenuItem();
      return;
    }

    if (Btn.Pressed(BTN_OK)) {
      UIMenuItem* c = UI.GetCurrentMenuItem();

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

        case 3:
          Settings.Save();
          break;

        case 99:
          Pages::GoBack();
          break;
      }

      return;
    }

    if (Btn.Pressed(BTN_BACK)) {
      Pages::GoBack();
      return;
    }
  }
};

#endif