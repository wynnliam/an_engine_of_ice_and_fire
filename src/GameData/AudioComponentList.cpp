//Liam "AFishyFez" Wynn, 8/1/2016, An Engine of Ice and Fire

#include "AudioComponentList.h"
#include <cstring>
#include <iostream> //For NULL and debugging

using namespace AEOIAF_Utilities;
using namespace std;

/*AUDIO COMPONENT LIST IMPLEMENTATIONS*/

AudioComponentList::AudioComponentList(int size)
{
	if(size < 7)
		tableSize = 7;
	else
		tableSize = size;
	
	table = new AudioComponentListNode*[tableSize];
	for(int i = 0; i < tableSize; ++i)
		table[i] = NULL;
}

AudioComponentList::~AudioComponentList()
{
	Clear();

	delete[] table;
	table = NULL;
}

void AudioComponentList::Insert(const char* id, AudioComponent* toInsert)
{
	if(!id || !toInsert || !table)
		return;

	int hashIndex = GetHashIndex(id);
	AudioComponentListNode* temp = new AudioComponentListNode;
	
	temp->component = toInsert;
	temp->next = table[hashIndex];
	temp->id = new char[strlen(id) + 1];
	strcpy(temp->id, id);
	table[hashIndex] = temp;
}

AudioComponent* AudioComponentList::GetComponent(const char* id) const
{
	if(!id || !table)
		return NULL;

	AudioComponent* result;
	int hashIndex = GetHashIndex(id);

	if(hashIndex == -1)
		result = NULL;
	else
		result = GetComponent(id, table[hashIndex]);

	return result;
}

AudioComponent* AudioComponentList::GetComponent(const char* id, AudioComponentListNode* head) const
{
	if(!id)
		return NULL;

	AudioComponentListNode* temp = head;
	AudioComponent* result = NULL;

	while(temp)
	{
		if(strcmp(id, temp->id) == 0)
		{
			result = temp->component;
			break;
		}

		else
			temp = temp->next;
	}

	return result;
}

void AudioComponentList::Clear()
{
	if(!table)
		return;

	for(int i = 0; i < tableSize; ++i)
		Clear(table[i]);
}

void AudioComponentList::Clear(AudioComponentListNode*& head)
{
	if(!head)
		return;

	Clear(head->next);

	delete head;
	head = NULL;
}

int AudioComponentList::GetHashIndex(const char* toHash) const
{
	if(!toHash || tableSize <= 0)
		return -1;

	int result = 0;
	int len = strlen(toHash);

	for(int i = 0; i < len; ++i)
		result += toHash[i];

	result %= tableSize;

	return result;
}

/*AUDIO COMPONENT LIST NODE IMPLEMENTATIONS*/

AudioComponentListNode::AudioComponentListNode()
{
	id = NULL;
	component = NULL;
	next = NULL;
}

AudioComponentListNode::~AudioComponentListNode()
{
	if(id)
	{
		delete[] id;
		id = NULL;
	}

	if(component)
	{
		delete component;
		component = NULL;
	}

	next = NULL;
}
