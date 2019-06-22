#ifndef THERMAL_PAGE_h
#define THERMAL_PAGE_h

class PThermalPage : public Pages {
  void Enter() {
    UI.ClearMenu();
    UI.AddMenuItem(1, "Activate 1");
    UI.AddMenuItem(2, "Activate 2");
    UI.AddMenuItem(3, "Activate 3");
    UI.AddMenuItem(0, "Deactivate");
    UI.AddMenuItem(99, "Back");
  }

  void Render() {
    UI.Title("Test Menu");
    UI.RenderMenu();
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
      Serial.print("Menu select: ");
      Serial.println(c->label);
      Serial.print("(Value: ");
      Serial.print(c->value);
      Serial.println(")");

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