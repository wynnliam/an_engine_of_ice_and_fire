//Liam "AFishyFez" Wynn, 1/16/2015, A Clash of Colors

#include "TestShield.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

TestShield::TestShield()
{
	CreateComponents();
}

TestShield::TestShield(const char* newID) : Shield(newID)
{
	CreateComponents();
}

TestShield::TestShield(const TestShield& toCopy)
{
	Copy(toCopy);
}

TestShield::~TestShield()
{
}

TestShield& TestShield::operator = (const TestShield& toCopy)
{
	Copy(toCopy);
	return *this;
}

void TestShield::Copy(const TestShield& toCopy)
{
	Shield::Copy(toCopy);
}

TestShield* TestShield::GetCopy()
{
	return new TestShield(*this);
}

void TestShield::CreateComponents()
{
	SetMovableComponent(new MovableComponent);
	SetCollisionComponent(new CollisionComponent(8, 64));
}
