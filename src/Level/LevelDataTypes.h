//Liam "AFishyFez" Wynn, 4/23/2015, AEOIAF: Level Data Types

/*
 The classes stored here are basically data structures that hold all the
 various actors that appear in a level (props, characters, weapons, etc).
 I felt it would be wise to keep them all here in a separate area from
 the Level class itself, for cleanliness.
*/

#ifndef AEOIAF_LEVEL_DATA_TYPES
#define AEOIAF_LEVEL_DATA_TYPES

#include <SDL2/SDL.h>

namespace AEOIAF_Actor
{
    class Character;
    class Prop;
	class ParticleEmitter;
	class Weapon; //So we can check for collisions
	class RadiusList; //Enables us to find characters in a radius
}

namespace AEOIAF_ScriptedEvents
{
	class ScriptSequence;
}

namespace AEOIAF_Utilities
{
    class Matrix;
	class Camera;
	class Vector;
}

//When we stream between levels, we need to use
//these to keep track of information about level
//actors
namespace ACOC_GameDataHandling
{
	class StreamDataHandler;
}

namespace AEOIAF_Level
{
    class Level;
	class ActorCollisionList;

    /*CHARACTER LIST*/
    //Basically a simple doubly linked list
    class CharacterList
    {
        public:
            CharacterList();
            ~CharacterList();

            void Add(AEOIAF_Actor::Character* toAdd);
            //If a character with ID toRemove exists, then
			//remove him
			int Remove(const char* toRemove);
            //Finds the character at the given position,
            //returns 0 if the character cannot be found
            AEOIAF_Actor::Character* Find(const char* toFind) const;
			//Clears the entire list
			void Clear();

            //A wrapper function to call all characters' update method
            void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime) const;

			//Traverses each character and determines if it was hit by
			//checkWith. If it was, we add it to hitList
			void FindHitCharacters(AEOIAF_Actor::Weapon* checkWith, ActorCollisionList& hitList) const;

