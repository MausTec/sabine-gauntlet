#ifndef STANDBY_PAGE_h
#define STANDBY_PAGE_h

class PStandbyPage : public Pages {
  void Enter() {
    GLCD.OffBacklight();
  }

  void Exit() {
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