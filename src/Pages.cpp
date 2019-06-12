#include "Pages.h"
#include "openGLCD/openGLCD.h"

Pages* Pages::currentPage = NULL;
Pages* Pages::previousPage = NULL;

void Pages::Go(Pages* page) {
  if (page == currentPage) return;

	previousPage = currentPage;

  if (previousPage != NULL)
    previousPage->Exit();

	currentPage = page;
	Rerender();
  currentPage->Enter();
}

void Pages::GoBack() {
	if(previousPage != NULL) {
		Go(previousPage);
		previousPage = NULL;
	}
}

void Pages::Rerender() {
	GLCD.ClearScreen();
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

// Initialize Pages:
PMainPage MainPage = PMainPage();
PStandbyPage StandbyPage = PStandbyPage();