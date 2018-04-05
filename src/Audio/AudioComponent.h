//Liam "AFishyFez" Wynn, 7/28/2016, An Engine of Ice and Fire

/*
 Well shit, this was a bit overdue. Anyways, Audio management
 is a core feature of modern games. Be they 2D or 3D, a good
 engine should support sounds and music to some capacity.

 The most basic form of sound management is the AudioComponent.
 In this case, all it does is act as a parent class for the
 SoundComponent and MusicComponent classes.

 While you should look at those to see what those are about,
 the audio system in AEOIAF is mainly a series of wrappers for
 SDL_mixer in an object-oriented fashion. As such, the kinds
 of effects possible are quite primitive.
*/

#ifndef AEOIAF_AUDIO_COMPONENT
#define AEOIAF_AUDIO_COMPONENT

#include <SDL2/SDL_mixer.h>

namespace AEOIAF_Audio
{
	class AudioComponent
	{
		public:
			AudioComponent();
			AudioComponent(const AudioComponent& toCopy);
			AudioComponent(const char* newAudioPath);
			virtual ~AudioComponent();

			virtual AudioComponent& operator = (const AudioComponent& toCopy);

			bool SetAudioPath(const char* setTo);
			bool GetAudioPath(char*& result) const;

			virtual void Copy(const AudioComponent& toCopy);

			//Handles the process of initializing anything needed to
			//pre-playing
			virtual void Initialize() = 0;
			//Handles the logic of playing the sound
			virtual void Play() = 0;
			//Will close down the audio component (ie: free it)
			virtual void Close() = 0;

		protected:
			//Stores the path to the audio content. Since
			//music and sound chunks use different SDL structs
			//to store them, we can only really have this here.
			char* audioPath;
	};
}

#endif
