//Liam "AFishyFez" Wynn, 1/18/2016, A Clash of Colors

/*
 The CharacterHandler is a simple factory that, given a string,
 will return the associating character.

 For now, we can have it simply use a series of if-else statements.
 However, in the future, I'd like to have a data structure of some
 kind.
*/

#ifndef ACOC_CHARACTER_HANDLER
#define ACOC_CHARACTER_HANDLER

#include <SDL2/SDL.h>

//Use a forward declaration for now, and the
//real deal in the .cpp file
namespace AEOIAF_Actor
{
	class Character;
}

namespace AEOIAF_Utilities
{
	class DrawComponentTable;
}

namespace ACOC_GameDataHandling
{
	class CharacterHandler
	{
		public:
			CharacterHandler();
			~CharacterHandler();

			//The main driver for our character factory
			AEOIAF_Actor::Character* GetCharacter(const char* toGet, const AEOIAF_Utilities::DrawComponentTable& drawTable) const;
	};
}

#endif
