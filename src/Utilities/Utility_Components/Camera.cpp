#include "Camera.h"
#include "../../Actors/Actor.h"
#include <iostream>

using namespace AEOIAF_Utilities;
using namespace AEOIAF_Actor;
using namespace std;

Camera::Camera()
{
    zoom = 1.0f;
}

Camera::Camera(const Camera& toCopy)
{
    Copy(toCopy);
}

Camera& Camera::operator= (const Camera& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Camera::Copy(const Camera& toCopy)
{
    position = toCopy.position;
    zoom = toCopy.zoom;
    viewMatrix = toCopy.viewMatrix;
}

Vector Camera::TransformPoint(const Vector& point)
{
    return Matrix::Transform(point, viewMatrix);
}

void Camera::Update(const Vector& newPos, int width, int height, bool bUpdateZoom)
{
    if(bUpdateZoom) 
		UpdateZoom();

	Vector translationPos = newPos * -1.0f;
	Vector dimensions(width / 2, height / 2);

	position = newPos;

    viewMatrix = Matrix::CreateTranslation(translationPos, 0) *
				 //Matrix::CreateRotation(0.0f) *
				 Matrix::CreateScale(zoom) *
				 Matrix::CreateTranslation(dimensions, 0);

	viewBox.xMin = -position.GetX();
	viewBox.yMin = -position.GetY();
	viewBox.xMax = position.GetX() + (width / zoom);
	viewBox.yMax = position.GetY() + (height / zoom);
}

void Camera::UpdateZoom()
{
    //TODO: Finish me!
    zoom = 1.0f;
}

bool Camera::CanSee(const AxisAllignedBoundingBox& toCheck) const
{
	//TODO: Viewbox is somehow detecting that it hits every thing
	//It's dimensions must be wack
	return true;
	//return viewBox.CollidesWith(toCheck);
}

bool Camera::CanSee(Actor* toCheck)
{
	if(!toCheck)
		return false;

	return toCheck->CollidesWith(viewBox);
}