            //A wrapper function to call all characters' draw method
            void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL,
					  AEOIAF_Utilities::Camera* drawCam = NULL) const;

        private:
			int GetHashValue(const char* toHash) const;

			void Clear(struct CharacterListNode*& head);
			int Remove(struct CharacterListNode*& head, const char* toFind);
			AEOIAF_Actor::Character* Find(struct CharacterListNode* head, const char* toFind) const;			

			void Update(struct CharacterListNode* head, AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime) const;
            void Draw(struct CharacterListNode* head, SDL_Renderer* renderer, SDL_RendererFlip flip, 
					  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
					  AEOIAF_Utilities::Matrix* matrix = NULL,
					  AEOIAF_Utilities::Camera* drawCam = NULL) const;

			void FindHitCharacters(AEOIAF_Actor::Weapon* checkWith, ActorCollisionList& hitList, struct CharacterListNode* head) const;

            struct CharacterListNode** table;
			int tableSize;
    };

    struct CharacterListNode
    {
        CharacterListNode();
        ~CharacterListNode();

        AEOIAF_Actor::Character* character;

        CharacterListNode* next;
    };

    /*PROP LIST*/
    //Just a simple LLL of props
    class PropList
    {
        public:
            PropList();
            ~PropList();

            int GetNumProps() { return numProps; }

            void Add(AEOIAF_Actor::Prop* toAdd);
            //Returns false if there are no props to remove, or the ID is not found
            int Remove(const char* id);
            //Removes the item at position
            int Remove(int position);
            //Returns the first prop with id, returns NULL if it can't find said prop
            AEOIAF_Actor::Prop* Find(char* id);
            //Returns the prop at position, or NULL if the position is bad or head is NULL
            AEOIAF_Actor::Prop* Find(int position);
            //Removes all props
            void ClearAll();
            //Updates all props, returns false if none to update
            void Update(AEOIAF_Level::Level* currentLevel, SDL_Event* e, float deltaTime,
						ACOC_GameDataHandling::StreamDataHandler& streamData);
			//Traverses each character and determines if it was hit by
			//checkWith. If it was, we add it to hitList
			void FindHitProps(AEOIAF_Actor::Weapon* checkWith, ActorCollisionList& hitList) const;
			//Draws all props to the screen, returns false if none to update
            void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL,
					  AEOIAF_Utilities::Camera* drawCam = NULL);

        private:
            /*Recursive implementations*/
            int Remove(const char* id, struct PropListNode*& head);
            int Remove(int current, int length, struct PropListNode*& head);
            AEOIAF_Actor::Prop* Find(char* id, struct PropListNode* head);
            AEOIAF_Actor::Prop* Find(int current, int length, struct PropListNode* head);
            void Update(AEOIAF_Level::Level* currentLevel, SDL_Event* e, float deltaTime,
						struct PropListNode*& head, ACOC_GameDataHandling::StreamDataHandler& streamData);
			void FindHitProps(AEOIAF_Actor::Weapon* checkWith, ActorCollisionList& hitList, struct PropListNode* head) const;

            struct PropListNode* head;
            int numProps;
    };

    struct PropListNode
    {
        PropListNode();
        ~PropListNode();

        AEOIAF_Actor::Prop* data;
        PropListNode* next;
    };

	/*PARTICLE LIST*/
	class ParticleList
	{
		public:
			ParticleList();
			~ParticleList();

			//Inserts toAdd into the list
			void Insert(AEOIAF_Actor::ParticleEmitter* toAdd);
			//Removes toRemove from the list, if it exists
			int Remove(const char* toRemove);
			//Returns the first particle with the id of toFind, if it exists
			int Find(const char* toFind);
			//Clears the entire list
			void ClearAll();

			//Updates each particle in the level
            void Update(AEOIAF_Level::Level* currentLevel, SDL_Event* e, float deltaTime);
			//Draws each particle to the screen
            void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL);
		private:
			/*RECURSIVE FUNCTIONS*/
			int Remove(const char* toFind, struct ParticleListNode*& head);
            void Update(AEOIAF_Level::Level* currentLevel, SDL_Event* e, float deltaTime, struct ParticleListNode*& head);

			struct ParticleListNode* head;
	};

	/*PARTICLE LIST NODE*/
	struct ParticleListNode
	{
		ParticleListNode();
		~ParticleListNode();

		AEOIAF_Actor::ParticleEmitter* data;
		ParticleListNode* next;
	};

	/*SCRIPTED SEQUENCES LIST*/
	class ScriptedSequenceList
	{
		public:
			ScriptedSequenceList();
			~ScriptedSequenceList();

			int GetHashMagicValue() const { return hashMagicVal; }
			void SetHashMagicValue(const int val) { hashMagicVal = val; }

			bool IsEmpty();

			/*DATA STRUCTURE SPECIFIC FUNCTIONS*/
			//Insert toAdd into the tree
			int Insert(AEOIAF_ScriptedEvents::ScriptSequence* toAdd);
			//Remove toRemove from the tree
			int Remove(const char* toRemove);
			//Clears the entire tree
			void Clear();

			/*SCRIPTED EVENT WRAPPERS*/
			void Update(AEOIAF_Level::Level* level, float deltaTime);

		private:
			/*General case recursive functions*/
			//key is used to traverse, root is our current sub-tree, and subTree
			//tells us if we are the root, left, center, or right sub-trees
			int Insert(AEOIAF_ScriptedEvents::ScriptSequence* toAdd, int key, struct ScriptedSequenceNode*& root, int subTree);
			int Remove(const char* toRemove, int key, struct ScriptedSequenceNode*& root, int subTree);
			void Clear(struct ScriptedSequenceNode*& root);

			/*Recusrive functions for scripted events*/
			void Update(struct ScriptedSequenceNode* root, AEOIAF_Level::Level* level,
						float deltaTime, class RemoveScriptSequenceStack& removeStack);
			//Removes all empty items from the list
			void ClearEmptyEvents(class RemoveScriptSequenceStack& itemsToRemove);

			/*Insertion utility functions*/
			//When root is just a leaf, we handle that here
			int InsertRootIsLeaf(AEOIAF_ScriptedEvents::ScriptSequence* toAdd, int key);
			//Insert a node, as the left child, into a 2-node root
			int Insert2NodeLeft(int key, AEOIAF_ScriptedEvents::ScriptSequence* toAdd, struct ScriptedSequenceNode* root);
			//Insert a node, as the right child, into a 2-node root
			int Insert2NodeRight(int key, AEOIAF_ScriptedEvents::ScriptSequence* toAdd, struct ScriptedSequenceNode* root);
			//Insert a node, as the left child, into a 3-node root
			int Insert3NodeLeft(int key, AEOIAF_ScriptedEvents::ScriptSequence* toAdd, struct ScriptedSequenceNode* root);
			//Insert a node, as the center child, into a 3-node root
			int Insert3NodeCenter(int key, AEOIAF_ScriptedEvents::ScriptSequence* toAdd, struct ScriptedSequenceNode* root);
			//Insert a node, as the right child, into a 3-node root
			int Insert3NodeRight(int key, AEOIAF_ScriptedEvents::ScriptSequence* toAdd, struct ScriptedSequenceNode* root);
			//When rebalancing the tree, and the split node was the left child of a 2-node root
			int InsertBalance2NodeLeft(struct ScriptedSequenceNode* root);
			//When rebalancing the tree, and the split node was the right child of a 2-node root
			int InsertBalance2NodeRight(struct ScriptedSequenceNode* root);
			//When rebalacing the tree, and the split node was the left child of a 3-node root
			int InsertBalance3NodeLeft(struct ScriptedSequenceNode* root);
			//When rebalacing the tree, and the split node was the center child of a 3-node root
			int InsertBalance3NodeCenter(struct ScriptedSequenceNode* root);
			//When rebalacing the tree, and the split node was the right child of a 3-node root
			int InsertBalance3NodeRight(struct ScriptedSequenceNode* root);

			/*Removal utility functions*/
			//A special case when the root is just a key
			int RemoveRootIsLeaf(const char* toRemove, int key);
			//Determines which of root's children has toRemove, if it's children are leaves
			int RemoveContains(const char* toRemove, int key, struct ScriptedSequenceNode* root);
			//Removes the given child from root
			int Remove(struct ScriptedSequenceNode* root, int child);
			//If root was a 3-node, and we removed an item, we use this to fix it up
			void RemoveFix3Node(struct ScriptedSequenceNode* root, int removedChild);
			//Our root is a 2-node, and the left child needs to be fixed
			int RemoveBalance2NodeLeft(struct ScriptedSequenceNode* root);
			//Our root is a 2-node, and the right child needs to be fixed
			int RemoveBalance2NodeRight(struct ScriptedSequenceNode* root);
			//Our root is a 3-node, and the left child needs to be fixed
			int RemoveBalance3NodeLeft(struct ScriptedSequenceNode* root);
			//Our root is a 3-node, and the center child needs to be fixed
			int RemoveBalance3NodeCenter(struct ScriptedSequenceNode* root);
			//Our root is a 3-node, and the right child needs to be fixed
			int RemoveBalance3NodeRight(struct ScriptedSequenceNode* root);
			
			//Determines what child we go to
			int FindChildToTraverse(int key, struct ScriptedSequenceNode* root);
			//Finds the smallest key of a given subtree
			int FindSmallestKey(struct ScriptedSequenceNode* root);

			int GetKey(AEOIAF_ScriptedEvents::ScriptSequence* data) const;	
			int GetHashKey(const char* toHash) const;

			int hashMagicVal; //A value used in GetHashKey
			struct ScriptedSequenceNode* root;
			struct ScriptedSequenceNode* temp;
	};

	struct ScriptedSequenceNode
	{
		ScriptedSequenceNode();
		~ScriptedSequenceNode();

		bool IsLeaf();
		bool Is2Node();

		ScriptedSequenceNode* left;
		ScriptedSequenceNode* center;
		ScriptedSequenceNode* right;

		int key1, key2;

		AEOIAF_ScriptedEvents::ScriptSequence* data;
	};

	//As we update scripted sequences, once they end, we need to remove them.
	//This will store data we need to remove
	class RemoveScriptSequenceStack
	{
		public:
			RemoveScriptSequenceStack();
			~RemoveScriptSequenceStack();

			//Pushes a scripted sequence ID onto the stack
			int Push(const char* toAdd);
			//Pops the head off of the stack. Return 0 if already empty
			int Pop();
			//Returns a copy of the id in the head
			char* Peek();
			//Clears the entire stack
			int Clear();
			//Returns if the stack is empty
			bool IsEmpty();

		private:
			struct RemoveScriptSequenceNode* head;
	};

	struct RemoveScriptSequenceNode
	{
		RemoveScriptSequenceNode();
		~RemoveScriptSequenceNode();

		char* sequenceID; //The id of the item we want to remove
		RemoveScriptSequenceNode* next;
	};
}

#endif // AEOIAF_LEVEL_DATA_TYPES
