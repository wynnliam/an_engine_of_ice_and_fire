//Liam "AFishyFez" Wynn, 2/1/2016, A Clash of Colors

#include "StreamData.h"
#include "../GameDataHandler.h"
#include "../../Level/Level.h"
#include "../../Utilities/Utility_Components/Vector.h"
#include <iostream>
#include <cstring>

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

/*STREAM DATA HANDLER IMPLEMENTATIONS*/

StreamDataHandler::StreamDataHandler()
{
	tableSize = 13;
	table = new StreamDataList[tableSize];
}

StreamDataHandler::StreamDataHandler(const int newTableSize)
{
	tableSize = newTableSize;
	table = new StreamDataList[tableSize];
}

StreamDataHandler::~StreamDataHandler()
{
	if(table)
	{
		delete[] table;
		table = NULL;
	}
}

int StreamDataHandler::InsertStreamData(const char* toInsert)
{
	int index; //Where we will add toInsert

	index = GetHashValue(toInsert);
	if(index == -1)
		return 0;

	return table[index].Insert(toInsert);
}

int StreamDataHandler::RemoveStreamData(const char* toRemove)
{
	int index; //Where we will attempt to remove from

	index = GetHashValue(toRemove);
	if(index == -1)
		return 0;

	return table[index].Remove(toRemove);
}

bool StreamDataHandler::FindStreamData(const char* toFind) const
{
	int index;

	index = GetHashValue(toFind);
	if(index == -1)
		return 0;

	return table[index].Find(toFind);
}

/*INSERT ACTOR LIST WRAPPERS*/

int StreamDataHandler::InsertActorToInsert(const char* levelID, const char* toInsert, const Vector& pos)
{
	int index = GetHashValue(levelID);
	int result;

	if(index == -1)
		result = 0;
	else
		result = table[index].InsertActorToInsert(levelID, toInsert, pos);

	return result;
}

int StreamDataHandler::AddActorsToLevel(Level* level, const GameDataHandler& dataHandler)
{
	if(!level)
		return 0;
	
	//Use this to get index
	char* levelID = NULL; 
	//Index of the LLL that holds the level's stream data
	int index;
	//Success flag we return
	int result;

	level->GetID(levelID); //If no ID, sets levelID to NULL
	index = GetHashValue(levelID); //If ID is NULL, returns -1

	if(index == -1)
		result = 0;
	else
		result = table[index].AddActorsToLevel(levelID, level, dataHandler);

	//GetID allocates memory for levelID
	if(levelID)
	{
		delete[] levelID;
		levelID = NULL;
	}

	return result;
}

int StreamDataHandler::RemoveActorToInsert(const char* levelID, const char* toRemove)
{
	int index = GetHashValue(levelID);
	int result;

	if(index == -1)
		result = 0;
	else
		result = table[index].RemoveActorToInsert(levelID, toRemove);

	return result;
}

/*REMOVE ACTOR LIST WRAPPERS*/

int StreamDataHandler::InsertActorToRemove(const char* levelID, const char* toInsert)
{
	int index = GetHashValue(levelID);
	int result; //What we will return

	if(index == -1)
		result = 0;
	else
		result = table[index].InsertActorToRemove(levelID, toInsert);

	return result;
}

int StreamDataHandler::RemoveActorToRemove(const char* levelID, const char* toRemove)
{
	int index = GetHashValue(levelID);
	int result; //What we will return

	if(index == -1)
		result = 0;
	else
		result = table[index].RemoveActorToRemove(levelID, toRemove);

	return result;
}

int StreamDataHandler::RemoveActorsFromLevel(Level* level, const GameDataHandler& dataHandler)
{
	if(!level)
		return 0;
	
	//Use this to get index
	char* levelID = NULL; 
	//Index of the LLL that holds the level's stream data
	int index;
	//Success flag we return
	int result;

	level->GetID(levelID); //If no ID, sets levelID to NULL
	index = GetHashValue(levelID); //If ID is NULL, returns -1

	if(index == -1)
		result = 0;
	else
		result = table[index].RemoveActorsFromLevel(levelID, level, dataHandler);

	//GetID allocates memory for levelID
	if(levelID)
	{
		delete[] levelID;
		levelID = NULL;
	}

	return result;
}

