//Liam "AFishyFez" Wynn, 1/17/2016, A Clash of Colors

#include "TestWeaponTracer.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

TestWeaponTracer::TestWeaponTracer()
{
	CreateComponents();
}

TestWeaponTracer::TestWeaponTracer(const char* newID) : WeaponTracer(newID)
{
	CreateComponents();
}

TestWeaponTracer::TestWeaponTracer(const TestWeaponTracer& toCopy)
{
	Copy(toCopy);
}

TestWeaponTracer::~TestWeaponTracer()
{
}

TestWeaponTracer& TestWeaponTracer::operator = (const TestWeaponTracer& toCopy)
{
	Copy(toCopy);
	return *this;
}

void TestWeaponTracer::Copy(const TestWeaponTracer& toCopy)
{
	WeaponTracer::Copy(toCopy);
}

TestWeaponTracer* TestWeaponTracer::GetCopy()
{
	return new TestWeaponTracer(*this);
}

void TestWeaponTracer::CreateComponents()
{
	SetDrawableComponent(new DrawableComponent("Content/melee_weapon.png"));
	SetMovableComponent(new MovableComponent);
	//With the exception of Melee weapons, we don't really need a collision component

	SetPrefMinFightDist(200.0f);
	SetPrefMaxFightDist(500.0f);
}

bool TestWeaponTracer::DidHit(Actor* toCheck)
{
	return WeaponTracer::DidHit(toCheck);
}
