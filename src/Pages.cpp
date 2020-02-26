#include "Pages.h"

Pages* Pages::currentPage = nullptr;
Pages* Pages::previousPage = nullptr;
Pages* Pages::previousPages[HISTORY_LENGTH] = { nullptr };
size_t Pages::historyIndex = 0;

void Pages::Go(Pages* page, bool saveHistory) {
  if (page == currentPage) return;

	previousPage = currentPage;

  if (previousPage != nullptr)
    previousPage->Exit();

  if (saveHistory)
    pushHistory(page);

  // Reset UI State:
  UI.ClearMenu();
  UI.AttachButtonHandlers();
  AttachButtonHandlers();

	currentPage = page;
  currentPage->Enter();
  Rerender();
}

void Pages::Go(Pages* page) {
  Go(page, true);
}

void Pages::GoBack() {
  Pages* prev = popHistory();

	if(prev != nullptr) {
		Go(prev, false);
	}
}

void Pages::Rerender() {
	UI.Clear();
	if(currentPage != nullptr)
		currentPage->Render();
}

void Pages::DoLoop() {
	if(currentPage != nullptr)
		currentPage->Loop();
}

// Instance Methods

void Pages::Loop() {
	//noop
}

void Pages::Enter() {
  //noop
}

void Pages::Exit() {
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

void Pages::AttachButtonHandlers() {
  Btn.Back.attachClick(GoBack);
  Btn.Back.attachDoubleClick([]() { Pages::Go(&MainPage); });
  Btn.Back.attachLongPressStart([]() { Pages::Go(&StandbyPage); });
}

Pages *Pages::CurrentPage() {
  return currentPage;
}

// Initialize Pages:
PMainPage MainPage = PMainPage();
PStandbyPage StandbyPage = PStandbyPage();
PThermalPage ThermalPage = PThermalPage();
PSettingsPage SettingsPage = PSettingsPage();
PFilesPage FilesPage = PFilesPage();