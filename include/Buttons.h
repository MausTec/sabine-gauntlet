#ifndef BUTTONS_h
#define BUTTONS_h

#include "Arduino.h"
#include "../config.h"
#include "OneButton.h"

#define BTN_ACTIVE_STATE LOW

class Buttons {
	public:
		void Setup();
		void tick();

        OneButton *Back;
        OneButton *Up;
        OneButton *Down;
        OneButton *OK;

  void attachAny(callbackFunction callback);
};

extern Buttons Btn;
#endif