//Liam "AFishyFez" Wynn, 9/25/2015, A Clash of Colors

#include "Projectile.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;

Projectile::Projectile()
{
}

Projectile::Projectile(const char* newID) : Actor(newID)
{
}

Projectile::Projectile(const Projectile& toCopy)
{
	Copy(toCopy);
}

Projectile::~Projectile()
{
}

Projectile& Projectile::operator= (const Projectile& toCopy)
{
	Copy(toCopy);
	return *this;
}

void Projectile::Copy(const Projectile& toCopy)
{
	Actor::Copy(toCopy);
}

Projectile* Projectile::GetCopy()
{
	return new Projectile(*this);
}

void Projectile::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!movableComponent || !collisionComponent)
		return;

	movableComponent->Update(deltaTime);
}


void Projectile::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
					  bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
					  Matrix* matrix)
{
	if(!drawableComponent || !movableComponent)
		return;

	Vector position = movableComponent->GetPosition();
	Vector offset(drawableComponent->GetWidth() / 2,
				  drawableComponent->GetHeight() / 2);

	position -= offset;
	movableComponent->SetPosition(position);

	Actor::Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);

	position += offset;
	movableComponent->SetPosition(position);
	
}
