//Liam "AFishyFez" Wynn, 7/28/2016, An Engine of Ice and Fire

#include "AudioComponent.h"
#include <cstring>
#include <iostream> //For NULL, and debugging perhaps

using namespace AEOIAF_Audio;
using namespace std;

AudioComponent::AudioComponent()
{
	audioPath = NULL;
}

AudioComponent::AudioComponent(const AudioComponent& toCopy)
{
	audioPath = NULL;

	Copy(toCopy);
}

AudioComponent::AudioComponent(const char* newAudioPath)
{
	audioPath = NULL;
	SetAudioPath(newAudioPath);
}

AudioComponent::~AudioComponent()
{
	if(audioPath)
	{
		delete[] audioPath;
		audioPath = NULL;
	}
}

AudioComponent& AudioComponent::operator = (const AudioComponent& toCopy)
{
	Copy(toCopy);
	return *this;
}

bool AudioComponent::SetAudioPath(const char* setTo)
{
	if(!setTo)
		return false;

	if(audioPath)
		delete[] audioPath;

	audioPath = new char[strlen(setTo) + 1];
	strcpy(audioPath, setTo);

	return true;
}

bool AudioComponent::GetAudioPath(char*& result) const
{
	if(!audioPath)
	{
		result = NULL;
		return false;
	}

	result = new char[strlen(audioPath) + 1];
	strcpy(result, audioPath);

	return true;
}

void AudioComponent::Copy(const AudioComponent& toCopy)
{
	if(this == &toCopy)
		return;

	SetAudioPath(toCopy.audioPath);
}
