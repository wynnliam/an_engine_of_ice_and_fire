//Liam "AFishyFez" Wynn, 1/16/2016, A Clash of Colors

#include "TestProjectile.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

TestProjectile::TestProjectile()
{
	CreateComponents();
}

TestProjectile::TestProjectile(const char* newID) : Projectile(newID)
{
	CreateComponents();
}

TestProjectile::TestProjectile(const TestProjectile& toCopy)
{
	Copy(toCopy);
}

TestProjectile::~TestProjectile()
{
}

TestProjectile& TestProjectile::operator= (const TestProjectile& toCopy)
{
	Copy(toCopy);
	return *this;
}

void TestProjectile::Copy(const TestProjectile& toCopy)
{
	Projectile::Copy(toCopy);
}

TestProjectile* TestProjectile::GetCopy()
{
	return new TestProjectile(*this);
}

void TestProjectile::CreateComponents()
{
	SetCollisionComponent(new CollisionComponent(32, 32));

	//We don't set the movable component because generally that's handled by the
	//Projectile Weapon
}
