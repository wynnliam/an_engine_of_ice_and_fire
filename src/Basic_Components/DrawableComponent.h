//Liam "AFishyFez" Wynn, 4/10/2015, AEOIAF: Drawable Component

/*
A drawable component is an abstraction
that handles all the logic of rendering
a texture to the screen. The goal is to
allow various entities to not have to
worry about this functionality in themselves
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../Utilities/Color_Utilities/AEOIAFColor.h"
#include "../Utilities/General_Purpose/Matrix.h"

#ifndef AEOIAF_DRAW_COMPONENT
#define AEOIAF_DRAW_COMPONENT

namespace AEOIAF_Utilities
{
	//While the Drawable component needs Vectors, they should
	//not be included with the Drawable component.
	class Vector;

    class DrawableComponent
    {
        public:
            DrawableComponent();
            DrawableComponent(const char* newTexturePath);
            DrawableComponent(const DrawableComponent& toCopy);
            virtual ~DrawableComponent();

            virtual DrawableComponent& operator = (const DrawableComponent& toCopy);

            bool IsInitialized() const { return bInitialized; }

            int GetTexturePath(char*& copyTo) const;
            int SetTexturePath(const char* newTexturePath);

            int GetWidth() const { return width; }
			void SetWidth(int val) { width = val; }

            int GetHeight() const { return height; }
			void SetHeight(int val) { height = val; }

            Vector GetCenter() const { return center; }
            void SetCenter(const Vector& val) { center = val; }

            float GetRotation() const { return rotation; }
            void SetRotation(float val) { rotation = val; }

            float GetScale() const { return scale; }
            void SetScale(float val) { scale = val; }

            AEOIAF_Content::AEOIAFColor& GetColor() { return color; }

            //Will copy the properties of toCopy into this
            virtual void Copy(const DrawableComponent& toCopy);
            //Creates a copy of this component as a pointer and returns it
            virtual DrawableComponent* GetCopy();
            //Will initialize the rendered object so
            //that it can be drawn
            virtual void Initialize(SDL_Renderer* renderer);
            //The drawing method proper. The goal is to have a uniform
            //drawing function
            virtual void Draw(SDL_Renderer* renderer, Vector& position, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL,
							  SDL_Rect* source = NULL);
            //Deallocates the rendered object
            virtual void Close();

        protected:
            SDL_Texture* rendered; //Effectively what we are rendering
            char* texturePath; //The file path to the texture we render
            int width, height; //Width and height of the texture

            bool bInitialized; //Has this been initialized so we can render?

            AEOIAF_Utilities::Vector center; //The point that we rotate around
            float rotation; //The angle of rotation to orient rendered
            float scale; //The scale of the

            AEOIAF_Content::AEOIAFColor color; //The color to render the texture in
    };
}

#endif // AEOIAF_DRAW_COMPONENT
