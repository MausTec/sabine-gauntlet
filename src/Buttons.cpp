#include "Buttons.h"

void Buttons::Setup() {
  Back = new OneButton(BTN_1_PIN, BTN_ACTIVE_STATE, false);
	Up = new OneButton(BTN_2_PIN, BTN_ACTIVE_STATE, false);
	Down = new OneButton(BTN_3_PIN, BTN_ACTIVE_STATE, false);
  OK = new OneButton(BTN_4_PIN, BTN_ACTIVE_STATE, false);

  OK->attachLongPressStop([]() {
    Serial.println("OK LONG PRESS");
  });
}

void Buttons::tick() {
    Back->tick();
    Up->tick();
    Down->tick();
    OK->tick();
}

void Buttons::attachAny(callbackFunction callback) {
  Back->attachClick(callback);
  Up->attachClick(callback);
  Down->attachClick(callback);
  OK->attachClick(callback);
}

Buttons Btn = Buttons();