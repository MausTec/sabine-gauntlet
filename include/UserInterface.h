#ifndef USER_INTERFACE_h
#define USER_INTERFACE_h

#include "Arduino.h"
#include "Aurebesh.h"

#define SIDE_MENU_WIDTH 8

struct UIMenuItem {
  uint8_t value;
  const __FlashStringHelper* label;
  void(*callback)(UIMenuItem*);
  UIMenuItem* next;
  UIMenuItem* previous;
};

struct UINumberField {
  int defaultValue;
  int currentValue;
  const __FlashStringHelper* label;
  UINumberField* next;
  UINumberField* previous;
  int(*onChange)(int, int);
};

typedef void(*menuCallback)(UIMenuItem*);
typedef int(*numberFieldChangeHandler)(int, int);

class UserInterface {
  public:
    UserInterface();

    void Clear();
    void Title();
    void Title(const char* title);
    void Title(const __FlashStringHelper* title);
    void Puts(const char* str);
    static void TextBox(const char* text);
    
    // Menu
    // void AddMenuItem(uint8_t value, const char* label);
    void AddMenuItem(uint8_t value, const __FlashStringHelper* label);
    void AddMenuItem(uint8_t value, const __FlashStringHelper *label, menuCallback callback);
    void ClearMenu();
    UIMenuItem* GetCurrentMenuItem();
    void RenderMenu(int y);
    void RenderMenu(uint8_t x, uint8_t y);
    void RenderMenu();
    void RenderMenuItem(UIMenuItem* item);
    void SelectNextMenuItem();
    void SelectPreviousMenuItem();

    // Control Indicators
    void RenderControls();

    // Button Attachments
    static void AttachButtonHandlers();
    void onMenuClick(menuCallback callback);

    // Misc.
    void Modal(const __FlashStringHelper *message, bool alignTop = false);
    void Flash(const __FlashStringHelper *pHelper);

    // Inputs (Modals)
    void NumberInput(const __FlashStringHelper *label, int defaultValue, numberFieldChangeHandler onChange);
    void AddNumberInput(const __FlashStringHelper *label, int defaultValue, numberFieldChangeHandler onChange);
    void RenderNumberInput(bool init = true);
    void ClearNumberInput();
    void inputBack();
    void inputOK();
    void inputUp();
    void inputDown();

private:
    UIMenuItem* firstMenuItem;
    UIMenuItem* lastMenuItem;
    UIMenuItem* currentMenuItem;
    uint8_t menuSize;
    int menuLastY;
    int cursorY;
    int menuStartX;
    bool hasControls;

    menuCallback menuClickHandler;

  void menuClick();
  uint8_t getWidth();

  void RenderMenuItem(UIMenuItem *item, uint8_t ypos);

  // Inputs
  UINumberField* firstNumberField;
  UINumberField* lastNumberField;
  UINumberField* currentNumberField;

  void updateInput();
};

extern UserInterface UI;
#endif