//Liam "AFishyFez" Wynn, 3/1/2016, A Clash of Colors

/*
 The RemoveActorList is a red-black tree of
 actors that we want to remove from a level
 as we stream between levels.
*/

#ifndef ACOC_REMOVE_ACTOR_LIST
#define ACOC_REMOVE_ACTOR_LIST

namespace AEOIAF_Level
{
	class Level;
}

namespace ACOC_GameDataHandling
{
	class GameDataHandler;

	//Keeps track of all actors we removed from a level
	class RemoveActorList
	{
		public:
			RemoveActorList();
			~RemoveActorList();

			//Inserts the ID of an actor into the list
			int Insert(const char* toInsert);
			//Removes the ID of an actor into the list
			int Remove(const char* toRemove);
			//Determines if the ID of an actor exists in the list
			bool Find(const char* toFind) const;
			//Display the entire list
			void Display() const;
			//Clears the entire list
			int Clear();

			void RemoveActorsFromLevel(AEOIAF_Level::Level* level, const GameDataHandler& dataHandler);

		private:
			int Insert(struct RemoveActorNode*& root, int key, const char* toAdd);
			int Remove(struct RemoveActorNode*& root, int key, const char* toRemove);
			bool Find(struct RemoveActorNode* root, int key, const char* toFind) const;
			void Display(struct RemoveActorNode* root) const;
			void Clear(struct RemoveActorNode*& root);

			void RemoveActorsFromLevel(struct RemoveActorNode* root, AEOIAF_Level::Level* level,
									   const GameDataHandler& dataHandler);

			/*Traversal utilities*/
			//Given a node's key and some other key, determine which child
			//we want to traverse to
			int FindChildToTraverse(const int key, const int node) const;
			
			/*Insertion Balancing Cases*/
			void InsertionCase1(struct RemoveActorNode* root);
			//Note that root is the grandparent, so parent is
			//a child of root
			void InsertionCase2(struct RemoveActorNode*& root, struct RemoveActorNode*& parent);
			void InsertionCase3(struct RemoveActorNode*& root, struct RemoveActorNode*& parent);
			void InsertionCase4(struct RemoveActorNode*& root, struct RemoveActorNode*& parent);
			void InsertionCase5(struct RemoveActorNode*& root, struct RemoveActorNode*& parent);
			/*Insertion Utilities*/
			//After we insert a node, call this to determine if there are
			//imbalances
			int InsertIsImabalanced(struct RemoveActorNode* root, const int childToTraverse);
			//Manages all of the rotation and recoloring cases
			int RotateAndRecolor(struct RemoveActorNode*& root, const int childToTraverse);
			//As we return from our recursive calls, sometimes the offending
			//node is one of root's children. In this case, we can check if
			//the tree is balanced or not. Otherwise, we must handle imbalances
			//at the grandparent level
			int CheckParent(struct RemoveActorNode* root);
			//Handles all five insertion balacing cases. Returns 1 if the tree
			//is now completely balanced, or 0 if it still needs rebalancing.
			//childToTraverse is the child node we went to when in serting
			int HandleInsertionRebalance(struct RemoveActorNode*& root, const int childToTraverse);
			//Given a node a traversal flag, get the uncle node
			struct RemoveActorNode* GetUncle(struct RemoveActorNode* grandparent, const int traverseFlag);

			/*Removal Cases*/
			//Once we deduce we need to perform one of the removal balancing
			//cases, we use this function to determine which one we do
			int HandleRemovalRebalance(struct RemoveActorNode*& root);
			void RemoveCase1(struct RemoveActorNode*& root);
			void RemoveCase2(struct RemoveActorNode*& root, struct RemoveActorNode*& parent,
							 struct RemoveActorNode*& sibiling);
			void RemoveCase3(struct RemoveActorNode* parent, struct RemoveActorNode* sibiling);
			void RemoveCase4(struct RemoveActorNode* parent, struct RemoveActorNode* sibiling);
			void RemoveCase5(struct RemoveActorNode* parent, struct RemoveActorNode*& sibiling);
			void RemoveCase6(struct RemoveActorNode*& root, struct RemoveActorNode*& parent,
							 struct RemoveActorNode*& sibiling);
			/*Removal Utilities*/
			//Call this when the node we delete is a leaf
			int RemoveIsLeaf(struct RemoveActorNode*& root);
			//Call this when the node we delete has one child
			int RemoveHasOneChild(struct RemoveActorNode*& root);
			//Returns the sibiling of the offending node (assuming the
			//offending node's parent is parent)
			struct RemoveActorNode* GetOffendingNodeSibiling(struct RemoveActorNode* parent);
			//Makes a double black NULL or just regular black
			void FixDoubleBlack(struct RemoveActorNode*& toFix);

			/*Rotations*/
			//Performs a right rotation around the root, assuming it and its
			//right child exist
			bool RightRotation(struct RemoveActorNode*& root);
			//Perform a left rotation around the root, provided it and its
			//left child exist
			bool LeftRotation(struct RemoveActorNode*& root);

			/*Other Utilities*/
			//Takes some string and hashes it
			int GetHashValue(const char* toHash) const;

			struct RemoveActorNode* root;
			struct RemoveActorNode* offendingNode; //Maintain a pointer to the offending node
			//When we delete a black leaf, we violate property 4. So we replace it
			//with this Node until the tree is full balanced
			struct RemoveActorNode* doubleBlackNull;
	};

	struct RemoveActorNode
	{
		RemoveActorNode();
		~RemoveActorNode();

		//Returns if the node is a leaf
		bool IsLeaf();
		//Returns the key and data of the in-order successor
		bool GetInOrderSuccessor();
		//Given a flag, return the left or right child. If bad flag,
		//then return NULL
		RemoveActorNode* GetChild(int childFlag);
		//Given an insertion flag and a node, attempt to insert a child
		//node. Return 1 on success, and 0 if the child node already exists
		int AttemptInsertChild(int key, const char* toAdd, int insertFlag);

		//The actor ID
		char* data;
		int key;
		int color;

		RemoveActorNode* left;
		RemoveActorNode* right;
	};
}

#endif
