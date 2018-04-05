//Liam "AFishyFez" Wynn, 12/14/2015, An Engine of Ice and Fire

#include "../LevelDataTypes.h"
#include "../../Scripted_Events/ScriptSequence.h"
#include "../Level.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_Level;
using namespace AEOIAF_ScriptedEvents;
using namespace std;

//Some flags used in traversal
#define ROOT  0
#define LEFT  1
#define CENT  2
#define RIGHT 3

/*TREE IMPLEMENTAIONS*/
ScriptedSequenceList::ScriptedSequenceList()
{
	hashMagicVal = 101;

	root = NULL;
	temp = NULL;
}

ScriptedSequenceList::~ScriptedSequenceList()
{
	temp = NULL;
	Clear();
}

bool ScriptedSequenceList::IsEmpty()
{
	return !root;
}

void ScriptedSequenceList::Update(Level* level, float deltaTime)
{
	RemoveScriptSequenceStack itemsToRemove; //Store the IDs of all the events to remove

	Update(root, level, deltaTime, itemsToRemove);
	
	ClearEmptyEvents(itemsToRemove);
}

void ScriptedSequenceList::Update(ScriptedSequenceNode* root, Level* level, float deltaTime, RemoveScriptSequenceStack& removeStack)
{
	if(!root)
		return;

	char* id; //If the data is empty, we add its id to removeStack

	if(root->data)
	{
		root->data->Update(level, deltaTime);

		if(root->data->IsEmpty())
		{
			root->data->GetID(id);
			removeStack.Push(id);

			//Delete this temp copy
			delete[] id;
			id = NULL;
		}
	}

	Update(root->left, level, deltaTime, removeStack);
	Update(root->center, level, deltaTime, removeStack);
	Update(root->right, level, deltaTime, removeStack);
}

void ScriptedSequenceList::ClearEmptyEvents(RemoveScriptSequenceStack& itemsToRemove)
{
	char* nextID; //Use this for removal

	while(!itemsToRemove.IsEmpty())
	{
		nextID = itemsToRemove.Peek();
		itemsToRemove.Pop();

		Remove(nextID);

		delete[] nextID;
		nextID = NULL;
	}
}

//If toAdd is NULL, then return 0. If root is NULL,
//then create a new root and have toAdd be its data.
//If root is a leaf, then make it apart of a 2-node
//tree. Otherwise, call the recursive function.
int ScriptedSequenceList::Insert(ScriptSequence* toAdd)
{
	if(!toAdd)
		return 0;

	int key = GetKey(toAdd);
	int result; //What we will return

	if(key == -1)
		return 0; //This means failure!

	//Special root case 1: Tree is empty
	if(!root)
	{
		root = new ScriptedSequenceNode;
		root->key1 = key;
		root->data = toAdd;
		result = 1;
	}

	else if(root->IsLeaf())
		result = InsertRootIsLeaf(toAdd, key);

	//At this point, we know there are no special root cases to handle
	else
		result = Insert(toAdd, key, root, ROOT);

	//If the result is 0, it means the root of the entire tree was split.
	//When splitting occurs, we know that the largest sub tree is in temp
	//and, thankfully, at the same height as root. As such, all we need
	//to do here is make a new root whose key is in temp, the old root
	//in the left, and temp in right
	if(result == 0)
	{
		ScriptedSequenceNode* newRoot = new ScriptedSequenceNode;
		newRoot->key1 = FindSmallestKey(temp);
		newRoot->left = root;
		newRoot->right = temp;

		temp = NULL;
		root = newRoot;
		result = 1;
	}

	else if(result == -1)
		result = 0;

	return result;
}

