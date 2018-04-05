//Liam "AFishyFez" Wynn, 4/21/2015, AEOIAF: Collision Component

/*
Primarily used for actors, the collision component
determines if an actor has collided with other actors,
wall tiles, projectiles, tracers, or really anything
that involves a collision.
*/

#ifndef AEOIAF_COLLIDE_COMPONENT
#define AEOIAF_COLLIDE_COMPONENT

#include "../Utilities/Utility_Components/AxisAllignedBoundingBox.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Level
{
    class Level;
}

namespace AEOIAF_Utilities
{
	class Vector;
	class Tracer;

    class CollisionComponent
    {
        public:
            CollisionComponent();
            CollisionComponent(const unsigned int width, const unsigned int height)
                              : aabb(0, 0, width, height) {}
            CollisionComponent(const CollisionComponent& toCopy);
            virtual ~CollisionComponent();

            CollisionComponent& operator = (const CollisionComponent& toCopy);

            AxisAllignedBoundingBox GetBoundingBox() const { return aabb; }
            void SetBoundingBox(const AxisAllignedBoundingBox& val) { aabb = val; }

            void Copy(const CollisionComponent& toCopy);
            virtual CollisionComponent* GetCopy();

            //Will check if the player has collided with a wall in the level
            //(ignores other actors), position being the position of the actor
            virtual bool CollidesWithWall(AEOIAF_Level::Level* level, const Vector& position) const;
			//Determines if toCheck and aabb collide
			virtual bool Contains(AEOIAF_Utilities::AxisAllignedBoundingBox& toCheck) const;
			//Determine if this collision component contains toCheck. The current position
            //is the position of the movable component of the actor that also uses this as
            //it's collision component
            virtual bool Contains(const Vector& currentPosition, AEOIAF_Utilities::AxisAllignedBoundingBox& toCheck) const;
			//Determine if this collision component intersects wth the tracer. The current
			//position is the position of the movable component of the actor that also uses
			//this collision component
			virtual bool Contains(const Vector& currentPosition, const Tracer& tracer) const;

        private:
            //This is the main collision component, and the one
            //we use to check collisions with other objects
            AEOIAF_Utilities::AxisAllignedBoundingBox aabb;
    };
}

#endif
