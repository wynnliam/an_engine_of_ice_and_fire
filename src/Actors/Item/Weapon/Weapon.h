//Liam "AFishyFez" Wynn, 7/25/2015, A Clash of Colors

/*
 At the top of the Weapon sub-hierarchy, we have the Weapon
 abstract base class. Extending from this are (as of writing
 this) the Melee, Projectile, and Tracer classes. Like Weapon,
 these are also abstract base classes. For more info on those
 specifically, please see the .h files for those classes.

 Here is the general rule of thumb for weapons: beyond some
 very basic and common things, specific weapon implementation
 is handled in each weapon class. That is, the only thing the
 Melee class would handle is checking for input for different
 melee attack types. Whether or not each melee weapon type handles
 these is entirely up to them. The parent class will make no
 assumptions in this regard.

 So if this class doesn't really handle anything specific to
 a Weapon, then what is the point of its existence? Primarily,
 this class is meant to act as a means to group all weapon
 items in a similar category. That way when something like an
 inentory comes into play, we can easily store/sort all weapons.
*/

#ifndef ACOC_WEAPON
#define ACOC_WEAPON

#include "../Item.h"
#include "../../../Utilities/General_Purpose/Timer.h"

#define WEP_TYPE_PROJ	1
#define WEP_TYPE_TRCR	2
#define WEP_TYPE_MLEE	3

namespace AEOIAF_Level
{
	class Tile;
}

namespace AEOIAF_Actor
{
	class Weapon : public Item
	{
		public:
            Weapon();
            Weapon(const char* newID);
            Weapon(const Weapon& toCopy);
            virtual ~Weapon();

			int GetFireRate() const { return fireRate; }
			void SetFireRate(int val) { fireRate = val; }

			bool IsRecharging() const { return bIsRecharging; }

			bool WantToFire() const { return bWantToFire; }
			void SetWantToFire(const bool val) { bWantToFire = val; }

			int GetWeaponType() const { return weaponType; }

			float GetPrefMinFightDist() const { return prefMinDist; }
			void SetPrefMinFightDist(const float val) { prefMinDist = val; }

			float GetPrefMaxFightDist() const { return prefMaxDist; }
			void SetPrefMaxFightDist(const float val) { prefMaxDist = val; }

            virtual Weapon& operator = (const Weapon& toCopy);

            virtual void Copy(const Weapon& toCopy);
			virtual Weapon* GetCopy();

			//When you've fire your weapon, we need to start the timer
			void StartFireRateTimer();

			virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);

			//Determines if this weapon hit toCheck
			virtual bool DidHit(Actor* toCheck);
			virtual bool DidHit(AEOIAF_Level::Tile* toCheck);

            virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);

		protected:
			void SetPositionToOwnerPosition();

			int fireRate; //The rate at which we can fire a weapon
			
			//Basically a bit of info for the AI to make decisions about his
			//weapon and prefered fighting range
			int weaponType;

		private:
			//Reset currentRechargeTime, and bIsRecharging to a state
			//that allows us to fire our gun again
			void Reset();

			AEOIAF_Utilities::Timer fireRateTimer;
			bool bIsRecharging; //Are we waiting to fire again?
			//Use this to determine if we want to fire the weapon.
			//This enables the owner, AI or not, to set when they
			//want to fire
			bool bWantToFire;
			int currentRechargeTime; //A number that counts down until it reaches 0. After 0, we may fire again

			//For AI mainly. Describe the region for preffered fighting distance
			//an AI would like to be in to use this weapon
			float prefMinDist, prefMaxDist;
	};
}

#endif