//If root is NULL or a leaf, we've gone too far. Return -1. If
//root's children are leaves, then determine the correct insertion
//case and handle accordingly. If the root's children are not leaves,
//then use key to traverse to the correct node. If the returning value
//is 0, then rebalance the tree, and return the result of that.
int ScriptedSequenceList::Insert(ScriptSequence* toAdd, int key, ScriptedSequenceNode*& root, int subTree)
{
	if(!root || root->IsLeaf())
		return -1; //Our traversal went too far, so return -1

	int result; //The result of insertion
	int childIndex; //Used to know where we are going, and in rebalacing if needed

	//At this point, we know we are not a leaf. Since the properties
	//of a 2-3 tree ensure that the left child is always present (we
	//could use the right one as well), this will work. Also, we know
	//we are at the correct node to insert, since the recursive call
	//ensures such
	if(root->left->IsLeaf()) //We found the correct node to insert to!
	{
		if(root->Is2Node())
		{
			if(key < root->key1) //Insert into the left
				result = Insert2NodeLeft(key, toAdd, root);
			else //Insert into right
				result = Insert2NodeRight(key, toAdd, root);
		}

		else
		{
			if(key < root->key1) //We are inserting left
				result = Insert3NodeLeft(key, toAdd, root);
			else if(key >= root->key1 && key < root->key2) //We are inserting into center
				result = Insert3NodeCenter(key, toAdd, root);
			else //We are inserting into right
				result = Insert3NodeRight(key, toAdd, root);

			result = 0;
		}
	}

	else //We've not found the correct node
	{
		childIndex = FindChildToTraverse(key, root);
	
		if(childIndex == LEFT)
			result = Insert(toAdd, key, root->left, childIndex);
		else if(childIndex == CENT)
			result = Insert(toAdd, key, root->center, childIndex);
		else if(childIndex == RIGHT)
			result = Insert(toAdd, key, root->right, childIndex);
		else
			result = -1;

		
		//If result is 0, we need to rebalance
		if(result == 0)
		{
			if(root->Is2Node())
			{
				if(childIndex == LEFT) //Our offending node is the left
					result = InsertBalance2NodeLeft(root);
				else //Our offending node must be the right
					result = InsertBalance2NodeRight(root);
			}

			else //Root is a 3-node
			{
				//The left child was split
				if(childIndex == LEFT)
					result = InsertBalance3NodeLeft(root);

				//The center child was split
				else if(childIndex == CENT)
					result = InsertBalance3NodeCenter(root);

				//The right child was split
				else
					result = InsertBalance3NodeRight(root);
			}
		}
	}

	return result;
}

//Make sure root is not NULL. Since we are inserting into the
//left child, we move root's key1 into key2. If key is smaller
//than what is already in root's left, then we make root's key1
//the key1 of root's left child. Then we make root's center it's
//former left child, and the new left child contains key and toAdd.
//On the otherhand, if key is >= root's left key1, then we put that
//in the center and make root's key1 key. Return 1, since no rebalacing
//is needed.
int ScriptedSequenceList::Insert2NodeLeft(int key, ScriptSequence* toAdd, ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	root->key2 = root->key1; //Move this over to add smaller data to the tree

	if(key < root->left->key1)
	{
		root->key1 = root->left->key1;
		root->center = root->left;

		root->left = new ScriptedSequenceNode;
		root->left->key1 = key;
		root->left->data = toAdd;
	}

	else //The data in root's left is the smallest
	{
		root->key1 = key;

		root->center = new ScriptedSequenceNode;
		root->center->key1 = key;
		root->center->data = toAdd;
	}

	return 1;
}

//Principally, we do the same as inserting a left child. However,
//we handle the case where the data needs to go to the right. Like
//the left child, since no splitting occurs, the by extension no
//rebalacing must follow. As such, we can return 1 for a clean
//insertion.
int ScriptedSequenceList::Insert2NodeRight(int key, ScriptSequence* toAdd, ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	if(key < root->right->key1)
	{
		root->key2 = root->right->key1;
		
		root->center = new ScriptedSequenceNode;
		root->center->key1 = key;
		root->center->data = toAdd;
	}

	else
	{
		root->key2 = key;
		root->center = root->right;
		
		root->right = new ScriptedSequenceNode;
		root->right->key1 = key;
		root->right->data = toAdd;
	}

	return 1;
}

//If root is NULL, return -1. Essentially, we split the root
//into two subtrees of equal height. What stays in root are
//the smaller items of the former root. The split stuff,
//being the largest items, get stored into temp. Since this
//insertion results in a split, we must return 0.
int ScriptedSequenceList::Insert3NodeLeft(int key, ScriptSequence* toAdd, ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	ScriptedSequenceNode* subTreeLarge = new ScriptedSequenceNode; //Contain the 2-node with the larger data
	
	subTreeLarge->key1 = root->key2;
	subTreeLarge->right = root->right;
	subTreeLarge->left = root->center;
	
	if(key < root->left->key1) //Smallest item
	{
		root->key1 = root->left->key1;
		root->key2 = -1;

		root->center = NULL;
		root->right = root->left;
		root->left = new ScriptedSequenceNode;
		root->left->key1 = key;
		root->left->data = toAdd;
	}

	else
	{
		root->key1 = key;
		root->key2 = -1;

		root->center = NULL;
		root->right = new ScriptedSequenceNode;
		root->right->key1 = key;
		root->right->data = toAdd;
	}

	temp = subTreeLarge;

	return 0;
}

