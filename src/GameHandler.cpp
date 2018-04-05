//Liam "AFishyFez" Wynn, 6/12/2015, A Clash of Colors

/*
 Not much to say that isn't already said in GameHandler.h.
 Please see that for more details
*/

#include "GameHandler.h"
#include "./Utilities/General_Purpose/Timer.h"
#include "./Utilities/Utility_Components/Constants.h"
#include "./Utilities/Utility_Components/InputHandler.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_Utilities;
using namespace ACOC_GameState;
using namespace std;

const int SCREEN_FPS = 60; //Our target FPS
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS; 
const int MAX_FRAMESKIP = 10;

GameHandler::GameHandler()
{
	SetName("My Game");
	Initialize();

	stateHandler.SetCurrentState(STATE_INTRO);
}

GameHandler::GameHandler(const char* name)
{
	SetName(name);
	Initialize();

	stateHandler.SetCurrentState(STATE_INTRO);
}

GameHandler::~GameHandler()
{
	if(name)
	{
		delete[] name;
		name = NULL;
	}

	Close();
}

//If toCopy is null, then set name to "My Game"
//otherwise copy toCopy into name
void GameHandler::SetName(const char* toCopy)
{
	char temp[] = "My Game"; //Use this if toCopy is null

	if(!toCopy)
	{
		name = new char[strlen(temp + 1)];
		strcpy(name, temp);
	}
	
	else
	{
		name = new char[strlen(toCopy) + 1];
		strcpy(name, toCopy);
	}
}

//Initialize SDL, the window, the renderer, and
//finally SDL_Image and SDL_TTF. If these fail,
//return false
bool GameHandler::Initialize()
{
	bool result; //The result of loading our assests

	//First initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		cout << "Failed to initialize SDL! " << SDL_GetError() << endl;
		result = false;
	}

	//Attempt to create the window
	else if(!MakeWindow())
	{
		cout << "Failed to initialize window! " << SDL_GetError()  << endl;
		result = false;
	}

	//Attempt to create the renderer
	else if((renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)) == NULL)
	{
		cout << "Failed to create renderer! " << SDL_GetError()  << endl;
		result = false;
	}

	//Allows us to use PNG files
	else if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		cout << "Failed to initialize SDL_Image! " << IMG_GetError()  << endl;
		result = false;
	}

	//Allows us to use TTF
	else if(TTF_Init() == -1)
	{
		cout << "Failed to initialize SDL_TTF! " << TTF_GetError() << endl;
		result = false;
	}

	else if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "Failed to initialize SDL_Mixer!" << Mix_GetError() << endl;
		result = false;
	}

	else
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		stateHandler.Initialize(renderer);
		result = true; //Got through all initialization!
	}

	return result;
}

//Attempt to make the window. If it is NULL
//return false. Otherwise return true
bool GameHandler::MakeWindow()
{
	window = SDL_CreateWindow(name,
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  AEOIAF_SCREEN_WIDTH,
							  AEOIAF_SCREEN_HEIGHT,
							  SDL_WINDOW_SHOWN);

	return window != NULL;
}

void do_effect(int chan, void* stream, int len, void *udata)
{
	Mix_SetPosition(chan, 90, 250);
}

//Essentially, the game's speed and the rendering are independent of eachother.
//So what happens is that we update the game at a constant 60 FPS, however, the
//rendering is done as fast as possible. If the hardware cannot handle this, then
//it drops to a slower FPS, while maintaining smooth visuals. Note that the FPS 
//should probably be set in some .INI file, or allow the user to define it somehow 
//at launch.
void GameHandler::RunLoop()
{
	bool bQuit = false; //Use this flag to determine if we want to exit the game
	uint32_t frameTicks; //The frame ticks at the current update
	Timer capTimer; //Use this to cap the frames each second so we don't go too fast
	SDL_Event eventHandler; //The event handler

	while(!bQuit)
	{
		capTimer.Start();

		//stateHandler.GrabCurrentState();

		ProcessInput(eventHandler, bQuit);
		Update(1.0f);
		Draw();

		frameTicks = capTimer.GetTicks();
		if(frameTicks < SCREEN_TICKS_PER_FRAME)
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
	}

	//I can't explain this, but without this guy, we get a stack smash. My guess
	//is that it relates the SDL threads for audio somehow
	cout << "Thanks for playing!" << endl;

	/*bool bQuit = false; //Use this flag to determine if we want to exit the game
	unsigned int nextGameTick = SDL_GetTicks();
	int loops;
	SDL_Event eventHandler; //The event handler

	while(!bQuit)
	{
		loops = 0;
		while(SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP)
		{
			//stateHandler.GrabCurrentState();

			ProcessInput(eventHandler, bQuit);
			Update(1.0f);

			nextGameTick += SCREEN_TICKS_PER_FRAME;
			++loops;
		}

		Draw();
	}*/
}

//This function is essentially just a wrapper function for the
//statHandler's ProcessInput function
void GameHandler::ProcessInput(SDL_Event& e, bool& bQuit)
{
	//Since pretty much every state would call this, or use
	//its functionality in some way, it is my belief that
	//it makes since to have this here
	InputHandler::Update();

	stateHandler.ProcessInput(e, bQuit);
}

void GameHandler::Update(float deltaTime)
{
	stateHandler.Update(deltaTime);

	//After updating the game, we need to save the previous keyboard state
	//for the next frame, so we can check things like if a key was pressed once
	InputHandler::SavePreviousKeyboardState();
}

void GameHandler::Draw()
{
	if(!renderer || !window)
		return; //Don't draw if we can't draw anywhere!

	SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
	SDL_RenderClear(renderer);

	stateHandler.Draw(renderer);

	SDL_RenderPresent(renderer);
}

//First destroy the renderer and the window if they are not NULL
//Then close all SDL subsystems
void GameHandler::Close()
{
	if(renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if(window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}

	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
