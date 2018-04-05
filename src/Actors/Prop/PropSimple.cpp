//Liam "AFishyFez" Wynn, 1/15/2016, An Engine of Ice and Fire

#include "PropSimple.h"
#include "../../Level/Level.h"
#include "../../Utilities/Utility_Components/InputHandler.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace std;

PropSimple::PropSimple()
{
	CreateComponents();
}

PropSimple::PropSimple(const char* newID) : Prop(newID)
{
	CreateComponents();
}

PropSimple::PropSimple(const PropSimple& toCopy)
{
	Copy(toCopy);
}

PropSimple::~PropSimple()
{
}

PropSimple& PropSimple::operator = (const PropSimple& toCopy)
{
	Copy(toCopy);
	return *this;
}

void PropSimple::Copy(const PropSimple& toCopy)
{
	Prop::Copy(toCopy);
}

PropSimple* PropSimple::GetCopy()
{
	return new PropSimple(*this);
}

void PropSimple::CreateComponents()
{
	//SetDrawableComponent(new DrawableComponent("Content/rum_from_rum.png"));
	SetMovableComponent(new MovableComponent);
	SetCollisionComponent(new CollisionComponent(16, 16));
}

void PropSimple::Update(Level* level, SDL_Event* e)
{
    CheckActivated(level);

    if(bIsActive)
        HandleActivated(level, e);
    if(bDamaged)
        HandleDamaged(level, e);
}

void PropSimple::CheckActivated(Level* level)
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

void PropSimple::HandleActivated(Level* currentLevel, SDL_Event* e)
{
	cout << "I am of activated!" << endl;
	bIsActive = false;
	bMustDestroy = true;
}

void PropSimple::HandleDamaged(Level* currentLevel, SDL_Event* e)
{
	cout << "I am of damaged!" << endl;
}
