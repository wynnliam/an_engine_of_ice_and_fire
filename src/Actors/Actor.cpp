//Liam "AFishyFez", 4/12/2015, AEOIAF: Actor

#include "Actor.h"
#include "../Utilities/General_Purpose/Tracer.h"
#include "../Utilities/Utility_Components/Constants.h"
#include <cstring>
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace std;

Actor::Actor()
{
    id = NULL;
    name = NULL;

	CreateComponents();

	bIsPossessed = false;
	bMustDestroy = false;

	rotation = 0.0f;
}

Actor::Actor(const char* newID)
{
    if(!newID)
        id = NULL;
    else
    {
        id = new char[strlen(newID) + 1];
        strcpy(id, newID);
    }

    name = NULL;

	CreateComponents();

	bIsPossessed = false;
	bMustDestroy = false;

	rotation = 0.0f;
}

Actor::Actor(const Actor& toCopy)
{
	//Make sure default values are set
	//before attempting to copy
    id = NULL;
    name = NULL;

	CreateComponents();

	bIsPossessed = false;
	bMustDestroy = false;

    Copy(toCopy);

	rotation = 0.0f;
}

Actor::~Actor()
{
    if(id)
        delete[] id;
    if(name)
        delete[] name;
    if(movableComponent)
        delete movableComponent;
    if(collisionComponent)
        delete collisionComponent;

    id = NULL;
    name = NULL;
	//The drawable component is handled elsewhere
    drawableComponent = NULL;
    movableComponent = NULL;
    collisionComponent = NULL;
}

Actor& Actor::operator = (const Actor& toCopy)
{
    Copy(toCopy);
    return *this;
}

int Actor::GetID(char*& copyTo) const
{
    int result; //What we will return

    if(!id || id == copyTo)
        result = 0;

    else
    {
        copyTo = new char[strlen(id) + 1];
        strcpy(copyTo, id);

        result = 1;
    }


    return result;
}

int Actor::SetID(const char* newId)
{
    if(id == newId)
        return 0;

    if(id)
        delete[] id; //Free memory if we are overriding it

    int result; //What we will return

    if(!newId)
    {
        id = NULL;
        result = 0;
    }

    else
    {
        id = new char[strlen(newId) + 1];
        strcpy(id, newId);

        result = 1;
    }

    return result;
}

int Actor::GetName(char*& copyTo) const
{
    int result; //What we are returning

    if(!name || name == copyTo)
        result = 0;
    else
    {
        copyTo = new char[strlen(name) + 1];
        strcpy(copyTo, name);

        result = 1;
    }

    return result;
}

int Actor::SetName(const char* newName)
{
    if(name == newName)
        return 0;

    if(name)
        delete[] name; //Free memory if we are overriding it

    int result; //What we are returning

    if(!newName)
    {
        name = NULL;

        result = 0;
    }

    else
    {
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);

        result = 1;
    }

    return result;
}

void Actor::SetDrawableComponent(DrawableComponent* draw)
{
    drawableComponent = draw;
}

void Actor::SetMovableComponent(MovableComponent* mov)
{
    if(mov == movableComponent)
        return;

    if(movableComponent)
        delete movableComponent;

    movableComponent = mov;
}

void Actor::SetCollisionComponent(CollisionComponent* col)
{
    if(col == collisionComponent)
        return;

    if(collisionComponent)
        delete collisionComponent;

    collisionComponent = col;
}

bool Actor::IsPossessed() const
{
	return bIsPossessed;
}

void Actor::SetIsPossessed(const bool val)
{
	bIsPossessed = val;
}

bool Actor::MustDestroy() const
{
	return bMustDestroy;
}

void Actor::SetMustDestroy(const bool val)
{
	bMustDestroy = val;
}

int Actor::GetWidth() const
{
	if(!drawableComponent)
		return 0;

	return drawableComponent->GetWidth();
}

int Actor::GetHeight() const
{
	if(!drawableComponent)
		return 0;

	return drawableComponent->GetHeight();
}