//Pricinpally the same as inserting a left child. However,
//where we place toAdd has more significance. If it is bigger
//(or equal) than the data in root's middle child, toAdd will
//end up in the subtree for larger items. However, if it is
//lesser than the data, then it will stay in root, and root's
//old middle child will go to the larger item subtree. Since
//splitting occurs in this case, we return 0.
int ScriptedSequenceList::Insert3NodeCenter(int key, ScriptSequence* toAdd, ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	ScriptedSequenceNode* subTreeLarge = new ScriptedSequenceNode; //Contain the 2-node with the larger data

	subTreeLarge->key1 = root->key2;
	root->key2 = -1;
	subTreeLarge->right = root->right;

	if(key < root->center->key1)
	{
		subTreeLarge->left = root->center;

		root->center = NULL;
		root->right = new ScriptedSequenceNode;
		root->right->key1 = key;
		root->right->data = toAdd;
	}

	else
	{
		subTreeLarge->left = new ScriptedSequenceNode;
		subTreeLarge->left->key1 = key;
		subTreeLarge->left->data = toAdd;

		root->right = root->center;
		root->center = NULL;
	}

	temp = subTreeLarge;
	
	return 0;
}

//Basically the same as inserting into the left, but we do
//the right (hence the name). What's nice about this case
//is that root's right and the data we add will end up in
//subTreeLarge. The middle and left childs of root stay
//with it.
int ScriptedSequenceList::Insert3NodeRight(int key, ScriptSequence* toAdd, ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	ScriptedSequenceNode* subTreeLarge = new ScriptedSequenceNode; //Contains the 2-node with the larger data

	if(key < root->right->key1)
	{
		subTreeLarge->key1 = root->right->key1;
		root->key2 = -1;

		subTreeLarge->right = root->right;
		root->right = root->center;
		root->center = NULL;

		subTreeLarge->left = new ScriptedSequenceNode;
		subTreeLarge->left->key1 = key;
		subTreeLarge->left->data = toAdd;
	}

	else
	{
		subTreeLarge->key1 = key;
		root->key2 = -1;

		subTreeLarge->left = root->right;
		root->right = root->center;
		root->center = NULL;

		subTreeLarge->right = new ScriptedSequenceNode;
		subTreeLarge->right->key1 = key;
		subTreeLarge->right->data = toAdd;
	}

	temp = subTreeLarge;

	return 0;
}

//In this case, root is a 2-node, and needs to rebalance its
//left child, who was split. Since root is a 2-node, the rebalancing
//will result in a fully balanced tree, so we may return 1.
int ScriptedSequenceList::InsertBalance2NodeLeft(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	root->key2 = root->key1;
	//When splitting, the larger items end up in temp, and always a 2-node
	root->key1 = FindSmallestKey(temp);
	root->center = temp;

	temp = NULL; //Important so that we never delete portions of the tree
	return 1;
}

//In this case, root is a 2-node, and the offending
//child is the right. This case is moreorless the
//same as the rebalacing of the offeding left child.
int ScriptedSequenceList::InsertBalance2NodeRight(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;
	
	root->key2 = FindSmallestKey(temp);
	root->center = root->right;
	root->right = temp;

	temp = NULL;
	return 1;
}

//In this case, the offending node is the left
//child. However, we are a 3-node root, so
//we need to split the root as well as rebalance.
//Since we split, we need to return 0, because the
//tree is not balanced still.
int ScriptedSequenceList::InsertBalance3NodeLeft(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	ScriptedSequenceNode* subTreeLarge = new ScriptedSequenceNode;
	subTreeLarge->key1 = root->key2;
	subTreeLarge->left = root->center;
	subTreeLarge->right = root->right;

	root->key1 = FindSmallestKey(temp);
	root->key2 = -1;
	root->center = NULL;
	root->right = temp;

	temp = subTreeLarge;
	return 0;
}

