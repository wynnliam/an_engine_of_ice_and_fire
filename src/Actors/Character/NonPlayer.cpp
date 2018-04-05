//Liam "AFishyFez" Wynn

#include "NonPlayer.h"
#include "../../Level/Level.h"

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;

NonPlayer::NonPlayer()
{
}

NonPlayer::NonPlayer(const char* newID) : Character(newID)
{
}

NonPlayer::NonPlayer(const NonPlayer& toCopy)
{
    Copy(toCopy);
}

NonPlayer::~NonPlayer()
{
}

NonPlayer& NonPlayer::operator = (const NonPlayer& toCopy)
{
    Copy(toCopy);
    return *this;
}

void NonPlayer::Copy(const NonPlayer& toCopy)
{
    if(this == &toCopy)
        return;

    Character::Copy(toCopy);
}

NonPlayer* NonPlayer::GetCopy()
{
	return new NonPlayer(*this);
}

void NonPlayer::Update(Level* level, SDL_Event* e, float deltaTime)
{
}

void NonPlayer::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip, 
					 bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos, Matrix* matrix)
{
	Character::Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
}

