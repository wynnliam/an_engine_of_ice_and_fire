//Liam "AFishyFez" Wynn, 6/17/2015, A Clash of Colors

#include "GameState.h"

using namespace ACOC_GameState;

GameState::GameState()
{
	bQuit = false;
	gameDataHandler = NULL;
}

GameState::~GameState()
{
	bQuit = true;
	gameDataHandler = NULL;
}

//All we will do is run SDL_PollEvent in a loop, and
//check for if e is a quit event
void GameState::ProcessSDLEvents(SDL_Event& e)
{
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			bQuit = true;
	}
}
