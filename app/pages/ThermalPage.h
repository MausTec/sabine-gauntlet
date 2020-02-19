#ifndef THERMAL_PAGE_h
#define THERMAL_PAGE_h

class PThermalPage : public Pages {
  void Enter() override {
    UI.ClearMenu();
    UI.AddMenuItem(1, F("Activate 1"));
    UI.AddMenuItem(2, F("Activate 2"));
    UI.AddMenuItem(3, F("Activate 3"));
    UI.AddMenuItem(4, F("Activate 4"));
    UI.AddMenuItem(5, F("Activate 5"));
    UI.AddMenuItem(6, F("Activate 6"));
    UI.AddMenuItem(7, F("Activate 7"));
    UI.AddMenuItem(0, F("Activate 0"));
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