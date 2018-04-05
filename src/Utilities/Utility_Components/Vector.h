//Liam "AFishyFez" Wynn, 8/29/2015, A Clash of Colors

/*
 I'm surprised I didn't have this class until now.
 The Vector class is what you would have in math
 and physics. That is, it describes a direction
 and magnitude. However, we do that here with
 and x and y component.

 This class can also be used in not just describing
 velocity, but also a point in space. As such, this
 class will serve two functions: movement for Actors
 and desribing where to draw a texture.

 I noticed that my code was rather incosistent when
 it came to positions/vectors. My steering forces
 use their own vector class; Movement components
 micromanage their own velocities, directions,
 and accelerations; some things work with the
 limited functionality of the SDL_Point struct
 (which, to be fair, has worked perfectly thus
 far).

 My goal with this class is to standardize all these
 things with a general purpose Vector class.
*/

#ifndef AEOIAF_VECTOR
#define AEOIAF_VECTOR

namespace AEOIAF_Utilities
{
	class Vector
	{
		public:
			Vector();
			Vector(float newX, float newY);
			Vector(const Vector& toCopy);
			~Vector();

			float GetX() const { return x; }
			void SetX(float val) { x = val; }

			float GetY() const { return y; }
			void SetY(float val) { y = val; }

			Vector& operator= (const Vector& toCopy);
			bool operator== (const Vector& compareTo) const;
			bool operator!= (const Vector& compareTo) const;
			bool operator> (const Vector& compareTo) const;
			bool operator>= (const Vector& compareTo) const;
			bool operator< (const Vector& compareTo) const;
			bool operator<= (const Vector& compareTo) const;

			Vector& operator+= (const Vector& toAdd);
			Vector& operator+= (const float val);
			Vector operator+ (const Vector& toAdd) const;

			Vector& operator-= (const Vector& toSub);
			Vector& operator-= (const float val);
			Vector& operator- ();
			Vector operator- (const Vector& toSub) const;

			Vector& operator*= (const float val);
			Vector& operator*= (const Vector& toMul);
			Vector operator* (const float val) const;
			Vector operator* (const Vector& toMul) const;

			Vector& operator/= (const float val);
			Vector& operator/= (const Vector& toDiv);
			Vector operator/ (const float val) const;
			Vector operator/ (const Vector& toDiv) const;

			void Copy(const Vector& toCopy);
			void Add(const Vector& toAdd);
			void Add(const float val);
			void Subtract(const Vector& toSub);
			void Multiply(const Vector& toMul);

			void Negate();
			void ScaleBy(const float val);
			float GetMagnitude() const;
			//If you want to compare magnitudes of vectors
			//quickly, you can use this value. We simply
			//omit the square-root portion of the calculation
			float GetMagnitudeSquared() const;
			float GetDotProduct(const Vector& b) const;

			Vector GetNormalized() const;

		private:
			float x, y; //The x and y components of our vector
	};
}

AEOIAF_Utilities::Vector operator+ (const AEOIAF_Utilities::Vector& vect, const float val);
AEOIAF_Utilities::Vector operator- (const AEOIAF_Utilities::Vector& vect, const float val);

#endif
