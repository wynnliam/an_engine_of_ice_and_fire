//Liam "AFishyFez" Wynn, 4/11/2015, AEOIAF: Movable Component

/*
The movable component is an interface
to handle all logic in moving an object.
While it has direction, speed, and acceleration,
it does NOT have steering forces. Those handle
different things, which are beyond the scope of this
class.
*/

#ifndef AEOIAF_MOVE_COMPONENT
#define AEOIAF_MOVE_COMPONENT

#include "../Utilities/Utility_Components/Vector.h"

namespace AEOIAF_Utilities
{
    class MovableComponent
    {
        public:
            MovableComponent();
            MovableComponent(float newX, float newY);
            MovableComponent(const MovableComponent& toCopy);
            virtual ~MovableComponent();

            virtual MovableComponent& operator = (const MovableComponent& toCopy);

			Vector GetPosition() const { return position; }
			void SetPosition(const Vector& val) { position = val; }

			Vector GetDirection() const { return direction; }
			void SetDirection(const Vector& val) { direction = val; }

			float GetMagnitude() const { return magnitude; }
			void SetMagnitude(const float& val) { magnitude = val; }

            //Copies the data from toCopy into this
            virtual void Copy(const MovableComponent& toCopy);
            //Copies this component into a pointer and returns the pointer
            virtual MovableComponent* GetCopy();
            //Apply velocity and direction to the position
            virtual void Update(float deltaTime);

        protected:
            Vector position; //Describes the position of the component
            Vector direction; //Describes the direction component of velocity
			float magnitude; //Describes the magnitude of velocity
    };
}

#endif // AEOIAF_MOVE_COMPONENT
