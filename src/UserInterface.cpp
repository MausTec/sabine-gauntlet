#include <Buttons.h>
#include <Pages.h>
#include "UserInterface.h"

UserInterface::UserInterface() {
  firstMenuItem = nullptr;
  lastMenuItem = nullptr;
  currentMenuItem = nullptr;
  menuSize = 0;
  menuStartX = 0;
  cursorY = 0;
  menuLastY = 255;
  hasControls = false;

  menuClickHandler = nullptr;
  firstNumberField = nullptr;
  lastNumberField = nullptr;
  currentNumberField = nullptr;
}

void UserInterface::Clear() {
  cursorY = 0;
  menuLastY = 255;
  menuStartX = 0;
  hasControls = false;
  LCD.Clear(PIXEL_OFF);
}

void UserInterface::Title() {
  uint8_t width = getWidth();
  // LCD.DrawLine(0, 9, 128, 9, PIXEL_ON);
  LCD.FillRect(0, 0, width, 9, PIXEL_ON);
  cursorY = 12;
}

void UserInterface::Title(const char* title) {
  Title();
  Str.PutsCenter(2, title, false);
}

void UserInterface::Title(const __FlashStringHelper* title) {
  Title();
  Str.PutsCenter(2, title, true);
}

void UserInterface::Modal(const __FlashStringHelper* message, bool alignTop) {
  uint8_t width = getWidth();

  LCD.FillRect(8, 8, (width-16), (64-16), PIXEL_OFF);
  LCD.DrawRect(10, 10, (width-20), (64-20), PIXEL_ON);
  Str.PutsCenter(alignTop ? 13 : 28, width, message, PIXEL_OFF);
}

void UserInterface::Puts(const char* str) {
  Str.Puts(0, cursorY, str);
  cursorY += AUREBESH_CHR_HEIGHT + 1;
}

void UserInterface::TextBox(const char* text) {
  
}

void UserInterface::ClearMenu() {
  UIMenuItem* ptr = firstMenuItem;
  
  while (ptr != nullptr) {
    ptr = ptr->next;
    delete ptr;
  }

  firstMenuItem = nullptr;
  lastMenuItem = nullptr;
  currentMenuItem = nullptr;
}

// void UserInterface::AddMenuItem(uint8_t value, const char* label) {
//   AddMenuItem(value, FPSTR(label));
// }

void UserInterface::AddMenuItem(uint8_t value, const __FlashStringHelper* label, menuCallback callback) {
  auto *item = new UIMenuItem;
  item->value = value;
  item->label = label;
  item->callback = callback;
  item->next = nullptr;
  item->previous = lastMenuItem;

  if (item->previous != nullptr) {
    item->previous->next = item;
  }

  if (firstMenuItem == nullptr) {
    firstMenuItem = item;
    currentMenuItem = item;
  }

  lastMenuItem = item;
  menuSize++;
}

void UserInterface::AddMenuItem(uint8_t value, const __FlashStringHelper* label) {
  AddMenuItem(value, label, nullptr);
}



void UserInterface::RenderMenu(uint8_t x, uint8_t y) {
  menuStartX = x;
  RenderMenu(y);
}

void UserInterface::RenderMenu(int y) {
  UIMenuItem* ptr = firstMenuItem;
  uint8_t i = 0;
  menuLastY = y;

  while (ptr != nullptr) {
    uint8_t ypos = y + (7 * i);
    RenderMenuItem(ptr, ypos);

    i++;
    ptr = ptr->next;
  }
}

void UserInterface::RenderMenu() {
  if (menuLastY == 255)
    menuLastY = cursorY;
  RenderMenu(menuLastY);
}

void UserInterface::RenderMenuItem(UIMenuItem* item) {
  UIMenuItem* ptr = firstMenuItem;
  uint8_t i = 0;

  while (ptr != nullptr) {
    if (ptr == item) break;
    i++;
    ptr = ptr->next;
  }

  uint8_t ypos = menuLastY + (7 * i);
  RenderMenuItem(ptr, ypos);
}

void UserInterface::RenderMenuItem(UIMenuItem *item, uint8_t ypos) {
  bool invert = item == currentMenuItem;

  uint8_t width = getWidth() - menuStartX;

  if (invert) {
//    LCD.FillRect(0, ypos, width, 7, PIXEL_ON);
    Str.PutChar(menuStartX, ypos + 1, '>');
  } else {
//    LCD.FillRect(0, ypos, width, 7, PIXEL_OFF);
    Str.PutChar(menuStartX, ypos + 1, ' ');
  }

  Str.Puts(menuStartX + 10, ypos + 1, item->label);
}

