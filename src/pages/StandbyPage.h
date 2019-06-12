#ifndef STANDBY_PAGE_h
#define STANDBY_PAGE_h

#include "../../Buttons.h"

class PStandbyPage : public Pages {
  void Enter() {
    Serial.println("StandbyPage loaded.");
    GLCD.OffBacklight();
  }

  void Exit() {
    Serial.println("StandbyPage exited.");
    GLCD.OnBacklight();
  }

	void Render() {
	  Str.PutsCenter(29, "Standby Mode", false);
	}

	void Loop() {
		delay(100);

		if (Btn.Pressed() != 0) {
			Pages::GoBack();
		}
	}
};

#endif