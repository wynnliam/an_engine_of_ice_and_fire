//Liam "AFishyFez" Wynn, 7/25/2015, A Clash of Colors

#include "Weapon.h"
#include "../../../Level/Level.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace std;

Weapon::Weapon()
{
	fireRate = 0;
	weaponType = 0;
	currentRechargeTime = 0;
	bIsRecharging = false;
	bWantToFire = false;

	prefMinDist = 0.0f;
	prefMaxDist = 0.0f;
}

Weapon::Weapon(const char* newID) : Item(newID)
{
	fireRate = 0;
	weaponType = 0;
	currentRechargeTime = 0;
	bIsRecharging = false;
	bWantToFire = false;

	prefMinDist = 0.0f;
	prefMaxDist = 0.0f;
}

Weapon::Weapon(const Weapon& toCopy)
{
	currentRechargeTime = 0;
	bIsRecharging = false;
	bWantToFire = false;

	Copy(toCopy);
}

Weapon::~Weapon()
{
}

Weapon& Weapon::operator = (const Weapon& toCopy)
{
	Copy(toCopy);
	return *this;
}

void Weapon::Copy(const Weapon& toCopy)
{
	if(this == &toCopy)
		return;

	fireRate = toCopy.fireRate;
	weaponType = toCopy.weaponType;

	prefMinDist = toCopy.prefMinDist;
	prefMaxDist = toCopy.prefMaxDist;

	Item::Copy(toCopy);
}

Weapon* Weapon::GetCopy()
{
	return new Weapon(*this);
}

void Weapon::StartFireRateTimer()
{
	bIsRecharging = true;
	currentRechargeTime = fireRate;
	fireRateTimer.Start();
}

void Weapon::Update(Level* level, SDL_Event* e, float deltaTime)
{
	SetPositionToOwnerPosition();

	if(!bIsRecharging)
		return;

	if(currentRechargeTime <= 0)
		Reset();
	else
		currentRechargeTime -= fireRateTimer.GetTicks();
}

void Weapon::SetPositionToOwnerPosition()
{
	if(!owner || !movableComponent)
		return;

	Vector newPos;
	owner->GetPosition(newPos);
	movableComponent->SetPosition(newPos);
}

bool Weapon::DidHit(Actor* toCheck)
{
	return false; //For checking purposes
}

bool Weapon::DidHit(Tile* toCheck)
{
	return false; //For testing purposes
}

void Weapon::Reset()
{
	fireRateTimer.Stop();
	currentRechargeTime = 0;
	bIsRecharging = false;
}

void Weapon::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
				  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
				  Matrix* matrix)
{
	Item::Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
}

