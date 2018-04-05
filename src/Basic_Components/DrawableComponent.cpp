//Liam "AFishyFez" Wynn, 4/11/2015

#include "DrawableComponent.h"
#include "../Utilities/Utility_Components/Constants.h" //For Constants::TILE_SIZE
#include <cstring>
#include <iostream>
#include <cmath>

#define DEFAULT_CENT 1000 //Use to denote center of image

using namespace std;
using namespace AEOIAF_Content;
using namespace AEOIAF_Utilities;

DrawableComponent::DrawableComponent()
{
    rendered = NULL;
    bInitialized = false;

    width = 0;
    height = 0;

    center.SetX(DEFAULT_CENT);
    center.SetY(DEFAULT_CENT);

    rotation = 0.0f;
    scale = 1.0f;

    color = AEOIAFColor::White();

    texturePath = NULL;
}

DrawableComponent::DrawableComponent(const char* newTexturePath)
{
    texturePath = NULL;
    SetTexturePath(newTexturePath);

    rendered = NULL;
    bInitialized = false;

    width = 0;
    height = 0;

    center.SetX(DEFAULT_CENT);
    center.SetY(DEFAULT_CENT);

    rotation = 0.0f;
    scale = 1.0f;

    color = AEOIAFColor::White();
}

DrawableComponent::DrawableComponent(const DrawableComponent& toCopy)
{
    rendered = NULL;
    bInitialized = false;

	texturePath = NULL;

    Copy(toCopy);
}

DrawableComponent::~DrawableComponent()
{
    if(texturePath)
        delete[] texturePath;

    //This will deallocate the texture,
    //so no need to delete it
    Close();
}

DrawableComponent& DrawableComponent::operator = (const DrawableComponent& toCopy)
{
    Copy(toCopy);

    return *this;
}

int DrawableComponent::GetTexturePath(char*& copyTo) const
{
    int result;

    if(texturePath && texturePath != copyTo)
    {
        copyTo = new char[strlen(texturePath) + 1];
        strcpy(copyTo, texturePath);

        result = 1;
    }

    else
    {
        copyTo = NULL;

        result = 0;
    }

    return result;
}

int DrawableComponent::SetTexturePath(const char* newTexturePath)
{
    //Lest we achieve death
    if(texturePath == newTexturePath)
        return 0;

    if(texturePath)
        delete[] texturePath;

    int result;

    if(newTexturePath)
    {
        texturePath = new char[strlen(newTexturePath) + 1];
        strcpy(texturePath, newTexturePath);

        result = 1;
    }

    else
    {
        texturePath = NULL;

        result = 0;
    }

    return result;
}

void DrawableComponent::Copy(const DrawableComponent& toCopy)
{
    if(this == &toCopy)
        return;

    SetTexturePath(toCopy.texturePath);

    center = toCopy.center;

    rotation = toCopy.rotation;
    scale = toCopy.scale;

    color = toCopy.color;
}

DrawableComponent* DrawableComponent::GetCopy()
{
    DrawableComponent* result = new DrawableComponent(*this);
    return result;
}

void DrawableComponent::Initialize(SDL_Renderer* renderer)
{
    if(bInitialized || !renderer)
        return; //It has already been initialized!

    SDL_Surface* loadedSurface = IMG_Load(texturePath);

    if(loadedSurface == NULL)
        cout << "Unable to load image! " << IMG_GetError() << endl;

    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
        rendered = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if(rendered == NULL)
            cout << "Unable to create texture: " << SDL_GetError() << endl;

        else
        {
            //Grab width and height properties of the base texture
            SDL_QueryTexture(rendered, NULL, NULL, &width, &height);

			SDL_FreeSurface(loadedSurface);
			loadedSurface = NULL;

            bInitialized = true; //Initialization was a success!
        }
    }
}

void DrawableComponent::Draw(SDL_Renderer* renderer, Vector& position, SDL_RendererFlip flip,
                             bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos, Matrix* matrix,
							 SDL_Rect* source)
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
	SDL_Point tempCenter; //Handles the origin of the texture for rotation
	float centX, centY; //Use these to grab the center's components, to avoid many getter calls

    destRect.x = (int)position.GetX();
    destRect.y = (int)position.GetY();

	//If a source rectangle is not supplied, then have the
	//destination rect's width and height the size of the
	//entire texture. Otherwise, set the dest's width and
	//height to the source's
	if(!source)
	{
		destRect.w = width * tempScale;
		destRect.h = height * tempScale;
	}

	else
	{
		destRect.w = source->w * tempScale;
		destRect.h = source->h * tempScale;
	}

	//If the center of rotation is not supplied, then
	//use destRect's center (as is the SDL default).
	//otherwise, use the supplied center
	centX = center.GetX();
	centY = center.GetY();

	if(centX == DEFAULT_CENT && centY == DEFAULT_CENT)
		tempCenter = { destRect.w / 2, destRect.h / 2 };
	else
		tempCenter = { (int)centX, (int)centY };

    SDL_RenderCopyEx(renderer, rendered, source, &destRect, tempRot, &tempCenter, flip);
}

//Deallocates the rendered object
void DrawableComponent::Close()
{
    if(bInitialized)
    {
        if(rendered)
		{
            SDL_DestroyTexture(rendered);
			rendered = NULL;
		}

        bInitialized = false;
    }
}
