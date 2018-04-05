//Liam "AFishyFez" Wynn, 1/22/2016, A Clash of Colors

/*
 Level handling is done a bit differently than handling
 actors. Since levels are big in size, the goal is to
 have only one level loaded into memory at a time. As
 such, what the level handler will do is read in a level
 from a file, and return the result.

 What makes the level handler particularly challenging is
 that we will also need to supply it the other actor
 handlers to load in each item.
*/

#ifndef ACOC_LEVEL_HANDLER
#define ACOC_LEVEL_HANDLER

#include <SDL2/SDL.h>
#include <fstream> //Use this to read in files
#include "../Level/LevelDrawComponentList.h"

namespace AEOIAF_Level
{
	class Level;
}

namespace AEOIAF_Utilities
{
	class AxisAllignedBoundingBox;
	class Vector;
}

namespace ACOC_GameDataHandling
{
	class GameDataHandler;
	class StreamDataHandler;

	class LevelHandler
	{
		public:
			LevelHandler();
			~LevelHandler();

			AEOIAF_Level::Level* GetLevel(const char* toGet,
										  const GameDataHandler& dataHandler,
										  StreamDataHandler& streamHandler,
										  SDL_Renderer* renderer);

		private:
			/*SPECIFIC LEVEL LOADING FUNCTIONS*/
			AEOIAF_Level::Level* GetLevel(const GameDataHandler& dataHandler, StreamDataHandler& streamHandler,
										  SDL_Renderer* renderer, const char* filePath);

			/*GENERAL PURPOSE LEVEL PROPERTY FUNCTIONS*/
			//Loads all the properties of the tiles: dimensions, texture, walls, etc
			bool LoadLevelTileProperties(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer);
			//Handles the logic of loading draw component
			void LoadLevelDrawComponent(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer);
			//Handles the logic of loading AI traversal areas
			void LoadLevelTraversalAreas(AEOIAF_Level::Level* level, std::ifstream& in) const;

			//Loads in edges that connect AI traversal areas
			void LoadLevelTraversalEdges(AEOIAF_Level::Level* level, std::ifstream& in) const;
			//Loads all characters for the level
			bool LoadLevelCharacters(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer,
									 const GameDataHandler& dataHandler) const;
			//Handles loading a single character
			bool LoadACharacter(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer,
								const GameDataHandler& dataHandler, const int index) const;

			//Loads all props for the level
			bool LoadLevelProps(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer,
								const GameDataHandler& dataHandler) const;

			//Handles loading a single prop
			bool LoadAProp(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer,
						   const GameDataHandler& dataHandler, const int index) const;
			
			//Loads all particles for the level
			bool LoadLevelParticles(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer,
									const GameDataHandler& dataHandler) const;
			//Handles loading a single particle
			bool LoadAParticle(AEOIAF_Level::Level* level, std::ifstream& in, SDL_Renderer* renderer,
							   const GameDataHandler& dataHandler) const;

			/*UTILITY FUNCTIONS*/
			char* ReadInString(std::ifstream& in) const;
			unsigned int ReadInUnsignedInt(std::ifstream& in) const;
			unsigned int* ReadInUnsignedIntArray(std::ifstream& in, const unsigned int length) const;
			bool* ReadInBooleanArray(std::ifstream& in, const unsigned int length) const;
			void ReadInVector(std::ifstream& in, AEOIAF_Utilities::Vector& vector) const;
			char* MakeID(const char* type, const int index) const;

			AEOIAF_Level::LevelDrawComponentList drawComponentList;
	};
}

#endif
