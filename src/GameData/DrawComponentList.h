//Liam "AFishyFez" Wynn, 6/19/2016, An Engine of Ice and Fire

/*
 SDL has a small problem when loading textures: there's a memory
 leak. Now, this might not be a big deal for small projects.
 However, for larget projects, with constant loading and changes,
 this can be problematic.

 We rectify this issue with the DrawComponentList. Essentially,
 this list is a table of all draw components in the game. While
 memory inefficient, it allows us to load every draw component
 once, and actors use these instead of their own draw components.
 While the memory leaks will still exist, they will be contained.
*/

#ifndef AEOIAF_DRAW_COMPONENT_TABLE
#define AEOIAF_DRAW_COMPONENT_TABLE

#include "../Basic_Components/DrawableComponent.h"

namespace AEOIAF_Utilities
{
	struct DrawComponentTableNode
	{
		DrawComponentTableNode();
		~DrawComponentTableNode();

		void SetID(const char* val);
		bool CompareID(const char* compareTo);

		char* id;
		DrawableComponent* drawComponent;
		DrawComponentTableNode* next;
	};

	class DrawComponentTable
	{
		public:
			DrawComponentTable(int size = 7);
			~DrawComponentTable();

			void Insert(const char* id, DrawableComponent* component);
			DrawableComponent* GetDrawableComponent(const char* id) const;

			void Clear();

		private:
			DrawableComponent* GetDrawableComponent(const char* id, DrawComponentTableNode* head) const;
			void ClearList(DrawComponentTableNode*& head);

			int GetHashIndex(const char* toHash) const;

			DrawComponentTableNode** table;
			int tableSize;
	};
}

#endif
