//Liam "AFishyFez" Wynn, 7/29/2016, An Engine of Ice and Fire

/*
 A simple component that manages the logic of playing music.
 Basically, the MusicComponent is just a wrapper for SDL_Mixer
 loading and playing functions for music. As such, a requirement
 for MusicComponents is that ONLY ONE CAN BE ACTIVE AT A TIME.
 This means that when you play, Mix_HaltMusic is called first
 when Play is called.
*/

#ifndef AEOIAF_MUSIC_COMPONENT
#define AEOIAF_MUSIC_COMPONENT

#include "AudioComponent.h"

namespace AEOIAF_Audio
{
	class MusicComponent : public AudioComponent
	{
		public:
			MusicComponent();
			MusicComponent(const MusicComponent& toCopy);
			MusicComponent(const char* newAudioPath);
			virtual ~MusicComponent();

			virtual void Initialize();
			virtual void Play();
			virtual void Close();

		private:
			Mix_Music* song; //The song this component plays
	};
}

#endif
