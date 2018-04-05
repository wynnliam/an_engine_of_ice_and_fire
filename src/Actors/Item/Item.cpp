//Liam "AFishyFez" Wynn, 7/25/2015, A Clash of Colors

#include "Item.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

Item::Item()
{
	owner = NULL;
}

Item::Item(const char* newID) : Actor(newID)
{
	owner = NULL;
}

Item::Item(const Item& toCopy)
{
	owner = NULL;
	Copy(toCopy);
}

Item::~Item()
{
}

Item& Item::operator = (const Item& toCopy)
{
	Copy(toCopy);
	return *this;
}

void Item::Copy(const Item& toCopy)
{
	if(this == &toCopy)
		return;

	owner = toCopy.owner;

	Actor::Copy(toCopy);
}

Item* Item::GetCopy()
{
	return new Item(*this);
}

bool Item::CollidesWith(Actor* toCheck) const
{
	return Actor::CollidesWith(toCheck);
}

bool Item::CollidesWith(AxisAllignedBoundingBox& toCheck) const
{
	return Actor::CollidesWith(toCheck);
}

bool Item::CollidesWith(const Tracer& tracer) const
{
	return Actor::CollidesWith(tracer);
}

void Item::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                Matrix* matrix)
{
	Actor::Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
}

