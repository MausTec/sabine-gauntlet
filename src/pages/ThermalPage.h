#ifndef THERMAL_PAGE_h
#define THERMAL_PAGE_h

class PThermalPage : public Pages {
  void Enter() {
    UI.ClearMenu();
    UI.AddMenuItem(0, "Select Detonator");
    UI.AddMenuItem(1, "Configure");
    UI.AddMenuItem(99, "Back");
  }

  void Render() {
    UI.Title("Remote Control");
    UI.RenderMenu();
  }

  void Loop() {
    if (Btn.Pressed(BTN_UP)) {
      UI.SelectNextMenuItem();
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
      }
    }

    if (Btn.Pressed(BTN_BACK)) {
      Pages::GoBack();
    }
  }
};

#endif