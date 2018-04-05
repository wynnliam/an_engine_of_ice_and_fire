//Liam "AFishyFez" Wynn, 7/30/2015, A Clash of Colors

#include "Animation.h"
#include "../Utilities/Utility_Components/Vector.h"
#include <iostream>

using namespace ACOC_Animation;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Content;
using namespace std;

/*ANIMATION MANAGER IMPLEMENTATIONS*/
AnimationHandler::AnimationHandler()
{
	elapsedTime = 0;
	previousTime = 0;

	numAnims = 0;
	currentAnim = 0;
	animations = NULL;

	frameWidth = 0;
	frameHeight = 0;

	bPlaying = false;

	drawComponent = NULL;
}

AnimationHandler::AnimationHandler(const char* texturePath)
{
	elapsedTime = 0;
	previousTime = 0;

	numAnims = 0;
	currentAnim = 0;
	animations = NULL;

	frameWidth = 0;
	frameHeight = 0;

	bPlaying = false;

	drawComponent = new DrawableComponent(texturePath);
}

AnimationHandler::AnimationHandler(const AnimationHandler& toCopy)
{
	Copy(toCopy);
}

AnimationHandler::~AnimationHandler()
{
	if(animations)
	{
		delete[] animations;
		animations = NULL;
	}

	//This is handled by the DrawTable
	drawComponent = NULL;
}

AnimationHandler& AnimationHandler::operator= (const AnimationHandler& toCopy)
{
	Copy(toCopy);
	return *this;
}

void AnimationHandler::SetNumAnims(unsigned int val)
{
	numAnims = val;

	if(animations)
		delete[] animations;

	animations = new Animation[numAnims];
}

int AnimationHandler::GetTexturePath(char*& copyTo) const
{
	if(!drawComponent)
		return 0;

	return drawComponent->GetTexturePath(copyTo);
}

int AnimationHandler::GetWidth() const
{
	if(!drawComponent)
		return 0;

	return drawComponent->GetWidth();
}

int AnimationHandler::GetHeight() const
{
	if(!drawComponent)
		return 0;

	return drawComponent->GetHeight();
}

unsigned int AnimationHandler::GetCurrentFrame(unsigned int index) const
{
	if(!animations || index >= numAnims)
		return 0;

	return animations[index].GetCurrentFrame();
}

void AnimationHandler::SetCurrentFrame(unsigned int index, unsigned int val)
{
	if(!animations || index >= numAnims)
		return;

	animations[index].SetCurrentFrame(val);
}

unsigned int AnimationHandler::GetFrameRate(unsigned int index) const
{
	if(!animations || index >= numAnims)
		return 0;

	return animations[index].GetFrameRate();
}

void AnimationHandler::SetFrameRate(unsigned int index, unsigned int val)
{
	if(!animations || index >= numAnims)
		return;

	animations[index].SetFrameRate(val);
}

//If animations is NULL, or index is greater than or equal to
//numAnims, then return 0. Otherwise, return GetNumFrames from
//the animation at index
unsigned int AnimationHandler::GetNumFrames(unsigned int index) const
{
	if(!animations || index >= numAnims)
		return 0;

	return animations[index].GetNumFrames();
}

//If animations is NULL, or index is greater than or equal to numAnims,
//then return. Otherwise, set the number of frames for the animation
//at index.
void AnimationHandler::SetNumFrames(unsigned int index, unsigned int val)
{
	if(!animations || index >= numAnims)
		return;

	animations[index].SetNumFrames(val);
}

//If animations is NULL, or the index is greater than or equal
//numAnims, then return false. Otherwise, return the result from
//the animation at index
bool AnimationHandler::IsRepeating(unsigned int index) const
{
	if(!animations || index >= numAnims)
		return false;

	return animations[index].IsRepeating();
}

//If animations is NULL, or the index is greater than or equal to
//numAnims, then return. Otherwise set the nature of repeating of
//the animation at index to the value of val.
void AnimationHandler::ShouldRepeat(unsigned int index, bool val)
{
	if(!animations || index >= numAnims)
		return;

	animations[index].ShouldRepeat(val);
}

