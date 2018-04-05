//Liam "AFishyFez" Wynn, 4/20/2015, AEOIAF: Tile

/*
The tile, although closely related to the level,
is a very special component that I believe deserves
a CPP file of its own. A level is comprised of many tiles
*/

#include "Level.h"
#include "../Utilities/Utility_Components/Vector.h"

using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;

Tile::Tile()
{
    type = 0;
    bIsWall = false;
}

Tile::Tile(unsigned int newType, bool newIsWall)
{
    type = newType;
    bIsWall = newIsWall;
}

Tile::Tile(const Tile& toCopy)
{
    Copy(toCopy);
}

Tile::~Tile()
{
}

Tile& Tile::operator = (const Tile& toCopy)
{
    Copy(toCopy);
    return *this;
}

void Tile::Copy(const Tile& toCopy)
{
    type = toCopy.type;
    bIsWall = toCopy.bIsWall;
    position = toCopy.position;
}

void Tile::Draw(SDL_Renderer* renderer, LevelDrawComponent* levelDraw, const Camera& camera, Matrix* matrix)
{
	if(!levelDraw)
		return;

    SDL_Rect sourceRect;
    Vector tempPos = position; //Have to save a copy because draw modifies the position!
    
	levelDraw->GetSourceRectangle(type, sourceRect);

	if(camera.CanSee(CreateBoundingBox(position, 64, 64)))
		levelDraw->Draw(renderer, tempPos, SDL_FLIP_NONE, false, false, true, sourceRect, matrix);
}
