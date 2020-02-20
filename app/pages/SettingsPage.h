#ifndef SETTINGS_PAGE_h
#define SETTINGS_PAGE_h

#include "Settings.h"
#include "RTC.h"

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
    UI.NumberInput(F("Backlight"), Settings.BacklightBrightness, [](int value, int lastValue) {
      int newValue = step(value, 31, value < lastValue);
      Settings.BacklightBrightness = newValue;
      LCD.BacklightSet(0, newValue);
      return newValue;
    });
  }

  static void setTxAddr(UIMenuItem *c) {
    UI.NumberInput(F("TX Address"), Settings.TXAddress, [](int value, int lastValue) {
      int newValue = step(value, 0, value < lastValue);
      Settings.TXAddress = newValue;
      return newValue;
    });
  }

  static void setDate(UIMenuItem *c) {
    UI.AddNumberInput(F("Year"), RTC.Year(), [](int value, int lastValue) {
      int newValue = step(value, 0, value < lastValue, 1990, 3000);
      RTC.SetYear(newValue);
      return newValue;
    });

    UI.AddNumberInput(F("Month"), RTC.Month(), [](int value, int lastValue) {
      int newValue = step(value, 0, value < lastValue, 1, 12);
      RTC.SetMonth(newValue);
      return newValue;
    });

    UI.AddNumberInput(F("Day"), RTC.Day(), [](int value, int lastValue) {
      int newValue = step(value, 0, value < lastValue, 1, 31);
      RTC.SetDay(newValue);
      return newValue;
    });

    UI.AddNumberInput(F("Hour"), RTC.Hour(), [](int value, int lastValue) {
      int newValue = step(value, 0, value < lastValue, 0, 23);
      RTC.SetHour(newValue);
      return newValue;
    });

    UI.AddNumberInput(F("Minute"), RTC.Minute(), [](int value, int lastValue) {
      int newValue = step(value, 0, value < lastValue, 0, 59);
      RTC.SetMinute(newValue);
      return newValue;
    });

    UI.RenderNumberInput();
  }

  static void save(UIMenuItem *c) {
    UI.Modal(F("Saving"));
    Settings.Save();
    UI.Flash(F("Saved."));
  }
};

#endif