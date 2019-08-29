#include "Pages.h"

Pages* Pages::currentPage = NULL;
Pages* Pages::previousPage = NULL;
Pages* Pages::previousPages[HISTORY_LENGTH] = { NULL };
size_t Pages::historyIndex = 0;

void Pages::Go(Pages* page, bool saveHistory) {
  if (page == currentPage) return;

	previousPage = currentPage;

  if (previousPage != NULL)
    previousPage->Exit();

  if (saveHistory)
    pushHistory(page);

	currentPage = page;
  currentPage->Enter();
  Rerender();
}

void Pages::Go(Pages* page) {
  Go(page, true);
}

void Pages::GoBack() {
  Pages* prev = popHistory();

	if(prev != NULL) {
		Go(prev, false);
	}
}

void Pages::Rerender() {
	UI.Clear();
	if(currentPage != NULL)
		currentPage->Render();
}

void Pages::DoLoop(void) {
	if(currentPage != NULL)
		currentPage->Loop();
}

// Instance Methods

void Pages::Loop(void) {
	//noop
}

void Pages::Enter(void) {
  //noop
}

void Pages::Exit(void) {
  //noop
}

// Private Methods

void Pages::pushHistory(Pages* page) {
  historyIndex = (historyIndex + 1) % HISTORY_LENGTH;
  previousPages[historyIndex] = page;
}

Pages* Pages::popHistory() {
  historyIndex = (historyIndex - 1) % HISTORY_LENGTH;
  return previousPages[historyIndex];
}

// Initialize Pages:
PMainPage MainPage = PMainPage();
PStandbyPage StandbyPage = PStandbyPage();
PThermalPage ThermalPage = PThermalPage();
PSettingsPage SettingsPage = PSettingsPage();