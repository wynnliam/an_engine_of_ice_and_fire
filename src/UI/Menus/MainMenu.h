//Liam "AFishyFez" Wynn, 6/20/2015, A Clash of Colors

/*
 When you first load up the game, this is the very
 first thing the user sees. This system of hard-coding
 menus is a far-cry from the likes of the Unreal Engine
 but it does the job.
*/

#ifndef ACOC_UI_MAIN_MENU
#define ACOC_UI_MAIN_MENU

#include "../MenuContainer.h"

namespace ACOC_UIElements
{
	class MenuMainMenu : public MenuContainer
	{
		public:
			MenuMainMenu();
			~MenuMainMenu();

			bool IsPlayClicked() const { return bPlay; }

			void ProcessInput(SDL_Event& e);
			void Update();

		private:
			bool bPlay; //True when we press the play button		
	};
}

#endif
