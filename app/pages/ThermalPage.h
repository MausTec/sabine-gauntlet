#ifndef THERMAL_PAGE_h
#define THERMAL_PAGE_h

class PThermalPage : public Pages {
  void Enter() override {
    UI.ClearMenu();
    UI.AddMenuItem(1, F("Activate 1"));
    UI.AddMenuItem(2, F("Activate 2"));
    UI.AddMenuItem(3, F("Activate 3"));
    UI.AddMenuItem(0, F("Deactivate"));
    UI.AddMenuItem(99, F("Back"));

    UI.AttachButtonHandlers();
    UI.RenderControls();

    Btn.OK->attachClick(handleOKClick);
  }

  void Render() override {
    UI.Title(F("Prop Activation"));
    UI.RenderMenu();
  }

private:

  static void handleOKClick() {
      UIMenuItem* c = UI.GetCurrentMenuItem();
      switch(c->value) {
        case 99:
          Pages::GoBack();
          break;
        default:
          TX.Send(0x00, c->value);
      }
  }
};

#endif