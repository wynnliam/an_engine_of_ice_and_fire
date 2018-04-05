//Liam "AFishyFez" Wynn, 9/24/2015, A Clash of Colors

/*
 Projectile weapons are pretty self-explanatory.
 Essentially, upon firing, a projectile is created.
 The interesting thing to note is that a Projectile
 Weapon essentially just creates the projectile and
 adds it to a queue. Collision handling is done via
 the Projectile Queue, as well as updating/drawing each
 projectile.
*/

#ifndef ACOC_WEAPON_PROJECTILE
#define ACOC_WEAPON_PROJECTILE

#include "../Weapon.h"
#include "Projectile.h"

namespace AEOIAF_Actor
{
	struct ProjectileQueueNode
	{
		ProjectileQueueNode();
		~ProjectileQueueNode();		

		Projectile* projectile;
		ProjectileQueueNode* next;
	};

	class ProjectileQueue
	{
		public:
			ProjectileQueue();
			~ProjectileQueue();

			void Enqueue(Projectile* toAdd);
			void Dequeue();
			void Clear();

			bool IsEmpty() { return rear == NULL; }

            void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            
			//Returns if the actor was hit by any projectile in the queue
			bool HitActor(AEOIAF_Actor::Actor* toCheck);
			//Returns if the tile was hit by any projectile in the queue
			bool HitTile(AEOIAF_Level::Tile* toCheck);

			void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL);
			

		private:
			ProjectileQueueNode* rear;
	};

	class WeaponProjectile : public Weapon
	{
		public:
            WeaponProjectile();
            WeaponProjectile(const char* newID);
            WeaponProjectile(const WeaponProjectile& toCopy);
            virtual ~WeaponProjectile();

			Projectile* GetProjectileType() { return projectileType; }
			void SetProjectileType(Projectile* val);
            
			virtual WeaponProjectile& operator = (const WeaponProjectile& toCopy);

            virtual void Copy(const WeaponProjectile& toCopy);
			virtual WeaponProjectile* GetCopy();
            
			//Initializes the collision component and the draw component
			virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            
			virtual void HandlePotentialHits(AEOIAF_Level::Level* level);		
			virtual bool DidHit(Actor* toCheck);
			virtual bool DidHit(AEOIAF_Level::Tile* toCheck);

			virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);

		protected:
			virtual bool FiredWeapon();
			
			virtual void MakeProjectile();
			//Handles the creation of a projectile's movable component
			virtual AEOIAF_Utilities::MovableComponent* MakeProjectileMovableComponent();

			ProjectileQueue projectiles; //Where we keep all active projectiles
			Projectile* projectileType; //Essentially what we'll make a copy of each time we fire
			SDL_Renderer* projectileRenderer; //Use this to initialize all projectiles when we fire
	};
}


#endif
