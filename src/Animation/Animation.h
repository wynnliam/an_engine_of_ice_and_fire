//Liam "AFishyFez" Wynn, 7/30/2015, A Clash of Colors

/*
 In virtually all games, animations are important.
 They bring to life an otherwise static universe.
 In A Clash of Colors (and AEOIAF), I set out to
 build animations through the AnimationHandler and
 Animation classes.

 The AnimationHandler essentially holds a drawable
 component, a timer, and an array of Animation classes.
 It's job is to act as the frontend of the animation
 system. That is, when the outside world interacts
 with an animation, they must go through the AnimationHandler.
 In addition, the AnimationHandler also keeps track of time,
 which animation to play, and how to draw the animation.

 The Animation class handles a specific row in a sprite sheet.
 It will keep track of the current frame in the row, when the
 animation is done, and whether or not we repeat the specific
 animation or not.
*/

#ifndef ACOC_ANIMATION
#define ACOC_ANIMATION

#include "../Basic_Components/DrawableComponent.h"
#include "../Utilities/General_Purpose/Timer.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Utilities
{
	class Vector;
}

namespace ACOC_Animation
{
	class Animation
	{
		public:
			Animation();
			Animation(unsigned int newNumFrames, unsigned int newFrameRate);
			Animation(const Animation& toCopy);
			~Animation();

			Animation& operator= (const Animation& toCopy);

			unsigned int GetFrameRate() const { return frameRate; }
			void SetFrameRate(unsigned int val) { frameRate = val; }

			unsigned int GetNumFrames() const { return numFrames; }
			void SetNumFrames(unsigned int val) { numFrames = val; }

			unsigned int GetCurrentFrame() const { return currentFrame; }
			void SetCurrentFrame(unsigned int val) { currentFrame = val; }

			bool IsRepeating() const { return bRepeat; }
			void ShouldRepeat(bool val) { bRepeat = val; }

			bool IsFinished() const { return bFinished; }

			void Copy(const Animation& toCopy);

			//Returns if the frame finished
			bool Update(unsigned int elapsedTime, unsigned int previousTime);

		private:
			//Upon finishing the animation, we invoke this
			//to decide what to do next
			void HandleFinishAnimation();

			unsigned int frameRate; //The rate that we go from one frame to another
			unsigned int numFrames; //The number of frames in this row
			unsigned int currentFrame; //The frame we are currently on

			bool bRepeat; //Do we replay this animation infinitely?
			bool bFinished; //Have we reached the final frame?
	};

	class AnimationHandler
	{
		public:
			AnimationHandler();
			AnimationHandler(const char* texturePath);
			AnimationHandler(const AnimationHandler& toCopy);
			~AnimationHandler();

			AnimationHandler& operator= (const AnimationHandler& toCopy);

			unsigned int GetNumAnims() const { return numAnims; }
			void SetNumAnims(unsigned int val);

			unsigned int GetCurrentAnim() const { return currentAnim; }
			void SetCurrentAnim(unsigned int val) { currentAnim = val; }

			unsigned int GetFrameWidth() const { return frameWidth; }
			void SetFrameWidth(unsigned int val) { frameWidth = val; }

			unsigned int GetFrameHeight() const { return frameHeight; }
			void SetFrameHeight(unsigned int val) { frameHeight = val; }

			bool IsPlaying() const { return bPlaying; }

			//Drawable component wrapper getters and setters
			AEOIAF_Utilities::DrawableComponent* GetDrawableComponent() { return drawComponent; }
			void SetDrawableComponent(AEOIAF_Utilities::DrawableComponent* val) { drawComponent = val; }

            int GetTexturePath(char*& copyTo) const;

            int GetWidth() const;
            int GetHeight() const;

			//Animation wrapper getters and setters
			unsigned int GetCurrentFrame(unsigned int index) const;
			void SetCurrentFrame(unsigned int index, unsigned int val);

			unsigned int GetFrameRate(unsigned int index) const;
			void SetFrameRate(unsigned int index, unsigned int val);

			unsigned int GetNumFrames(unsigned int index) const;
			void SetNumFrames(unsigned int index, unsigned int val);

			bool IsRepeating(unsigned int index) const;
			void ShouldRepeat(unsigned int index, bool val);

			void Copy(const AnimationHandler& toCopy);

			//Handler functions
			void Initialize(SDL_Renderer* renderer);

			void Start();
			void Stop();

			void Update();

            void Draw(SDL_Renderer* renderer, AEOIAF_Utilities::Vector& position, const float rotation,
					  const AEOIAF_Content::AEOIAFColor& color,SDL_RendererFlip flip,
                      bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                      AEOIAF_Utilities::Matrix* matrix = NULL);
			
		private:
			AEOIAF_Utilities::Timer timur;

			//The amount of time that has passed since the last update,
			//and the last time stamp of when a frame changed
			unsigned int elapsedTime, previousTime;

			//Because each row represents an animation in a sprite
			//sheet, this basically holds how many rows we have
			unsigned int numAnims;
			unsigned int currentAnim;
			Animation* animations;

			unsigned int frameWidth, frameHeight;

			bool bPlaying; //Is the current animation playing, or is it paysed?

			AEOIAF_Utilities::DrawableComponent* drawComponent;
	};
}

#endif
