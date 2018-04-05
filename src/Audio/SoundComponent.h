//Liam "AFishyFez" Wynn, 7/31/2016, An Engine of Ice and Fire

/*
 One of the most important things about games is sound effects.
 Gunshots, footsteps, anything that isn't music, really. We
 handle such effects here, with the SoundComponent. As a requirement,
 a channel MUST be supplied by the user. Sound effects are played on
 a channel, and if one is not given, we assume 2 by default.
*/

#ifndef AEOIAF_SOUND_COMPONENT
#define AEOIAF_SOUND_COMPONENT

#include "AudioComponent.h"

namespace AEOIAF_Audio
{
	class SoundComponent : public AudioComponent
	{
		public:
			SoundComponent(const int newChannel = 2);
			SoundComponent(const SoundComponent& toCopy);
			SoundComponent(const char* newAudioPath, const int newChannel = 2);
			virtual ~SoundComponent();

			int GetChannel() const { return channel; }
			void SetChannel(const int val) { channel = val; }

			virtual SoundComponent& operator = (const SoundComponent& toCopy);

			virtual void Copy(const SoundComponent& toCopy);

			//Handles the process of initializing anything needed to
			//pre-playing
			virtual void Initialize();
			//Handles the logic of playing the sound
			virtual void Play();
			//Will close down the audio component (ie: free it)
			virtual void Close();

		private:
			Mix_Chunk* chunk; //What we use to play the sound effect
			int channel; //The channel we play the chunk on
	};
}

#endif
