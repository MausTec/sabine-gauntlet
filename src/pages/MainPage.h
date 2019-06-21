#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

class PMainPage : public Pages {
	void Render() {
  	Str.Puts(8*0,  t0 % 64, "No", false);
    Str.Puts(8*2,  t1 % 64, "No", false);
    Str.Puts(8*4,  t2 % 64, "No", false);
    Str.Puts(8*6,  t3 % 64, "No", false);
    Str.Puts(8*8,  t4 % 64, "No", false);
    Str.Puts(8*10, t5 % 64, "No", false);
    Str.Puts(8*12, t6 % 64, "No", false);
    Str.Puts(8*14, t7 % 64, "No", false);
	}

  void Loop() {
    if (Btn.Pressed(1)) {
      Pages::Go(&ThermalPage);
    }

    t0 += 1;
    t1 += 10;
    t2 += 3;
    t3 += 8;
    t4 += 16;
    t5 += 4;
    t6 += 9;
    t7 += 20;

    UI.Clear();
    Render();
  }  

  uint8_t t0 = 0;
  uint8_t t1 = 0;
  uint8_t t2 = 0;
  uint8_t t3 = 0;
  uint8_t t4 = 0;
  uint8_t t5 = 0;
  uint8_t t6 = 0;
  uint8_t t7 = 0;
};

#endif