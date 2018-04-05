//Liam "AFishyFez" Wynn, 3/16/2016, An Engine of Ice and Fire

/*
 The version of SDL I use has memory leaks when a level's draw
 component closes. While on its own, this isn't a problem, such
 leaks do add up.

 The way I will rectify this issue is by keeping a list of level
 draw components. Basically, when a level closes, we preserve its
 draw component here. As we open up levels, we can access the
 needed draw component here as well.

 As an added bonus, by having this list, we can maintain draw
 components that levels might share. In this way, we can save on
 memory overhead, in addition to making mitigating the memory
 leaks.
*/

#ifndef AEOIAF_LEVEL_DRAW_COMPONENT_LIST
#define AEOIAF_LEVEL_DRAW_COMPONENT_LIST

#include "LevelDrawComponent.h"

namespace AEOIAF_Level
{
	class LevelDrawComponentList
	{
		public:
			LevelDrawComponentList();
			~LevelDrawComponentList();

			//Inserts a new level draw component into the list
			void Insert(LevelDrawComponent* toInsert);
			//Determine if any level draw component has the same
			//texture path as texturePath
			bool Contains(const char* texturePath) const;
			//Return the component with the given texture path
			LevelDrawComponent* GetComponent(const char* texturePath) const;
			//Clear the list
			void Clear();

		private:
			/*UTILITY FUNCTIONS*/
			bool Compare(const struct LevelDrawComponentNode* node,
						 const char* texturePath) const;

			struct LevelDrawComponentNode* head;
	};

	struct LevelDrawComponentNode
	{
		LevelDrawComponentNode();
		~LevelDrawComponentNode();

		LevelDrawComponent* component;
		LevelDrawComponentNode* next;
	};
}

#endif
