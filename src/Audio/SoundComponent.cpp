//Liam "AFishyFez" Wynn, 7/31/2016, An Engine of Ice and Fire

#include "SoundComponent.h"
#include <iostream> //For NULL and debugging

using namespace AEOIAF_Audio;
using namespace std;

SoundComponent::SoundComponent(const int newChannel)
{
	chunk = NULL;
	channel = newChannel;
}

SoundComponent::SoundComponent(const SoundComponent& toCopy)
{
	chunk = NULL;
	Copy(toCopy);
}

SoundComponent::SoundComponent(const char* newAudioPath, const int newChannel) : AudioComponent(newAudioPath)
{
	chunk = NULL;
	channel = newChannel;
}

SoundComponent::~SoundComponent()
{
	Close();
}

SoundComponent& SoundComponent::operator = (const SoundComponent& toCopy)
{
	Copy(toCopy);
	return *this;
}

void SoundComponent::Copy(const SoundComponent& toCopy)
{
	if(this == &toCopy)
		return;

	//Overwrite everything; we need to Close to do it safely!
	Close();

	AudioComponent::Copy(toCopy);

	channel = toCopy.channel;
}

void SoundComponent::Initialize()
{
	if(!audioPath)
		return;

	//Only allocate if it isn't open!
	if(!chunk)
		chunk = Mix_LoadWAV(audioPath);

	if(!chunk)
		cout << "Error loading sound! " << Mix_GetError() << endl;
}

void SoundComponent::Play()
{
	if(!chunk || !audioPath)
		return;

	Mix_PlayChannel(channel, chunk, 0);
}

void SoundComponent::Close()
{
	if(!chunk)
		return;

	Mix_FreeChunk(chunk);
	chunk = NULL;
}
