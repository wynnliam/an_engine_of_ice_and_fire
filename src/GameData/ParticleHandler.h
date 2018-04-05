//Liam "AFishyFez" Wynn, 1/20/2016, A Clash of Colors

/*
 A key part of levels is atmosphere. Particles can help
 develop the atmosphere and mood of a level. We can use
 the ParticleHandler to dynamically create and add particles
 to levels, or even items if need be.
*/

#ifndef ACOC_PARTICLE_HANDLER
#define ACOC_PARTICLE_HANDLER

#include <SDL2/SDL.h> //So we can initialize the particles we create

namespace AEOIAF_Actor
{
	class ParticleEmitter;
}

namespace AEOIAF_Utilities
{
	class DrawComponentTable;
}

namespace ACOC_GameDataHandling
{
	class ParticleHandler
	{
		public:
			ParticleHandler();
			~ParticleHandler();

			//The main driver for creating props
			AEOIAF_Actor::ParticleEmitter* GetParticleEmitter(const char* toGet,
															  const AEOIAF_Utilities::DrawComponentTable& drawTable) const;
	};
}

#endif
