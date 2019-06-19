#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

class PMainPage : public Pages {
	void Render() {
  	UI.Title("No no no");
    UI.Puts("No no  no    no");
    UI.Puts(" no no no no");
    UI.Puts("No no no");
    UI.Puts("     no     ");
    UI.Puts("no        no");
	}

  void Loop() {
    if (Btn.Pressed(1)) {
      Pages::Go(&ThermalPage);
    }
  }
};

#endif