//Liam "AFishyFez" Wynn, 1/19/2016, An Engine of Ice and Fire

/*
 A simple particle that demonstrates the bare basics of creating
 a custom particle.
*/

#ifndef AEOIAF_PARTICLE_SIMPLE
#define AEOIAF_PARTICLE_SIMPLE

#include "Particle.h"

namespace AEOIAF_Actor
{
	class ParticleEmitterSimple : public ParticleEmitter
	{
		public:
            ParticleEmitterSimple();
            ParticleEmitterSimple(const char* newID);
            ParticleEmitterSimple(const ParticleEmitterSimple& toCopy);
            ~ParticleEmitterSimple();

            ParticleEmitterSimple& operator = (const ParticleEmitterSimple& toCopy);

            void Copy(const ParticleEmitterSimple& toCopy);
            ParticleEmitterSimple* GetCopy();

			void CreateComponents();
	};
}

#endif

