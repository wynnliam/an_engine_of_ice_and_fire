//Liam "AFishyFez" Wynn, 1/22/2016, A Clash of Colors

#include "LevelHandler.h"
#include "GameDataHandler.h" //Include this so we can add actors to our level
#include "StreamData/StreamData.h" //So we can make modifications to our level

#include "../Level/Level.h"

//Include these so we can actually add things to a level
#include "../Actors/Character/Character.h"
#include "../Actors/Prop/Prop.h"
#include "../Actors/Item/Weapon/Weapon.h"
#include "../Actors/Item/Shield/Shield.h"
#include "../Actors/Particle/Particle.h"

//Use theses to define the positions of characters
//And defining traversal areas
#include "../Utilities/Utility_Components/AxisAllignedBoundingBox.h"
#include "../Utilities/Utility_Components/Vector.h"

//Use this to get digit count (for modding character ID)
#include "../Utilities/General_Purpose/HelpfulMethods.h"

//Use this to create actor IDs
#include <cstdio>
#include <cstring>

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

LevelHandler::LevelHandler()
{
}

LevelHandler::~LevelHandler()
{
}

//Eventually we'd like to load in levels from text files. However, for now all we will do
//is create the default level and return that
Level* LevelHandler::GetLevel(const char* toGet, const GameDataHandler& dataHandler,
							  StreamDataHandler& streamHandler, SDL_Renderer* renderer)
{
	if(!toGet || !renderer)
		return NULL;
	
	Level* result; //What we will return

	if(strcmp(toGet, "TEST") == 0)
		result = GetLevel(dataHandler, streamHandler, renderer, "Content/Levels/test_level.txt");
	else if(strcmp(toGet, "OTHER") == 0)
		result = GetLevel(dataHandler, streamHandler, renderer, "Content/Levels/other_level.txt");
	else if(strcmp(toGet, "WORLD_MAP") == 0)
		result = GetLevel(dataHandler, streamHandler, renderer, "Content/Levels/world_map.txt");
	else
		result = NULL;

	return result;
}

Level* LevelHandler::GetLevel(const GameDataHandler& dataHandler, StreamDataHandler& streamHandler,
							  SDL_Renderer* renderer, const char* filePath)
{
	if(!renderer || !filePath)
		return NULL;

	ifstream in(filePath); //Read in level information with this
	Level* result; //What we will return if all goes well

	//Level specific items
	char* id = NULL;
	char* name = NULL;

	if(!in.is_open())
		result = NULL;
	else
	{
		result = new Level;

		id = ReadInString(in);
		//Will now add stream data for this level. If it was already inserted,
		//it simply returns. So we are okay to do this
		streamHandler.InsertStreamData(id);

		name = ReadInString(in);

		result->SetID(id);
		result->SetName(name);
		
		LoadLevelTileProperties(result, in, renderer);
		LoadLevelCharacters(result, in, renderer, dataHandler);

		LoadLevelProps(result, in, renderer, dataHandler);
		LoadLevelParticles(result, in, renderer, dataHandler);

		//Traverse the Remove Actor List to remove actors that shouldn't
		//be there
		streamHandler.RemoveActorsFromLevel(result, dataHandler);
		//Now have the stream data handler insert any extra actors into
		//the level
		streamHandler.AddActorsToLevel(result, dataHandler);

		//Now that we've got everything loaded, we need to delete these
		if(id) { delete[] id; id = NULL; }
		if(name) { delete[] name; name = NULL; }		
	}

	in.close();

	return result;
}

//If level is NULL, or in is not open, then return false. Otherwise, use it to
//read in the level dimensions, the texture file path, and the tile and wall 
//types. After setting these values, return true
bool LevelHandler::LoadLevelTileProperties(Level* level, ifstream& in, SDL_Renderer* renderer)
{
	if(!level || !in.is_open() || !renderer)
		return false;

	unsigned int width, height; //Use these to store the dimensions of the world
	unsigned int* tiles = NULL; //Stores the texture map for the tiles themselves
	bool* walls = NULL; //Describes which tiles are walls and which are not
	
	width = ReadInUnsignedInt(in);
	height = ReadInUnsignedInt(in);

	LoadLevelDrawComponent(level, in, renderer);

	tiles = ReadInUnsignedIntArray(in, width * height);
	walls = ReadInBooleanArray(in, width * height);

	level->SetWidth(width);
	level->SetHeight(height);
	//level->SetTileTexturePath(texture);
	//level->SetNumTileTypes(numTileTypes);
	
	level->Initialize(renderer, tiles, walls);

	LoadLevelTraversalAreas(level, in);

	if(tiles) { delete[] tiles; tiles = NULL; }
	if(walls) { delete[] walls; walls = NULL; }

	return true;
}