int ScriptedSequenceList::InsertBalance3NodeCenter(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	ScriptedSequenceNode* subTreeLarge = new ScriptedSequenceNode;
	subTreeLarge->key1 = root->key2;
	subTreeLarge->left = temp;
	subTreeLarge->right = root->right;

	root->key2 = -1;
	root->right = root->center;
	root->center = NULL;

	temp = subTreeLarge;
	return 0;
}

int ScriptedSequenceList::InsertBalance3NodeRight(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	ScriptedSequenceNode* subTreeLarge = new ScriptedSequenceNode;
	subTreeLarge->key1 = FindSmallestKey(temp);
	subTreeLarge->left = root->right;
	subTreeLarge->right = temp;

	root->key2 = -1;
	root->right = root->center;
	root->center = NULL;

	temp = subTreeLarge;
	return 0;
}

//If root is NULL, return -1. If root is a leaf,
//return its data. Otherwise, call the function with
//root's left
int ScriptedSequenceList::FindSmallestKey(ScriptedSequenceNode* root)
{
	if(!root)
		return -1; //Went too far, or root is NULL

	int result; //What we're returning

	if(root->IsLeaf())
		result = root->key1;
	else
		result = FindSmallestKey(root->left);

	return result;
}

//If root is NULL, return -1. If it is a 2-node, and the
//key is < root's key1, then return LEFT. Otherwise, return
//right. On the other hand, if root is a 3-node, and key
//is < key1, return LEFT. If it is >= key1, but < key2,
//then return CENTER. Otherwise, return RIGHT.
int ScriptedSequenceList::FindChildToTraverse(int key, ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	int result; //What we are returning

	if(root->Is2Node())
	{
		if(key < root->key1)
			result = LEFT;
		else
			result = RIGHT;
	}

	else
	{
		if(key < root->key1)
			result = LEFT;
		else if(key >= root->key1 && key < root->key2)
			result = CENT;
		else
			result = RIGHT;
	}

	return result;
}

//Create a new node. If root is less than toAdd,
//then make this new node's key toAdd, and root as
//the left child. Otherwise, make the key root, and
//root the right child. Make this new node the root
//and return 1.
int ScriptedSequenceList::InsertRootIsLeaf(ScriptSequence* toAdd, int key)
{
	//Effectively the new root of our tree
	ScriptedSequenceNode* temp = new ScriptedSequenceNode;

	if(root->key1 < key)
	{
		temp->key1 = key;
		temp->left = root;
		
		temp->right = new ScriptedSequenceNode;
		temp->right->key1 = key;
		temp->right->data = toAdd;
	}

	else
	{
		temp->key1 = root->key1;
		temp->right = root;
		
		temp->left = new ScriptedSequenceNode;
		temp->left->key1 = key;
		temp->left->data = toAdd;
	}

	root = temp;

	return 1;
}

//If toRemove is -1, then return 0. If root
//is a leaf and contains or data, then delete
//it and return 1. Otherwise, return the result
//of the recursive function.
int ScriptedSequenceList::Remove(const char* toRemove)
{
	if(!toRemove || !root)
		return 0;

	//If we need to rebalance the root, we use this to fix the final tree
	ScriptedSequenceNode* temp;
	int key = GetHashKey(toRemove); //The key used in traversal
	int result; //What we will return
	
	if(root->IsLeaf())
		result = RemoveRootIsLeaf(toRemove, key);
	else
		result = Remove(toRemove, key, root, ROOT);

	if(result == 0)
	{
		temp = root;
		root = root->center;

		delete temp;
		temp = NULL;
	}

	return result;
}

