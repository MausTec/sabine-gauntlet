#ifndef USER_INTERFACE_h
#define USER_INTERFACE_h

#include "Arduino.h"
#include "Aurebesh.h"
#include "assets/Icons.h"

#define SIDE_MENU_WIDTH 8

struct UIMenuItem {
  uint8_t value;
  const __FlashStringHelper* label;
  UIMenuItem* next;
  UIMenuItem* previous;
};

class UserInterface {
  public:
    UserInterface();

    void Clear(void);
    void Title(const char* title);
    void Title(const __FlashStringHelper* title);
    void Puts(const char* str);
    void TextBox(const char* text);
    
    // Menu
    // void AddMenuItem(uint8_t value, const char* label);
    void AddMenuItem(uint8_t value, const __FlashStringHelper* label);
    void ClearMenu();
    UIMenuItem* GetCurrentMenuItem();
    void RenderMenu(int y);
    void RenderMenu(void);
    void RenderMenuItem(UIMenuItem* item);
    void SelectNextMenuItem();
    void SelectPreviousMenuItem();

    // Control Indicators
    void SetBackAction(uint8_t icon, void* callback);
    void SetOKAction(uint8_t icon, void* callback);
    void SetUpAction(uint8_t icon, void* callback);
    void SetDownAction(uint8_t icon, void* callback);
    void RenderControls();

    // Button Attachments
    void AttachButtonHandlers(void);


  private:
    UIMenuItem* firstMenuItem;
    UIMenuItem* lastMenuItem;
    UIMenuItem* currentMenuItem;
    uint8_t menuSize;
    int menuLastY;
    int cursorY;
};

extern UserInterface UI;
#endif