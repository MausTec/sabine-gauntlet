#include "Buttons.h"

void Buttons::Setup() {
	pinMode(BTN_1_PIN, INPUT);
#ifdef BTN_2_PIN
	pinMode(BTN_2_PIN, INPUT);
#endif
#ifdef BTN_3_PIN
	pinMode(BTN_3_PIN, INPUT);
#endif
#ifdef BTN_4_PIN
	pinMode(BTN_4_PIN, INPUT);
#endif

	lastPress = millis();
}

// Returns true on the first frame where +btn+ is high.
//
bool Buttons::Pressed(uint8_t btn) {
  uint8_t btnPin = getButtonPin(btn);
  if (btnPin == 255) return false;

	uint8_t pressed = digitalReadFast(btnPin);
	bool lastReading = lastState[btn - 1];

  // Update last pressed here, too.
  if(pressed == BTN_ACTIVE_STATE) lastPress = millis();

	// Button input changed, update last debounce time
	if (pressed != lastReading) {
		lastDebounceTime[btn - 1] = millis();
	}	

	// Reading has been set for longer than one debounce period
	if ((millis() - lastDebounceTime[btn - 1]) > DEBOUNCE_DELAY) {
		// Valid transition, store.
		if (pressed != currentState[btn - 1]) {
      if (true) {
  			Serial.print("Btn ");
  			Serial.print(btn);
  			Serial.print(" value ");
  			Serial.println(pressed);
      }

			currentState[btn - 1] = pressed;
			return pressed == BTN_ACTIVE_STATE;
		}
	}

	lastState[btn - 1] = pressed;
	return false;
}

uint8_t Buttons::Pressed() {
  if(Pressed(1)) return 1;
  if(Pressed(2)) return 2;
  if(Pressed(3)) return 3;
  if(Pressed(4)) return 4;
  return 0;
}

unsigned long Buttons::LastPress() {
  // Update lastPress here in case we weren't polling for
  // presses already.
	if(digitalReadFast(BTN_1_PIN) == BTN_ACTIVE_STATE
#ifdef BTN_2_PIN
		|| digitalReadFast(BTN_2_PIN) == BTN_ACTIVE_STATE
#endif
#ifdef BTN_3_PIN
		|| digitalReadFast(BTN_3_PIN) == BTN_ACTIVE_STATE
#endif
#ifdef BTN_3_PIN
		|| digitalReadFast(BTN_4_PIN) == BTN_ACTIVE_STATE
#endif
	) {
    lastPress = millis();
	}

  return millis() - lastPress;
}

uint8_t Buttons::getButtonPin(uint8_t btn) {
	switch(btn) {
		case 1:
			return BTN_1_PIN;
			break;

#ifdef BTN_2_PIN
		case 2:
			return BTN_2_PIN;
			break;
#endif

#ifdef BTN_3_PIN
		case 3:
			return BTN_3_PIN;
			break;
#endif

#ifdef BTN_4_PIN
		case 4:
			return BTN_4_PIN;
			break;
#endif
	}

	return 255;
}

Buttons Btn = Buttons();