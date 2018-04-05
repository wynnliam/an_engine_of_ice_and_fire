//Liam "AFishyFez" Wynn, 1/25/2016, A Clash of Colors

#include "PropDoor.h"
#include "../../../Level/Level.h"
#include "../../../Utilities/Utility_Components/InputHandler.h"
#include <iostream>
#include <cstring>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace std;

PropDoor::PropDoor()
{
	nextLevelName = NULL;
	CreateComponents();
}

PropDoor::PropDoor(const char* newID) : Prop(newID)
{
	nextLevelName = NULL;
	CreateComponents();
}

PropDoor::PropDoor(const PropDoor& toCopy)
{
	nextLevelName = NULL;
	Copy(toCopy);
}

PropDoor::~PropDoor()
{
	if(nextLevelName)
	{
		delete[] nextLevelName;
		nextLevelName = NULL;
	}
}

PropDoor& PropDoor::operator = (const PropDoor& toCopy)
{
	Copy(toCopy);
	return *this;
}

bool PropDoor::SetNextLevelName(const char* val)
{
	if(!val)
		return false;

	if(nextLevelName)
		delete[] nextLevelName;

	nextLevelName = new char[strlen(val) + 1];
	strcpy(nextLevelName, val);

	return true;
}

void PropDoor::Copy(const PropDoor& toCopy)
{
	if(this == &toCopy)
		return;

	SetNextLevelName(toCopy.nextLevelName);
	Prop::Copy(toCopy);
}

PropDoor* PropDoor::GetCopy()
{
	return new PropDoor(*this);
}

void PropDoor::CreateComponents()
{
	//SetDrawableComponent(new DrawableComponent("Content/door.png"));
	SetMovableComponent(new MovableComponent);
	SetCollisionComponent(new CollisionComponent(16, 64));
}

void PropDoor::Update(Level* level, SDL_Event* e)
{
    CheckActivated(level);

    if(bIsActive)
        HandleActivated(level, e);
    if(bDamaged)
        HandleDamaged(level, e);
}

void PropDoor::CheckActivated(Level* level)
{
    if(!level || !movableComponent || !collisionComponent)
        return;

    if(InputHandler::KeyPressedOnce(SDL_SCANCODE_E))
    {
        Vector currentPos = movableComponent->GetPosition();
        Vector playerPos = level->GetPlayerPosition();
        Vector mousePoint = level->GetMousePosition();
        AxisAllignedBoundingBox mouseRect(mousePoint.GetX(), mousePoint.GetY(),
                                          mousePoint.GetX() + 1, mousePoint.GetY() + 1);

        float dist = (playerPos - currentPos).GetMagnitude();

        if(dist <= maxActivateDist && collisionComponent->Contains(currentPos, mouseRect))
            bIsActive = true;
    }
}

void PropDoor::HandleActivated(Level* currentLevel, SDL_Event* e)
{
	if(nextLevelName)
		currentLevel->SetNextLevelName(nextLevelName);

    bIsActive = false;
}

void PropDoor::HandleDamaged(Level* currentLevel, SDL_Event* e)
{
    cout << "Prop: I've been damaged!" << endl;
    bDamaged = false;
}
