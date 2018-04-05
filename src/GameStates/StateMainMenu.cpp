//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

#include "StateMainMenu.h"

using namespace ACOC_GameState;
using namespace ACOC_UIElements;

StateMainMenu::StateMainMenu()
{
}

StateMainMenu::~StateMainMenu()
{
}

void StateMainMenu::Initialize(SDL_Renderer* renderer)
{
	if(!renderer)
		return;

	mainMenu.SetBackground(gameDataHandler->GetDrawableComponent("ACOC_MAIN_MENU_BACKGROUND"));
	mainMenu.SetMenuComponentDrawComponent(gameDataHandler->GetDrawableComponent("ACOC_MAIN_MENU_PLAY_DRAW"), 0);
}

void StateMainMenu::ProcessInput(SDL_Event& e)
{
	//We need to check if the window is closed
	ProcessSDLEvents(e);

	mainMenu.ProcessInput(e);
}

void StateMainMenu::Update(GameStateHandler* engine, float deltaTime)
{
	if(!engine)
		return;

	mainMenu.Update();

	HandleNextState(engine);
}

void StateMainMenu::HandleNextState(GameStateHandler* engine)
{
	if(!engine)
		return;

	if(mainMenu.IsPlayClicked())
		engine->SetCurrentState(STATE_IN_TOP_DOWN);
	else
		engine->SetCurrentState(STATE_MAIN_MENU);
}

void StateMainMenu::Draw(SDL_Renderer* renderer)
{
	if(!renderer)
		return;

	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderClear(renderer);

	mainMenu.Draw(renderer);
}
