//Liam "AFishyFez" Wynn, 7/15/2015, A Clash of Colors

#include "StateTopDown.h"
#include "../GameData/StreamData/StreamData.h"
#include "../TestVars.h"
#include "../Actors/Prop/Prop.h"
#include "../Actors/Character/TestNonPlayer.h"
#include "../Actors/Character/Faction.h"
#include "../Utilities/Color_Utilities/AEOIAFColor.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace ACOC_GameState;
using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Content;
using namespace AEOIAF_Actor;
using namespace AEOIAF_AIBehavior;
using namespace AEOIAF_Content;
using namespace std;

StateTopDown::StateTopDown()
{
	currentLevel = NULL;
}

StateTopDown::~StateTopDown()
{
	//This is handled elsewhere
	currentLevel = NULL;
}

void StateTopDown::Initialize(SDL_Renderer* renderer)
{
	//currentLevel = CreateBattlefield(renderer);
}

void StateTopDown::ProcessInput(SDL_Event& e)
{
	//Check if the window is closed
	ProcessSDLEvents(e);
}

void StateTopDown::Update(GameStateHandler* engine, float deltaTime)
{
	if(!engine)
		return;

	StreamDataHandler* currentStreamData = gameDataHandler->GetStreamHandler();

	if(gameDataHandler && !currentLevel)
	{
		currentLevel = gameDataHandler->GetLevel("TEST"); //You can put anything you want here, as long as it isn't NULL
		//currentLevel = CreateBattlefield(renderer);
	}

	if(currentLevel)
	{
		currentLevel->Update(NULL, deltaTime, *currentStreamData);
		HandleNextLevel();
	}

	HandleNextState(engine);
}

void StateTopDown::HandleNextLevel()
{
	if(!currentLevel)
		return;

	char* nextLevel;

	if(currentLevel->GetNextLevelName(nextLevel))
	{
		delete currentLevel;
		currentLevel = gameDataHandler->GetLevel(nextLevel);

		delete[] nextLevel;
		nextLevel = NULL;
	}
}

void StateTopDown::HandleNextState(GameStateHandler* engine)
{
	if(!engine)
		return;

	engine->SetCurrentState(STATE_IN_TOP_DOWN);
}

void StateTopDown::Draw(SDL_Renderer* renderer)
{
	if(!renderer || !currentLevel)
		return;

	SDL_SetRenderDrawColor(renderer, 255, 155, 0, 255);
	SDL_RenderClear(renderer);
	
	currentLevel->Draw(renderer);
}
