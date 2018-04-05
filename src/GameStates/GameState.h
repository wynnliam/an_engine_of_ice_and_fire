//Liam "AFishyFez" Wynn, 6/15/2015, A Clash of Colors

/*
 Here we have the abstract base Game State class.
 As the game progresses, it will enter various states
 such as being in the regular game, playing a minigame,
 or in a menu. To reperesent these states, the Game Handler
 not only runs a loop, but also maintains a stack of these
 states. Basically as we enter a state, we push that onto
 the stack, and when we are done, we pop it off the stack.
*/

#ifndef ACOC_GAME_STATE
#define ACOC_GAME_STATE

#include "../GameStateHandler.h"
#include "../GameData/GameDataHandler.h"

namespace ACOC_GameState
{
	class GameState
	{
		public:
			//When we create the state (NOT PUSHING ONTO STACK)
			GameState();
			//When we close the game (NOT POPPING OFF STACK)
			virtual ~GameState();

			bool ShouldQuit() { return bQuit; }

			void SetGameDataHandler(ACOC_GameDataHandling::GameDataHandler* val) { gameDataHandler = val; }

			//Primarily for loading graphial content, but also
			//for other assests as well
			virtual void Initialize(SDL_Renderer* renderer) = 0;
			virtual void ProcessInput(SDL_Event& e) = 0;
			virtual void Update(GameStateHandler* engine, float deltaTime) = 0;
			virtual void Draw(SDL_Renderer* renderer) = 0;

		protected:
			//To handle SDL inputs, use this function
			virtual void ProcessSDLEvents(SDL_Event& e);

			//This function is meant to handle the transitions between states
			virtual void HandleNextState(GameStateHandler* engine) = 0;

			//A flag to denote if we want to quit the game entirely
			bool bQuit;

			ACOC_GameDataHandling::GameDataHandler* gameDataHandler;
	};
}

#endif
