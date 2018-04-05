//Liam "AFishyFez" Wynn, 5/7/2015, AEOIAF: Test AI Character

#include "TestNonPlayer.h"
#include "../../Level/Level.h"
#include "../../Utilities/Utility_Components/Constants.h"
#include "../../Utilities/General_Purpose/HelpfulMethods.h"
#include "../Item/Weapon/Projectile/TestWeaponProjectile.h"
#include "../Item/Shield/TestShield.h"
#include "../../Utilities/General_Purpose/Tracer.h"
#include <cmath>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_AIBehavior;

TestSoldier::TestSoldier()
{
	CreateComponents();
}

TestSoldier::TestSoldier(const char* newID) : NonPlayer(newID)
{
	CreateComponents();
}

TestSoldier::TestSoldier(const TestSoldier& toCopy) : NonPlayer(toCopy)
{
}

TestSoldier* TestSoldier::GetCopy()
{
	return new TestSoldier(*this);
}

void TestSoldier::CreateComponents()
{
	SetMovableComponent(new MovableComponent);
	SetCollisionComponent(new CollisionComponent(64, 64));

	movableComponent->SetMagnitude(2.0f);
}

	/*TestShield* shield = new TestShield;
	shield->Initialize(renderer);
	shield->SetOffset(Vector(24, 24));
	shield->SetDrawRotationOffset(45.0f);
	shield->SetOwner(this);
	SetEquippedShield(shield);*/

//Update the actor
void TestSoldier::Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime)
{
	if(!level || !movableComponent)
		return;

    Vector force; //Final steering force to apply to our AI
	Vector nextDest; //The next path node position we need to go to
	Vector avoid(320, 192); //THe position we want to avoid
	TraversalArea t;

	UpdateDestination(level);

	if(!currentPath.IsEmpty())
	{
		currentPath.Peek(t);
		nextDest = t.center;
		force += steeringHandler.Seek(*movableComponent, nextDest);
		steeringHandler.ApplyForce(force, *movableComponent);

		if(t.bound.Contains(movableComponent->GetPosition()))
			currentPath.Pop();
	}

	/*
    if(level && movableComponent)
    {
		UpdateDestination(level);

        if(!currentPath.IsEmpty())
        {
			nextDest = (currentPath.Peek() * 64) + Vector(32, 32);
            force += steeringHandler.Seek(*movableComponent, nextDest);

            //if((movableComponent->GetPosition() - avoid).GetMagnitude() <= 128)
                //force += steeringHandler.Flee(*movableComponent, avoid);
			
			steeringHandler.ApplyForce(force, *movableComponent);

			//LookAt(targetPos);

			if((movableComponent->GetPosition() - nextDest).GetMagnitude() <= 4)
				currentPath.Pop();
        }
    }*/

	if(equippedShield)
		equippedShield->Update(level, e, deltaTime);
}

void TestSoldier::UpdateDestination(Level* level)
{
	Vector targetPos; //Current position of the target
	int targetArea; //Index of the traversal area of the target
	Character* target = level->GetCharacter("PLAYER_0");

	target->GetPosition(targetPos);
	targetArea = level->GetLevelAIData()->FindAssociatedMapNode(targetPos);

	if(targetArea != destArea)
	{
		destArea = targetArea;
		level->GetLevelAIData()->GetPath(movableComponent->GetPosition(), targetPos, currentPath);
	}
}

void TestSoldier::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
					   bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos, Matrix* matrix)
{
	int halfCharSize = AEOIAF_CHAR_SIZE / 2;
	Vector position = movableComponent->GetPosition();
	Vector offset(halfCharSize, halfCharSize);

	movableComponent->SetPosition(position - offset);
	NonPlayer::Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
	movableComponent->SetPosition(position);

	if(equippedShield)
		equippedShield->Draw(renderer, flip, true, false, true, matrix);

	/*AxisAllignedBoundingBox aabb = collisionComponent->GetBoundingBox();
	Vector pos = position - offset;

	aabb.AddVector(pos);
	colDraw->SetWidth((int)(aabb.xMax - aabb.xMin));
	colDraw->SetHeight((int)(aabb.yMax - aabb.yMin));
	colDraw->Draw(renderer, pos, flip, false, false, true, matrix);*/
}
