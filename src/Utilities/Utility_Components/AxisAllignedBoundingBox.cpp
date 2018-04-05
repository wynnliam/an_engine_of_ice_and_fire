#include "AxisAllignedBoundingBox.h"

using namespace AEOIAF_Utilities;

AxisAllignedBoundingBox::AxisAllignedBoundingBox()
{
    xMin = 0;
    yMin = 0;
    xMax = 0;
    yMax = 0;
}

AxisAllignedBoundingBox::AxisAllignedBoundingBox(const AxisAllignedBoundingBox& aabb)
{
    Copy(aabb);
}

AxisAllignedBoundingBox& AxisAllignedBoundingBox::operator = (const AxisAllignedBoundingBox& aabb)
{
    Copy(aabb);
    return *this;
}

bool AxisAllignedBoundingBox::operator == (const AxisAllignedBoundingBox& aabb)
{
    return Equals(aabb);
}

void AxisAllignedBoundingBox::Copy(const AxisAllignedBoundingBox& aabb)
{
    xMin = aabb.xMin;
    xMax = aabb.xMax;
    yMin = aabb.yMin;
    yMax = aabb.yMax;
}

bool AxisAllignedBoundingBox::Equals(const AxisAllignedBoundingBox& aabb)
{
    return xMin == aabb.xMin
        && yMin == aabb.yMin
        && xMax == aabb.xMax
        && yMax == aabb.yMax;
}

void AxisAllignedBoundingBox::AddVector(const Vector& toAdd)
{
	float x, y; //Use these in place of getters

	x = toAdd.GetX();
	y = toAdd.GetY();

    xMin += x;
    yMin += y;
    xMax += x;
    yMax += y;
}

bool AxisAllignedBoundingBox::CollidesWith(const AxisAllignedBoundingBox toCheck) const
{
    return (toCheck.xMin < xMax) &&
           (toCheck.xMax > xMin) &&
           (toCheck.yMin < yMax) &&
           (toCheck.yMax > yMin);
}

bool AxisAllignedBoundingBox::Contains(const Vector& toCheck) const
{
	return toCheck.GetX() >= xMin &&
		   toCheck.GetX() <= xMax &&
		   toCheck.GetY() >= yMin &&
		   toCheck.GetY() <= yMax;
}

/*EXTRA UTILITY FUNCTIONS*/
AxisAllignedBoundingBox CreateBoundingBox(const Vector& pos, int width, int height)
{
	//Allows us to call the getters and setters once
	float x, y;

	x = pos.GetX();
	y = pos.GetY();

	return AxisAllignedBoundingBox(x, y, x + (float)width, y + (float)height);
}

