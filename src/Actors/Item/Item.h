//Liam "AFishyFez" Wynn, 7/25/2015, A Clash of Colors

/*
 In A Clash of Colors (and in many games, including top down ones),
 the player and NPCs will have items attached to them. This includes
 things like shields, armors, and weapons. Everything within the
 item sub-hierarchy represents these things. In ACOC, all items will
 eventually be either a shield, armor, or a weapon.
*/

#ifndef AEOIAF_ITEM
#define AEOIAF_ITEM

#include "../Actor.h"
#include "../Character/Character.h"

namespace AEOIAF_Actor
{
	class Item : public Actor
	{
		public:
            Item();
            Item(const char* newID);
            Item(const Item& toCopy);
            virtual ~Item();

            virtual Item& operator = (const Item& toCopy);

            virtual void Copy(const Item& toCopy);
			virtual Item* GetCopy();

			Character* GetOwner() const { return owner; }
			void SetOwner(Character* val) { owner = val; }

			//Determines if we collide with another actor
			virtual bool CollidesWith(Actor* toCheck) const;
			//Determines if our collision component collides with toCheck
			virtual bool CollidesWith(AEOIAF_Utilities::AxisAllignedBoundingBox& toCheck) const;
			//Determines if our collision component collides with tracer
			virtual bool CollidesWith(const AEOIAF_Utilities::Tracer& tracer) const;
            
			virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);

		protected:
			Character* owner; //The character who owns this weapon
	};
}

#endif
