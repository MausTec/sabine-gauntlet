//
// Created by eiser on 2/22/2020.
//

#ifndef GAUNTLETCONTROL_FILESPAGE_H
#define GAUNTLETCONTROL_FILESPAGE_H

#include <SDCard.h>

class PFilesPage : public Pages {
  void Enter() override {
    strcpy_P(cwd, PSTR("/C2E2"));
    Storage.chdir(cwd);
  }

  void Render() override {
    UI.Title(cwd);
    populateMenu();
    UI.RenderMenu();
  }

  void Exit() override {
  }

  // Because we have super limited ram, let's only go
  // one level deep.
  char cwd[30] = "";

private:

  static void chdirUp(UIMenuItem *i) {
    auto self = (PFilesPage*) Pages::CurrentPage();
    if (strlen(self->cwd) <= 1)
      return;
    char *slash = strrchr(self->cwd, '/');
    if (slash == nullptr)
      return;
    if (slash == self->cwd) {
      // We're at root
      self->cwd[1] = '\0';
    } else {
      self->cwd[slash - self->cwd] = '\0';
    }
    Storage.chdir(self->cwd);
    Pages::Rerender();
  }

  static void chdir(UIMenuItem *i) {
    auto self = (PFilesPage*) Pages::CurrentPage();
    if (strlen(self->cwd) > 1)
      strcat_P(self->cwd, PSTR("/"));
    strncat(self->cwd, i->labelCStr, strlen(i->labelCStr) - 1);
    Storage.chdir(self->cwd);
    Pages::Rerender();
  }

  static void openFile(UIMenuItem *i) {
    UI.Flash(F("OPEN FILE?"));
  }

  void populateMenu() {
    UI.ClearMenu();
    SdFile *p = Storage.openRoot();
    char name[15];

    auto self = (PFilesPage*) Pages::CurrentPage();
    if (strlen(self->cwd) > 1) {
      UI.AddMenuItem(0, F(".."), chdirUp);
    }

    while (p != nullptr) {
      if (!p->isHidden()) {
        p->getName(name, 15);
        if (p->isDir()) {
          // A lazy hack to prevent overflowing CWD
          if (strlen(cwd) + strlen(name) >= 28)
            continue;
          strcat(name, "/");
          UI.AddMenuItem(p->dirIndex(), name, chdir);
        } else {
          UI.AddMenuItem(p->dirIndex(), name, openFile);
        }
      }

      p->close();
      p = Storage.nextFile();
    }
  }
};

#endif //GAUNTLETCONTROL_FILESPAGE_H
