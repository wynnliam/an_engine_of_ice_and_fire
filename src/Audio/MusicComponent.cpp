//Liam "AFishyFez" Wynn, 7/29/2016, An Engine of Ice and Fire

#include "MusicComponent.h"
#include <iostream>

using namespace AEOIAF_Audio;
using namespace std;

MusicComponent::MusicComponent()
{
	song = NULL;
}

MusicComponent::MusicComponent(const MusicComponent& toCopy) : AudioComponent(toCopy)
{
	song = NULL;
}

MusicComponent::MusicComponent(const char* newAudioPath) : AudioComponent(newAudioPath)
{
	song = NULL;
}

MusicComponent::~MusicComponent()
{
	Close();
}

void MusicComponent::Initialize()
{
	if(!audioPath)
		song = NULL;
	else
	{
		Close();

		song = Mix_LoadMUS(audioPath);
		if(!song)
			cout << "Error loading song! " << Mix_GetError() << endl;
	}
}

void MusicComponent::Play()
{
	if(!song)
		return;

	Mix_HaltMusic();
	Mix_PlayMusic(song, 0);
}

void MusicComponent::Close()
{
	Mix_HaltMusic();

	if(song)
	{
		Mix_FreeMusic(song);
		song = NULL;
	}
}