bool StreamDataHandler::FindActorToRemove(const char* levelID, const char* toFind) const
{
	int index = GetHashValue(levelID);
	int result; //What we will return

	if(index == -1)
		result = 0;
	else
		result = table[index].FindActorToRemove(levelID, toFind);

	return result;
}

int StreamDataHandler::ClearActorsToRemove(const char* levelID)
{
	int index = GetHashValue(levelID);
	int result; //What we will return

	if(index == -1)
		result = 0;
	else
		result = table[index].ClearActorsToRemove(levelID);

	return result;
}

int StreamDataHandler::GetHashValue(const char* toHash) const
{
	if(!toHash)
		return -1;

	int result = 0; //What we will return
	int length = strlen(toHash); //Use this to get result

	for(int i = 0; i < length; ++i)
		result += toHash[i];

	result %= tableSize;

	return result;
}

/*STREAM DATA LIST IMPLEMENTATIONS*/
StreamDataList::StreamDataList()
{
	head = NULL;
}

StreamDataList::~StreamDataList()
{
	Clear();
}

//If toInsert is NULL, or is already in the list, then return 0.
//Create a new node called temp. Make temp's levelID the same as
//toInsert. Make temp's next head. Finally, set head to temp.
//Return 1
int StreamDataList::Insert(const char* toInsert)
{
	if(!toInsert || Find(toInsert))
		return 0;

	StreamDataNode* temp = new StreamDataNode;
	
	temp->levelID = new char[strlen(toInsert) + 1];
	strcpy(temp->levelID, toInsert);

	temp->next = head;
	head = temp;

	return 1;
}

int StreamDataList::Remove(const char* toRemove)
{
	if(!toRemove)
		return 0;

	return Remove(toRemove, head);
}

//If toRemove or head is NULL, then return. If toRemove and head's levelID
//match, then remove head. Otherwise, call the function again with head's
//next
int StreamDataList::Remove(const char* toRemove, StreamDataNode*& head)
{
	//toRemove is NULL, or the list is empty, or we reached the end
	if(!toRemove || !head)
		return 0;

	StreamDataNode* temp; //If we remove head, use this in the process of removal
	int result; //What we will return
	
	if(strcmp(toRemove, head->levelID) == 0) //We have a match!
	{
		temp = head;
		head = head->next;

		delete temp;
		temp = NULL;

		result = 1;
	}

	else
		result = Remove(toRemove, head->next);

	return result;
}

bool StreamDataList::Find(const char* toFind) const
{
	if(!toFind)
		return false;

	return Find(head, toFind);
}

//If toFind or head are NULL, return false. Otherwise, if head's levelID
//matches toFind, return true. Otherwise, call the function again.
bool StreamDataList::Find(StreamDataNode* head, const char* toFind) const
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !toFind)
		return false;

	if(strcmp(toFind, head->levelID) == 0)
		return true;
	else
		return Find(head->next, toFind);
}

void StreamDataList::Clear()
{
	Clear(head);
}

//Traverse the list. As we return, delete head and set it to
//NULL.
void StreamDataList::Clear(StreamDataNode*& head)
{
	if(!head)
		return;

	Clear(head->next);

	delete head;
	head = NULL;
}

/*INSERT ACTOR LIST WRAPPERS*/

int StreamDataList::InsertActorToInsert(const char* levelID, const char* toInsert, const Vector& pos)
{
	return InsertActorToInsert(levelID, toInsert, pos, head);
}

int StreamDataList::InsertActorToInsert(const char* levelID, const char* toInsert,
										const Vector& pos, StreamDataNode* head)
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !levelID)
		return false;

	if(strcmp(levelID, head->levelID) == 0)
		return head->levelHandler.InsertActorToInsert(toInsert, pos);
	else
		return InsertActorToInsert(levelID, toInsert, pos, head->next);
}

