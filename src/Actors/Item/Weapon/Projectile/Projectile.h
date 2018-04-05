//Liam "AFishyFez" Wynn, 9/25/2015, A Clash of Colors

/*
 Projectiles are what Projectile Weapons fire. Essentially
 The goal of the Projectile is to move forward until it's
 destroyed (ie: collides with something or goes too far).
 However, this behavior may change depending on the behavior
 needed for particular Weapon.
*/

#ifndef ACOC_PROJECTILE
#define ACOC_PROJECTILE

#include "../../../Actor.h"

namespace AEOIAF_Actor
{
	class Projectile : public Actor
	{
		public:
            Projectile();
            Projectile(const char* newID);
            Projectile(const Projectile& toCopy);
            virtual ~Projectile();

			virtual Projectile& operator= (const Projectile& toCopy);

			virtual void Copy(const Projectile& toCopy);
			virtual Projectile* GetCopy();

            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
			//Simply adjusts the projectile to be originating at the center
			virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
							  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
							  AEOIAF_Utilities::Matrix* matrix = NULL);
		protected:
	};
}

#endif
