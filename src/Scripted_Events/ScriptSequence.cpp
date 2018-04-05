//Liam "AFishyFez" Wynn, 11/30/2015, An Engine of Ice and Fire

#include "ScriptSequence.h"
#include "../Actors/Actor.h"
#include "../Level/Level.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_ScriptedEvents;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace std;

/*SCRIPT SEQUENCE IMPLEMENTATIONS*/
ScriptSequence::ScriptSequence()
{
	id = NULL;
	rear = NULL;
	bCanRun = false;
}

ScriptSequence::ScriptSequence(const ScriptSequence& toCopy)
{
	id = NULL;
	rear = NULL;
	bCanRun = false;

	Copy(toCopy);
}

ScriptSequence::~ScriptSequence()
{
	if(id)
	{
		delete[] id;
		id = NULL;
	}

	Clear();
}

int ScriptSequence::GetID(char*& result) const
{
	if(!id)
		return 0;

	result = new char[strlen(id) + 1];
	strcpy(result, id);

	return 1;
}

int ScriptSequence::SetID(const char* val)
{
	if(!val)
		return 0;

	if(id) //Deallocate it if it's already set
		delete[] id;

	id = new char[strlen(val) + 1];
	strcpy(id, val);

	return 1;
}


ScriptSequence& ScriptSequence::operator= (const ScriptSequence& toCopy)
{
	Copy(toCopy);

	return *this;
}

bool ScriptSequence::operator== (const ScriptSequence& compareTo) const
{
	return Equals(&compareTo);
}

bool ScriptSequence::operator== (const char* compareTo) const
{
	return Equals(compareTo);
}

//If compareTo is NULL, then return false. Otherwise, return the
//result of the other Equals function. For that, use compareTo's id
bool ScriptSequence::Equals(const ScriptSequence* compareTo) const
{
	if(!compareTo)
		return false;

	return Equals(compareTo->id);
}

//If compareTo or id are NULL, then return false. Otherwise return
//that id and compareTo are the same
bool ScriptSequence::Equals(const char* compareTo) const
{
	if(!id || !compareTo)
		return false;

	return strcmp(id, compareTo) == 0;
}

//If this and toCopy are the same or toCopy is empty return. 
//Set bCanRun to toCopy's bCanRun.Clear this list. Break 
//toCopy into a linear linked list. Call the recursive
//function. Reset toCopy at the end
void ScriptSequence::Copy(const ScriptSequence& toCopy)
{
	if(this == &toCopy || toCopy.IsEmpty() ||!id)
		return;

	//Use this to keep from losing nodes when breaking
	//toCopy into a LLL
	ScriptActionNode* toCopyHead = toCopy.rear->next;

	bCanRun = toCopy.bCanRun;	

	Clear();

	toCopy.rear->next = NULL;
	Copy(toCopyHead);
	toCopy.rear->next = toCopyHead;
}

//If source is NULL, then return. Otherwise, enqueue
//a copy of source's action into this list. Call the
//function again with source's next
void ScriptSequence::Copy(ScriptActionNode* source)
{
	if(!source)
		return;

	if(source->action)
		Enqueue(source->action->GetCopy());

	Copy(source->next);
}

//Create a new Script Action Node. If rear is NULL, then have the new node point to
//itself and then have rear point to this new node. Otherwise, store rear's next in
//a temporary node. Then make rear's next the new node. Next, set rear to this new
//next. Finally, have rear's next be temp.
void ScriptSequence::Enqueue(ScriptAction* toAdd)
{
	ScriptActionNode* nodeToAdd; //The node being added to the queue
	ScriptActionNode* temp; //Use this to store rear's next before adding the new node

	nodeToAdd = new ScriptActionNode;
	nodeToAdd->action = toAdd;

	//Special case: rear is NULL
	if(!rear)
	{
		nodeToAdd->next = nodeToAdd;
		rear = nodeToAdd;
	}

	//General case
	else
	{
		temp = rear->next;
		rear->next = nodeToAdd;
		rear = nodeToAdd;
		rear->next = temp;
	}
}

