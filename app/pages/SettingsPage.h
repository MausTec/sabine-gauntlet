#ifndef SETTINGS_PAGE_h
#define SETTINGS_PAGE_h

#include "Settings.h"

class PSettingsPage : public Pages {
  void Enter() override {
    UI.AddMenuItem(1, F("Backlight"), setBacklight);
    UI.AddMenuItem(2, F("TX Address"), setTxAddr);
    UI.AddMenuItem(3, F("Date & Time"), setDate);
    UI.AddMenuItem(98, F("Save"), save);
    UI.AddMenuItem(99, F("Exit"), [](UIMenuItem *c) { Pages::GoBack(); });
  }

  void Render() override {
    UI.RenderControls();
    UI.Title(F("Settings"));
    UI.RenderMenu();
  }

private:

  static int step(int value, int step, bool decrement, int min = 0, int max = 255) {
    int newValue = value;
    if (decrement) {
      value <= (min + step) ? newValue = min : newValue -= step;
    } else {
      value >= (max - step) ? newValue = max : newValue += step;
    }
    return newValue;
  }

  static void setBacklight(UIMenuItem *c) {
    UI.NumberInput(F("Backlight"), Settings.BacklightBrightness, [](int value) {
      int newValue = step(value, 31, value < Settings.BacklightBrightness);
      Settings.BacklightBrightness = newValue;
      LCD.BacklightSet(0, newValue);
      return newValue;
    });
  }

  static void setTxAddr(UIMenuItem *c) {
    UI.NumberInput(F("TX Address"), Settings.TXAddress, [](int value) {
      int newValue = step(value, 0, value < Settings.TXAddress);
      Settings.TXAddress = newValue;
      return newValue;
    });
  }

  static void setDate(UIMenuItem *c) {
    UI.Modal(F("Set Date"));
  }

  static void save(UIMenuItem *c) {
    UI.Modal(F("Saving"));
    Settings.Save();
    UI.Flash(F("Saved."));
  }
};

#endif