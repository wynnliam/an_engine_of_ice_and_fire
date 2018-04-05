//Liam "AFishyFez" Wynn, 4/20/2015, AEOIAF: Level Draw Component

/*
This basically handles the drawing requirements of a level.
It extends from DrawComponent, but has a bit more
functionality that is tailored to levels. Namely a method that
creates a source rectangle, and a draw method that uses that rectangle
*/

#ifndef AEOIAF_LEVEL_DRAW
#define AEOIAF_LEVEL_DRAW

#include "../Basic_Components/DrawableComponent.h"

using namespace AEOIAF_Utilities;

namespace AEOIAF_Utilities
{
	class Vector;
}

namespace AEOIAF_Level
{
    class LevelDrawComponent : public DrawableComponent
    {
        public:
            LevelDrawComponent();
            LevelDrawComponent(int numTypes, const char* newTexturePath);
            LevelDrawComponent(const LevelDrawComponent& toCopy);

            LevelDrawComponent& operator = (const LevelDrawComponent& toCopy);

            void SetNumTileTypes(unsigned int val) { numTypes = val; }

            void Copy(const LevelDrawComponent& toCopy);
            //Will create a source rectangle. Returns 0 if the value supplied is bad
            //(that is, >= numTypes)
            int GetSourceRectangle(unsigned int type, SDL_Rect& outSourceRectangle) const;

            //It will be almost exactly like the regular draw method, but this requires
            //a source rectangle
            void Draw(SDL_Renderer* renderer, AEOIAF_Utilities::Vector& position, SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      SDL_Rect& sourceRect, AEOIAF_Utilities::Matrix* matrix = NULL);

        private:
            //The number of tile types in this level
            //primarily used to detect if a supplied tile type in GetSourceRectangle
            //is valid or not
            unsigned int numTypes;
    };
}

#endif // AEOIAF_LEVEL_DRAW
