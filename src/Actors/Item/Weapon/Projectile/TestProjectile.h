//Liam "AFishyFez" Wynn, 1/16/2016, A Clash of Colors

/*
 A simple projectile whose purpose is to demonstrate
 how CreateContent works on an Actor.
*/

#ifndef ACOC_TEST_PROJECTILE
#define ACOC_TEST_PROJECTILE

#include "Projectile.h"

namespace AEOIAF_Actor
{
	class TestProjectile : public Projectile
	{
		public:
            TestProjectile();
            TestProjectile(const char* newID);
            TestProjectile(const TestProjectile& toCopy);
            ~TestProjectile();

			TestProjectile& operator= (const TestProjectile& toCopy);

			void Copy(const TestProjectile& toCopy);
			TestProjectile* GetCopy();

			void CreateComponents();
	};
}

#endif
