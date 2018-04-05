//Liam "AFishyFez" Wynn, 7/27/2015, A Clash of Colors

/*
 Games include tons of assests. They must manage everything
 from levels, to characters, weapons, and all points in between.
 The whole purpose of the GameDataHandler is too have a single
 place to manage all these assests. As the game progresses, and
 we need to go to certain levels, or have certain characters
 appear, or whatever, we can ask the GameDataHandler for these
 assests.

 Essentially, the GameDataHandler will has a series of wrapper
 functions for structures that hold instances of each kind of asset
 (Levels, Characters, Items, and Props). As we need objects, we will
 primarily get copies of these instances. However, this may not always
 be the case for each smaller data structure.

 In addition, the GameDataHandler will be responsible for reading/writing
 all assests to file. However, this functionality will be done far down
 the road.

 Until I add the LevelsHandler, CharactersHandler, PropsHanlder, and
 ItemsHandler, When asking for any level, we will return a simple
 test level with a player.
*/

#ifndef ACOC_GAME_DATA_HANDLER
#define ACOC_GAME_DATA_HANDLER

#include <SDL2/SDL.h>
#include "../Level/Level.h"

#include "DrawComponentList.h"
#include "AudioComponentList.h"

#include "LevelHandler.h"

#include "CharacterHandler.h"
#include "PropHandler.h"
#include "WeaponHandler.h"
#include "ShieldHandler.h"
#include "ParticleHandler.h"

//Keep track of level metadata
#include "StreamData/StreamData.h"

using namespace AEOIAF_Level;

namespace ACOC_GameDataHandling
{
	class GameDataHandler
	{
		public:
			GameDataHandler();
			GameDataHandler(SDL_Renderer* renderer);
			~GameDataHandler();

			StreamDataHandler* GetStreamHandler() { return streamHandler; }
			void SetStreamHandler(StreamDataHandler* val);

			void SetRenderer(SDL_Renderer* val) { renderer = val; }

			//Will return the level at the given
			//index. Levels will eventually be stored
			//in an array
			Level* GetLevel(const char* toGet);

			Level* GetWorldMap() { return worldMap; }
			void SetWorldMap(Level* val) { worldMap = val; }

			//Creates, initializes, and returns a character
			AEOIAF_Actor::Character* GetCharacter(const char* toGet) const;
			//Creates, initializes, and returns a prop
			AEOIAF_Actor::Prop* GetProp(const char* toGet) const;
			//Creates, initializes, and returns a weapon
			AEOIAF_Actor::Weapon* GetWeapon(const char* toGet) const;
			//Creates, initializes, and returns a shield
			AEOIAF_Actor::Shield* GetShield(const char* toGet) const;
			//Creates, initializes, and returns a particle
			AEOIAF_Actor::ParticleEmitter* GetParticleEmitter(const char* toGet) const;

			//Create and return an actor of unknown type
			//Type maps as follows:
			//	C = Character
			//	P = Prop
			//	W = Weapon
			//	S = Shield
			//	A = Particle Emitter
			//	U = Unknown
			AEOIAF_Actor::Actor* GetActorUnknownType(const char* toGet, char& type) const;

			//If the renderer is enabled, we create all draw components for the game
			bool LoadDrawComponents();
			void InsertDrawableComponent(const char* id, AEOIAF_Utilities::DrawableComponent* component);
			AEOIAF_Utilities::DrawableComponent* GetDrawableComponent(const char* id);

			bool LoadAudioComponents();
			AEOIAF_Audio::AudioComponent* GetAudioComponent(const char* id);

		private:
			AEOIAF_Utilities::DrawComponentTable drawComponentTable;
			AEOIAF_Utilities::AudioComponentList audioComponentTable;

			Level* currentLevel;
			Level* worldMap; //Where we go to traverse the entire world

			LevelHandler levelHandler; //Use this to get levels

			CharacterHandler characterHandler; //Use this to get characters for a level
			PropHandler propHandler; //Use this to get props for a level
			WeaponHandler weaponHandler; //Use this to get weapons for a level/character
			ShieldHandler shieldHandler; //Use this to get shields for a level/character
			ParticleHandler particleHandler; //Use this to get particles for a level/item

			StreamDataHandler* streamHandler;

			SDL_Renderer* renderer;
	};
}

#endif
