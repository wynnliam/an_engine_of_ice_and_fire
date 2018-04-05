//Liam "AFishyFez" Wynn, 4/20/2015 (yeeaaaaah.....), AEOIAF: Level Draw Component

#include "LevelDrawComponent.h"
#include "../Utilities/Utility_Components/Constants.h" //For Constants::TILE_SIZE
#include "../Utilities/Utility_Components/Vector.h"
#include <cmath>

#define DEFAULT_CENT 1000 //Use to denote center of image

using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;

LevelDrawComponent::LevelDrawComponent()
{
    numTypes = 0;
}

LevelDrawComponent::LevelDrawComponent(int newNumTypes, const char* newTexturePath)
                   : DrawableComponent(newTexturePath)
{
    numTypes = newNumTypes;
}

LevelDrawComponent::LevelDrawComponent(const LevelDrawComponent& toCopy)
{
    Copy(toCopy);
}

LevelDrawComponent& LevelDrawComponent::operator= (const LevelDrawComponent& toCopy)
{
    Copy(toCopy);
    return *this;
}

void LevelDrawComponent::Copy(const LevelDrawComponent& toCopy)
{
    if(this == &toCopy)
        return;

    numTypes = toCopy.numTypes;
    DrawableComponent::Copy(toCopy); //To copy all properties
}

//Calculate the x position of the source rect by doing type * tileSize
//because the position of the source rectangle is relative to the top-left corner,
//and to get that corner of any given tile type, we have to scale by the tile size.
int LevelDrawComponent::GetSourceRectangle(unsigned int type, SDL_Rect& outSourceRectangle) const
{
    int result;

    if(type >= numTypes)
        result = 0;
    else
    {
        outSourceRectangle.x = type * AEOIAF_TILE_SIZE;
        outSourceRectangle.y = 0;
        outSourceRectangle.w = AEOIAF_TILE_SIZE;
        outSourceRectangle.h = AEOIAF_TILE_SIZE;

        result = 1;
    }

    return result;
}

void LevelDrawComponent::Draw(SDL_Renderer* renderer, Vector& position, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              SDL_Rect& sourceRect, Matrix* matrix)
{
    if(!renderer || !rendered)
        return;

	float tempRot = rotation;
	float tempScale = scale;

    if(matrix)
    {
		position = Matrix::Transform(position, *matrix);
		tempRot -= (asin(matrix->m21 / matrix->m33) * 180.0f) / AEOIAF_PI;
		tempScale *= matrix->m33;
    }

    //Modulate texture
    SDL_SetTextureColorMod(rendered, color.GetR(), color.GetG(), color.GetB());
    SDL_SetTextureAlphaMod(rendered, color.GetA());

    //Handles position and scale of the texture
    SDL_Rect destRect;
    destRect.x = (int)position.GetX();
    destRect.y = (int)position.GetY();
    destRect.w = AEOIAF_TILE_SIZE * tempScale;
    destRect.h = AEOIAF_TILE_SIZE * tempScale;

    SDL_RenderCopyEx(renderer, rendered, &sourceRect, &destRect, tempRot, NULL, flip);
}
