#ifndef STANDBY_PAGE_h
#define STANDBY_PAGE_h

class PStandbyPage : public Pages {
  void Enter() {
    // LCD.OffBacklight();
  }

  void Exit() {
    // LCD.OnBacklight();
  }

	void Render() {
	  Str.PutsCenter(29, F("Standby Mode"), false);
	}

	void Loop() {
		delay(100);

		if (Btn.Pressed() != 0) {
			Pages::GoBack();
		}
	}
};

#endif