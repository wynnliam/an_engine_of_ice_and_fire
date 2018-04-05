//Liam "AFishyFez" Wynn, 8/14/2015, An Engine of Ice and Fire

/*
 Although a Tracer is primarily used for Tracer Weapons, it
 has many uses outside of weapons. Essentially, a Tracer is
 a line which we check collisions against.
*/

#ifndef AEOIAF_TRACER
#define AEOIAF_TRACER

#include "../Utility_Components/Vector.h"

namespace AEOIAF_Utilities
{
	class AxisAllignedBoundingBox;

	class Tracer
	{
		public:
			Tracer();
			Tracer(const AEOIAF_Utilities::Vector& start, float rotation);
			Tracer(const Tracer& toCopy);

			Tracer& operator= (const Tracer& toCopy);

			void Copy(const Tracer& toCopy);

			Vector GetStart() const { return start; }
			void SetStart(const Vector& val) { start = val; }

			Vector GetEnd() { return end; }
			void SetEnd(const Vector& val ) { end = val; }

			bool Intersects(const AxisAllignedBoundingBox& toCheck) const;

		private:
			//The meat of the collision detection. Determines if there is a successful
			//intersection along a single axis/dimension
			bool ClipLine(bool bIsXDimension, const AxisAllignedBoundingBox& toCheck, 
						  float& fracLo, float& fracHi) const;

			Vector start, end;
	};
}

#endif
