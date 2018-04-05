//Liam "AFishyFez" Wynn, 4/18/2015, AEOIAF: Level

/*
Levels basically bring every actor and component
together. They as containers for all assets save
things like HUDs and menus. All games have something
similar to a level. Also stored here is a tile class.
Every level is basically a rectangle of tiles.
*/

#ifndef AEOIAF_LEVEL
#define AEOIAF_LEVEL

#include <SDL2/SDL.h>
#include "LevelDataTypes.h"
#include "Level_AI_Data/LevelAIData.h"
#include "LevelDrawComponent.h"
#include "../Utilities/Utility_Components/Camera.h"

namespace AEOIAF_Actor
{
	//Used in finding hit actors/tiles in
	//the level.
	//Levels shouldn't be including weapons,
	//except in the .cpp file. So we'll just
	//do this
	class Weapon;
}

namespace AEOIAF_Utilities
{
	//Just like the weapon, the Vector class
	//shouldn't be included here.
	class Vector;
	class Tracer;
}

namespace AEOIAF_Level
{
	class ActorCollisionList;
	class TileCollisionList;

    class Level
    {
        public:
            Level();
            Level(const char* newId);
            Level(const char* newId, const char* newName);
            ~Level();

            //Returns 0 if the ID is NULL
            int GetID(char*& copyTo) const;
            //Returns 0 if newId is NULL
            int SetID(const char* newId);

            //Returns 0 if name is NULL
            int GetName(char*& copyTo) const;
            //Returns 0 if newName is NULL
            int SetName(const char* newName);

            unsigned int GetWidth() const { return width; }
            void SetWidth(unsigned int  val) { width = val; }

            unsigned int GetHeight() const { return height; }
            void SetHeight(unsigned int  val) { height = val; }

            //Set the number of tiles that appear on a tile sheet
            void SetNumTileTypes(unsigned int numTileTypes);
            //Set the path to the texture sheet itself
            int SetTileTexturePath(const char* texturePath);

			LevelDrawComponent* GetDrawComponent() const { return drawComponent; }
			void SetDrawComponent(LevelDrawComponent* val) { drawComponent = val; }

            unsigned int GetNumSpawnPoints() const { return numSpawnPoints; }
            void SetNumSpawnPoints(unsigned int val) { numSpawnPoints = val; }

            //Gets the spawn at a given index. If it does not exist,
            //or there are no spawns, return 0.
            int GetSpawnPoint(AEOIAF_Utilities::Vector& result, unsigned int index) const;
            //Set the spawn point at a given index. If the index is bad,
            //or spawnPoints in NULL, return 0
            int SetSpawnPoint(const AEOIAF_Utilities::Vector& toAdd, unsigned int index);

			AEOIAF_Utilities::Matrix* GetDrawMatrix();
            void SetDrawMatrix(AEOIAF_Utilities::Matrix* val) { drawMatrix = val; }

            Vector GetPlayerPosition() const { return playerPosition; }
            void SetPlayerPosition(const Vector& val) { playerPosition = val; }

            Vector GetMousePosition() const { return mousePosition; }
            void SetMousePosition(const Vector& val) { mousePosition = val; }

			int GetNextLevelName(char*& result);
			int SetNextLevelName(const char* val);

			LevelAIData* GetLevelAIData() { return levelAIData; }
			void SetLevelAIData(LevelAIData* val);

			AEOIAF_Utilities::Camera* GetDrawCamera() const { return drawCam; }
			void SetDrawCamera(AEOIAF_Utilities::Camera* val) { drawCam = val; }

            void AddCharacter(AEOIAF_Actor::Character* toAdd);
			void RemoveCharacter(const char* toRemove);
            AEOIAF_Actor::Character* GetCharacter(const char* toFind);

            void AddProp(AEOIAF_Actor::Prop* toAdd);
			void RemoveProp(const char* toRemove);

			void AddParticle(AEOIAF_Actor::ParticleEmitter* toAdd);
			void RemoveParticleEmitter(const char* toRemove);

			void AddScriptedEvent(AEOIAF_ScriptedEvents::ScriptSequence* toAdd);

            //Initialize the tiles, the draw component, and all of our actors and other
            //content. Types keeps track of tile types, and walls denote which are walls
            void Initialize(SDL_Renderer* renderer, unsigned int* types, bool* walls);

            void Update(SDL_Event* e, float deltaTime, ACOC_GameDataHandling::StreamDataHandler& streamData);

			//Will add data to the supplied hitActorList for the weapon to use
			void HitActor(AEOIAF_Actor::Weapon* checkWith, ActorCollisionList& hitActorList) const;
			void HitTile(AEOIAF_Actor::Weapon* checkWith, TileCollisionList& hitTileList) const;

            //Will determine if the tile at position is a wall
            bool IsWall(const AEOIAF_Utilities::Vector& position) const;

			//Given a tracer, finds the closest hit wall's position
			void GetClosestHitWallPos(const AEOIAF_Utilities::Tracer& tracer,
									  AEOIAF_Utilities::Vector& result) const;

            //A simple function that displays the name and id of the level
            void Display() const;
            //Call this to draw all components within the level
            void Draw(SDL_Renderer* renderer);

        private:
            //Creates the tile array and assigns each tile their type
            //and wall property
            void InitializeTiles(unsigned int* types, bool* walls);
			//Finds all tiles that are walls that a weapon hit
			void FindHitTiles(AEOIAF_Actor::Weapon* checkWith, TileCollisionList& result) const;

            //Identification
            char* id; //What you would use in accessing in global game variables
            char* name; //What would be displayed if you entered the level

            //Tile related properties
            unsigned int width, height; //The width and height in tilesS
            class Tile* tiles; //The tiles proper

            //Data types/containers
            unsigned int numSpawnPoints; //The number of spawn points in this level
            AEOIAF_Utilities::Vector* spawnPoints; //All possible positions for characters (ie players) to spawn at

            CharacterList characters;
            PropList props;
			ParticleList particles;
			ScriptedSequenceList scriptedEvents;

			//Use this to store the next level we want to go to
			char* nextLevelName;

            //Components
            LevelDrawComponent* drawComponent; //We use this to handle the drawing of tiles
            //The matrix we apply transformations with when drawing components
            AEOIAF_Utilities::Matrix* drawMatrix;

			//AI Data
			LevelAIData* levelAIData;

            //Extra stuff
            AEOIAF_Utilities::Vector playerPosition;
            AEOIAF_Utilities::Vector mousePosition; //Part of a janky solution to prop activation
			AEOIAF_Utilities::Camera* drawCam;
    };

    class Tile
    {
        public:
            Tile();
            Tile(unsigned int newType, bool bIsWall);
            Tile(const Tile& toCopy);
			~Tile();

            Tile& operator = (const Tile& toCopy);

            unsigned int GetType() const { return type; }
            void SetType(unsigned int val) { type = val; }

            bool IsWall() const { return bIsWall; }
            void SetIsWall(bool val) { bIsWall = val; }

            AEOIAF_Utilities::Vector& Position() { return position; }

            void Copy(const Tile& toCopy);
            //Use the levelDraw to render this tile
            void Draw(SDL_Renderer* renderer, LevelDrawComponent* levelDraw,
					  const AEOIAF_Utilities::Camera& drawCamera, Matrix* matrix = NULL);

        private:
            unsigned int type; //Which tile on the tileset to use
            bool bIsWall; //Basically, can we walk on this tile or not?
            AEOIAF_Utilities::Vector position; //Where the tile is drawn
    };
}

#endif // AEOIAF_LEVEL
