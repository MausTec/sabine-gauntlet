#ifndef USER_INTERFACE_h
#define USER_INTERFACE_h

#include "Arduino.h"
#include "Aurebesh.h"
#include "assets/Icons.h"

#define SIDE_MENU_WIDTH 8

struct UIMenuItem {
  uint8_t value;
  const __FlashStringHelper* label;
  void(*callback)(UIMenuItem*);
  UIMenuItem* next;
  UIMenuItem* previous;
};

typedef void(*menuCallback)(UIMenuItem*);

class UserInterface {
  public:
    UserInterface();

    void Clear(void);
    void Title();
    void Title(const char* title);
    void Title(const __FlashStringHelper* title);
    void Puts(const char* str);
    void TextBox(const char* text);
    
    // Menu
    // void AddMenuItem(uint8_t value, const char* label);
    void AddMenuItem(uint8_t value, const __FlashStringHelper* label);
    void AddMenuItem(uint8_t value, const __FlashStringHelper *label, menuCallback callback);
    void ClearMenu();
    UIMenuItem* GetCurrentMenuItem();
    void RenderMenu(int y);
    void RenderMenu(uint8_t x, uint8_t y);
    void RenderMenu(void);
    void RenderMenuItem(UIMenuItem* item);
    void SelectNextMenuItem();
    void SelectPreviousMenuItem();

    // Control Indicators
    void RenderControls();

    // Button Attachments
    void AttachButtonHandlers(void);
    void onMenuClick(menuCallback callback);

    // Misc.
    void Modal(const __FlashStringHelper *message);
    void Flash(const __FlashStringHelper *pHelper);


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
};

extern UserInterface UI;
#endif