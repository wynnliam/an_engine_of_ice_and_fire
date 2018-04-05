//Liam "AFishyFez" Wynn, 1/16/2016, A Clash of Colors

#include "TestWeaponProjectile.h"
#include "TestProjectile.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

TestWeaponProjectile::TestWeaponProjectile()
{
	CreateComponents();
}

TestWeaponProjectile::TestWeaponProjectile(const char* newID) : WeaponProjectile(newID)
{
	CreateComponents();
}

TestWeaponProjectile::TestWeaponProjectile(const TestWeaponProjectile& toCopy)
{
	Copy(toCopy);
}

TestWeaponProjectile::~TestWeaponProjectile()
{
}

TestWeaponProjectile& TestWeaponProjectile::operator = (const TestWeaponProjectile& toCopy)
{
	Copy(toCopy);
	return *this;
}

void TestWeaponProjectile::Copy(const TestWeaponProjectile& toCopy)
{
	WeaponProjectile::Copy(toCopy);
}

TestWeaponProjectile* TestWeaponProjectile::GetCopy()
{
	return new TestWeaponProjectile(*this);
}

void TestWeaponProjectile::CreateComponents()
{
	SetMovableComponent(new MovableComponent);
	//With the exception of Melee weapons, we don't really need a collision component

	//SetProjectileType(new TestProjectile);

	SetPrefMinFightDist(100.0f);
	SetPrefMaxFightDist(145.0f);
}

bool TestWeaponProjectile::DidHit(Actor* toCheck)
{
	return WeaponProjectile::DidHit(toCheck);
}
