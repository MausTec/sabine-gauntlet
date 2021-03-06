#include "Buttons.h"

void Buttons::Setup() {
  Back = OneButton(BTN_4_PIN, BTN_ACTIVE_STATE, false);
	Up = OneButton(BTN_3_PIN, BTN_ACTIVE_STATE, false);
	Down = OneButton(BTN_2_PIN, BTN_ACTIVE_STATE, false);
  OK = OneButton(BTN_1_PIN, BTN_ACTIVE_STATE, false);
}

void Buttons::tick() {
    Back.tick();
    Up.tick();
    Down.tick();
    OK.tick();
}

void Buttons::attachAny(callbackFunction callback) {
  Back.attachClick(callback);
  Up.attachClick(callback);
  Down.attachClick(callback);
  OK.attachClick(callback);
}

void Buttons::RestoreCallbacks() {
  Back.restoreClick();
  Up.restoreClick();
  Down.restoreClick();
  OK.restoreClick();
}

void Buttons::StoreCallbacks() {
  Back.storeClick();
  Up.storeClick();
  Down.storeClick();
  OK.restoreClick();
}

Buttons Btn = Buttons();