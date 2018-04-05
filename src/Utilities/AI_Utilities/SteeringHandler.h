//Liam "AFishyFez" Wynn, 5/6/2015, AEOIAF: Steering Handler

/*
Here we store the SteeringVector, and the SteeringHandler
classes. Their purpose is to provide functions that allow
primarily AI characters (although not tied to them specifically)
smooth movement, and to move a large portion of their movement
logic to a specialized class
*/

#ifndef AEOIAF_STEERING_FORCES
#define AEOIAF_STEERING_FORCES

#include "../Utility_Components/Vector.h"

namespace AEOIAF_Utilities
{
    class MovableComponent;
}

namespace AEOIAF_Level
{
	class Level;
}

namespace AEOIAF_AIBehavior
{
    class SteeringHandler
    {
        public:
            SteeringHandler();
            SteeringHandler(float newMass, float newArrivalRadius, float newMaxVelocity)
                            : mass(newMass), arrivalRadius(newArrivalRadius), maxVelocity(newMaxVelocity) {}
            SteeringHandler(const SteeringHandler& toCopy);

            float GetMass() { return mass; }
            void SetMass(float val) { mass = val; }

            float GetArrivalRadius() { return arrivalRadius; }
            void SetArrivalRadius(float val) { arrivalRadius = val; }

            float GetMaxVelocity() { return maxVelocity; }
            void SetMaxVelocity(float val) { maxVelocity = val; }

			float GetSeperationRadius() const { return seperationRadius; }
			void SetSeperationRadius(const float val) { seperationRadius = val; }

			float GetMaxSeperation() const { return maxSeperation; }
			void SetMaxSeperation(const float val) { maxSeperation = val; }

            SteeringHandler& operator = (const SteeringHandler& toCopy);

            //Copies all properties from toCopy into this
            void Copy(const SteeringHandler& toCopy);
            //Creates a steering force that moves towards the target
            AEOIAF_Utilities::Vector Seek(const AEOIAF_Utilities::MovableComponent& host,
										  const AEOIAF_Utilities::Vector& targetPos);
            //Creates a steering force that moves away from the target
            AEOIAF_Utilities::Vector Flee(const AEOIAF_Utilities::MovableComponent& host,
										  const AEOIAF_Utilities::Vector& targetPos);

			//Where size is the side length of the character
			AEOIAF_Utilities::Vector ApplyWallPush(AEOIAF_Level::Level* level,
												   const AEOIAF_Utilities::MovableComponent& host,
												   const int size);

            //Will apply force to host's position
            void ApplyForce(AEOIAF_Utilities::Vector& force, AEOIAF_Utilities::MovableComponent& host);

        private:
			//Given a position and a size, outputs the corner positions
			//of the square that position is the center of
			void GetCorners(const AEOIAF_Utilities::Vector& position, const int size,
							AEOIAF_Utilities::Vector corners[4]);

			//Truncates a vector, given a value
			void TruncateVector(AEOIAF_Utilities::Vector& vector, float val);

            float mass; //The mass of the actor using steering forces
            float arrivalRadius; //Radius around the target for when we slow down
            float maxVelocity; //The maximum speed (aka magnitude of movement vector) host can travel
			float seperationRadius; //How close a character needs to be to move away from them
			float maxSeperation;
    };
}

#endif // AEOIAF_STEERING_FORCES
