//Liam "AFishyFez" Wynn, 6/17/2015, A Clash of Colors

/*
 The Game State Handler handles the various states
 that a game can enter. These would be things like
 The intro video/logos, the main menu, the game proper,
 the pause menu, etc.

 It will handle these states in two ways. First it will
 store all possible game states in an array, thereby
 making this class solely responsible for all states.
 Second, it will also keep track of the current game
 state by having a stack. As we change states, we can
 push or pop them onto (or off) the stack. This way,
 the game does not need to manually keep track of the
 state with if-else or switch-case statements.

 I got this idea from:
 gamedevgeek.com/tutorials/managing-game-states-in-c/
*/

#ifndef ACOC_GAME_STATE_STACK
#define ACOC_GAME_STATE_STACK

#include <SDL2/SDL.h>
#include "GameData/GameDataHandler.h"

#define NUM_GAME_STATES 3

#define STATE_INTRO        0
#define STATE_MAIN_MENU    1
#define STATE_IN_TOP_DOWN  2

using namespace ACOC_GameDataHandling;

namespace ACOC_GameState
{
	class GameState;

	class GameStateHandler
	{
		public:
			GameStateHandler();
			~GameStateHandler();

			/*State Functions*/

			void Initialize(SDL_Renderer* renderer);
			//This will grab the current state
			//to update.
			void GrabCurrentState();
			//Wrapper functions for the current state
			void ProcessInput(SDL_Event& e, bool& bQuit);
			void Update(float deltaTime);
			void Draw(SDL_Renderer* renderer);

			/*Stack Functions*/

			//Add a Game State to the stack
			void SetCurrentState(int stateType);

		private:
			/*RECURSIVE STACK FUNCTIONS*/
			void Clear(struct GameStateNode*& head);

			/*OTHER UTILITIES*/
			//Essentially this handles if we should
			//quit the game.
			void CheckQuit(bool& bQuit);
			
			GameState** states; //An array of all states. When we push, we use the address of the supplied state
			int currStateIndex;

			GameDataHandler* dataHandler; //Manages all game assests
	};
}

#endif
