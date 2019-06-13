#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

class PMainPage : public Pages {
	void Render() {
  	UI.Title("Sabine Gauntlet");
    UI.Puts("This is a test");
    UI.Puts("Of the Sabine");
    UI.Puts("gauntlet.");
    UI.Puts("I'll add a UI method");
    UI.Puts("To handle long strings.");
	}

  void Loop() {
    if (Btn.Pressed(1)) {
      Pages::Go(&ThermalPage);
    }
  }
};

#endif