void AnimationHandler::Copy(const AnimationHandler& toCopy)
{
	if(this == &toCopy)
		return;

	if(!toCopy.animations)
	{
		numAnims = 0;
		animations = NULL;
	}

	else
	{
		numAnims = toCopy.numAnims;
		animations = new Animation[numAnims];
		for(unsigned int i = 0; i < numAnims; ++i)
			animations[i] = toCopy.animations[i];
	}

	frameWidth = toCopy.frameWidth;
	frameHeight = toCopy.frameHeight;

	if(!toCopy.drawComponent)
		drawComponent = NULL;
	else
		drawComponent = toCopy.drawComponent->GetCopy();

	elapsedTime = 0;
	previousTime = 0;
	currentAnim = 0;
	bPlaying = false;
}

void AnimationHandler::Start()
{
	elapsedTime = 0;
	previousTime = 0;

	bPlaying = true;
	
	animations[currentAnim].SetCurrentFrame(0);
	timur.Start();
}

void AnimationHandler::Stop()
{
	elapsedTime = 0;
	previousTime = 0;

	bPlaying = false;

	timur.Stop();
}

//If animations is NULL, or the currentAnim is out of bounds,
//then return. Otherwise do the update logic
void AnimationHandler::Update()
{
	if(!bPlaying || !animations || currentAnim >= numAnims)
		return;

	elapsedTime += timur.GetTicks();

	if(animations[currentAnim].Update(elapsedTime, previousTime))
	{
		previousTime = elapsedTime;
		elapsedTime = 0;

		if(animations[currentAnim].IsFinished())
			Stop();
	}
}

//If the renderer, drawComponent, or animations are NULL then return false. Also, if the current
//animation index is not in the bounds of the number of animations, then return false. Otherwise,
//create a source rectangle given the frame width and height, and the current animation index.
//Use this in renderering the draw component.
void AnimationHandler::Draw(SDL_Renderer* renderer, Vector& position, const float rotation,
							const AEOIAFColor& color,SDL_RendererFlip flip,
							bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos, Matrix* matrix)
{
	if(!renderer || !drawComponent || !animations)
		return;
	if(currentAnim >= numAnims)
		return;

	drawComponent->SetRotation(rotation);
	drawComponent->GetColor() = color;

	//The source rectangle we will draw with
	SDL_Rect source;

	source.x = animations[currentAnim].GetCurrentFrame() * frameWidth;
	source.y = currentAnim * frameHeight;
	source.w = frameWidth;
	source.h = frameHeight;

	drawComponent->Draw(renderer, position, flip, bTrsfrmRot,
						bTrsfrmScale, bTrsfrmPos, matrix,
						&source);
}

/*ANIMATION IMPLMENTATIONS*/
Animation::Animation()
{
	frameRate = 0;
	numFrames = 0;
	currentFrame = 0;

	bRepeat = false;
	bFinished = false;
}

Animation::Animation(unsigned int newNumFrames, unsigned int newFrameRate)
{
	frameRate = newFrameRate;
	numFrames = newNumFrames;
	currentFrame = 0;

	bRepeat = false;
	bFinished = false;
}

Animation::Animation(const Animation& toCopy)
{
	Copy(toCopy);
}

Animation::~Animation()
{
}

Animation& Animation::operator= (const Animation& toCopy)
{
	Copy(toCopy);
	return *this;
}

void Animation::Copy(const Animation& toCopy)
{
	if(this == &toCopy)
		return;

	frameRate = toCopy.frameRate;
	numFrames = toCopy.numFrames;
	bRepeat = toCopy.bRepeat;

	currentFrame = 0;
	bFinished = false;
}

//We will check if the elapsed time is greater than the
//previous time plus the frame rate. If so, change our current
//frame. At this point, if we are finished, then call 
//HandleFinishAnimation. Otherwise, return false
bool Animation::Update(unsigned int elapsedTime, unsigned int previousTime)
{
	bool bFinishedFrame;

	if(elapsedTime >= previousTime + frameRate)
	{
		bFinishedFrame = true;

		++currentFrame;

		if(currentFrame >= numFrames)
			HandleFinishAnimation();
		else
			bFinished = false;
	}

	else
		bFinishedFrame = false;

	return bFinishedFrame;
}

//Set current frame to 0. If we are repeating,
//then set bFinsihed to false. Otherwise, set it to
//true
void Animation::HandleFinishAnimation()
{
	currentFrame = 0;
	bFinished = !bRepeat;
}