int ScriptedSequenceList::Remove(const char* toRemove, int key, ScriptedSequenceNode*& root, int subTree)
{
	if(!root || !toRemove)
		return -1;

	int result; //What we will return
	int childToRemove; //If we found our data, this tells us what case to handle
	int subTreeToTraverse; //Use this for the subTree flag in recursive calls
	bool bWas2Node; //When we remove a child, we can use this to store if root was a 2-node or 3-node prior to deletion

	//If a 2-3 tree is fully balanced (as it should be), and its left is a leaf,
	//then any other child of root must also be a leaf. We check at this height
	//so we can immediately handle cases post removal
	if(root->left->IsLeaf())
	{
		//Returns the child that has the data we want to remove
		childToRemove = RemoveContains(toRemove, key, root);

		if(childToRemove == -1)
			result = -1; //The data is not in the tree!
		else
		{
			bWas2Node = root->Is2Node(); //Store what root was prior to deletion, otherwise rebalacing yeilds a segfault!
			result = Remove(root, childToRemove);
		}

		if(result != -1)
		{
			if(bWas2Node) //We have only one child, so we need to rebalance
				result = 0;
			else //We simply become a 2-node. Since balance is preserved, we return 1
			{
				RemoveFix3Node(root, childToRemove);
				result = 1;
			}
		}
	}

	else
	{
		subTreeToTraverse = FindChildToTraverse(key, root);
		
		if(subTreeToTraverse == LEFT)
			result = Remove(toRemove, key, root->left, LEFT);
		else if(subTreeToTraverse == CENT)
			result = Remove(toRemove, key, root->center, CENT);
		else if(subTreeToTraverse == RIGHT)
			result = Remove(toRemove, key, root->right, RIGHT);

		//At this point, we need to rebalance
		if(result == 0)
		{
			if(root->Is2Node())
			{
				//Our offending node is the left child
				if(subTreeToTraverse == LEFT)
					result = RemoveBalance2NodeLeft(root);

				//Our offending node is the right child
				else
					result = RemoveBalance2NodeRight(root);
			}

			//Root is a 3-node
			else
			{
				//The offending node is the left
				if(subTreeToTraverse == LEFT)
					result = RemoveBalance3NodeLeft(root);

				//The offending node is the center
				else if(subTreeToTraverse == CENT)
					result = RemoveBalance3NodeCenter(root);

				//The offending node is the right
				else
					result = RemoveBalance3NodeRight(root);
			}
		}
	}

	return result;
}

int ScriptedSequenceList::RemoveBalance2NodeLeft(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	int result; //What we will return

	//Combine root's children into one
	if(root->right->Is2Node())
	{
		//Bring down our root's key down
		root->right->key2 = root->right->key1;
		root->right->key1 = root->key1;

		//Move the left child to the center
		root->right->center = root->right->left;
		//Bring the offending node's only child to the sibiling
		root->right->left = root->left->center;

		delete root->left; //Now delete the offending subtree's remaining node
		root->left = NULL;

		//Finally, put the remaining child as the center
		root->center = root->right;
		root->right = NULL;

		result = 0;
	}

	//Borrow from right sibiling. Preserves tree
	//balance, return 1
	else
	{
		//Begin by moving left's only child to the left child
		root->left->left = root->left->center;
		root->left->center = NULL;

		//Bring right's left child to left's right child
		root->left->right = root->right->left;

		//Now fix right by moving its center to the left
		root->right->left = root->right->center;
		root->right->center = NULL;

		//Now finally, fix the keys
		root->left->key1 = root->key1;
		root->key1 = root->right->key1;
		root->right->key1 = root->right->key2;
		root->right->key2 = -1;

		result = 1;
	}

	return result;
}

int ScriptedSequenceList::RemoveBalance2NodeRight(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	int result;

	//Combine root's children into one
	if(root->left->Is2Node())
	{
		//Bring down the root's key
		root->left->key2 = root->key1;
		
		//Now move left's right child to the center
		root->left->center = root->left->right;
		//Now move right's only child into the left node
		root->left->right = root->right->center;

		//Next delete the right child, as it's no longer needed
		delete root->right;
		root->right = NULL;

		//Finally, set the left child as root's center
		root->center = root->left;
		root->left = NULL;

		result = 0;
	}

	//Borrow from the left sibiling. Preserves the balance, so return 1
	else
	{
		//Begin by moving right's only child to the right
		root->right->right = root->right->center;
		//Now make center NULL
		root->right->center = NULL;

		//Now move left's rightmost child to root's right child
		root->right->left = root->left->right;

		//Next fix the children in left
		root->left->right = root->left->center;
		root->left->center = NULL;

		//Finally, fix the keys
		root->right->key1 = root->key1;
		root->key1 = root->left->key2;
		root->left->key2 = -1;

		result = 1;
	}

	return result;
}

int ScriptedSequenceList::RemoveBalance3NodeLeft(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	//Combine center and left
	if(root->center->Is2Node())
	{
		//Begin by moving root's key1 into the center
		root->center->key2 = root->center->key1;
		root->center->key1 = root->key1;
		
		//Next move the one child of left into center
		root->center->center = root->center->left;
		root->center->left = root->left->center;

		//Now delete the old center child
		delete root->left;
		root->left = root->center;
		root->center = NULL;

		//Finally, fix the keys in root
		root->key1 = root->key2;
		root->key2 = -1;
	}

	//Borrow from the sibiling
	else
	{
		//Move left's one child to the left
		root->left->left = root->left->center;
		root->left->center = NULL;

		//Move the center's left child to left
		root->left->right = root->center->left;

		//Now move center's center child to the left
		root->center->left = root->center->center;
		root->center->center = NULL;

		//Finally, fix all of our keys
		root->left->key1 = root->key1;
		root->key1 = root->center->key1;
		root->center->key1 = root->center->key2;
		root->center->key2 = -1;
	}

	return 1;
}

