//Liam "AFishyFez" Wynn, 6/19/2016, An Engine of Ice and Fire

#include "DrawComponentList.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_Utilities;
using namespace std;

/*DRAW COMPONENT TABLE*/
DrawComponentTable::DrawComponentTable(int size)
{
	tableSize = size;

	table = new DrawComponentTableNode*[tableSize];
	for(int i = 0; i < tableSize; ++i)
		table[i] = NULL;
}

DrawComponentTable::~DrawComponentTable()
{
	if(!table)
		return;

	Clear();

	delete[] table;
	table = NULL;
}

void DrawComponentTable::Insert(const char* id, DrawableComponent* component)
{
	int hashIndex = GetHashIndex(id);

	if(hashIndex == -1)
		return;

	DrawComponentTableNode* toAdd = new DrawComponentTableNode;
	toAdd->SetID(id);
	toAdd->drawComponent = component;
	toAdd->next = table[hashIndex];
	table[hashIndex] = toAdd;
}

DrawableComponent* DrawComponentTable::GetDrawableComponent(const char* id) const
{
	int hashIndex = GetHashIndex(id);
	DrawableComponent* result;

	if(hashIndex == -1)
		result = NULL;
	else
		result = GetDrawableComponent(id, table[hashIndex]);

	return result;
}

DrawableComponent* DrawComponentTable::GetDrawableComponent(const char* id, DrawComponentTableNode* head) const
{
	if(!head)
		return NULL;

	DrawableComponent* result = NULL;
	DrawComponentTableNode* temp = head;

	while(temp)
	{
		if(temp->CompareID(id))
		{
			result = temp->drawComponent;
			break;
		}

		else
			temp = temp->next;
	}

	return result;
}

int DrawComponentTable::GetHashIndex(const char* toHash) const
{
	if(!toHash)
		return -1;

	int result = 0;
	int len = strlen(toHash);

	for(int i = 0; i < len; ++i)
		result += toHash[i];

	result %= tableSize;

	return result;
}

void DrawComponentTable::Clear()
{
	if(!table)
		return;

	for(int i = 0; i < tableSize; ++i)
		ClearList(table[i]);
}

void DrawComponentTable::ClearList(DrawComponentTableNode*& head)
{
	if(!head)
		return;

	ClearList(head->next);

	delete head;
	head = NULL;
}

/*DRAW COMPONENT TABLE NODE IMPLEMENTATIONS*/
DrawComponentTableNode::DrawComponentTableNode()
{
	id = NULL;
	drawComponent = NULL;
	next = NULL;
}

DrawComponentTableNode::~DrawComponentTableNode()
{
	if(id)
	{
		delete[] id;
		id = NULL;
	}

	if(drawComponent)
	{
		delete drawComponent;
		drawComponent = NULL;
	}

	next = NULL;
}

void DrawComponentTableNode::SetID(const char* val)
{
	if(!val)
		return;

	if(id)
		delete[] id;

	id = new char[strlen(val) + 1];
	strcpy(id, val);
}

bool DrawComponentTableNode::CompareID(const char* compareTo)
{
	if(!compareTo)
		return id == NULL;
	else
		return strcmp(id, compareTo) == 0;
}
