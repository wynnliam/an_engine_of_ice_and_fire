//Liam "AFishyFez" Wynn, 5/7/2015, An Engine of Ice and Fire

//Tutorials for this found here:
//http://gamedevelopment.tutsplus.com/series/understanding-steering-behaviors--gamedev-12732

#include "SteeringHandler.h"
#include "../General_Purpose/HelpfulMethods.h"
#include "../../Basic_Components/MoveableComponent.h"
#include "../../Level/Level.h"

using namespace AEOIAF_AIBehavior;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;

/*STEERING HANDLER IMPLEMENTATIONS*/
SteeringHandler::SteeringHandler()
{
    //Just initialize with some simple default properties
    mass = 1.0f;
    arrivalRadius = 0.0f;
    maxVelocity = 2.0f;
	seperationRadius = 32.0f;
	maxSeperation = 64.0f;
}

SteeringHandler::SteeringHandler(const SteeringHandler& toCopy)
{
    Copy(toCopy);
}

SteeringHandler& SteeringHandler::operator = (const SteeringHandler& toCopy)
{
    Copy(toCopy);
    return *this;
}

void SteeringHandler::Copy(const SteeringHandler& toCopy)
{
    if(this == &toCopy)
        return;

    mass = toCopy.mass;
    arrivalRadius = toCopy.arrivalRadius;
    maxVelocity = toCopy.maxVelocity;
	seperationRadius = toCopy.seperationRadius;
	maxSeperation = toCopy.maxSeperation;
}

Vector SteeringHandler::Seek(const MovableComponent& host, const Vector& targetPos)
{
	//Host vectors
	Vector hostPos = host.GetPosition(); //Use this to avoid calling a bunch of getters
    //Vector hostVelocity = host.GetVelocity();

	Vector force; //The steering force we will return
	float distance; //Use to check if we are within arrival radius

    //The resultant velocity to apply to host's position
    force = targetPos - hostPos;
	distance = force.GetMagnitude();
    force = force.GetNormalized();

    if(distance <= arrivalRadius)
        force *= 0.0f;
    else
        force *= host.GetMagnitude();

    return force;
}

//Pretty much the same code as Seek, except we switch the target and host's positions
//and then don't deal with arrival
Vector SteeringHandler::Flee(const MovableComponent& host, const Vector& targetPos)
{
    Vector force; //What we will return
    
	//The resultant velocity to apply to host's position
    force = host.GetPosition() - targetPos;
    force = force.GetNormalized();
    force *= host.GetMagnitude();

    return force;
}


Vector SteeringHandler::ApplyWallPush(Level* level, const MovableComponent& host, const int size)
{
	if(!level)
		return Vector(0, 0);

	Vector result;
	Vector position = host.GetPosition();
	Vector corners[4];

	GetCorners(position, size, corners);
	for(int i = 0; i < 4; ++i)
	{
		if(level->IsWall(corners[i] / 64))
			result += Flee(host, corners[i]);
	}

	return result;
}

void SteeringHandler::GetCorners(const Vector& position, const int size,
								 Vector corners[4])
{
	int halfSize = size / 2;

	corners[0] = Vector(position.GetX() - halfSize, position.GetY() - halfSize);
	corners[1] = Vector(position.GetX() + halfSize, position.GetY() - halfSize);
	corners[2] = Vector(position.GetX() + halfSize, position.GetY() + halfSize);
	corners[3] = Vector(position.GetX() - halfSize, position.GetY() + halfSize);
}

void SteeringHandler::ApplyForce(Vector& force, MovableComponent& host)
{
    force /= mass;
	TruncateVector(force, maxVelocity);

	host.SetPosition(host.GetPosition() + force);
}

void SteeringHandler::TruncateVector(Vector& toTruncate, float val)
{
    float length = toTruncate.GetMagnitude(); //The length of the vector
    float i = length != 0 ? val / length : 0; //Creating a scalar less than 1

    if(i < 1)
		toTruncate *= i;
}