int ScriptedSequenceList::RemoveBalance3NodeCenter(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	//Borrow from left
	if(!root->left->Is2Node())
	{
		//Begin by making the center child the right one
		root->center->right = root->center->center;
		root->center->center = NULL;

		//Now move the right child of left into center
		root->center->left = root->left->right;

		//Fix the left child
		root->left->right = root->left->center;
		root->left->center = NULL;

		//Finally, fix keys
		root->center->key1 = root->key1;
		root->key1 = root->left->key2;
		root->left->key2 = -1;
	}

	//Borrow from right
	else if(!root->right->Is2Node())
	{
		//Begin by moving center's child to the left
		root->center->left = root->center->center;
		root->center->center = NULL;

		//Move right's left child to the center
		root->center->right = root->right->left;

		//Fix the remaining children in root's right
		root->right->left = root->right->center;
		root->right->center = NULL;

		//Finally fix the keys
		root->center->key1 = root->key2;
		root->key2 = root->right->key1;
		root->right->key1 = root->right->key2;
		root->right->key2 = -1;
	}

	//Combine
	else
	{
		//Begin by modifying root's keys
		root->key1 = root->key2;
		root->key2 = -1;

		//Modify the keys in the left child
		root->left->key2 = root->center->key1;

		//Fix the children in the left child so it can take another one
		root->left->center = root->left->right;
		//Now take the next child in
		root->left->right = root->center->center;

		//Now delete what is left over of the center child
		delete root->center;
		root->center = NULL;
	}

	return 1;
}

int ScriptedSequenceList::RemoveBalance3NodeRight(ScriptedSequenceNode* root)
{
	if(!root)
		return -1;

	if(root->center->Is2Node())
	{
		//Begin by moving keys
		root->center->key2 = root->key2;
		root->key2 = -1;

		//Move the children in the center
		root->center->center = root->center->right;

		//Integrate right child into center
		root->center->right = root->right->center;

		//Finally, delete old right and replace with center
		delete root->right;
		root->right = root->center;
		root->center = NULL;
	}

	//Borrow from center
	else
	{
		//Move right's child to the right
		root->right->right = root->right->center;
		root->right->center = NULL;

		//Move the right child of center to right
		root->right->left = root->center->right;

		//Fix the children of center
		root->center->right= root->center->center;
		root->center->center = NULL;

		//Fix the keys
		root->right->key1 = root->key2;
		root->key2 = root->center->key2;
		root->center->key2 = -1;
	}

	return 1;
}

//If root is NULL, or toRemove is -1, then return 0.
//Otherwise, if root's data is toRemove, then deallocate
//root and return 1. Otherwise, return 0.
int ScriptedSequenceList::RemoveRootIsLeaf(const char* toRemove, int key)
{
	if(!root || !toRemove)
		return 0;

	int result; //What we will return

	if(*root->data == toRemove)
	{
		delete root;
		root = NULL;

		result = 1;
	}

	else
		result = 0;

	return result;
}

//If root is NULL, or its children are not leaves, then return -1.
//Otherwise determine if the children contain toRemove, and return -1
//if they don't
int ScriptedSequenceList::RemoveContains(const char* toRemove, int key, ScriptedSequenceNode* root)
{
	if(!toRemove || !root || !root->left->IsLeaf())
		return -1;

	int result; //What we will return

	if(root->Is2Node())
	{
		if(key < root->key1 && *root->left->data == toRemove)
			result = LEFT;
		else if(*root->right->data == toRemove)
			result = RIGHT;
		else
			result = -1;
	}

	else
	{
		if(key < root->key1 && *root->left->data == toRemove)
			result = LEFT;
		else if(key >= root->key1 && key < root->key2 && *root->center->data == toRemove)
			result = CENT;
		else if(*root->right->data == toRemove)
			result = RIGHT;
		else
			result = -1;
	}

	return result;
}

