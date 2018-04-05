//Liam "AFishyFez" Wynn, 1/20/2016, A Clash of Colors

#include "ParticleHandler.h"
#include <cstring>

#include "DrawComponentList.h"

#include "../Actors/Particle/ParticleSimple.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;

ParticleHandler::ParticleHandler()
{
}

ParticleHandler::~ParticleHandler()
{
}

//If toGet or renderer are NULL, then return NULL. Use toGet to find the associative
//particle. If none exists, then return NULL. Initialize the newly created particle
//if we actually created it.
ParticleEmitter* ParticleHandler::GetParticleEmitter(const char* toGet, const DrawComponentTable& drawTable) const
{
	if(!toGet)
		return NULL;

	ParticleEmitter* result; //What we will return

	if(strcmp(toGet, "SIMPLE") == 0)
	{
		result = new ParticleEmitterSimple;
		result->SetDrawableComponent(drawTable.GetDrawableComponent("ACOC_TEST_PARTICLE_DRAW"));
	}

	else
		result = NULL;

	return result;
}
