//Liam "AFishyFez" Wynn, 3/9/2016, A Clash of Colors

#include "InsertActorList.h"
#include "../GameDataHandler.h"
#include "../../Level/Level.h"
#include "../../Actors/Actor.h"
#include "../../Actors/Character/Character.h"
#include "../../Actors/Prop/Prop.h"
#include "../../Actors/Particle/Particle.h"
#include <cmath>
#include <cstring>

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Actor;
using namespace std;

/*INSERT ACTOR LIST IMPLEMENTATIONS*/
InsertActorList::InsertActorList()
{
	root = NULL;
}

InsertActorList::~InsertActorList()
{
	Clear();
}

int InsertActorList::Insert(const char* toAdd, const Vector& pos)
{
	int key; //Use this for traversing
	int result;

	key = GetHashVal(toAdd);

	if(key == -1)
		result = 0;
	else
		result = Insert(key, toAdd, pos, root);

	return result;
}

int InsertActorList::Insert(int key, const char* toAdd, const Vector& pos, InsertActorNode*& root)
{
	if(!root)
	{
		root = new InsertActorNode;
		root->key = key;
		root->data = new char[strlen(toAdd) + 1];
		root->position = pos;
		strcpy(root->data, toAdd);
		
		return 1;
	}

	int result; //What we will return

	if(key < root->key)
		result = Insert(key, toAdd, pos, root->left);
	else
		result = Insert(key, toAdd, pos, root->right);

	RecalculateHeight(root);
	Rebalance(root);

	return result;
}

int InsertActorList::Remove(const char* toRemove)
{
	int key; //Use this for traversing
	int result;

	key = GetHashVal(toRemove);

	if(key == -1)
		result = 0;
	else
		result = Remove(key, toRemove, root);

	return result;
}

int InsertActorList::Remove(int key, const char* toRemove, InsertActorNode*& root)
{
	if(!root)
		return 0;

	int result;

	if(strcmp(root->data, toRemove) == 0)
	{
		if(root->IsLeaf())
		{
			delete root;
			root = NULL;

			result = 1;
		}

		else if(root->left && root->right)
		{
			root->SetAsInOrderSuccessor();
			result = Remove(root->key, toRemove, root->right);
		}

		else
		{
			InsertActorNode* temp;

			if(root->left)
				temp = root->left;
			else
				temp = root->right;

			delete root;
			root = temp;

			result = 1;
		}
	}

	else
	{
		if(key < root->key)
			result = Remove(key, toRemove, root->left);
		else
			result = Remove(key, toRemove, root->right);
	}

	if(root && result != 0)
	{
		RecalculateHeight(root);
		Rebalance(root);
	}

	return result;
}

void InsertActorList::Clear()
{
	Clear(root);
}

void InsertActorList::Clear(InsertActorNode*& root)
{
	if(!root)
		return;

	Clear(root->left);
	Clear(root->right);

	delete root;
	root = NULL;
}

void InsertActorList::Rebalance(InsertActorNode*& root)
{
	if(IsBalanced(root))
		return;

	InsertActorNode* child = GetChildLongestPath(root);
	InsertActorNode* grandChild = GetChildLongestPath(child);

	//Case 1: Left Left Rotation
	if(root->left == child && child->left == grandChild)
		RightRotation(root);

	//Case 2: Left Right Rotation
	else if(root->left == child && child->right == grandChild)
	{
		LeftRotation(child);
		root->left = child;
		RightRotation(root);
	}

	//Case 3: Right Left Rotation
	else if(root->right == child && child->left == grandChild)
	{
		RightRotation(child);
		root->right = child;
		LeftRotation(root);
	}

	//Case 4: Right Right Rotation
	else
		LeftRotation(root);

	RecalculateHeight(root->left);
	RecalculateHeight(root->right);
	RecalculateHeight(root);
}

bool InsertActorList::IsBalanced(InsertActorNode* toCheck)
{
	if(!toCheck)
		return false;

	int heightL, heightR;

	heightL = GetSubtreeHeight(toCheck->left);
	heightR = GetSubtreeHeight(toCheck->right);

	return abs(heightL - heightR) <= 1;
}

void InsertActorList::LeftRotation(InsertActorNode*& root)
{
	if(!root)
		return;

	InsertActorNode* temp = root->right;

	root->right = temp->left;
	temp->left = root;

	root = temp;
}

void InsertActorList::RightRotation(InsertActorNode*& root)
{
	if(!root)
		return;

	InsertActorNode* temp = root->left;

	root->left = temp->right;
	temp->right = root;

	root = temp;
}

