//Liam "AFishyFez" Wynn, 6/17/2015, A Clash of Colors

#include "GameStateHandler.h"
#include "GameStates/GameState.h"

//States
#include "GameStates/StateIntro.h"
#include "GameStates/StateMainMenu.h"
#include "GameStates/StateTopDown.h"

using namespace ACOC_GameState;

/*HANDLER IMPLEMENTATIONS*/

GameStateHandler::GameStateHandler()
{
	states = new GameState*[NUM_GAME_STATES];
	for(int i = 0; i < NUM_GAME_STATES; ++i)
		states[i] = NULL;

	dataHandler = new GameDataHandler;

	states[STATE_INTRO] = new StateIntro;
	states[STATE_MAIN_MENU] = new StateMainMenu;
	states[STATE_IN_TOP_DOWN] = new StateTopDown;

	currStateIndex = 0;
}

GameStateHandler::~GameStateHandler()
{
	if(states)
	{
		for(int i = 0; i < NUM_GAME_STATES; ++i)
		{
			if(states[i])
			{
				delete states[i];
				states[i] = NULL;
			}
		}

		delete[] states;
		states = NULL;
	}

	if(dataHandler)
	{
		delete dataHandler;
		dataHandler = NULL;
	}
}

//Loop through each item, if it is not NULL, then initialize it
void GameStateHandler::Initialize(SDL_Renderer* renderer)
{
	if(!renderer || !states)
		return;

	dataHandler = new GameDataHandler(renderer);
	dataHandler->LoadDrawComponents();
	dataHandler->LoadAudioComponents();

	for(int i = 0; i < NUM_GAME_STATES; ++i)
	{
		if(states[i])
		{
			states[i]->SetGameDataHandler(dataHandler);
			states[i]->Initialize(renderer);
		}
	}
}

void GameStateHandler::ProcessInput(SDL_Event& e, bool& bQuit)
{
	states[currStateIndex]->ProcessInput(e);

	//After we process input, we can examine here if we should
	//quit the game
	CheckQuit(bQuit);
}

void GameStateHandler::CheckQuit(bool& bQuit)
{
	//Only check if bQuit is false! If it was true
	//then this state could change it, locking the
	//user into the game forever!
	if(!bQuit)
		bQuit = states[currStateIndex]->ShouldQuit();
}

void GameStateHandler::Update(float deltaTime)
{
	states[currStateIndex]->Update(this, deltaTime);
}

void GameStateHandler::Draw(SDL_Renderer* renderer)
{
	states[currStateIndex]->Draw(renderer);
}

//First we make a new node. We set the data
//to toAdd, and next to head. Then we make the
//new node the new head
void GameStateHandler::SetCurrentState(int stateType)
{
	if(stateType >= NUM_GAME_STATES)
		return;

	currStateIndex = stateType;
}

