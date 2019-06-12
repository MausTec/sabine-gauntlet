#ifndef MAIN_PAGE_h
#define MAIN_PAGE_h

class PMainPage : public Pages {
	void Render() {
  	GLCD.FillRect(0, 0, 128, 9);
	  Str.PutsCenter(2, "New Bounty", true);
	  Str.Puts(0, 10, F("Vector Unit 1072"));
	}
};

#endif