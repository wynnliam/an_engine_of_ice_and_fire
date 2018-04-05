//Liam "AFishyFez" Wynn, 5/4/2015, AEOIAF: NPC

/*
Here we have the prototype for the base class of all non player
characters (NonPlayer). Arguably, this is one of the most important
classes to have in a single player engine such as this.
*/

#ifndef AEOIAF_NON_PLAYER
#define AEOIAF_NON_PLAYER

#include "Character.h"
#include "../../Utilities/AI_Utilities/SteeringHandler.h"

namespace AEOIAF_Actor
{
    class NonPlayer : public Character
    {
        public:
            NonPlayer();
            NonPlayer(const char* newID);
            NonPlayer(const NonPlayer& toCopy);
            virtual ~NonPlayer();

            virtual NonPlayer& operator = (const NonPlayer& toCopy);

            virtual void Copy(const NonPlayer& toCopy);
            virtual NonPlayer* GetCopy();

            //Update the actor
            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
			//Draw thy actor
			virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
							  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
							  AEOIAF_Utilities::Matrix* matrix = NULL);


        protected:
            //Use this for natural movement
            AEOIAF_AIBehavior::SteeringHandler steeringHandler;
    };
}

#endif // AEOIAF_NON_PLAYER
