#ifndef THERMAL_PAGE_h
#define THERMAL_PAGE_h

class PThermalPage : public Pages {
  void Enter() {
    UI.ClearMenu();
    UI.AddMenuItem(2, "RF ON");
    UI.AddMenuItem(3, "RF Off");
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
        case 2:
          TX.Send(0x01, 0x1);
          break;
        case 3:
          TX.Send(0x01, 0x0);
          break;
        case 99:
          Pages::GoBack();
          break;
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