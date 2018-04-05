//Liam "AFishyFez" Wynn, 1/25/2016, A Clash of Colors

/*
 A simple class whose job is to handle transitions from
 one level to another. In essence, the process goes like
 this: Player interacts with door. Door sets the NextLevel
 flag for the current level. After updating, the current
 level looks at this flag. If it isn't NULL, we close
 ourselves down and have the data handler open that new
 level.
*/

#ifndef ACOC_PROP_DOOR
#define ACOC_PROP_DOOR

#include "../Prop.h"

namespace AEOIAF_Actor
{
	class PropDoor : public Prop
	{
		public:
            PropDoor();
            PropDoor(const char* newID);
            PropDoor(const PropDoor& toCopy);
            virtual ~PropDoor();

            PropDoor& operator = (const PropDoor& toCopy);

			char* GetNextLevelName() { return nextLevelName; }
			bool SetNextLevelName(const char* val);

            void Copy(const PropDoor& toCopy);
			PropDoor* GetCopy();

			void CreateComponents();

            void Update(class AEOIAF_Level::Level* level, SDL_Event* e);

        protected:
            void CheckActivated(class AEOIAF_Level::Level* level);
            void HandleActivated(class AEOIAF_Level::Level* currentLevel, SDL_Event* e);
            void HandleDamaged(class AEOIAF_Level::Level* currentLevel, SDL_Event* e);

			char* nextLevelName; //Stores the level we will go to when we activate this prop
	};
}

#endif
