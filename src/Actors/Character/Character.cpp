//Liam "AFishyFez" Wynn, 4/15/2015, AEOIAF: Character

#include "Character.h"
#include "../Item/Weapon/Weapon.h"
#include "../Item/Shield/Shield.h"
#include "../../Utilities/Utility_Components/Constants.h"
#include "../../Utilities/General_Purpose/Tracer.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

Character::Character()
{
	equippedWeapon = NULL;
	equippedShield = NULL;
}

Character::Character(const char* newID) : Actor(newID)
{
	equippedWeapon = NULL;
	equippedShield = NULL;
}

Character::Character(const Character& toCopy)
{
	equippedWeapon = NULL;
	equippedShield = NULL;
	
    Copy(toCopy);
}

Character::~Character()
{
	SetEquippedWeapon(NULL);
	SetEquippedShield(NULL);
}

Character& Character::operator =(const Character& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Character::Copy(const Character& toCopy)
{
    if(this == &toCopy)
        return;

    Actor::Copy(toCopy);
}

Character* Character::GetCopy()
{
	Character* result = new Character(*this);

	return result;
}

//If the equipped weapon is not NULL, then deallocate it.
//Then set equipped weapon to val
void Character::SetEquippedWeapon(Weapon* val)
{
	if(equippedWeapon)
		delete equippedWeapon;

	equippedWeapon = val;

	if(equippedWeapon)
		equippedWeapon->SetOwner(this);
}

//If the equipped shield is not NULL, then deallocate it.
//Then set the equipped shield to val
void Character::SetEquippedShield(Shield* val)
{
	if(equippedShield)
		delete equippedShield;

	equippedShield = val;
}

//If toCheck is NULL, then return false. Determine if we were hit.
//If the owner was not hit, then return false. Otherwise, check if
//the shield was hit. If the shield was hit, then determine if
//toCheck hit the shield and not the owner. If so, return false.
//Otherwise, return true
bool Character::CollidesWith(Actor* toCheck) const
{
	if(!toCheck)
		return false;

	//The position accounting for the center of the character
	Vector pos = movableComponent->GetPosition();
	//The offset we apply to make the collision component in the correct
	//place
	Vector offset(AEOIAF_CHAR_SIZE / 2, AEOIAF_CHAR_SIZE / 2);
	//What we will return
	bool result;

	movableComponent->SetPosition(pos - offset);

	if(!Actor::CollidesWith(toCheck))
		result = false;
	else
	{
		//Not only is a shield collision checked, but also
		//if we were facing the shield as opposed to the owner
		if(HitShield(toCheck))
			result = false;
		else
			result = true;
	}

	//Need to reset this once we are done
	movableComponent->SetPosition(pos);

	return result;
}

//If equippedShield or toCheck is NULL, then return false
//If the shield was hit, then determine if toCheck faced the
//shield. Collisions don't really account for things like shields
//that may otherwise block an attack. So we need to check if
//toCheck actually looked at the shield at the time of collision
//which tells us if the shield was in front of our target.
bool Character::HitShield(Actor* toCheck) const
{
	if(!equippedShield || !toCheck)
		return false;

	//Use this to calculate shieldDirection
	float shieldRotation;
	//Use this to determine if toCheck was facing the shield
	//at the time of the collision
	float dotProduct;
	//The dotProduct is done using the shield's direction
	//and the vector from toCheck's position, to our position
	Vector shieldDirection;
	Vector toCheckPos, myPos;
	//What we will return
	bool result;

	if(!equippedShield->CollidesWith(toCheck))
		result = false;
	else
	{
		//Check these to be safe
		if(!toCheck->GetPosition(toCheckPos) || !GetPosition(myPos))
			result = false;
		else
		{
			//In degrees normally, so convert to radians
			shieldRotation = equippedShield->GetRotation() * (AEOIAF_PI / 180.0f);
			shieldDirection = Vector(cos(shieldRotation), sin(shieldRotation));
			//Calculate the dotProduct
			dotProduct = shieldDirection.GetDotProduct((toCheckPos - myPos).GetNormalized());

			//The dotProduct being greater than or equal to zero means we are either perpendicular
			//to the shield, or in its "field of view", which implies we are hitting it
			result = dotProduct >= 0 ? true : false;
		}
	}

	return result;
}

bool Character::CollidesWith(AxisAllignedBoundingBox& toCheck) const
{
	return Actor::CollidesWith(toCheck);
}

bool Character::CollidesWith(const Tracer& tracer) const
{
	//The position accounting for the center of the character
	Vector pos = movableComponent->GetPosition();
	//The offset we apply to make the collision component in the correct
	//place
	Vector offset(AEOIAF_CHAR_SIZE / 2, AEOIAF_CHAR_SIZE / 2);
	//What we will return
	bool result;

	movableComponent->SetPosition(pos - offset);

	if(!Actor::CollidesWith(tracer))
		result = false;
	else
	{
		//Not only is a shield collision checked, but also
		//if we were facing the shield as opposed to the owner
		if(HitShield(tracer))
			result = false;
		else
			result = true;
	}

	//Need to reset this once we are done
	movableComponent->SetPosition(pos);

	return result;
}

bool Character::HitShield(const Tracer& tracer) const
{
	if(!equippedShield)
		return false;

	//Use this to calculate shieldDirection
	float shieldRotation;
	//Use this to determine if toCheck was facing the shield
	//at the time of the collision
	float dotProduct;
	//The dotProduct is done using the shield's direction
	//and the direction vector of the tracer
	Vector shieldDirection;
	Vector myPos;
	//What we will return
	bool result;

	if(!equippedShield->CollidesWith(tracer))
		result = false;
	else
	{
		if(!GetPosition(myPos))
			result = false;
		else
		{
			//In degrees normally, so convert to radians
			shieldRotation = equippedShield->GetRotation() * (AEOIAF_PI / 180.0f);
			shieldDirection = Vector(cos(shieldRotation), sin(shieldRotation));
			//Calculate the dotProduct
			dotProduct = shieldDirection.GetDotProduct((tracer.GetStart() - myPos).GetNormalized());

			//The dotProduct being greater than or equal to zero means we are either perpendicular
			//to the shield, or in its "field of view", which implies we are hitting it
			result = dotProduct >= 0 ? true : false;
		}
	}

	return result;
}

void Character::Update(Level* level, SDL_Event* e, float deltaTime)
{
	Actor::Update(level, e, deltaTime);
}

void Character::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
					 bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
					 Matrix* matrix)
{
	Actor::Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
}

void Character::HandleWallCollisions(Level* level)
{
	if(!movableComponent || !level)
		return;

	//Our current position, used to calculate the
	//final position that we check wall collisions
	//with
	Vector position;
	//The position we check wall collisions with.
	//Essentially the position vector with an offset
	//applied that makes it the center of the character
    Vector tempPosition;
	float offset; //The offset we apply to tempPosition

	position = movableComponent->GetPosition();
	offset = AEOIAF_CHAR_SIZE / 2;
	tempPosition = position - Vector(offset, offset);

    if(collisionComponent && collisionComponent->CollidesWithWall(level, tempPosition))
        ResetPosition();
}

void Character::SavePreviousPosition()
{
	if(!movableComponent)
		return;

	previousPosition = movableComponent->GetPosition();
}

void Character::ResetPosition()
{
	if(!movableComponent)
		return;

	movableComponent->SetPosition(previousPosition);
}
