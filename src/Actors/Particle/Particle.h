//Liam "AFishyFez" Wynn, 4/29/2015, An Engine of Ice and Fire

/*
A particle is really just a simple effect for things
like fire, sparks, or whatever. For AEOIAF, a particles
are handled by an emitter which has an array of single particles.
To create elaborate effects, use multiple emitters at once.
*/

#ifndef AEOIAF_PARTICLE
#define AEOIAF_PARTICLE

#include "../Actor.h"
#include "../../Utilities/General_Purpose/Matrix.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Level
{
    class Level;
}

namespace AEOIAF_Utilities
{
    //Although each particle is not an actor, they behave
    //somewhat similar to one. Particles need special movement
    //components that handle their special movement
    class ParticleMoveComponent : public MovableComponent
    {
        public:
            ParticleMoveComponent();
            ParticleMoveComponent(const float newAccel);
            ParticleMoveComponent(const ParticleMoveComponent& toCopy);

			float GetAcceleration() const { return acceleration; }
			void SetAcceleration(const float& val) { acceleration = val; }

            float GetAccelFalloff() const { return accelFalloff; }
            void SetAccelFalloff(float val) { accelFalloff = val; }

            virtual ParticleMoveComponent& operator = (const ParticleMoveComponent& toCopy);

            virtual void Copy(const ParticleMoveComponent& toCopy);
            //Copies this component into a pointer and returns the result
            virtual ParticleMoveComponent* GetCopy();
            //Will apply acceleration to the particle, move it, and then
            //decrease acceleration until velocity is 0
            virtual void Update(float deltaTime);

        protected:
			//After applying acceleration, if the magnitude goes below a given value, then clamp it
			void HandleMagnitudeClamp(const float val);
			//After applying acceleration fall-off, if the acceleration goes below a given value,
			//then clamp it
			void HandleClampAcceleration(const float val);

			float acceleration; //Describes the acceleration of each particle each update
            float accelFalloff; //How much we subtract from acceleration each update
    };
}

namespace AEOIAF_Actor
{
    //Basically a particle emitter is a container of
    //many Particles. For efficiency purposes, the Emitter
    //is an actor so that we can reuse its drawable component.
    //Plus it makes sense: a single particle is just a little
    //effect, while the Emitter actually does stuff
    class ParticleEmitter : public Actor
    {
        public:
            ParticleEmitter();
            ParticleEmitter(const char* newID);
            ParticleEmitter(const ParticleEmitter& toCopy);
            virtual ~ParticleEmitter();

            virtual ParticleEmitter& operator = (const ParticleEmitter& toCopy);

            unsigned int GetNumParticles() const { return numParticles; }
            void SetNumParticles(unsigned int val) { numParticles = val; }

            void SetParticleMoveComponent(AEOIAF_Utilities::ParticleMoveComponent* val);

			int SetPosition(const AEOIAF_Utilities::Vector& val);

			//A simple function that creates all the particles that are managed
			//by this particle emitter
			virtual void CreateParticles();

            virtual void Copy(const ParticleEmitter& toCopy);
            virtual ParticleEmitter* GetCopy();
            //Updates each particle
            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            //Draws each particle
            virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
							  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
							  AEOIAF_Utilities::Matrix* matrix = NULL);

		protected:
            //Use this so that each particle can copy it
            AEOIAF_Utilities::ParticleMoveComponent* particleMoveComponent;

        private:
            unsigned int numParticles;
            class Particle* particles;
    };

    //A single particle in an effect
    class Particle
    {
        public:
            Particle();
            Particle(const Particle& toCopy);
            virtual ~Particle();

			AEOIAF_Utilities::Vector GetPosition() const;
			void SetPosition(const AEOIAF_Utilities::Vector& val);

            AEOIAF_Utilities::ParticleMoveComponent* GetMoveComponent() const { return moveComponent; }
			void SetMovableComponent(AEOIAF_Utilities::ParticleMoveComponent* val) { moveComponent = val; }

            virtual Particle& operator= (const Particle& toCopy);

            virtual void Copy(const Particle& toCopy);
            virtual void Update(float deltaTime);

        protected:
            AEOIAF_Utilities::ParticleMoveComponent* moveComponent;
    };
}

#endif // AEOIAF_PARTICLE
