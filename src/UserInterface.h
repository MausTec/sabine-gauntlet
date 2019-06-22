#ifndef USER_INTERFACE_h
#define USER_INTERFACE_h

#include "Arduino.h"
#include "../Aurebesh.h"

struct UIMenuItem {
  uint8_t value;
  const char* label;
  UIMenuItem* next;
  UIMenuItem* previous;
};

class UserInterface {
  public:
    UserInterface();

    void Clear(void);
    void Title(const char* title);
    void Puts(const char* str);
    void TextBox(const char* text);
    
    // Menu
    void AddMenuItem(uint8_t value, const char* label);
    void ClearMenu();
    UIMenuItem* GetCurrentMenuItem();
    void RenderMenu(int y);
    void RenderMenu(void);
    void RenderMenuItem(UIMenuItem* item);
    void SelectNextMenuItem();
    void SelectPreviousMenuItem();


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