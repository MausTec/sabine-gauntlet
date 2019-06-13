#ifndef PAGES_h
#define PAGES_h

#define HISTORY_LENGTH 5

#include "UserInterface.h"
#include "../Buttons.h"
#include "../Aurebesh.h"
#include "Transmitter.h"
#include "openGLCD/openGLCD.h"

class Pages {
	public:
    static void Go(Pages* page, bool saveHistory);
		static void Go(Pages* page);
		static void GoBack();
		static void DoLoop();
		static void Rerender();

    // Class Methods

		virtual void Render() = 0;
		virtual void Loop();
    virtual void Enter();
    virtual void Exit();

	private:
		static Pages* currentPage;
    static Pages* previousPage;
    static Pages* previousPages[HISTORY_LENGTH];
    static size_t historyIndex;

    static void pushHistory(Pages* page);
    static Pages* popHistory();
};

// Delcare Pages:
#include "pages/ThermalPage.h"
extern PThermalPage ThermalPage;

#include "pages/MainPage.h"
extern PMainPage MainPage;

#include "pages/StandbyPage.h"
extern PStandbyPage StandbyPage;

#endif