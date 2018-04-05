//Liam "AFishyFez" Wynn, 1/19/2016, A Clash of Colors

/*
 A simple factory that generates props given a string.

 At the moment, I'll use a big if-else statement. However,
 at some point I'd like to make a data structure. My plan
 will be some kind of tree perhaps that stores pointer
 functions.
*/

#ifndef ACOC_PROP_HANDLER
#define ACOC_PROP_HANDLER

#include <SDL2/SDL.h> //To use an SDL_Renderer for initialization

//Let's keep it simple and just have a forward declaration
//here instead of the real deal
namespace AEOIAF_Actor
{
	class Prop;
}

namespace AEOIAF_Utilities
{
	class DrawComponentTable;
}

namespace ACOC_GameDataHandling
{
	class PropHandler
	{
		public:
			PropHandler();
			~PropHandler();

			//The main driver for creating props
			AEOIAF_Actor::Prop* GetProp(const char* toGet,
										const AEOIAF_Utilities::DrawComponentTable& drawTable) const;
	};
}

#endif
