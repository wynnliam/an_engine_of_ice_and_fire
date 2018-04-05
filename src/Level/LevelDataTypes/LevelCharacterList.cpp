//Liam "AFishyFez" Wynn, 4/23/2015, AEOIAF: Level Character List

#include "../LevelDataTypes.h"
#include "../Level.h"
#include "../../Actors/Character/Character.h"
#include "../WeaponCollisionDataTypes.h"
#include "../../Actors/Item/Weapon/Weapon.h"
#include "../../Utilities/Utility_Components/Camera.h"
#include "../../Utilities/Utility_Components/Vector.h"
#include <cstring>

using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;

/*LIST IMPLEMENTATIONS*/
CharacterList::CharacterList()
{
	tableSize = 13;
    
	table = new CharacterListNode*[tableSize];
	for(int i = 0; i < tableSize; ++i)
		table[i] = NULL;
}

CharacterList::~CharacterList()
{
	Clear();
}

//If toAdd is NULL, then return. If we fail to get
//toAdd's ID, then return. Hash the ID. If the
//resulting index is not -1, then make a new node.
//Set this node's character to toAdd. Set its next
//to table[index]. Finally, set the table[next] node
//to this new node. Deallocate id if needed.
void CharacterList::Add(Character* toAdd)
{
	if(!toAdd)
		return;

	char* id = NULL; //Use this to get index
	int index; //The index to the LLL we will append
	CharacterListNode* temp;

	if(!toAdd->GetID(id))
		return; //Can't hash!

	index = GetHashValue(id);
	if(index != -1)
	{
		temp = new CharacterListNode;
		temp->character = toAdd;
		temp->next = table[index];
		table[index] = temp;
	}

	if(id)
	{
		delete[] id;
		id = NULL;
	}
}

//If table is NULL, then return 0. Hash toRemove. If
//the result is -1, return 0. Otherwise, return the
//result of the recursive Remove function
int CharacterList::Remove(const char* toRemove)
{
	if(!table)
		return 0;

	int hashIndex; //Use this to find the correct LLL
	int result; //What we will return

	hashIndex = GetHashValue(toRemove);

	if(hashIndex == -1)
		result = Remove(table[hashIndex], toRemove);
	else
		result = 0;

	return result;
}

int CharacterList::Remove(CharacterListNode*& head, const char* toRemove)
{
	if(!head)
		return 0;

	CharacterListNode* temp; //Use this to store the node we want to delete
	int result; //What we will return
	
	if(head->character && head->character->CompareID(toRemove))
	{
		temp = head;
		head = head->next;
		delete temp;
		temp = NULL;

		result = 1;
	}

	else
		result = Remove(head->next, toRemove);

	return result;
}

Character* CharacterList::Find(const char* toFind) const
{
	if(!table || !toFind)
		return NULL;

	Character* result; //What we will return
	int hashIndex; //Use this to find the correct LLL to traverse

	hashIndex = GetHashValue(toFind);

	if(hashIndex == -1)
		result = NULL;
	else
		result = Find(table[hashIndex], toFind);

	return result;
}

Character* CharacterList::Find(CharacterListNode* head, const char* toFind) const
{
	if(!head || !toFind)
		return NULL;

	Character* result; //What we will return

	if(head->character && head->character->CompareID(toFind))
		result = head->character;
	else
		result = Find(head->next, toFind);

	return result;
}

void CharacterList::Clear()
{
	if(!table)
		return;

	for(int i = 0; i < tableSize; ++i)
		Clear(table[i]);

	delete[] table;
	table = NULL;
}

//Traverse the list until we reach the end. As we return, delete
//nodes and set them to NULL
void CharacterList::Clear(CharacterListNode*& head)
{
	if(!head)
		return;

	Clear(head->next);

	delete head;
	head = NULL;
}

//If toHash is NULL, return -1. Otherwise, add each char in toHash.
//Mod the result of this by the tableSize. Return the final result
int CharacterList::GetHashValue(const char* toHash) const
{
	if(!toHash)
		return -1;

	int result = 0; //What we will return
	int length = strlen(toHash); //The length of toHash
	
	for(int i = 0; i < length; ++i)
		result += toHash[i];

	result %= tableSize;

	return result;
}

void CharacterList::Update(Level* level, SDL_Event* e, float deltaTime) const
{
	if(!table)
		return;

	for(int i = 0; i < tableSize; ++i)
		Update(table[i], level, e, deltaTime);
}

void CharacterList::Update(CharacterListNode* head, Level* level, SDL_Event* e, float deltaTime) const
{
	if(!head)
		return;

	CharacterListNode* temp = head;
	
	while(temp)
	{
		if(temp->character)
			temp->character->Update(level, e, deltaTime);
		
		temp = temp->next;
	}
}

//If checkWith is NULL, then return false. Call the recusrive implementation for this
//function
void CharacterList::FindHitCharacters(Weapon* checkWith, ActorCollisionList& hitList) const
{
	if(!checkWith || !table)
		return;

	for(int i = 0; i < tableSize; ++i)
		FindHitCharacters(checkWith, hitList, table[i]);
}

//If head is NULL, or it's number of characters is 0, then return. Otherwise, for each character, if it is hit
//by the weapon, then add it to the hitList. Only call this function again if the number of characters is equal
//to MAX_CHARS, because only then is there the potential that more characters are in the next node.
void CharacterList::FindHitCharacters(Weapon* checkWith, ActorCollisionList& hitList, CharacterListNode* head) const
{
	if(!checkWith || !head)
		return;

	CharacterListNode* temp = head;

	while(temp)
	{
		if(checkWith->DidHit(temp->character))
			hitList.Add(temp->character, checkWith);
		temp = temp->next;
	}
}

void CharacterList::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                         bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos, Matrix* matrix, Camera* drawCam) const
{
	if(!table || !drawCam)
		return;

	for(int i = 0; i < tableSize; ++i)
		Draw(table[i], renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix, drawCam);
}

void CharacterList::Draw(CharacterListNode* head, SDL_Renderer* renderer, SDL_RendererFlip flip, 
						 bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
						 Matrix* matrix, Camera* drawCam) const
{
	if(!head)
		return;

	CharacterListNode* temp = head; //Use this to traverse

	while(temp)
	{
		if(temp->character && drawCam->CanSee(temp->character))
			temp->character->Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);

		temp = temp->next;
	}
}

/*NODE IMPLEMENTATIONS*/
CharacterListNode::CharacterListNode()
{
    character = NULL;
    next = NULL;
}

CharacterListNode::~CharacterListNode()
{
	if(character)
	{
		delete character;
		character = NULL;
	}

    next = NULL;
}
