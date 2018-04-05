//Liam "AFishyFez" Wynn, 9/13/2015, A Clash of Colors

#include "WeaponTracer.h"
#include "../../../../Utilities/Utility_Components/InputHandler.h"
#include "../../../../Utilities/Utility_Components/Constants.h"
#include "../../../../Level/Level.h"
#include "../../../../Level/WeaponCollisionDataTypes.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

#define FIRE_RATE 100000

WeaponTracer::WeaponTracer()
{
	SetFireRate(FIRE_RATE);

	weaponType = WEP_TYPE_TRCR;
}

WeaponTracer::WeaponTracer(const char* newID) : Weapon(newID)
{
	SetFireRate(FIRE_RATE);

	weaponType = WEP_TYPE_TRCR;
}

WeaponTracer::WeaponTracer(const Weapon& toCopy)
{
	SetFireRate(FIRE_RATE);

	weaponType = WEP_TYPE_TRCR;

	Copy(toCopy);
}

WeaponTracer::~WeaponTracer()
{
}

WeaponTracer& WeaponTracer::operator = (const WeaponTracer& toCopy)
{
	Copy(toCopy);
	return *this;
}

void WeaponTracer::Copy(const WeaponTracer& toCopy)
{
	Weapon::Copy(toCopy);
}

WeaponTracer* WeaponTracer::GetCopy()
{
	return new WeaponTracer(*this);
}

//What will happen here will prove sufficient for virtually all weapons
//in A Clash of Colors. If the conditions for firing the weapon are met,
//we will then create a tracer and add it to the tracer list
void WeaponTracer::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!level)
		return;

	Weapon::Update(level, e, deltaTime);

	tracers.Clear();

	if(FiredWeapon())
	{
		SetWantToFire(false);
		MakeTracer();
		StartFireRateTimer();

		//Handles only one created tracer, so we can call this now
		HandlePotentialHits(level);
	}
}

//Otherwise we get a weird bug where actors can walk
//into lines that we fired previously, and still be
//registered as hits
void WeaponTracer::HandlePotentialHits(Level* level)
{
	if(!level)
		return;

	//Stores all the valid actors we hit
	ActorCollisionList hitActorList;
	//Stores all the wall tiles we hit
	TileCollisionList hitTileList;

	level->HitActor(this, hitActorList);
	level->HitTile(this, hitTileList);

	if(!hitActorList.IsEmpty())
	{
		hitActorList.DoDamageClosestActor(owner, 0.5f);
		cout << "WE HIT AN ACTOR" << endl;
	}

	else
		cout << "We did not hit an actor!" << endl;

	if(!hitTileList.IsEmpty())
		cout << "We hit a wall tile!" << endl;
	else
		cout << "We did not hit a wall tile!" << endl;
	
}

bool WeaponTracer::DidHit(Actor* toCheck)
{
	if(owner == toCheck)
		return false;

	return tracers.HitActor(toCheck);
}

bool WeaponTracer::DidHit(Tile* toCheck)
{
	return tracers.HitTile(toCheck);
}

//If the left mouse button is clicked, and the fire rate timer is not
//running, then we may fire. Otherwise, we may not.
bool WeaponTracer::FiredWeapon()
{
	if(!owner)
		return false;

	bool result; //What we will return

	if(WantToFire() && !IsRecharging())
		result = true;
	else
		result = false;

	return result;
}

//If the owner is NULL, then return. Get the position
//of the owner, and his rotation too. Convert his rotation
//to radians, and use that to construct a new tracer. Add
//toAdd to the tracer stack.
void WeaponTracer::MakeTracer()
{
	if(!owner)
		return;

	//Use these to construct the tracer
	float rotation;
	Vector position;
	
	//The final tracer we will add
	Tracer toAdd;

	rotation = owner->GetRotation();
	//If we fail to grab the position, then return
	if(!owner->GetPosition(position))
		return;

	//Rotation is currently in degrees, but we need it
	//in radians
	rotation *= AEOIAF_PI / 180.0f;

	//Now construct and add the tracer
	toAdd = Tracer(position, rotation);
	tracers.Push(toAdd);

	cout << "Added tracer!" << endl;
}

