#ifndef PAGES_h
#define PAGES_h

#include "../Aurebesh.h"
#include "openGLCD/openGLCD.h"

class Pages {
	public:
		static void Go(Pages* page);
		static void GoBack();
		static void DoLoop();
		static void Rerender();

		virtual void Render() = 0;
		virtual void Loop();
    virtual void Enter();
    virtual void Exit();

	private:
		static Pages* currentPage;
		static Pages* previousPage;
};

// Delcare Pages:
#include "pages/MainPage.h"
extern PMainPage MainPage;

#include "pages/StandbyPage.h"
extern PStandbyPage StandbyPage;

#endif