#ifndef AXISALLIGNEDBOUNDINGBOX_H
#define AXISALLIGNEDBOUNDINGBOX_H

#include "Vector.h"

namespace AEOIAF_Utilities
{
    class AxisAllignedBoundingBox
    {
        public:
            AxisAllignedBoundingBox();
            AxisAllignedBoundingBox(int x1, int y1, int x2, int y2)
                                    : xMin(x1), yMin(y1), xMax(x2), yMax(y2) { }

            AxisAllignedBoundingBox(const AxisAllignedBoundingBox& aabb);

            AxisAllignedBoundingBox& operator = (const AxisAllignedBoundingBox& aabb);
            bool operator == (const AxisAllignedBoundingBox& aabb);

            void Copy(const AxisAllignedBoundingBox& aabb);
            bool Equals(const AxisAllignedBoundingBox& aabb);

			void AddVector(const Vector& toAdd);
			bool CollidesWith(const AxisAllignedBoundingBox toCheck) const;
			bool Contains(const Vector& toCheck) const;

            float xMin, yMin, xMax, yMax;
    };

}

//While these functions might seem unneccessary, I've included them
//Because while they are rather trivial, it removes excess code from
//functions that would need them.

//Creates a bounding box from a vector and a width and height
AEOIAF_Utilities::AxisAllignedBoundingBox CreateBoundingBox(const AEOIAF_Utilities::Vector& pos, int width, int height);


#endif // AXISALLIGNEDBOUNDINGBOX_H
