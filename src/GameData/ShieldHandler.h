//Liam "AFishyFez" Wynn, 1/20/2016, A Clash of Colors

/*
 Specific to ACOC, we store shields here.
*/

#ifndef ACOC_SHIELD_HANDLER
#define ACOC_SHIELD_HANDLER

#include <SDL2/SDL.h>

namespace AEOIAF_Actor
{
	class Shield;
}

namespace AEOIAF_Utilities
{
	class DrawComponentTable;
}

namespace ACOC_GameDataHandling
{
	class ShieldHandler
	{
		public:
			ShieldHandler();
			~ShieldHandler();

			AEOIAF_Actor::Shield* GetShield(const char* toGet,
											const AEOIAF_Utilities::DrawComponentTable& table) const;
	};
}

#endif
