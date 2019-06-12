#ifndef BUTTONS_h
#define BUTTONS_h

#define BTN_1_PIN A2
#define BTN_2_PIN A3
// #define BTN_3_PIN A4
// #define BTN_4_PIN A5

#define DEBOUNCE_DELAY 50 //ms

#include "Arduino.h"

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