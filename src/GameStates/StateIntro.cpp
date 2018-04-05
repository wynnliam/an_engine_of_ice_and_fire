//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

#include "StateIntro.h"
#include "../Utilities/Utility_Components/InputHandler.h"
#include "../Audio/AudioComponent.h"

using namespace ACOC_GameState;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Audio;

StateIntro::StateIntro()
{
	bExit = false;
}

StateIntro::~StateIntro()
{
}

void StateIntro::Initialize(SDL_Renderer* renderer)
{
}

void StateIntro::ProcessInput(SDL_Event& e)
{
	//Handles the case wherein we close the window
	ProcessSDLEvents(e);

	if(InputHandler::KeyPressedOnce(SDL_SCANCODE_ESCAPE))
		bExit = true;
}

void StateIntro::Update(GameStateHandler* engine, float deltaTime)
{
	if(!engine)
		return;

	HandleNextState(engine);
}

void StateIntro::HandleNextState(GameStateHandler* engine)
{
	if(!engine)
		return;

	if(bExit)
		engine->SetCurrentState(STATE_MAIN_MENU);
	else
		engine->SetCurrentState(STATE_INTRO);
}

void StateIntro::Draw(SDL_Renderer* renderer)
{
	if(!renderer)
		return;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
}
