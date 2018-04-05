//Liam "AFishyFez" Wynn, 4/21/2015, AEOIAF: Collision Component

#include "CollisionComponent.h"
#include "../Level/Level.h"
#include "../Utilities/General_Purpose/HelpfulMethods.h"
#include "../Utilities/General_Purpose/Tracer.h"
#include "../Utilities/Utility_Components/Vector.h"
#include "../Utilities/Utility_Components/Constants.h"

using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::CollisionComponent(const CollisionComponent& toCopy)
{
    Copy(toCopy);
}

CollisionComponent::~CollisionComponent()
{

}

CollisionComponent& CollisionComponent::operator= (const CollisionComponent& toCopy)
{
    Copy(toCopy);
    return *this;
}

void CollisionComponent::Copy(const CollisionComponent& toCopy)
{
    aabb = toCopy.aabb;
}

CollisionComponent* CollisionComponent::GetCopy()
{
    CollisionComponent* result = new CollisionComponent(*this);
    return result;
}

bool CollisionComponent::CollidesWithWall(AEOIAF_Level::Level* level, const Vector& position) const
{
    if(!level)
        return false; //Nothing to check!

	//The x and y components of the position.
	//Avoids having to call getters a bunch
	float posX, posY;
	//Use these to avoid having to calculate
	//the corners' x and y components repeatedly
	int xMin, yMin, xMax, yMax;

	posX = position.GetX();
	posY = position.GetY();

	xMin = (int)(posX / AEOIAF_TILE_SIZE);
	yMin = (int)(posY / AEOIAF_TILE_SIZE);
	xMax = (int)((posX + aabb.xMax) / AEOIAF_TILE_SIZE);
	yMax = (int)((posY + aabb.yMax) / AEOIAF_TILE_SIZE);

    //Check if any corner of the collision component hits a wall
    Vector corners[4];
    corners[0] = Vector(xMin, yMin);
    corners[1] = Vector(xMin, yMax);
    corners[2] = Vector(xMax, yMin);
    corners[3] = Vector(xMax, yMax);

    for(int i = 0; i < 4; ++i)
    {
        if(level->IsWall(corners[i]))
            return true;
    }

    return false;
}

bool CollisionComponent::Contains(AxisAllignedBoundingBox& toCheck) const
{
	return aabb.CollidesWith(toCheck);
}

bool CollisionComponent::Contains(const Vector& currentPosition, AxisAllignedBoundingBox& toCheck) const
{
	//Use in place of aabb, because this will account for
	//position
	AxisAllignedBoundingBox temp;

	temp = aabb;
	temp.AddVector(currentPosition);

    return temp.CollidesWith(toCheck);
}

bool CollisionComponent::Contains(const Vector& currentPosition, const Tracer& tracer) const
{
	//Use in place of aabb, because this will account for
	//position
	AxisAllignedBoundingBox temp;

	temp = aabb;
	temp.AddVector(currentPosition);

	return tracer.Intersects(temp);
}

