//Liam "AFishyFez" Wynn, 12/24/2015, An Engine of Ice and Fire

#include "../LevelDataTypes.h"
#include <cstring>

using namespace AEOIAF_Level;
using namespace std;

/*STACK IMPLEMENTATIONS*/
RemoveScriptSequenceStack::RemoveScriptSequenceStack()
{
	head = NULL;
}

RemoveScriptSequenceStack::~RemoveScriptSequenceStack()
{
	Clear();
}

//Return 0 if toAdd is NULL. Otherwise push it onto the stack,
//and return 1.
int RemoveScriptSequenceStack::Push(const char* toAdd)
{
	if(!toAdd)
		return 0;

	//The new head of the stack
	RemoveScriptSequenceNode* temp = new RemoveScriptSequenceNode;
	
	temp->sequenceID = new char[strlen(toAdd) + 1];
	strcpy(temp->sequenceID, toAdd);

	temp->next = head;
	head = temp;

	return 1;
}

int RemoveScriptSequenceStack::Pop()
{
	if(!head)
		return 0;

	//Use this to deallocate
	RemoveScriptSequenceNode* temp = head;

	head = head->next;

	delete temp;
	temp = NULL;

	return 1;
}

char* RemoveScriptSequenceStack::Peek()
{
	char* result; //What we will return

	if(!head)
		result = NULL;
	else
	{
		result = new char[strlen(head->sequenceID) + 1];
		strcpy(result, head->sequenceID);
	}

	return result;
}

int RemoveScriptSequenceStack::Clear()
{
	int result = 0; //What we will return

	while(!IsEmpty())
	{
		Pop();
		++result;
	}

	return result;
}

bool RemoveScriptSequenceStack::IsEmpty()
{
	return !head;
}

/*NODE IMPLEMENTATIONS*/
RemoveScriptSequenceNode::RemoveScriptSequenceNode()
{
	sequenceID = NULL;
	next = NULL;
}

RemoveScriptSequenceNode::~RemoveScriptSequenceNode()
{
	if(sequenceID)
	{
		delete[] sequenceID;
		sequenceID = NULL;
	}

	next = NULL;
}
