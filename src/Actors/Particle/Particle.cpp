//Liam "AFishyFez" Wynn, 4/30/2015, AEOIAF: Particle

/*
Here I will implement all three classes found in Particle.h
that is, the Particle Emitter, the Particle, and the
Particle Move Component I am doing this to shorten the
number of .cpp files, but also because each class ought
to be relatively trivial to implement. In addition,
all three classes rely very heavily off each other,
as such it makes sense to have them all here
*/

#include "Particle.h"
#include "../../Level/Level.h"
#include "../../Utilities/General_Purpose/Random.h"
#include "../../Utilities/Utility_Components/Constants.h"
#include <math.h>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;

/*PARTICLE EMITTER IMPLEMENTATIONS*/
ParticleEmitter::ParticleEmitter()
{
    numParticles = 0;
    particles = NULL;
    particleMoveComponent = NULL;

	CreateComponents();
}

ParticleEmitter::ParticleEmitter(const char* newID) : Actor(newID)
{
    numParticles = 0;
    particles = NULL;
    particleMoveComponent = NULL;

	CreateComponents();
}

ParticleEmitter::ParticleEmitter(const ParticleEmitter& toCopy)
{
    Copy(toCopy);
}

ParticleEmitter::~ParticleEmitter()
{
    if(particles)
        delete[] particles;
    if(particleMoveComponent)
        delete particleMoveComponent;

    particles = NULL;
    particleMoveComponent = NULL;
}

void ParticleEmitter::SetParticleMoveComponent(ParticleMoveComponent* val)
{
    particleMoveComponent = val;
}

ParticleEmitter& ParticleEmitter::operator = (const ParticleEmitter& toCopy)
{
    Copy(toCopy);
    return *this;
}

int ParticleEmitter::SetPosition(const Vector& val)
{
	if(!movableComponent || !particles)
		return 0;

	movableComponent->SetPosition(val);
	
	for(unsigned int i = 0; i < numParticles; ++i)
		particles[i].SetPosition(val);

	return 1;
}

void ParticleEmitter::Copy(const ParticleEmitter& toCopy)
{
    if(this == &toCopy)
        return;

    numParticles = toCopy.numParticles;
    particles = NULL;

    if(toCopy.particleMoveComponent && particleMoveComponent != toCopy.particleMoveComponent)
    {
        if(particleMoveComponent)
            delete particleMoveComponent;

        particleMoveComponent = toCopy.particleMoveComponent->GetCopy();
    }

    Actor::Copy(toCopy);
}

ParticleEmitter* ParticleEmitter::GetCopy()
{
	return new ParticleEmitter(*this);
}

void ParticleEmitter::CreateParticles()
{
    Random rooseBolton;

    if(particles)
        delete[] particles; //Deallocate so we can reallocate

    particles = new Particle[numParticles];
    float angle, dirX, dirY; //Calculates velocity of each particle

    for(unsigned int i = 0; i < numParticles; ++i)
    {
        angle = (float)rooseBolton.GetRandomNumber(0, 360) * (AEOIAF_PI / 180.0f);
        dirX = cos(angle);
        dirY = sin(angle);

        if(particleMoveComponent && movableComponent)
        {
            ParticleMoveComponent* tempMoveComp = particleMoveComponent->GetCopy();
            tempMoveComp->SetPosition(movableComponent->GetPosition());
            tempMoveComp->SetDirection(Vector(dirX, dirY));
			particles[i].SetMovableComponent(tempMoveComp);
        }
    }
}

void ParticleEmitter::Update(Level* level, SDL_Event* e, float deltaTime)
{
    if(particles)
    {
        for(unsigned int i = 0; i < numParticles; ++i)
            particles[i].Update(deltaTime);
    }
}

void ParticleEmitter::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                           bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                           Matrix* matrix)
{
    if(!drawableComponent || !particles)
		return;

	Vector position;

	for(unsigned int i = 0; i < numParticles; ++i)
	{
		position = particles[i].GetPosition();

		if(drawableComponent)
			drawableComponent->Draw(renderer,
									position,
									flip,
									bTrsfrmRot,
									bTrsfrmScale,
									bTrsfrmPos,
									matrix);
	}
}

/*PARTICLE IMPLEMENTATIONS*/
Particle::Particle()
{
    moveComponent = NULL;
}

Particle::Particle(const Particle& toCopy)
{
    Copy(toCopy);
}

Particle::~Particle()
{
    if(moveComponent)
        delete moveComponent;

    moveComponent = NULL;
}

Vector Particle::GetPosition() const
{
	Vector result;

	if(moveComponent)
		result = moveComponent->GetPosition();

	return result;
}

void Particle::SetPosition(const Vector& val)
{
	if(!moveComponent)
		return;

	moveComponent->SetPosition(val);
}

Particle& Particle::operator = (const Particle& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Particle::Copy(const Particle& toCopy)
{
    if(this == &toCopy)
        return;

    if(toCopy.moveComponent && moveComponent != toCopy.moveComponent)
    {
        if(moveComponent)
            delete moveComponent;

        moveComponent = toCopy.moveComponent->GetCopy();
    }
}

void Particle::Update(float deltaTime)
{
    if(moveComponent)
        moveComponent->Update(deltaTime);
}

/*PARTICLE MOVMENT IMPLEMENTATION*/
ParticleMoveComponent::ParticleMoveComponent()
{
	acceleration = 0.0f;
    accelFalloff = 0.0f;
}

ParticleMoveComponent::ParticleMoveComponent(const float newAccel)
{
	acceleration = newAccel;
    accelFalloff = 0.0f;
}

ParticleMoveComponent::ParticleMoveComponent(const ParticleMoveComponent& toCopy)
{
    Copy(toCopy);
}

ParticleMoveComponent& ParticleMoveComponent::operator= (const ParticleMoveComponent& toCopy)
{
    Copy(toCopy);
    return *this;
}

void ParticleMoveComponent::Copy(const ParticleMoveComponent& toCopy)
{
    if(this == &toCopy)
        return;

	acceleration = toCopy.acceleration;
    accelFalloff = toCopy.accelFalloff;

    MovableComponent::Copy(toCopy);
}

ParticleMoveComponent* ParticleMoveComponent::GetCopy()
{
    ParticleMoveComponent* result = new ParticleMoveComponent(*this);
    return result;
}

void ParticleMoveComponent::Update(float deltaTime)
{
	magnitude += acceleration;

	//Make sure the velocity doesn't go backwards
	HandleMagnitudeClamp(0.0f);
	
	//Update position and velocity
	MovableComponent::Update(deltaTime);

	acceleration -= accelFalloff;

	HandleClampAcceleration(-100.0f);
}

void ParticleMoveComponent::HandleMagnitudeClamp(const float val)
{
	if(magnitude < val)
		magnitude = val;
}

void ParticleMoveComponent::HandleClampAcceleration(const float val)
{
	if(acceleration < val)
		acceleration = val;
}