void InsertActorList::RecalculateHeight(InsertActorNode* root)
{
	if(!root)
		return;

	int heightL, heightR;

	heightL = GetSubtreeHeight(root->left);
	heightR = GetSubtreeHeight(root->right);

	if(heightL < heightR)
		root->height = 1 + heightR;
	else
		root->height = 1 + heightL;
}

int InsertActorList::GetSubtreeHeight(InsertActorNode* subtree)
{
	if(!subtree)
		return 0;
	else
		return subtree->height;
}

int InsertActorList::GetHashVal(const char* toHash) const
{
	if(!toHash)
		return -1;

	//Make sure this is prime, for best results
	const int MAGIC_VAL = 23;

	int length = strlen(toHash);
	int result = 0;

	for(int i = 0; i < length; ++i)
		result += toHash[i];

	result %= MAGIC_VAL;

	return result;
}

void InsertActorList::AddActorsToLevel(Level* level, const GameDataHandler& dataHandler) const
{
	if(!level)
		return;

	AddActorsToLevel(root, level, dataHandler);
}

void InsertActorList::AddActorsToLevel(const InsertActorNode* root, Level* level,
									   const GameDataHandler& dataHandler) const
{
	if(!root || !level)
		return;

	//Not the ID of the actor, but its type. Use it
	//to create actors for the world
	char* actorToGet = GetActorFromID(root->data);
	//Type used to determine how to insert into level
	char actorType;

	Actor* toAdd = dataHandler.GetActorUnknownType(actorToGet, actorType);
	if(toAdd)
	{
		toAdd->SetID(root->data);
		toAdd->SetPosition(root->position);
	}

	InsertActorIntoLevel(toAdd, actorType, level);

	AddActorsToLevel(root->left, level, dataHandler);
	AddActorsToLevel(root->right, level, dataHandler);
}

char* InsertActorList::GetActorFromID(const char* actorID) const
{
	if(!actorID)
		return NULL;

	//Stores the portion of the string we want to
	//remove
	const char* badSubstring = strrchr(actorID, '_');
	int badSubstringLen;
	//What we will return
	char* result = NULL;
	//Used in copying into result
	int resultLen;

	//It failed to find the _ followed by a number
	//that comes at the end of a actor ID, so it must
	//be bad
	if(!badSubstring)
		return NULL;

	badSubstringLen = strlen(badSubstring);

	resultLen = strlen(actorID) - badSubstringLen;
	result = new char[resultLen + 1];
	strncpy(result, actorID, resultLen);

	//Must append manually
	result[resultLen] = '\0';

	return result;
}

void InsertActorList::InsertActorIntoLevel(Actor* actor, const char& actorType, Level* level) const
{
	if(actorType == 'C')
	{
		Character* temp = dynamic_cast<Character*>(actor);
		level->AddCharacter(temp);
	}

	else if(actorType == 'P')
	{
		Prop* temp = dynamic_cast<Prop*>(actor);
		level->AddProp(temp);
	}

	else if(actorType == 'A')
	{
		ParticleEmitter* temp = dynamic_cast<ParticleEmitter*>(actor);
		level->AddParticle(temp);
	}
}

/*INSERT ACTOR NODE IMPLEMENTATIONS*/

InsertActorNode* InsertActorList::GetChildLongestPath(InsertActorNode* subtree)
{
	if(!subtree)
		return NULL;

	int heightL, heightR;

	heightL = GetSubtreeHeight(subtree->left);
	heightR = GetSubtreeHeight(subtree->right);

	if(heightR > heightL)
		return subtree->right;
	else
		return subtree->left;
}

/*NODE IMPLEMENTATIONS*/
InsertActorNode::InsertActorNode()
{
	key = 0;
	data = NULL;

	height = 1;

	left = NULL;
	right = NULL;
}

InsertActorNode::~InsertActorNode()
{
	left = NULL;
	right = NULL;

	if(data)
	{
		delete[] data;
		data = NULL;
	}
}

bool InsertActorNode::IsLeaf()
{
	return !left && !right;
}

void InsertActorNode::SetAsInOrderSuccessor()
{
	if(!right)
		return;

	InsertActorNode* temp = right;

	while(temp->left)
		temp = temp->left;

	key = temp->key;

	if(data)
		delete[] data;
	
	data = new char[strlen(temp->data) + 1];
	strcpy(data, temp->data);
}

