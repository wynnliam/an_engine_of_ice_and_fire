//Liam "AFishyFez" Wynn, 6/12/2015, A Clash of Colors

/*
 The Game Handler is the main driver for the game (of course).
 Here we will handle the game loop itself. However, we will also
 maintain a stack of GameStates. GameStates will NOT handle specific
 states within the game itself. Please see GameState.h for more
 info.
*/

#ifndef ACOC_GAME_HANDLER
#define ACOC_GAME_HANDLER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameStateHandler.h"

class GameHandler
{
	public:
		GameHandler();
		GameHandler(const char* name);
		~GameHandler();

		//Sets the name to whatever is given
		void SetName(const char* toCopy);

		//The entry point for the game loop
		void RunLoop();

	private:
		//Initialize SDL and all of our graphics/audio
		bool Initialize();
		//So the initialize code isn't so gross.
		//Simply return if creating the window worked
		//or not
		bool MakeWindow();
		//Call these each frame
		void ProcessInput(SDL_Event& e, bool& bQuit);
		void Update(float deltaTime);
		void Draw();
		//Close down SDL and its subsystems
		void Close();
	
		//The game name
		char* name;
		//SDL content for drawing
		SDL_Window* window; //The window the user will see
		SDL_Renderer* renderer; //Use this for drawing

		//Use this to update the correct state each frame
		ACOC_GameState::GameStateHandler stateHandler;
};

#endif
