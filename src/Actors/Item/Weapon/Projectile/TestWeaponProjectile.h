//Liam "AFishyFez" Wynn, 1/16/2016, A Clash of Colors

/*
 A simple projectile weapon that demonstrates how to make
 CreateComponents in a projectile weapon
*/

#ifndef ACOC_TEST_WEAPON_PROJECTILE
#define ACOC_TEST_WEAPON_PROJECTILE

#include "WeaponProjectile.h"

namespace AEOIAF_Actor
{
	class TestWeaponProjectile : public WeaponProjectile
	{
		public:
            TestWeaponProjectile();
            TestWeaponProjectile(const char* newID);
            TestWeaponProjectile(const TestWeaponProjectile& toCopy);
            ~TestWeaponProjectile();
            
			TestWeaponProjectile& operator = (const TestWeaponProjectile& toCopy);

            void Copy(const TestWeaponProjectile& toCopy);
			TestWeaponProjectile* GetCopy();
			
			void CreateComponents();

			bool DidHit(Actor* toCheck);

		private:
			bool CheckForDead(Actor* toCheck);
			bool CheckFoFriendlyFire(Actor* toCheck);
	};
}

#endif
