//Liam "AFishyFez" Wynn, 1/20/2016, An Engine of Ice and Fire

#include "../LevelDataTypes.h"
#include "../../Actors/Particle/Particle.h"
#include "../Level.h"

using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;

/*PARTICLE LIST IMPLEMENTATIONS*/
ParticleList::ParticleList()
{
	head = NULL;
}

ParticleList::~ParticleList()
{
	ClearAll();
}

//If toAdd is NULL, then return. Otherwise, create a new node,
//and set its data to toAdd. Then set its next to head. Finally,
//set head to this new node
void ParticleList::Insert(ParticleEmitter* toAdd)
{
	if(!toAdd)
		return;

	//The new head of the list
	ParticleListNode* temp = new ParticleListNode;
	temp->data = toAdd;
	temp->next = head;
	head = temp;
}

int ParticleList::Remove(const char* toRemove)
{
	return Remove(toRemove, head);
}

int ParticleList::Remove(const char* toFind, ParticleListNode*& head)
{
	return 0;
}

int ParticleList::Find(const char* toFind)
{
	return 0;
}

void ParticleList::ClearAll()
{
}

void ParticleList::Update(Level* currentLevel, SDL_Event* e, float deltaTime)
{
	Update(currentLevel, e, deltaTime, head);
}

void ParticleList::Update(Level* currentLevel, SDL_Event* e, float deltaTime, ParticleListNode*& head)
{
    if(!head)
        return;

    if(head->data)
    {
        head->data->Update(currentLevel, e, deltaTime);

        if(head->data->MustDestroy())
        {
            ParticleListNode* temp = head->next;
            delete head;
            head = temp;

            Update(currentLevel, e, deltaTime, head); //Don't skip the next particle in the list!
        }
    }

	//At this point, we could've destroyed the tail, so we need to check if it still exists
	if(head)
		Update(currentLevel, e, deltaTime, head->next);
}

void ParticleList::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
						bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
						Matrix* matrix)
{
	ParticleListNode* temp = head;

	while(temp)
	{
		if(temp->data)
			temp->data->Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);

		temp = temp->next;
	}
}

/*PARTICLE LIST NODE IMPLEMENTATIONS*/
ParticleListNode::ParticleListNode()
{
	data = NULL;
	next = NULL;
}

ParticleListNode::~ParticleListNode()
{
	if(data)
	{
		delete data;
		data = NULL;
	}

	next = NULL;
}
