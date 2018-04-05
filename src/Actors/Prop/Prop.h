//Liam "AFishyFez" Wynn, 4/24/2015, AEOIAF: Prop

/*
A level is not complete if it only has characters
and tiles. Somethings in the world, like interactive
non-character actors, cannot be represented as a tile
or character (hence being a 'non-character'). This is
where a prop comes in.
*/

#ifndef AEOIAF_PROP
#define AEOIAF_PROP

#include "../Actor.h"

namespace AEOIAF_Actor
{
    class Prop : public Actor
    {
        public:
            Prop();
            Prop(const char* newID);
            Prop(const Prop& toCopy);
            virtual ~Prop();

            virtual Prop& operator = (const Prop& toCopy);

            bool IsActive() const { return bIsActive; }
            void SetIsActive(bool val) { bIsActive = val; }

            bool IsDamaged() const { return bDamaged; }
            void SetIsDamaged(bool val) { bDamaged = val; }

            float GetMaxActivateDist() const { return maxActivateDist; }
            void SetMaxActivateDist(float val) { maxActivateDist = val; }

            virtual void Copy(const Prop& toCopy);
			virtual Prop* GetCopy();

			virtual void CreateComponents();

            virtual void Update(class AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);

        protected:
            virtual void CheckActivated(class AEOIAF_Level::Level* level);
            virtual void HandleActivated(class AEOIAF_Level::Level* currentLevel, SDL_Event* e);
            virtual void HandleDamaged(class AEOIAF_Level::Level* currentLevel, SDL_Event* e);

            bool bIsActive; //If the NPC/player activates (presses 'E' on the prop)
            bool bDamaged; //If a character damaged the prop

            //The maximum distance the player can be from the prop and still activate it
            float maxActivateDist;
    };
}

#endif // AEOIAF_PROP
