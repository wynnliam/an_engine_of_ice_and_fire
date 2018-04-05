//Liam "AFishyFez" Wynn, 1/15/2016, An Engine of Ice and Fire

/*
 Nothing particularly special. However, this is the first actor
 who handles his own basic components.
*/

#ifndef AEOIAF_PROP_SIMP
#define AEOIAF_PROP_SIMP

#include "Prop.h"

namespace AEOIAF_Actor
{
	class PropSimple : public Prop
	{
        public:
            PropSimple();
            PropSimple(const char* newID);
            PropSimple(const PropSimple& toCopy);
            virtual ~PropSimple();

            PropSimple& operator = (const PropSimple& toCopy);

            void Copy(const PropSimple& toCopy);
			PropSimple* GetCopy();

			void CreateComponents();

            void Update(class AEOIAF_Level::Level* level, SDL_Event* e);

        protected:
            void CheckActivated(class AEOIAF_Level::Level* level);
            void HandleActivated(class AEOIAF_Level::Level* currentLevel, SDL_Event* e);
            void HandleDamaged(class AEOIAF_Level::Level* currentLevel, SDL_Event* e);
	};
}

#endif