void WeaponTracer::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                        bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                        Matrix* matrix)
{
	tracers.Draw(renderer, matrix);
}

/*TRACER LIST IMPLEMENTATIONS*/
TracerList::TracerList()
{
	head = NULL;
}

TracerList::TracerList(const TracerList& toCopy)
{
	Copy(toCopy);
}

TracerList::~TracerList()
{
	Clear();
	head = NULL;
}

void TracerList::Copy(const TracerList& toCopy)
{
	if(this == &toCopy)
		return;

	Copy(head, toCopy.head);
}

void TracerList::Copy(TracerListNode*& dest, TracerListNode* source)
{
	if(!source)
	{
		dest = NULL;
		return;
	}

	dest = new TracerListNode(source->tracer);
	Copy(dest->next, source->next);
}

void TracerList::Push(const Tracer& toAdd)
{
	//Use this to save the list
	TracerListNode* temp = head;

	head = new TracerListNode(toAdd);
	head->next = temp;
}

void TracerList::Clear()
{
	Clear(head);
}

void TracerList::Clear(TracerListNode*& head)
{
	if(!head)
		return;

	Clear(head->next);

	delete head;
	head = NULL;
}

bool TracerList::HitActor(Actor* toCheck) const
{
	if(!toCheck)
		return false;

	bool result; //What we will return
	TracerListNode* temp; //Use this to traverse

	temp = head;

	while(temp)
	{
		if(toCheck->CollidesWith(temp->tracer))
		{
			result = true;
			break;
		}

		result = false;
		temp = temp->next;
	}

	return result;
}

bool TracerList::HitTile(AEOIAF_Level::Tile* toCheck) const
{
	if(!toCheck || !toCheck->IsWall())
		return false;

	bool result; //What we will return
	TracerListNode* temp; //Use this to traverse
	AxisAllignedBoundingBox tileBox; //Use this to check collisions

	tileBox = CreateBoundingBox(toCheck->Position(), AEOIAF_TILE_SIZE, AEOIAF_TILE_SIZE);

	temp = head;
	
	while(temp)
	{
		if(temp->tracer.Intersects(tileBox))
		{
			result = true;
			break;
		}

		result = false;
		temp = temp->next;
	}

	return result;
}

void TracerList::Draw(SDL_Renderer* renderer, Matrix* matrix)
{
	//Use this to safely traverse the list
	TracerListNode* temp = head;

	while(temp)
	{
		DrawTracer(temp->tracer, renderer, matrix);
		temp = temp->next;
	}
}

void TracerList::DrawTracer(Tracer& toDraw, SDL_Renderer* renderer, Matrix* matrix)
{
	if(!renderer)
		return;

	Vector start = toDraw.GetStart();
	Vector end = toDraw.GetEnd();

	if(matrix)
	{
		start = Matrix::Transform(start, *matrix);
		end = Matrix::Transform(end, *matrix);
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, (int)start.GetX(), (int)start.GetY(), (int)end.GetX(), (int)end.GetY());
}

/*TRACER LIST NODE*/
TracerListNode::TracerListNode()
{
	next = NULL;
}

TracerListNode::TracerListNode(const Tracer& newTracer)
{
	tracer = newTracer;
	next = NULL;
}

TracerListNode::TracerListNode(const TracerListNode& toCopy)
{
	Copy(toCopy);
}

TracerListNode::~TracerListNode()
{
	next = NULL;
}

TracerListNode& TracerListNode::operator= (const TracerListNode& toCopy)
{
	Copy(toCopy);
	return *this;
}

void TracerListNode::Copy(const TracerListNode& toCopy)
{
	tracer = toCopy.tracer;

	next = NULL;
}
