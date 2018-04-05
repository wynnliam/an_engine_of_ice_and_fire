//Liam "AFishyFez" Wynn, 1/17/2016, A Clash of Colors

/*
 A very simple class demonstrating the bare-bones neccessities
 for a simple Tracer Weapon
*/

#ifndef ACOC_TEST_WEAPON_TRACER
#define ACOC_TEST_WEAPON_TRACER

#include "WeaponTracer.h"

namespace AEOIAF_Actor
{
	class TestWeaponTracer : public WeaponTracer
	{
		public:
            TestWeaponTracer();
            TestWeaponTracer(const char* newID);
            TestWeaponTracer(const TestWeaponTracer& toCopy);
            ~TestWeaponTracer();

            TestWeaponTracer& operator = (const TestWeaponTracer& toCopy);

            void Copy(const TestWeaponTracer& toCopy);
			TestWeaponTracer* GetCopy();

			void CreateComponents();

			bool DidHit(Actor* toCheck);

		private:
			bool CheckForDead(Actor* toCheck);
			bool CheckFoFriendlyFire(Actor* toCheck);
	};
}

#endif
