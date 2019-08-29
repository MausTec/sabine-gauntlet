#ifndef STANDBY_PAGE_h
#define STANDBY_PAGE_h

#include "../Settings.h"

class PStandbyPage : public Pages {
  void Enter() {
    LCD.BacklightOff(3000);
  }

  void Exit() {
    LCD.BacklightSet(1000, Settings.BacklightBrightness);
  }

	void Render() {
	  Str.PutsCenter(29, F("Standby Mode"), false);
	}

	void Loop() {
		if (Btn.Pressed() != 0) {
			Pages::GoBack();
		}
	}
};

#endif