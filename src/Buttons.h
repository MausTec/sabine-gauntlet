#ifndef BUTTONS_h
#define BUTTONS_h

#include "Arduino.h"
#include "../config.h"

#define BTN_OK 1
#define BTN_UP 3
#define BTN_DOWN 2
#define BTN_BACK 4

#define BTN_ACTIVE_STATE HIGH

#define DEBOUNCE_DELAY 50 //ms

class Buttons {
	public:
		void Setup();
		bool Pressed(uint8_t btn);
    uint8_t Pressed();
		unsigned long LastPress();

	private:
		unsigned long lastPress = 0;
		unsigned long lastDebounceTime[4] = { 0, 0, 0, 0 };
		uint8_t lastState[4] = { LOW, LOW, LOW, LOW }; 
		uint8_t currentState[4] = { LOW, LOW, LOW, LOW };

		uint8_t getButtonPin(uint8_t btn);
};

extern Buttons Btn;
#endif