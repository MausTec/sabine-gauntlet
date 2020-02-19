#ifndef STANDBY_PAGE_h
#define STANDBY_PAGE_h

#include "Settings.h"

class PStandbyPage : public Pages {
  void Enter() override {
    LCD.BacklightOff(3000);

    Btn.attachAny([]() {
      Pages::GoBack();
    });
  }

  void Exit() override {
    LCD.BacklightSet(1000, Settings.BacklightBrightness);
  }

	void Render() override {
	  Str.PutsCenter(29, F("Standby Mode"), false);
	}
};

#endif