int StreamDataList::AddActorsToLevel(const char* levelID, Level* level,
									 const GameDataHandler& dataHandler)
{
	if(!levelID || !level)
		return 0;

	//Use this to traverse list
	StreamDataNode* temp = head;
	//Success flag to return
	int result;

	//Keep traversing the list until we find our level
	//or we hit NULL
	while(temp && strcmp(levelID, temp->levelID) != 0)
		temp = temp->next;

	if(temp)
	{
		//We found the level, so add any actors needed
		temp->levelHandler.AddActorsToLevel(level, dataHandler);
		//Traversing was a success!
		result = 1;
	}

	else
		//We did not find the level
		result = 0;

	return result;
}

int StreamDataList::RemoveActorToInsert(const char* levelID, const char* toRemove)
{
	return RemoveActorToInsert(levelID, toRemove, head);
}

int StreamDataList::RemoveActorToInsert(const char* levelID, const char* toRemove, StreamDataNode* head)
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !levelID)
		return false;

	if(strcmp(levelID, head->levelID) == 0)
		return head->levelHandler.RemoveActorToInsert(toRemove);
	else
		return RemoveActorToInsert(levelID, toRemove, head->next);
}

/*REMOVE ACTOR LIST WRAPPERS*/

int StreamDataList::InsertActorToRemove(const char* levelID, const char* toInsert)
{
	return InsertActorToRemove(levelID, toInsert, head);
}

int StreamDataList::InsertActorToRemove(const char* levelID, const char* toInsert, StreamDataNode* head)
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !levelID)
		return 0;

	if(strcmp(levelID, head->levelID) == 0)
		return head->levelHandler.InsertActorToRemove(toInsert);
	else
		return InsertActorToRemove(levelID, toInsert, head->next);
}

int StreamDataList::RemoveActorToRemove(const char* levelID, const char* toRemove)
{
	return RemoveActorToRemove(levelID, toRemove, head);
}

int StreamDataList::RemoveActorToRemove(const char* levelID, const char* toRemove, StreamDataNode* head)
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !levelID)
		return false;

	if(strcmp(levelID, head->levelID) == 0)
		return head->levelHandler.RemoveActorToRemove(toRemove);
	else
		return RemoveActorToRemove(levelID, toRemove, head->next);
}

int StreamDataList::RemoveActorsFromLevel(const char* levelID, Level* level,
										  const GameDataHandler& dataHandler)
{
	if(!levelID)
		return 0;

	//Use this to traverse
	StreamDataNode* temp = head;
	//The success flag we return
	int result;

	while(temp && strcmp(temp->levelID, levelID) != 0)
		temp = temp->next;

	if(temp) //We found it!
	{
		temp->levelHandler.RemoveActorsFromLevel(level, dataHandler);
		result = 1;
	}

	else
		result = 0;

	return result;
}

bool StreamDataList::FindActorToRemove(const char* levelID, const char* toFind) const
{
	return FindActorToRemove(levelID, toFind, head);
}

bool StreamDataList::FindActorToRemove(const char* levelID, const char* toFind, StreamDataNode* head) const
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !levelID)
		return false;

	if(strcmp(levelID, head->levelID) == 0)
		return head->levelHandler.FindActorToRemove(toFind);
	else
		return FindActorToRemove(levelID, toFind, head->next);
}

int StreamDataList::ClearActorsToRemove(const char* levelID)
{
	return ClearActorsToRemove(levelID, head);
}

int StreamDataList::ClearActorsToRemove(const char* levelID, StreamDataNode* head)
{
	//toFind is NULL, the list is empty, or we reached the end of the list
	if(!head || !levelID)
		return false;

	if(strcmp(levelID, head->levelID) == 0)
		return head->levelHandler.ClearActorsToRemove();
	else
		return ClearActorsToRemove(levelID, head->next);
}

/*STREAM DATA NODE IMPLEMENTATIONS*/
StreamDataNode::StreamDataNode()
{
	levelID = NULL;
}

StreamDataNode::~StreamDataNode()
{
	if(levelID)
	{
		delete[] levelID;
		levelID = NULL;
	}
}

