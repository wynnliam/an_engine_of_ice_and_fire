#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <stdint.h>
#include <algorithm>
#include <SDL2/SDL.h>
#include "Vector.h"

using namespace std;

namespace AEOIAF_Utilities
{
    class InputHandler
    {
        public:
            static void Update();

            static Vector GetMousePosition() { return mousePos; }

            static bool GetMouseLeftClick() { return bLftMouseClick; }
            static bool GetMouseRightClick() { return bRgtMouseClick; }
            static bool GetMouseLeftClickOnce() { return bLftMouseClick && !bPrvLftMouseClick; }
            static bool GetMouseRightClickOnce() { return bRgtMouseClick && !bPrvRgtMouseClick; }

            static bool KeyPressed(SDL_Scancode code);
            static bool KeyPressedOnce(SDL_Scancode code);

            static void SavePreviousKeyboardState();

        private:
            static Vector mousePos;
            static bool bLftMouseClick, bRgtMouseClick;
            static bool bPrvLftMouseClick, bPrvRgtMouseClick;
            static uint8_t* currentKeyState;
            static uint8_t* previousKeyState;
    };
}

#endif // INPUTHANDLER_H