void LevelHandler::LoadLevelDrawComponent(Level* level, ifstream& in, SDL_Renderer* renderer)
{
	unsigned int numTileTypes; //Stores the number of possible tiles in the texture path
	char* texture = NULL; //Stores the texture path itself

	texture = ReadInString(in);
	numTileTypes = ReadInUnsignedInt(in);

	if(drawComponentList.Contains(texture))
		level->SetDrawComponent(drawComponentList.GetComponent(texture));
	else
	{
		LevelDrawComponent* drawComponent = new LevelDrawComponent();
		drawComponent->SetTexturePath(texture);
		drawComponent->SetNumTileTypes(numTileTypes);
		drawComponent->Initialize(renderer);

		drawComponentList.Insert(drawComponent);
		level->SetDrawComponent(drawComponent);
	}

	if(texture) { delete[] texture; texture = NULL; }
}

void LevelHandler::LoadLevelTraversalAreas(Level* level, ifstream& in) const
{
	unsigned int numAreas;
	Vector nextAreaPos, nextAreaDim;
	LevelAIData* aiData = level->GetLevelAIData();


	numAreas = ReadInUnsignedInt(in);
	aiData->SetMapNumNodes(numAreas);

	for(unsigned int i = 0; i < numAreas; ++i)
	{
		ReadInVector(in, nextAreaPos);
		ReadInVector(in, nextAreaDim);

		aiData->SetMapVertexArea(i, CreateBoundingBox(nextAreaPos,
													  (int)nextAreaDim.GetX(),
													  (int)nextAreaDim.GetY()));
	}

	LoadLevelTraversalEdges(level, in);

	aiData->CalculateAllMapPaths();
}

void LevelHandler::LoadLevelTraversalEdges(Level* level, ifstream& in) const
{
	if(!level)
		return;

	unsigned int numEdges;
	Vector nextEdge; //Where the x and y are area indecies
	LevelAIData* aiData = level->GetLevelAIData();

	numEdges = ReadInUnsignedInt(in);
	for(unsigned int i = 0; i < numEdges; ++i)
	{
		ReadInVector(in, nextEdge);
		aiData->InsertMapEdge((int)nextEdge.GetX(), (int)nextEdge.GetY());
	}
}

//If the level or renderer are NULL, or in is not open, then return false. First read in
//the number of characters that will be in the level. Then for that amount of times read
//in a character and a position to spawn him. Then return true.
bool LevelHandler::LoadLevelCharacters(Level* level, ifstream& in, SDL_Renderer* renderer,
									   const GameDataHandler& dataHandler) const
{
	if(!level || !renderer || !in.is_open())
		return false;
	
	unsigned int numCharacters = ReadInUnsignedInt(in); //So we know how many characters we will add

	for(unsigned int i = 0; i < numCharacters; ++i)
		LoadACharacter(level, in, renderer, dataHandler, i);

	return true;
}

bool LevelHandler::LoadACharacter(Level* level, ifstream& in, SDL_Renderer* renderer,
								  const GameDataHandler& dataHandler, const int index) const
{
	if(!level || !renderer || !in.is_open())
		return false;
	
	Character* nextCharacter = NULL; //The next character to add
	char* nextCharacterType = NULL; //Use this to get the character from dataHandler
	char* nextCharacterID = NULL;
	Vector nextCharacterPos; //Where we will place the next character
	bool result; //What we will return

	nextCharacterType = ReadInString(in);
	nextCharacter = dataHandler.GetCharacter(nextCharacterType);
	nextCharacterID = MakeID(nextCharacterType, index);
	nextCharacter->SetID(nextCharacterID);
	ReadInVector(in, nextCharacterPos);

	if(nextCharacter)
	{
		nextCharacter->SetPosition(nextCharacterPos);
		level->AddCharacter(nextCharacter);

		result = true;
	}

	else
		result = false;

	if(nextCharacterType)
	{
		delete[] nextCharacterType;
		nextCharacterType = NULL;
	}

	if(nextCharacterID)
	{
		delete[] nextCharacterID;
		nextCharacterID = NULL;
	}

	return result;
}

bool LevelHandler::LoadLevelProps(Level* level, ifstream& in, SDL_Renderer* renderer,
								  const GameDataHandler& dataHandler) const
{
	if(!level || !renderer || !in.is_open())
		return false;
	
	unsigned int numProps = ReadInUnsignedInt(in); //So we know how many characters we will add

	for(unsigned int i = 0; i < numProps; ++i)
		LoadAProp(level, in, renderer, dataHandler, i);

	return true;
}