int Actor::GetPosition(Vector& result) const
{
    if(!movableComponent)
        return 0;

    result = movableComponent->GetPosition();

    return 1;
}

int Actor::SetPosition(const Vector& val)
{
    if(!movableComponent)
        return 0;

	movableComponent->SetPosition(val);

    return 1;
}

float Actor::GetRotation() const
{
	return rotation;
}

void Actor::SetRotation(float val)
{
	rotation = val;
}

void Actor::Copy(const Actor& toCopy)
{
    if(this == &toCopy)
        return;

    if(toCopy.drawableComponent)
		//Don't want to make a copy!
        SetDrawableComponent(toCopy.drawableComponent);

    if(toCopy.movableComponent)
        SetMovableComponent(toCopy.movableComponent->GetCopy());

    if(toCopy.collisionComponent)
        SetCollisionComponent(toCopy.collisionComponent->GetCopy());

    SetName(toCopy.name);
    SetID(toCopy.id);
}

Actor* Actor::GetCopy()
{
	Actor* result = new Actor(*this);

	return result;
}

//Use toCheck's movableComponent and collisionComponent to
//create a bounding box with position accounted for. Then call
//our collisionComponent's Contains functions
bool Actor::CollidesWith(Actor* toCheck) const
{
	if(!collisionComponent || !movableComponent || !toCheck ||
	   !toCheck->collisionComponent || !toCheck->movableComponent)
		return false;

	//Used for collision component collision check
	AxisAllignedBoundingBox toCheckBox;

	toCheckBox = toCheck->collisionComponent->GetBoundingBox();
	toCheckBox.AddVector(toCheck->movableComponent->GetPosition());

	return collisionComponent->Contains(movableComponent->GetPosition(), toCheckBox);
}

//Pretty much only used for melee weapons. I may change that, but
//it's such a cluster fuck that it's not worth it, in my opinion
bool Actor::CollidesWith(AxisAllignedBoundingBox& toCheck) const
{
	if(!collisionComponent || !movableComponent)
		return false;

	return collisionComponent->Contains(movableComponent->GetPosition(), toCheck);
}

bool Actor::CollidesWith(const Tracer& tracer) const
{
	if(!collisionComponent || !movableComponent)
		return false;

	return collisionComponent->Contains(movableComponent->GetPosition(), tracer);
}

//Get the vector between lookAt and our position. Use atan2
//on this to get the rotation. Convert to degrees. Set actor
//rotation to result
void Actor::LookAt(Vector& lookAt)
{
	if(!movableComponent)
		return;

	Vector diff = lookAt - movableComponent->GetPosition(); //USe Atan2 on
	float rotation = (float)atan2(diff.GetY(), diff.GetX()); //Our rotation

	//Convert to degrees
	rotation *= 180.0f / AEOIAF_PI;

	SetRotation(rotation);
}

void Actor::DoDamage(Actor* instigator, const float damage)
{
	if(!instigator)
		return;

	cout << instigator->id << " did " << damage << " damage to " << id << endl;
}

void Actor::Display()
{
    if(id)
        cout << "Actor ID: " << id << endl;
    if(name)
        cout << "Actor Name: " << name << endl;
}

bool Actor::CompareID(const char* compareTo)
{
    return compareTo && strcmp(compareTo, id) == 0;
}

void Actor::CreateComponents()
{
	drawableComponent = NULL;
	movableComponent = NULL;
	collisionComponent = NULL;
}

void Actor::Update(Level* level, SDL_Event* e, float deltaTime)
{
}

//Draw the actor
void Actor::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                 bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                 Matrix* matrix)
{
    Vector position; //Where we will render the actor's texture
    if(movableComponent)
        position = movableComponent->GetPosition();

    if(drawableComponent)
	{
		drawableComponent->SetRotation(rotation);
		drawableComponent->GetColor() = color;
        drawableComponent->Draw(renderer,
                                position,
                                flip,
                                bTrsfrmRot,
                                bTrsfrmScale,
                                bTrsfrmPos,
                                matrix);
	}
}
