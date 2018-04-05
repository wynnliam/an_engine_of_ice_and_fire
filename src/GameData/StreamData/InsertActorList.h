//Liam "AFishyFez" Wynn, 3/9/2016, A Clash of Colors

/*
 When you stream levels, any modifications to the level
 are not retained. This includes any actors that may have
 been added to the level after loading.

 We can rectify this situation by keeping a list of actors
 that were inserted into the level after loading.

 We will use an AVL tree to handle this.
*/

#ifndef ACOC_INSERT_ACTOR_LIST
#define ACOC_INSERT_ACTOR_LIST

#include <SDL2/SDL.h>
#include "../../Utilities/Utility_Components/Vector.h"

namespace AEOIAF_Actor
{
	class Actor;
}

namespace AEOIAF_Level
{
	class Level;
}

namespace ACOC_GameDataHandling
{
	class GameDataHandler;

	class InsertActorList
	{
		public:
			InsertActorList();
			~InsertActorList();

			int Insert(const char* toAdd, const AEOIAF_Utilities::Vector& pos);
			int Remove(const char* toRemove);
			void Clear();

			void AddActorsToLevel(AEOIAF_Level::Level* level, const GameDataHandler& dataHandler) const;

		private:
			int Insert(int key, const char* toAdd, const AEOIAF_Utilities::Vector& pos,
					   struct InsertActorNode*& root);
			int Remove(int key, const char* toRemove, struct InsertActorNode*& root);
			void Display(struct InsertActorNode* root) const;
			void Clear(struct InsertActorNode*& root);

			void AddActorsToLevel(const struct InsertActorNode* root, AEOIAF_Level::Level* level,
								  const GameDataHandler& dataHandler) const;

			/*BALANCING UTILITIES*/
			//If root is unbalanced, we balance it
			void Rebalance(struct InsertActorNode*& root);
			//Determines if a tree is balanced or not
			bool IsBalanced(struct InsertActorNode* toCheck);

			/*ROTATION UTILITIES*/
			void LeftRotation(struct InsertActorNode*& root);
			void RightRotation(struct InsertActorNode*& root);

			/*UTILITY FUNCTIONS*/
			//Given a string, hash it and return a key
			int GetHashVal(const char* toHash) const;
			//Calculate the new height of a subtree
			void RecalculateHeight(struct InsertActorNode* root);
			//Return the height of a subtree
			int GetSubtreeHeight(struct InsertActorNode* subtree);
			//Returns the child of subtree wit the longer path
			struct InsertActorNode* GetChildLongestPath(struct InsertActorNode* subtree);

			//Given an actor id, return an actor
			char* GetActorFromID(const char* actorID) const;
			//Inserts an actor into a level
			void InsertActorIntoLevel(AEOIAF_Actor::Actor* actor, const char& actorType,
									  AEOIAF_Level::Level* level) const;

			struct InsertActorNode* root;
	};

	struct InsertActorNode
	{
		InsertActorNode();
		~InsertActorNode();

		bool IsLeaf();
		void SetAsInOrderSuccessor();

		int key;

		char* data;
		AEOIAF_Utilities::Vector position;

		int height;

		InsertActorNode* left;
		InsertActorNode* right;
	};
}

#endif
