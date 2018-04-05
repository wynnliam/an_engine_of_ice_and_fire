#ifndef CAMERA_H
#define CAMERA_H

#include "../General_Purpose/Matrix.h"
#include "Vector.h"
#include "AxisAllignedBoundingBox.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Actor
{
	class Actor;
}

namespace AEOIAF_Utilities
{
    class Camera
    {
        public:
            Camera();
            Camera(const Camera& toCopy);

            Camera& operator= (const Camera& toCopy);

            void Copy(const Camera& toCopy);

            Matrix& GetViewMatrix() { return viewMatrix; }

            Vector TransformPoint(const Vector& point);

            void Update(const Vector& newPos, int width, int height, bool bUpdateZoom);
            void UpdateZoom();

			bool CanSee(const AxisAllignedBoundingBox& toCheck) const;
			bool CanSee(AEOIAF_Actor::Actor* toCheck);

        private:
			Vector position;
            float zoom;
            Matrix viewMatrix;

			//Use this to determine if tiles/objects can actually be viewd by the camera
			AxisAllignedBoundingBox viewBox;
    };
}

#endif // CAMERA_H