//Handles loading a single prop
bool LevelHandler::LoadAProp(Level* level, ifstream& in, SDL_Renderer* renderer,
							 const GameDataHandler& dataHandler, const int index) const
{
	if(!level || !renderer || !in.is_open())
		return false;
	
	Prop* nextProp = NULL; //The next prop to add
	char* nextPropType = NULL; //Use this to get the prop from dataHandler
	char* nextPropID = NULL;
	Vector nextPropPos; //Where we will place the next prop
	bool result; //What we will return

	nextPropType = ReadInString(in);
	nextPropID = MakeID(nextPropType, index);

	nextProp = dataHandler.GetProp(nextPropType);

	ReadInVector(in, nextPropPos);

	if(nextProp)
	{
		nextProp->SetID(nextPropID);
		nextProp->SetPosition(nextPropPos);
		level->AddProp(nextProp);

		result = true;
	}

	else
		result = false;

	if(nextPropType)
	{
		delete[] nextPropType;
		nextPropType = NULL;
	}

	if(nextPropID)
	{
		delete[] nextPropID;
		nextPropID = NULL;
	}

	return result;
}


bool LevelHandler::LoadLevelParticles(Level* level, ifstream& in, SDL_Renderer* renderer,
									  const GameDataHandler& dataHandler) const
{
	if(!level || !renderer || !in.is_open())
		return false;
	
	unsigned int numParticles = ReadInUnsignedInt(in); //So we know how many characters we will add

	for(unsigned int i = 0; i < numParticles; ++i)
		LoadAParticle(level, in, renderer, dataHandler);

	return true;
}

bool LevelHandler::LoadAParticle(Level* level, ifstream& in, SDL_Renderer* renderer, 
								 const GameDataHandler& dataHandler) const
{
	if(!level || !renderer || !in.is_open())
		return false;
	
	ParticleEmitter* nextParticleEmitter = NULL; //The next particle emitter to add
	char* nextParticleEmitterType = NULL; //Use this to get the particle emitter from dataHandler
	Vector nextParticleEmitterPos; //Where we will place the next particle emitter
	bool result; //What we will return

	nextParticleEmitterType = ReadInString(in);
	nextParticleEmitter = dataHandler.GetParticleEmitter(nextParticleEmitterType);
	ReadInVector(in, nextParticleEmitterPos);

	if(nextParticleEmitter)
	{
		nextParticleEmitter->SetPosition(nextParticleEmitterPos);
		level->AddParticle(nextParticleEmitter);

		result = true;
	}

	else
		result = false;

	if(nextParticleEmitterType)
	{
		delete[] nextParticleEmitterType;
		nextParticleEmitterType = NULL;
	}

	return result;
}

//If in is not open, return NULL. Create a char buffer.
//Read into this buffer until we hit a semi-colon.
//Copy the contents of the buffer into a new char array.
//Return the resulting array.
char* LevelHandler::ReadInString(ifstream& in) const
{
	if(!in.is_open())
		return NULL;

	char buffer[1000]; //Read the contents of in into this
	char* result; //What we will return

	in.get(buffer, 1000, ';');
	in.ignore(1000, ';');

	result = new char[strlen(buffer) + 1];
	strcpy(result, buffer);

	return result;
}

unsigned int LevelHandler::ReadInUnsignedInt(ifstream& in) const
{
	if(!in.is_open())
		return 0;

	unsigned int result; //What we will return

	in >> result;
	in.ignore(1000, ';');

	return result;
}

//If in is not opened, return NULL. Make an uint array 
//of size length. Loop through the array and read in
//the next uint. Use ignore to clear buffer upon completion. 
//Return result
unsigned int* LevelHandler::ReadInUnsignedIntArray(ifstream& in, const unsigned int length) const
{
	if(!in.is_open())
		return NULL;

	unsigned int* result = new unsigned int[length];
	
	for(unsigned int i = 0; i < length; ++i)
		in >> result[i];

	in.ignore(length, ';');

	return result;
}

bool* LevelHandler::ReadInBooleanArray(ifstream& in, const unsigned int length) const
{
	if(!in.is_open())
		return NULL;

	bool* result = new bool[length];
	
	for(unsigned int i = 0; i < length; ++i)
		in >> result[i];

	in.ignore(length, ';');

	return result;
}

void LevelHandler::ReadInVector(ifstream& in, Vector& vector) const
{
	if(!in.is_open())
		return;

	float nextVal; //Use this to get vector components

	in >> nextVal;
	vector.SetX(nextVal);

	in >> nextVal;
	vector.SetY(nextVal);

	in.ignore(1000, ';');
}

char* LevelHandler::MakeID(const char* type, const int index) const
{
	if(!type)
		return NULL;

	char* result; //What we will return
	char indexString[1000]; //We'll add this to id to make it unique

	sprintf(indexString, "%d", index);
	//Do + 2 for _ and \0
	result = new char[strlen(type) + strlen(indexString) + 2];
	strcpy(result, type);
	strcat(result, "_");
	strcat(result, indexString);

	return result;
}
