//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

/*
 Here we handle all the logic for the intro state.
 In this state, the player would see things like a
 logo or two, perhaps a little introductory video,
 or whatever else I need to show them.

 As of writing this, I've not defined what exactly
 the intro will for sure entail. However, my goal
 with this is to create a flexible interface that
 will allow me to handle that.
*/

#ifndef ACOC_STATE_INTRO
#define ACOC_STATE_INTRO

#include "GameState.h"

using namespace ACOC_GameState;

namespace ACOC_GameState
{
	class StateIntro : public GameState
	{
		public:
			//When we create the state (NOT PUSHING ONTO STACK)
			StateIntro();
			//When we close the game (NOT POPPING OFF STACK)
			~StateIntro();

			void Initialize(SDL_Renderer* renderer);
			void ProcessInput(SDL_Event& e);
			void Update(GameStateHandler* engine, float deltaTime);
			void Draw(SDL_Renderer* renderer);

		private:
			void HandleNextState(GameStateHandler* engine);
			
			bool bExit; //Do we want to exit this state?
	};
}

#endif
