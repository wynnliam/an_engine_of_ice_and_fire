//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

/*
 The Main Menu State is what follows the Intro state.
 Here we will have to option to play, load a old game,
 modify settings, or just exit the application.
*/

#ifndef ACOC_STATE_MAIN_MENU
#define ACOC_STATE_MAIN_MENU

#include "GameState.h"
#include "../UI/Menus/MainMenu.h"

using namespace ACOC_GameState;

namespace ACOC_GameState
{
	class StateMainMenu : public GameState
	{
		public:
			//When we create the state (NOT PUSHING ONTO STACK)
			StateMainMenu();
			//When we close the game (NOT POPPING OFF STACK)
			~StateMainMenu();

			void Initialize(SDL_Renderer* renderer);
			void ProcessInput(SDL_Event& e);
			void Update(GameStateHandler* engine, float deltaTime);
			void Draw(SDL_Renderer* renderer);			
	
		private:
			void HandleNextState(GameStateHandler* engine);

			ACOC_UIElements::MenuMainMenu mainMenu;
	};
}

#endif