//If root is NULL, return -1. If the subTree we want
//to remove is NULL or not a leaf, then return -1.
//Otherwise deallocate it, and return 1.
int ScriptedSequenceList::Remove(ScriptedSequenceNode* root, int child)
{
	if(!root)
		return -1;

	int result = 0; //What we will return

	if(root->Is2Node())
	{
		if(child == LEFT && root->left && root->left->IsLeaf())
		{
			delete root->left;
			root->left = NULL;

			//Move our remaining child to the middle
			//to keep consistency in rebalacing cases
			root->center = root->right;
			root->right = NULL;
		}

		else if(child == RIGHT && root->right && root->right->IsLeaf())
		{
			delete root->right;
			root->right = NULL;

			//Move our remaining child to the middle
			//to keep consistency in rebalacing cases
			root->center = root->left;
			root->left = NULL;
		}

		else
			result = -1;
	}

	else
	{
		if(child == LEFT && root->left && root->left->IsLeaf())
		{
			delete root->left;
			root->left = NULL;
		}

		else if(child == CENT && root->center && root->center->IsLeaf())
		{
			delete root->center;
			root->center = NULL;
		}

		else if(child == RIGHT && root->right && root->right->IsLeaf())
		{
			delete root->right;
			root->right = NULL;
		}

		else
			result = -1;
	}

	if(result != -1)
		result = 1; //Successful deallocation!

	return result;
}

//Make sure root not NULL. Since programmers can read,
//we can assume that root was a 3-node but now lacks a child.
//As such, we will perform our operations with that assumption
//in mind.
void ScriptedSequenceList::RemoveFix3Node(ScriptedSequenceNode* root, int removedChild)
{
	if(!root)
		return;

	if(removedChild == LEFT) //The left child was removed
	{
		root->key1 = root->right->key1;
		root->key2 = -1;
		root->left = root->center;
		root->center = NULL;
	}

	else if(removedChild == CENT)
	{
		root->key1 = root->right->key1;
		root->key2 = -1;
		//At this point, center is already NULL, so we're done
	}

	else if(removedChild == RIGHT)
	{
		root->key1 = root->center->key1;
		root->key2 = -1;
		root->right = root->center;
		root->center = NULL;
	}
}

//Call the recurisve function
void ScriptedSequenceList::Clear()
{
	Clear(root);
}

//If root is NULL, then return. Call the function
//for root's left, center, and right. Delete root
//and set it to NULL
void ScriptedSequenceList::Clear(ScriptedSequenceNode*& root)
{
	if(!root)
		return;

	Clear(root->left);
	Clear(root->center);
	Clear(root->right);

	delete root;
	root = NULL;
}

//If data is NULL, then return -1. Get a copy of data's id. If that
//is NULL, then return -1. Otherwise, use the ID in a GetHashKey call.
int ScriptedSequenceList::GetKey(ScriptSequence* data) const
{
	if(!data)
		return -1;

	char* id = NULL; //Used in GetHashKey
	int key; //What we will return

	if(!data->GetID(id))
		key = -1;
	else
	{
		key = GetHashKey(id);

		//At this point we know id is not NULL, so we can safely deallocate it
		delete[] id;
		id = NULL;
	}

	return key;
}

//If toHash is NULL, then return -1. Otherwise take each char in it
//and add them together. Finally, mod the sum by hashMagicVal. Return
//this final value
int ScriptedSequenceList::GetHashKey(const char* toHash) const
{
	if(!toHash)
		return -1;

	int result = 0; //What we're returning
	int length = strlen(toHash); //Used for traversing

	for(int i = 0; i < length; ++i)
		result += toHash[i];

	result %= hashMagicVal;

	return result;
}

/*TREE NODE IMPLEMENTATIONS*/
ScriptedSequenceNode::ScriptedSequenceNode()
{
	left = NULL;
	center = NULL;
	right = NULL;

	key1 = -1;
	key2 = -1;

	data = NULL;
}

ScriptedSequenceNode::~ScriptedSequenceNode()
{
	left = NULL;
	center = NULL;
	right = NULL;

	//The data is handled elsewhere, so we just set this to NULL
	data = NULL;
}

//Nodes are leaves if they have no
//children. So return if all the child
//pointers are NULL
bool ScriptedSequenceNode::IsLeaf()
{
	return !left && !center && !right;
}

bool ScriptedSequenceNode::Is2Node()
{
	return !center;
}