//If bCanRun is false, then call UpdateCanRun. Otherwise, call
//UpdateQueue
void ScriptSequence::Update(Level* level, float deltaTime)
{
	if(!bCanRun)
		UpdateCanRun();
	else
		UpdateQueue(level, deltaTime);
}

void ScriptSequence::UpdateCanRun()
{
	bCanRun = true;
}

//If rear or level is NULL, then return. Update rear's next (the 
//front of the queue). If it is complete, or its action is NULL,
//then dequeue.
void ScriptSequence::UpdateQueue(Level* level, float deltaTime)
{
	if(!rear || !level) 
		return;

	//Use this to get the front most item in the queue
	//and to avoid pointer dereferencing all over the place
	ScriptAction* action = rear->next->action;

	if(action && !action->IsComplete())
		action->Update(level, deltaTime);
	else
		Dequeue(); //Remove the front item, as its action is NULL or complete
}

//If rear is NULL, then return. If rear is the only item, then
//just delete rear and set it to NULL. Otherwise, set rear's next
//to be the next of rear's next. Then delete the rear's original
//next
void ScriptSequence::Dequeue()
{
	if(!rear)
		return;

	//Stores the item we want to remove
	ScriptActionNode* temp;

	if(rear->next == rear)
	{
		delete rear;
		rear = NULL;
	}

	else
	{
		temp = rear->next;
		rear->next = temp->next;
		delete temp;
		temp = NULL;
	}
}

//Keep removing the front item until the
//entire queue is empty
void ScriptSequence::Clear()
{
	while(!IsEmpty())
		Dequeue();
}

bool ScriptSequence::IsEmpty() const
{
	return rear == NULL;
}

/*SCRIPT ACTION IMPLEMENTATIONS*/
ScriptAction::ScriptAction()
{
	toOverride = NULL;
	bComplete = false;
}

ScriptAction::ScriptAction(Actor* newToOverride)
{
	toOverride = newToOverride;
	bComplete = false;
}

ScriptAction::ScriptAction(const ScriptAction& toCopy)
{
	toOverride = NULL;
	bComplete = false;
}

//toOverride is handled elsewhere, so we don't want to
//deallocate him!
ScriptAction::~ScriptAction()
{
	toOverride = NULL;
}

//If toCopy's address is the same as this one, then return.
//Otherwise assign toCopy's data to the data here
void ScriptAction::Copy(const ScriptAction& toCopy)
{
	if(&toCopy == this)
		return; //Lest we get problems!

	//Since toOverride is handled elsewhere, we don't want to
	//deallocate him!
	toOverride = toCopy.toOverride;
	bComplete = toCopy.bComplete;
}

ScriptAction* ScriptAction::GetCopy()
{
	return NULL;
}

/*SCRIPT ACTION NODE IMPLEMENTATIONS*/

ScriptActionNode::ScriptActionNode()
{
	action = NULL;
	next = NULL;
}

ScriptActionNode::ScriptActionNode(const ScriptActionNode& toCopy)
{
	action = NULL;
	next = NULL;

	Copy(toCopy);
}

ScriptActionNode::~ScriptActionNode()
{
	if(action)
	{
		delete action;
		action = NULL;
	}

	next = NULL;
}

//If action and val are the same, return.
//If val is NULL, then return. If action 
//is not NULL, then delete it. Set action 
//to val
void ScriptActionNode::SetScriptAction(ScriptAction* val)
{
	if(!val || action == val)
		return; //Don't want to cause problems!

	if(action)
		delete action; //Avoids the memory leak

	action = val->GetCopy();
}

//If this and toCopy are the same node, then return. Otherwise,
//set action to toCopy's action
void ScriptActionNode::Copy(const ScriptActionNode& toCopy)
{
	if(&toCopy == this)
		return;

	SetScriptAction(toCopy.action);
}
