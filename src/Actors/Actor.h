//Liam "AFishyFez" Wynn, 4/11/2015, AEOIAF: Actor

/*
The big ticket item. Basically, every interactive
thing in the game except HUD, menu, and levels extend
from this puppy.
*/

#ifndef AEOIAF_ACTOR
#define AEOIAF_ACTOR

#include "../Basic_Components/DrawableComponent.h"
#include "../Basic_Components/MoveableComponent.h"
#include "../Basic_Components/CollisionComponent.h"
#include "../Utilities/General_Purpose/Matrix.h"
#include "../Utilities/Utility_Components/Vector.h"

namespace AEOIAF_Level
{
    class Level;
}

namespace AEOIAF_Utilities
{
	class Tracer;
}

namespace AEOIAF_Actor
{
    class Actor
    {
        public:
            Actor();
            Actor(const char* newID);
            Actor(const Actor& toCopy);
            virtual ~Actor();

            virtual Actor& operator = (const Actor& toCopy);

            //Returns 0 if the ID is NULL
            int GetID(char*& copyTo) const;
            //Returns 0 if the newID is NULL
            int SetID(const char* newID);

            //Returns 0 if the name is NULL
            int GetName(char*& copyTo) const;
            //Returns 0 if the newName is NULL
            int SetName(const char* newName);

            void SetDrawableComponent(AEOIAF_Utilities::DrawableComponent* draw);
            void SetMovableComponent(AEOIAF_Utilities::MovableComponent* mov);
            void SetCollisionComponent(AEOIAF_Utilities::CollisionComponent* col);
            
			bool IsPossessed() const;
			void SetIsPossessed(const bool val);

			bool MustDestroy() const;
			void SetMustDestroy(const bool val);

			int GetWidth() const;
			int GetHeight() const;

			//Returns 0 of the movable component is NULL
            int GetPosition(AEOIAF_Utilities::Vector& result) const;
			//Make this virtual because particle emitters need to override this
			//to handle the extra particle move component
            virtual int SetPosition(const AEOIAF_Utilities::Vector& val);

			float GetRotation() const;
			void SetRotation(float val);

			AEOIAF_Content::AEOIAFColor GetColor() const { return color; }
			virtual void SetColor(const AEOIAF_Content::AEOIAFColor& val) { color = val; }

			//Copies the properties of toCopy into this actor
            virtual void Copy(const Actor& toCopy);
			//Creates a copy of this actor and returns it
			virtual Actor* GetCopy();

			//Determines if we collide with another actor
			virtual bool CollidesWith(Actor* toCheck) const;
			//Determines if our collision component collides with toCheck
			virtual bool CollidesWith(AEOIAF_Utilities::AxisAllignedBoundingBox& toCheck) const;
			//Determines if our collision component collides with tracer
			virtual bool CollidesWith(const AEOIAF_Utilities::Tracer& tracer) const;

			//Makes the actor face a vector
			void LookAt(AEOIAF_Utilities::Vector& lookAt);
            
			//When called, will handle the logic of damaging this actor
			virtual void DoDamage(Actor* instigator, const float damage);

			//Displays the character data in the console
			virtual void Display();
            //Will return if compareTo is equal to the id here
            bool CompareID(const char* compareTo);

			//Since actors manage their own components, we can override this function
			//to create all the components
			virtual void CreateComponents();

            //Update the actor
            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            //Draw the actor
            virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);

        protected:
            char* name;
            char* id;

            AEOIAF_Utilities::DrawableComponent* drawableComponent;
            AEOIAF_Utilities::MovableComponent* movableComponent;
            AEOIAF_Utilities::CollisionComponent* collisionComponent;

			//A flag to tell us if an active scripted sequence is possessing
			//this actor
			bool bIsPossessed;
			//A flag to tell us if this actor needs to be deallocated. How this
			//is handled, if it is, is context depended. I'd suggest looking at
			//the level data structures
			bool bMustDestroy;

			/*DRAWABLE COMPONENT OVERRIDE PROPERTIES*/
			float rotation;
			AEOIAF_Content::AEOIAFColor color;
    };
}

#endif // AEOIAF_ACTOR
