#include "InputHandler.h"

using namespace AEOIAF_Utilities;

//static member variables need to be defined outside of the class
Vector InputHandler::mousePos = Vector(0, 0);

bool InputHandler::bLftMouseClick = false;
bool InputHandler::bRgtMouseClick = false;
bool InputHandler::bPrvLftMouseClick = false;
bool InputHandler::bPrvRgtMouseClick = false;

uint8_t* InputHandler::currentKeyState = NULL;
uint8_t* InputHandler::previousKeyState = NULL;

void InputHandler::Update()
{
	//Store the result of GetMouseState in these
	int mouseX, mouseY;

    SDL_PumpEvents();
    currentKeyState = const_cast<uint8_t*>(SDL_GetKeyboardState(NULL));

    SDL_GetMouseState(&mouseX, &mouseY);
    mousePos.SetX(mouseX);
	mousePos.SetY(mouseY);

	bLftMouseClick = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
    bRgtMouseClick = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
}

bool InputHandler::KeyPressed(SDL_Scancode code)
{
    if(!currentKeyState)
		return false;

    return currentKeyState[code];
}

bool InputHandler::KeyPressedOnce(SDL_Scancode code)
{
    if(!currentKeyState|| !previousKeyState) 
		return false;

	bool result;
    bool bCurrentKey = currentKeyState[code];
    bool bPreviousKey = previousKeyState[code];

    if(bCurrentKey && !bPreviousKey)
        result = true;
	else
		result = false;

    return result;
}

//If previous keyboard state is not NULL, then deallocate it.
//Then copy the values of current key state into previous.
void InputHandler::SavePreviousKeyboardState()
{
	if(!currentKeyState)
		return;

	if(previousKeyState)
		delete[] previousKeyState;

    //This is an absolute shit way to do it, but whatever:
    //According to this: https://wiki.libsdl.org/SDLScancodeLookup
    //There are 282 SDL scan codes

    const int NUM_SCAN_CODES = 282;
    previousKeyState = new uint8_t[NUM_SCAN_CODES];

	for(int i = 0; i < NUM_SCAN_CODES; ++i)
		previousKeyState[i] = currentKeyState[i];

    bPrvLftMouseClick = bLftMouseClick;
    bPrvRgtMouseClick = bRgtMouseClick;
}
