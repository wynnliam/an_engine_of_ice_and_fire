//Liam "AFishyFez" Wynn, 8/1/2016, An Engine of Ice and Fire

/*
 Like the DrawComponentList, we keep a list of all audio components
 in the game, and make copies of them as needed. The user should determine
 the channel used by the component before inserting. Unless it's music.
 In which case, we don't really care.
*/

#ifndef AEOIAF_AUDIO_COMPONENT_LIST
#define AEOIAF_AUDIO_COMPONENT_LIST

#include "../Audio/AudioComponent.h"
#include "../Audio/SoundComponent.h"
#include "../Audio/MusicComponent.h"

using namespace AEOIAF_Audio;

namespace AEOIAF_Utilities
{
	struct AudioComponentListNode
	{
		AudioComponentListNode();
		~AudioComponentListNode();

		char* id;
		AudioComponent* component;
		AudioComponentListNode* next;
	};

	class AudioComponentList
	{
		public:
			AudioComponentList(int size = 7);
			~AudioComponentList();

			void Insert(const char* id, AudioComponent* toInsert);
			AudioComponent* GetComponent(const char* id) const;

			void Clear();

		private:
			AudioComponent* GetComponent(const char* id, AudioComponentListNode* head) const;
			//Recursively clears a single LLL in the table
			void Clear(AudioComponentListNode*& head);

			int GetHashIndex(const char* toHash) const;

			int tableSize;
			AudioComponentListNode** table;
	};
}

#endif
