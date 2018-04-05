//Liam "AFishyFez" Wynn, 1/20/2016, A Clash of Colors

/*
 In any shooter game, it's important to have a means
 to... well... actually get weapons! As you can no
 doubt guess, the WeaponHander does just that. It's
 job is to simply return a copy of a weapon as specified
 by the user
*/

#ifndef ACOC_WEAPON_HANDLER
#define ACOC_WEAPON_HANDLER

#include <SDL2/SDL.h>

namespace AEOIAF_Actor
{
	class Weapon;
}

namespace AEOIAF_Utilities
{
	class DrawComponentTable;
}

namespace ACOC_GameDataHandling
{
	class WeaponHandler
	{
		public:
			WeaponHandler();
			~WeaponHandler();

			//The main driver for getting weapons
			AEOIAF_Actor::Weapon* GetWeapon(const char* toGet, const AEOIAF_Utilities::DrawComponentTable& drawTable) const;

		private:
	};
}

#endif
