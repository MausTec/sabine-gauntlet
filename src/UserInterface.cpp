#include "UserInterface.h"

UserInterface::UserInterface() {
  firstMenuItem = NULL;
  lastMenuItem = NULL;
  currentMenuItem = NULL;
  menuSize = 0;
  cursorY = 0;
  menuLastY = 255;
}

void UserInterface::Clear(void) {
  cursorY = 0;
  menuLastY = 255;
  LCD.Clear(PIXEL_OFF);
}

void UserInterface::Title(const char* title) {
  Str.PutsCenter(2, title, false);
  LCD.DrawLine(0, 9, 128, 9, PIXEL_ON);
  cursorY = 12;
}

void UserInterface::Puts(const char* str) {
  Str.Puts(0, cursorY, str);
  cursorY += AUREBESH_CHR_HEIGHT + 1;
}

void UserInterface::TextBox(const char* text) {
  
}

void UserInterface::ClearMenu() {
  UIMenuItem* ptr = firstMenuItem;
  
  while (ptr != NULL) {
    ptr = ptr->next;
    delete ptr;
  }

  firstMenuItem = NULL;
  lastMenuItem = NULL;
  currentMenuItem = NULL;
}

void UserInterface::AddMenuItem(uint8_t value, const char* label) {
  UIMenuItem* item = new UIMenuItem;
  item->value = value;
  item->label = label;
  item->next = NULL;
  item->previous = lastMenuItem;

  if (item->previous != NULL) {
    item->previous->next = item;
  }

  if (firstMenuItem == NULL) {
    firstMenuItem = item;
    currentMenuItem = item;
  }

  lastMenuItem = item;
  menuSize++;
}

void UserInterface::RenderMenu(int y) {
  UIMenuItem* ptr = firstMenuItem;
  uint8_t i = 0;
  menuLastY = y;

  while (ptr != NULL) {
    uint8_t ypos = y + (7 * i);
    bool invert = ptr == currentMenuItem;

    if (invert) {
      LCD.FillRect(0, ypos, DISPLAY_WIDTH, 7, PIXEL_ON);
    } else {
      LCD.FillRect(0, ypos, DISPLAY_WIDTH, 7, PIXEL_OFF);
    }

    Str.Puts(1, ypos + 1, ptr->label, invert);

    i++;
    ptr = ptr->next;
  }
}

void UserInterface::RenderMenu(void) {
  if (menuLastY == 255)
    menuLastY = cursorY;
  RenderMenu(menuLastY);
}

void UserInterface::RenderMenuItem(UIMenuItem* item) {
  UIMenuItem* ptr = firstMenuItem;
  uint8_t i = 0;
  uint8_t ypos;
  bool invert;

  while (ptr != NULL) {
    if (ptr == item) break;
    i++;
    ptr = ptr->next;
  }

  ypos = menuLastY + (7 * i);
  invert = ptr == currentMenuItem;

  if (invert) {
    LCD.FillRect(0, ypos, DISPLAY_WIDTH, 7, PIXEL_ON);
  } else {
    LCD.FillRect(0, ypos, DISPLAY_WIDTH, 7, PIXEL_OFF);
  }

  Str.Puts(1, ypos + 1, ptr->label, invert);
}

void UserInterface::SelectNextMenuItem() {
  UIMenuItem* last = currentMenuItem;
  UIMenuItem* next = currentMenuItem->next;

  if (next == NULL) {
    currentMenuItem = firstMenuItem;
  } else {
    currentMenuItem = next;
  }

  RenderMenuItem(last);
  RenderMenuItem(currentMenuItem);
}

void UserInterface::SelectPreviousMenuItem() {
  UIMenuItem* last = currentMenuItem;
  UIMenuItem* previous = currentMenuItem->previous;

  if (previous == NULL) {
    currentMenuItem = lastMenuItem;
  } else {
    currentMenuItem = previous;
  }

  RenderMenuItem(last);
  RenderMenuItem(currentMenuItem);
}

UIMenuItem* UserInterface::GetCurrentMenuItem() {
  return currentMenuItem;
}

UserInterface UI = UserInterface();