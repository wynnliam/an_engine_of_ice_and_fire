//Liam "AFishyFez" Wynn, 4/27/2015, AEOIAF: Level Prop List

#include "../LevelDataTypes.h"
#include "../Level.h"
#include "../WeaponCollisionDataTypes.h"
#include "../../Actors/Prop/Prop.h"
#include "../../Actors/Item/Weapon/Weapon.h"
#include "../../Utilities/General_Purpose/Matrix.h"
#include "../../Utilities/Utility_Components/Camera.h"
#include "../../GameData/StreamData/StreamData.h"
#include <cstring>

using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace ACOC_GameDataHandling;
using namespace std;

PropList::PropList()
{
    head = NULL;
    numProps = 0;
}

PropList::~PropList()
{
    ClearAll();
}

void PropList::Add(Prop* toAdd)
{
    PropListNode* temp = new PropListNode;
    temp->data = toAdd;
    temp->next = head;

    head = temp;

    ++numProps;
}

int PropList::Remove(const char* id)
{
    int result = Remove(id, head);

    if(result)
        --numProps;

    return result;
}

int PropList::Remove(const char* id, PropListNode*& head)
{
    if(!id || !head)
        return 0;

    if(head->data && head->data->CompareID(id))
    {
        PropListNode* temp = head->next;
        delete head;
        head = temp;

        return 1;
    }

    return 1 + Remove(id, head->next);
}

int PropList::Remove(int position)
{
    int result = Remove(0, position, head);

    if(result)
        --numProps;

    return result;
}

int PropList::Remove(int current, int length, PropListNode*& head)
{
    if(current < 0 || current >= numProps || !head)
        return 0;

    if(current == length)
    {
        PropListNode* temp = head->next;
        delete head;
        head = temp;

        return 1;
    }

    return Remove(current + 1, length, head->next);
}

Prop* PropList::Find(char* id)
{
    return Find(id, head);
}

//Will find the first match by id, or return NULL
Prop* PropList::Find(char* id, PropListNode* head)
{
    if(!head || !id)
        return NULL;

    if(head->data && head->data->CompareID(id))
        return head->data;

    return Find(id, head->next);
}

Prop* PropList::Find(int position)
{
    return Find(0, position, head);
}

Prop* PropList::Find(int current, int length, PropListNode* head)
{
    if(current < 0 || current >= numProps || !head)
        return NULL;

    if(current == length)
        return head->data;

    return Find(current + 1, length, head->next);
}

//Traverse the list and remove all items in it
void PropList::ClearAll()
{
    PropListNode* temp;

    while(head)
    {
        temp = head->next;
        delete head;
        head = temp;
    }

    temp = NULL; //For safety
    head = NULL;
}

void PropList::Update(Level* currentLevel, SDL_Event* e, float deltaTime,
					  StreamDataHandler& streamData)
{
    Update(currentLevel, e, deltaTime, head, streamData);
}

void PropList::Update(Level* currentLevel, SDL_Event* e, float deltaTime,
					  PropListNode*& head, StreamDataHandler& streamData)
{
    if(!head)
        return;

	//So we can add information about currentLevel to
	//streamData
	char* levelID;
	//If we remove the prop, we use its ID to save
	//in streamData
	char* propID;

    if(head->data)
    {
        head->data->Update(currentLevel, e, deltaTime);

        if(head->data->MustDestroy())
        {
			//Before we destroy, we need to put the actor into
			//the remove actor list
			currentLevel->GetID(levelID);
			head->data->GetID(propID);

			//If removing from the InsertActorList fails,
			//add to the remove actor list
			if(streamData.RemoveActorToInsert(levelID, propID) == 0)
				//The prop was from the original level, and not inserted
				//after loading from file
				streamData.InsertActorToRemove(levelID, propID);

			delete[] levelID; levelID = NULL;
			delete[] propID; propID = NULL;

            PropListNode* temp = head->next;
            delete head;
            head = temp;

            Update(currentLevel, e, deltaTime, head, streamData); //Don't skip the next prop in the list!
        }
    }

	//At this point, we could've destroyed the tail, so we need to check if it still exists
	if(head)
		Update(currentLevel, e, deltaTime, head->next, streamData);
}

//If checkWith is NULL, then return. Otherwise, call the recursive version of this
//function
void PropList::FindHitProps(Weapon* checkWith, ActorCollisionList& hitList) const
{
	if(!checkWith)
		return;

	FindHitProps(checkWith, hitList, head);
}

//If checkWith or head are NULL, or if the number of props in head is 0, then return. Otherwise,
//For each prop, if it collides with checkWith, then add it to the hitList. If the number of props
//in head is greater than or equal to the maximum number of props for a node, then call the
//function again with next, because only then can there be more props than a single node can carry
void PropList::FindHitProps(Weapon* checkWith, ActorCollisionList& hitList, PropListNode* head) const
{
	if(!checkWith || !head)
		return;

	if(checkWith->DidHit(head->data))
		hitList.Add(head->data, checkWith);

	FindHitProps(checkWith, hitList, head->next);
}

void PropList::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
          bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
          Matrix* matrix, Camera* drawCam)
{
    PropListNode* temp = head;

    while(temp)
    {
        if(temp->data && drawCam->CanSee(temp->data))
            temp->data->Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);

        temp = temp->next;
    }
}

/*PROP NODE IMPLEMENTATIONS*/
PropListNode::PropListNode()
{
    data = NULL;
    next = NULL;
}

PropListNode::~PropListNode()
{
    if(data)
        delete data;

    data = NULL;
    next = NULL;
}
