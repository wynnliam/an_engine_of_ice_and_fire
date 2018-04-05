//Liam "AFishyFez" Wynn, 4/11/2015, AEOIAF: Movable Component

#include "MoveableComponent.h"

using namespace AEOIAF_Utilities;

MovableComponent::MovableComponent()
{
	magnitude = 0.0f;
}

MovableComponent::MovableComponent(float newX, float newY) : position(newX, newY)
{
	magnitude = 0.0f;
}

MovableComponent::MovableComponent(const MovableComponent& toCopy)
{
    Copy(toCopy);
}

MovableComponent::~MovableComponent()
{
}

MovableComponent& MovableComponent::operator = (const MovableComponent& toCopy)
{
    Copy(toCopy);
    return *this;
}

void MovableComponent::Copy(const MovableComponent& toCopy)
{
	position = toCopy.position;
    direction = toCopy.direction;
	magnitude = toCopy.magnitude;
}

MovableComponent* MovableComponent::GetCopy()
{
    MovableComponent* result = new MovableComponent(*this);
    return result;
}

void MovableComponent::Update(float deltaTime)
{
	//Use this to modify position
	Vector velocity = direction * magnitude * deltaTime;
	position += velocity;
}
