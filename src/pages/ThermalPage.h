#ifndef THERMAL_PAGE_h
#define THERMAL_PAGE_h

class PThermalPage : public Pages {
  void Enter() {
    UI.ClearMenu();
    UI.AddMenuItem(1, F("Activate 1"));
    UI.AddMenuItem(2, F("Activate 2"));
    UI.AddMenuItem(3, F("Activate 3"));
    UI.AddMenuItem(0, F("Deactivate"));
    UI.AddMenuItem(99, F("Back"));
  }

  void Render() {
    long start = millis();
    UI.Title(F("Test Menu"));
    UI.RenderMenu();
    
    Serial.print("Render took ");
    Serial.print(millis() - start);
    Serial.println("ms");
  }

  void Loop() {
    if (Btn.Pressed(BTN_UP)) {
      UI.SelectPreviousMenuItem();
      return;
    }

    if (Btn.Pressed(BTN_DOWN)) {
      UI.SelectNextMenuItem();
      return;
    }

    if (Btn.Pressed(BTN_OK)) {
      UIMenuItem* c = UI.GetCurrentMenuItem();

      switch(c->value) {
        case 99:
          Pages::GoBack();
          break;
        default:
          TX.Send(0x01, c->value);
      }

      return;
    }

    if (Btn.Pressed(BTN_BACK)) {
      Pages::GoBack();
      return;
    }
  }
};

#endif