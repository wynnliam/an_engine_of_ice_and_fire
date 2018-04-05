//Liam "AFishyFez" Wynn, 1/16/2015, A Clash of Colors

/*
 Here we have a test shield. The goal is to demonstrate loading
 all components for a shield
*/

#ifndef ACOC_TEST_SHIELD
#define ACOC_TEST_SHIELD

#include "Shield.h"

namespace AEOIAF_Actor
{
	class TestShield : public Shield
	{
		public:
            TestShield();
            TestShield(const char* newID);
            TestShield(const TestShield& toCopy);
            ~TestShield();

            TestShield& operator = (const TestShield& toCopy);

            void Copy(const TestShield& toCopy);
			TestShield* GetCopy();

			void CreateComponents();
	};
}

#endif