void UserInterface::SelectNextMenuItem() {
  UIMenuItem* last = currentMenuItem;
  UIMenuItem* next = currentMenuItem->next;

  if (next == nullptr) {
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

  if (previous == nullptr) {
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

void UserInterface::RenderControls() {
  hasControls = true;
  uint8_t x = DISPLAY_WIDTH - SIDE_MENU_WIDTH;
  uint8_t height = DISPLAY_HEIGHT / 4;

  LCD.FillRect(x - 1, height * 0,
               SIDE_MENU_WIDTH,
               height - 1,
               PIXEL_ON);
  Str.PutChar(x, (height * 0) + 4, '<', true);

  LCD.FillRect(x - 1, height * 1,
               SIDE_MENU_WIDTH,
               height - 1,
               PIXEL_ON);
  Str.PutChar(x, (height * 1) + 4, '^', true);

  LCD.FillRect(x - 1, height * 2,
               SIDE_MENU_WIDTH,
               height - 1,
               PIXEL_ON);
  Str.PutChar(x, (height * 2) + 4, '`', true);

  LCD.FillRect(x - 1, height * 3,
               SIDE_MENU_WIDTH,
               height - 1,
               PIXEL_ON);
  Str.PutChar(x, (height * 3) + 4, '>', true);
}

void UserInterface::AttachButtonHandlers() {
  Btn.Up->attachClick([]() {
    UI.SelectPreviousMenuItem();
  });

  Btn.Down->attachClick([]() {
    UI.SelectNextMenuItem();
  });

  Btn.OK->attachClick([]() {
    UI.menuClick();
  });
}

void UserInterface::onMenuClick(menuCallback callback) {
  menuClickHandler = callback;
}

void UserInterface::menuClick() {
  if (currentMenuItem == nullptr) {
    return;
  }

  if (currentMenuItem->callback != nullptr) {
    return currentMenuItem->callback(currentMenuItem);
  }

  if (menuClickHandler != nullptr) {
    menuClickHandler(currentMenuItem);
  }
}

void UserInterface::Flash(const __FlashStringHelper *pHelper) {
  Modal(pHelper);
  delay(1000);
  Pages::Rerender();
}

uint8_t UserInterface::getWidth() {
  if (hasControls) {
    return DISPLAY_WIDTH - 10;
  } else {
    return DISPLAY_WIDTH;
  }
}

void UserInterface::NumberInput(const __FlashStringHelper *label, int value, numberFieldChangeHandler onChange) {
  ClearNumberInput();
  AddNumberInput(label, value, onChange);
  RenderNumberInput();
}

void UserInterface::RenderNumberInput(bool init) {
  if (init) {
    Btn.StoreCallbacks();

    Btn.Back->attachClick([]() { UI.inputBack(); });
    Btn.OK->attachClick([]() { UI.inputOK(); });
    Btn.Up->attachClick([]() { UI.inputUp(); });
    Btn.Down->attachClick([]() { UI.inputDown(); });
  }

  Modal(currentNumberField->label, true);
  updateInput();
}

void UserInterface::updateInput() {
  char valueStr[5];
  sprintf_P(valueStr, PSTR("%-3d"), currentNumberField->currentValue);
  Str.PutsCenter(28, getWidth(), valueStr, false);
}

void UserInterface::inputBack() {
  if (currentNumberField == firstNumberField) {
    // Restore default value.
    currentNumberField->onChange(currentNumberField->defaultValue, currentNumberField->defaultValue);

    // Exit Input
    Pages::Rerender();
    Btn.RestoreCallbacks();
    UI.AttachButtonHandlers();
  } else {
    currentNumberField = currentNumberField->previous;
    RenderNumberInput(false);
  }
}

void UserInterface::inputOK() {
  if (currentNumberField == lastNumberField) {
    Pages::Rerender();
    Btn.RestoreCallbacks();
    UI.AttachButtonHandlers();
  } else {
    currentNumberField = currentNumberField->next;
    RenderNumberInput(false);
  }
}

void UserInterface::inputUp() {
  int lastValue = currentNumberField->currentValue;
  currentNumberField->currentValue = currentNumberField->onChange(lastValue + 1, lastValue);
  updateInput();
}

void UserInterface::inputDown() {
  int lastValue = currentNumberField->currentValue;
  currentNumberField->currentValue = currentNumberField->onChange(lastValue - 1, lastValue);
  updateInput();
}

void
UserInterface::AddNumberInput(const __FlashStringHelper *label, int defaultValue, numberFieldChangeHandler onChange) {
  auto *field = new UINumberField;
  field->label = label;
  field->defaultValue = defaultValue;
  field->currentValue = defaultValue;
  field->onChange = onChange;
  field->previous = lastNumberField;
  field->next = nullptr;

  if (lastNumberField != nullptr) {
    lastNumberField->next = field;
  }

  // Add to list
  lastNumberField = field;

  if (firstNumberField == nullptr) {
    firstNumberField = field;
  }

  if (currentNumberField == nullptr) {
    currentNumberField = field;
  }
}

void UserInterface::ClearNumberInput() {
  UINumberField *p = firstNumberField;

  while (p != nullptr) {
    UINumberField *next = p->next;
    delete p;
    p = next;
  }

  firstNumberField = nullptr;
  lastNumberField = nullptr;
  currentNumberField = nullptr;
}

UserInterface UI = UserInterface();