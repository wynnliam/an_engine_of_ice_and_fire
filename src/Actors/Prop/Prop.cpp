//Liam "AFishyFez" Wynn, 4/24/2015, AEOIAF: Prop

#include "Prop.h"
#include "../../Level/Level.h"
#include "../../Utilities/Utility_Components/InputHandler.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

Prop::Prop()
{
    bIsActive = false;
    bDamaged = false;

    maxActivateDist = 100.0f;
}

Prop::Prop(const char* newID) : Actor(newID)
{
    bIsActive = false;
    bDamaged = false;

    maxActivateDist = 100.0f;
}

Prop::Prop(const Prop& toCopy)
{
    Copy(toCopy);

    bIsActive = false;
    bDamaged = false;
}

Prop::~Prop()
{
}

Prop& Prop::operator = (const Prop& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Prop::Copy(const Prop& toCopy)
{
    if(this == &toCopy)
        return;

    maxActivateDist = toCopy.maxActivateDist;

    Actor::Copy(toCopy);
}

Prop* Prop::GetCopy()
{
	return new Prop(*this);
}

void Prop::CreateComponents()
{
	Actor::CreateComponents();
}

void Prop::Update(Level* level, SDL_Event* e, float deltaTime)
{
    CheckActivated(level);

    if(bIsActive)
        HandleActivated(level, e);
    if(bDamaged)
        HandleDamaged(level, e);
}

//First make sure that the level and the movable and
//collision components are valid, then if the activate key
//is pressed, and the collision component contains the mouse point,
//activate the prop
void Prop::CheckActivated(Level* level)
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

void Prop::HandleActivated(Level* currentLevel, SDL_Event* e)
{
    cout << "Prop: I am active!" << endl;
    bIsActive = false;
}

void Prop::HandleDamaged(Level* currentLevel, SDL_Event* e)
{
    cout << "Prop: I've been damaged!" << endl;
    bDamaged = false;
}
