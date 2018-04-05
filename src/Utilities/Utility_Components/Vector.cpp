//Liam "AFishyFez" Wynn, 8/29/2015, A Clash of Colors

#include "Vector.h"
#include <math.h>

using namespace AEOIAF_Utilities;

Vector::Vector()
{
	x = 0.0f;
	y = 0.0f;
}

Vector::Vector(float newX, float newY)
{
	x = newX;
	y = newY;
}

Vector::Vector(const Vector& toCopy)
{
	Copy(toCopy);
}

Vector::~Vector()
{
	x = 0.0f;
	y = 0.0f;
}

Vector& Vector::operator= (const Vector& toCopy)
{
	Copy(toCopy);
	return *this;
}

bool Vector::operator== (const Vector& compareTo) const
{
	return x == compareTo.x && y == compareTo.y;
}

bool Vector::operator!= (const Vector& compareTo) const
{
	return x != compareTo.x || y != compareTo.y;
}

bool Vector::operator> (const Vector& compareTo) const
{
	//Use the magnitudes to determine who is bigger
	float magnitude, compMagnitude;

	//Squared magnitude quicker to compute
	magnitude = GetMagnitudeSquared();
	compMagnitude = compareTo.GetMagnitudeSquared();

	return magnitude > compMagnitude;
}

bool Vector::operator>= (const Vector& compareTo) const
{
	//Use the magnitudes to determine who is bigger
	float magnitude, compMagnitude;

	//Squared magnitude quicker to compute
	magnitude = GetMagnitudeSquared();
	compMagnitude = compareTo.GetMagnitudeSquared();

	return magnitude >= compMagnitude;
}

bool Vector::operator< (const Vector& compareTo) const
{
	//Use the magnitudes to determine who is bigger
	float magnitude, compMagnitude;

	//Squared magnitude quicker to compute
	magnitude = GetMagnitudeSquared();
	compMagnitude = compareTo.GetMagnitudeSquared();

	return magnitude < compMagnitude;
}

bool Vector::operator<= (const Vector& compareTo) const
{
	//Use the magnitudes to determine who is bigger
	float magnitude, compMagnitude;

	//Squared magnitude quicker to compute
	magnitude = GetMagnitudeSquared();
	compMagnitude = compareTo.GetMagnitudeSquared();

	return magnitude <= compMagnitude;
}

Vector& Vector::operator+= (const Vector& toAdd)
{
	Add(toAdd);
	return *this;
}

Vector& Vector::operator+= (const float val)
{
	Add(val);
	return *this;
}

Vector Vector::operator+ (const Vector& toAdd) const
{
	Vector result(x + toAdd.x, y + toAdd.y);
	return result;
}

Vector operator+ (const Vector& vect, const float val)
{
	Vector result(vect.GetX() + val, vect.GetY() + val);
	return result;
}

Vector& Vector::operator-= (const Vector& toSub)
{
	Subtract(toSub);
	return *this;
}

Vector& Vector::operator-= (const float val)
{
	Add(-val);
	return *this;
}

Vector& Vector::operator- ()
{
	Negate();
	return *this;
}

Vector Vector::operator- (const Vector& toSub) const
{
	Vector result(x - toSub.x, y - toSub.y);
	return result;
}

Vector operator- (const Vector& vect, const float val)
{
	Vector result(vect.GetX() - val, vect.GetY() - val);
	return result;
}

Vector& Vector::operator*= (const float val)
{
	ScaleBy(val);
	return *this;
}

Vector& Vector::operator*= (const Vector& toMul)
{
	Multiply(toMul);
	return *this;
}

Vector Vector::operator* (const float val) const
{
	Vector result(x * val, y * val);
	return result;
}

Vector Vector::operator* (const Vector& toMul) const
{
	return Vector(x * toMul.x, y * toMul.y);
}

Vector& Vector::operator/= (const float val)
{
	float scalar; //What we will scale by;

	if(val == 0.0f)
		scalar = 1.0f;
	else
		scalar = 1.0f / val;

	ScaleBy(scalar);

	return *this;
}

Vector& Vector::operator/= (const Vector& toDiv)
{
	if(toDiv.x != 0.0f)
		x /= toDiv.x;
	if(toDiv.y != 0.0f)
		y /= toDiv.y;

	return *this;
}

Vector Vector::operator/ (const float val) const
{
	Vector result;

	if(val != 0.0f)
		result = Vector(x / val, y / val);

	return result;
}

Vector Vector::operator/ (const Vector& toDiv) const
{
	return Vector(x / toDiv.x, y / toDiv.y);
}

void Vector::Copy(const Vector& toCopy)
{
	x = toCopy.x;
	y = toCopy.y;
}

void Vector::Add(const Vector& toAdd)
{
	x += toAdd.x;
	y += toAdd.y;
}

void Vector::Add(const float val)
{
	x += val;
	y += val;
}

void Vector::Subtract(const Vector& toSub)
{
	x -= toSub.x;
	y -= toSub.y;
}

void Vector::Multiply(const Vector& toMul)
{
	x *= toMul.x;
	y *= toMul.y;
}

void Vector::Negate()
{
	x = -x;
	y = -y;
}

void Vector::ScaleBy(const float val)
{
	x *= val;
	y *= val;
}

float Vector::GetMagnitude() const
{
	float sqrdX, sqrdY; //Squared x and y components.
	float result; //What we will return

	sqrdX = x * x;
	sqrdY = y * y;
	result = (float)sqrt(sqrdX + sqrdY);

	return result;
}

float Vector::GetMagnitudeSquared() const
{
	float sqrdX, sqrdY;

	sqrdX = x * x;
	sqrdY = y * y;

	return sqrdX + sqrdY;
}

float Vector::GetDotProduct(const Vector& b) const
{
	//The x and y components multiplied
	//Use these to get the result
	float xComponents, yComponents;
	float result; //What we will return

	xComponents = x * b.x;
	yComponents = y * b.y;
	result = xComponents + yComponents;

	return result;
}

Vector Vector::GetNormalized() const
{
	float magnitude; //What we scale by for the result
	Vector result = *this; //What we will return

	magnitude = GetMagnitude();
	result /= magnitude;

	return result;
}
