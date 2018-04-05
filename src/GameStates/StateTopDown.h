//Liam "AFishyFez" Wynn, 7/15/2015, A Clash of Colors

/*
 The most relevent to AEOIAF, in this state
 we handle all the logic of being in top down.
 This state is basically what the engine was
 built for.
*/

#ifndef ACOC_STATE_TOP_DOWN
#define ACOC_STATE_TOP_DOWN

#include "GameState.h"
#include "../Level/Level.h"
#include "../Actors/Character/Player.h"

using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;

namespace ACOC_GameState
{
	class StateTopDown : public GameState
	{
		public:
			//When we create the state (NOT PUSHING ONTO STACK)
			StateTopDown();
			//When we close the game (NOT POPPING OFF STACK)
			~StateTopDown();

			void Initialize(SDL_Renderer* renderer);
			void ProcessInput(SDL_Event& e);
			void Update(GameStateHandler* engine, float deltaTime);
			void Draw(SDL_Renderer* renderer);			
	
		private:
			//If the current level requests a new level, then we can change it here
			void HandleNextLevel();

			void HandleNextState(GameStateHandler* engine);

			//Note: when I add GlobalGameVariables, I don't want allocation/deallocation
			//of the level handled in this state, but there. Because what we will do is
			//grab the GlobalGameVariable's current level, or set it was we need to. But
			//those levels (except procedurally generated battles perhaps) will be managed there
			Level* currentLevel; //The level to update
	};
}

#endif

