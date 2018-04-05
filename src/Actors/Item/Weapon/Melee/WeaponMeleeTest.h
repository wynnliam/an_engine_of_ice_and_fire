//Liam "AFishyFez" Wynn, 7/27/2015, A Clash of Colors

/*
 A test and template melee weapon. The goal with this
 is to figure out other portions of the melee weapon
 system. That is, not mouse input, but weapon movement,
 collision, and so on.
*/

#ifndef ACOC_WEAPON_MELEE_TEST
#define ACOC_WEAPON_MELEE_TEST

#include "WeaponMelee.h"

namespace AEOIAF_Actor
{
	class WeaponMeleeTest : public WeaponMelee
	{
		public:
            WeaponMeleeTest();
            WeaponMeleeTest(const char* newID);
            WeaponMeleeTest(const WeaponMeleeTest& toCopy);
            ~WeaponMeleeTest();

            WeaponMeleeTest& operator = (const WeaponMeleeTest& toCopy);

            void Copy(const WeaponMeleeTest& toCopy);

			bool IsAttackStateValid(const int toCheck);

			void CreateComponents();
			void GetAvailableAttackStates(int* outStates, int& outNumStates);

			bool IsStateIdle() const;
			bool IsStateReadyLeft() const;
			bool IsStateReadyRight() const;
			bool IsStateReadyCenter() const;
			bool IsStateAttackLeft() const;
			bool IsStateAttackRight() const;
			bool IsStateAttackCenter() const;
			bool IsStateBlockLeft() const;
			bool IsStateBlockRight() const;
			bool IsStateBlockCenter() const;

            void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);

			void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL);

			bool DidHit(Actor* toCheck);

		private:
			//Sets all data (except the draw component for the animation
			void CreateAnimationData();
			//When no animation is playing, find a new one to play
			void UpdateAnimation();
			//When we are in a swing animation, we can use this to
			//handle all logic around an attack
			void HandleSwingAnimation(int currentAnim, AEOIAF_Level::Level* level);
			//Gets list of all hit actors and tiles, and handles them
			void HandlePotentialHits(AEOIAF_Level::Level* level);

			bool CheckForDead(Actor* toCheck);
			bool CheckFoFriendlyFire(Actor* toCheck);

			//Janky temp code, please remove when rectangles are drawn properly
			AEOIAF_Utilities::DrawableComponent* rectangleRegion;
	};
}

#endif
