//Liam "AFishyFez" Wynn, 1/19/2016, An Engine of Ice and Fire

#include "ParticleSimple.h"
//Use these to make a random color for the particle
#include "../../Utilities/General_Purpose/Random.h"
#include <ctime>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Content;

ParticleEmitterSimple::ParticleEmitterSimple()
{
	CreateComponents();
}

ParticleEmitterSimple::ParticleEmitterSimple(const char* newID) : ParticleEmitter(newID)
{
	CreateComponents();
}

ParticleEmitterSimple::ParticleEmitterSimple(const ParticleEmitterSimple& toCopy)
{
	Copy(toCopy);
}

ParticleEmitterSimple::~ParticleEmitterSimple()
{
}

ParticleEmitterSimple& ParticleEmitterSimple::operator = (const ParticleEmitterSimple& toCopy)
{
	Copy(toCopy);
	return *this;
}

void ParticleEmitterSimple::Copy(const ParticleEmitterSimple& toCopy)
{
	ParticleEmitter::Copy(toCopy);
}

ParticleEmitterSimple* ParticleEmitterSimple::GetCopy()
{
	return new ParticleEmitterSimple(*this);
}

void ParticleEmitterSimple::CreateComponents()
{
	SetMovableComponent(new MovableComponent);
	SetParticleMoveComponent(new ParticleMoveComponent(1.0f));

	SetNumParticles(10);
	particleMoveComponent->SetAccelFalloff(0.1f);

	CreateParticles();
}
