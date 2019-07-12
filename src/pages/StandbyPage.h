#ifndef STANDBY_PAGE_h
#define STANDBY_PAGE_h

class PStandbyPage : public Pages {
  void Enter() {
    LCD.BacklightOff(3000);
  }

  void Exit() {
    LCD.BacklightOn(1000);
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