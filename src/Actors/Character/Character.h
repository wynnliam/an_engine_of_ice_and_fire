//Liam "AFishyFez" Wynn, 4/15/2015, AEOIAF: Character

/*
This is where the Character class is handled.
Characters, children of Actors, are one of the
most important components to a game. In sum, these
are the guys/gals/players that interact with the world.
Both NPCs and Player extend from this.
*/

#ifndef AEOIAF_CHARACTER
#define AEOIAF_CHARACTER

#include "../Actor.h"

using namespace AEOIAF_Actor;

namespace AEOIAF_Actor
{
	//Items include Characters. So if we include
	//those here, we'd have a nasty loop. So just
	//do a forward declaration instead
	class Weapon;
	class Shield;

    class Character : public Actor
    {
        public:
            Character();
            Character(const char* newID);
            Character(const Character& toCopy);
            virtual ~Character();

            virtual Character& operator = (const Character& toCopy);

            virtual void Copy(const Character& toCopy);
			virtual Character* GetCopy();

			Weapon* GetEquippedWeapon() { return equippedWeapon; }
			virtual void SetEquippedWeapon(Weapon* val);

			Shield* GetEquippedShield() { return equippedShield; }
			virtual void SetEquippedShield(Shield* val);

			//Determines if we collide with another actor
			virtual bool CollidesWith(Actor* toCheck) const;
			//Determines if our collision component collides with toCheck
			virtual bool CollidesWith(AEOIAF_Utilities::AxisAllignedBoundingBox& toCheck) const;
			//Determines if our collision component collides with tracer
			virtual bool CollidesWith(const AEOIAF_Utilities::Tracer& tracer) const;

            //Update the actor
            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            //Draw the actor
            virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);

        protected:
            //Handles collision with walls
            virtual void HandleWallCollisions(AEOIAF_Level::Level* level);
			//Returns if the equipped shield was hit
			bool HitShield(Actor* toCheck) const;
			bool HitShield(const AEOIAF_Utilities::Tracer& tracer) const;

            //This will store the character's current position into previous position
            void SavePreviousPosition();
            //Will reset the movableComponent's position back to the previous position
            void ResetPosition();

            AEOIAF_Utilities::Vector previousPosition; //The previous position of the actor

			//Characters will have equipped items and shields, representing their inventory
			Weapon* equippedWeapon;
			Shield* equippedShield;
    };
}

#endif // AEOIAF_CHARACTER
