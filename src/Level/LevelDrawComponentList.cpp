//Liam "AFishyFez" Wynn, 3/16/2016, An Engine of Ice and Fire

#include "LevelDrawComponentList.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_Level;
using namespace std;

/*LIST IMPLEMENTATIONS*/

LevelDrawComponentList::LevelDrawComponentList()
{
	head = NULL;
}

LevelDrawComponentList::~LevelDrawComponentList()
{
	Clear();
}

void LevelDrawComponentList::Insert(LevelDrawComponent* toInsert)
{
	if(!toInsert)
		return;

	//If we can insert, we use this to do so
	LevelDrawComponentNode* temp = NULL;
	//Use this to check if toInsert is valid
	char* texPath = NULL;

	toInsert->GetTexturePath(texPath);

	if(texPath && !Contains(texPath))
	{
		temp = new LevelDrawComponentNode;
		temp->component = toInsert;
		temp->next = head;

		head = temp;

		delete[] texPath;
		texPath = NULL;
	}
}

bool LevelDrawComponentList::Contains(const char* texturePath) const
{
	if(!texturePath)
		return false;

	LevelDrawComponentNode* temp = head;
	bool result = false;

	while(temp)
	{
		result = Compare(temp, texturePath);

		if(result == true)
			temp = NULL;
		else
			temp = temp->next;
	}

	return result;
}

LevelDrawComponent* LevelDrawComponentList::GetComponent(const char* texturePath) const
{
	if(!texturePath)
		return NULL;

	LevelDrawComponent* result = NULL; //What we will return
	LevelDrawComponentNode* temp = head;

	while(temp)
	{
		if(Compare(temp, texturePath) == true)
		{
			result = temp->component;
			break;
		}

		else
			temp = temp->next;
	}

	return result;
}

bool LevelDrawComponentList::Compare(const LevelDrawComponentNode* node,
									 const char* texturePath) const
{
	char* nodeTexPath = NULL;
	bool result;

	node->component->GetTexturePath(nodeTexPath);

	result = strcmp(nodeTexPath, texturePath) == 0;

	delete[] nodeTexPath;
	nodeTexPath = NULL;

	return result;
}

void LevelDrawComponentList::Clear()
{
	LevelDrawComponentNode* temp = head;

	while(temp)
	{
		head = head->next;
		delete temp;
		temp = head;
	}

	head = NULL;
	temp = NULL;
}

/*NODE IMPLEMENTATIONS*/

LevelDrawComponentNode::LevelDrawComponentNode()
{
	component = NULL;
	next = NULL;
}

LevelDrawComponentNode::~LevelDrawComponentNode()
{
	if(component)
	{
		delete component;
		component = NULL;
	}

	next = NULL;
}
