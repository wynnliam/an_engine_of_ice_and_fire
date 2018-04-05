//Liam "AFishyFez" Wynn, 4/19/2015, AEOIAF: Level

#include "Level.h"
#include "../Actors/Character/Character.h"
#include "../Actors/Item/Weapon/Weapon.h"
#include "../Scripted_Events/ScriptSequence.h"
#include "../Utilities/Utility_Components/Constants.h"
#include "../Utilities/General_Purpose/Tracer.h"
#include "WeaponCollisionDataTypes.h"
#include "../GameData/StreamData/StreamData.h"
#include <cstring>
#include <iostream>

using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_ScriptedEvents;
using namespace ACOC_GameDataHandling;
using namespace std;

Level::Level()
{
    id = NULL;
    name = NULL;

    width = 0;
    height = 0;
    tiles = NULL;

	nextLevelName = NULL;

    numSpawnPoints = 0;
    spawnPoints = NULL;

	drawComponent = NULL;
    drawMatrix = NULL;
	drawCam = NULL;

	levelAIData = NULL;
}

Level::Level(const char* newId)
{
    id = NULL;
    SetID(newId);

    name = NULL;

    width = 0;
    height = 0;
    tiles = NULL;

	nextLevelName = NULL;

    numSpawnPoints = 0;
    spawnPoints = NULL;

	drawComponent = NULL;
    drawMatrix = NULL;
	drawCam = NULL;	

	levelAIData = NULL;
}

Level::Level(const char* newId, const char* newName)
{
    id = NULL;
    name = NULL;
    SetID(newId);
    SetName(newName);

    width = 0;
    height = 0;
    tiles = NULL;

	nextLevelName = NULL;

    numSpawnPoints = 0;
    spawnPoints = NULL;

	drawComponent = NULL;
    drawMatrix = NULL;
	drawCam = NULL;	

	levelAIData = NULL;
}

Level::~Level()
{
    if(id)
        delete[] id;

    if(name)
        delete[] name;

    if(tiles)
        delete[] tiles;

    if(spawnPoints)
        delete[] spawnPoints;

	if(nextLevelName)
		delete[] nextLevelName;

    id = NULL;
    name = NULL;
    tiles = NULL;
	nextLevelName = NULL;
    spawnPoints = NULL;
    drawMatrix = NULL;
	drawComponent = NULL;
	drawCam = NULL;
	SetLevelAIData(NULL);
}

int Level::GetID(char*& copyTo) const
{
    int result; //What we will return

    if(!id)
        result = 0;

    else
    {
        copyTo = new char[strlen(id) + 1];
        strcpy(copyTo, id);

        result = 1;
    }

    return result;
}

int Level::SetID(const char* newId)
{
    if(id == newId)
        return 0;

    if(id)
        delete[] id; //Free memory if we are overriding

    int result; //What we will return

    if(!newId)
    {
        id = NULL;
        result = 0;
    }

    else
    {
        id = new char[strlen(newId) + 1];
        strcpy(id, newId);

        result = 1;
    }

    return result;
}

int Level::GetName(char*& copyTo) const
{
    int result; //What we are returning

    if(!name)
    {
        copyTo = NULL;

        result = 0;
    }

    else
    {
        copyTo = new char[strlen(name) + 1];
        strcpy(copyTo, name);

        result = 1;
    }

    return result;
}

int Level::SetName(const char* newName)
{
    if(name == newName)
        return 0;

    if(name)
        delete[] name; //Free memory if we are overriding

    int result; //What we are returning

    if(!newName)
    {
        name = NULL;

        result = 0;
    }

    else
    {
        name = new char[strlen(newName) + 1];
        strcpy(name, newName);

        result = 1;
    }

    return result;
}

void Level::SetNumTileTypes(unsigned int numTileTypes)
{
	if(!drawComponent)
		drawComponent = new LevelDrawComponent();

    drawComponent->SetNumTileTypes(numTileTypes);
}

int Level::SetTileTexturePath(const char* texturePath)
{
	if(!texturePath)
		return 0;

	if(!drawComponent)
		drawComponent = new LevelDrawComponent();

    return drawComponent->SetTexturePath(texturePath);
}

int Level::GetNextLevelName(char*& result)
{
	if(!nextLevelName)
	{
		result = NULL;
		return 0;
	}

	else
	{
		result = new char[strlen(nextLevelName) + 1];
		strcpy(result, nextLevelName);

		return 1;
	}
}

int Level::SetNextLevelName(const char* val)
{
	if(nextLevelName)
		delete[] nextLevelName;

	if(!val)
		nextLevelName = NULL;
	else
	{
		nextLevelName = new char[strlen(val) + 1];
		strcpy(nextLevelName, val);
	}

	return 1;
}

int Level::GetSpawnPoint(Vector& result, unsigned int index) const
{
    if(index >= numSpawnPoints || !spawnPoints)
        return 0; //Bad index or NULL spawn points!

    result = spawnPoints[index];

    return 1;
}

int Level::SetSpawnPoint(const Vector& toAdd, unsigned int index)
{
    if(index >= numSpawnPoints || !spawnPoints)
        return 0; //Bad index or NULL spawn points!

    spawnPoints[index] = toAdd;

    return 1;
}

void Level::SetLevelAIData(LevelAIData* val)
{
	if(levelAIData)
		delete levelAIData;

	levelAIData = val;
}

Matrix* Level::GetDrawMatrix()
{
	return drawMatrix;
}

void Level::AddCharacter(Character* toAdd)
{
    characters.Add(toAdd);
}

void Level::RemoveCharacter(const char* toRemove)
{
	characters.Remove(toRemove);
}

Character* Level::GetCharacter(const char* toFind)
{
    return characters.Find(toFind);
}

void Level::AddProp(Prop* toAdd)
{
    props.Add(toAdd);
}

void Level::RemoveProp(const char* toRemove)
{
	props.Remove(toRemove);
}

void Level::AddParticle(ParticleEmitter* toAdd)
{
	particles.Insert(toAdd);
}

void Level::RemoveParticleEmitter(const char* toRemove)
{
	particles.Remove(toRemove);
}

void Level::AddScriptedEvent(ScriptSequence* toAdd)
{
	scriptedEvents.Insert(toAdd);
}

//Initialize the tiles, the draw component, and all of our actors and other
//content
void Level::Initialize(SDL_Renderer* renderer, unsigned int* types, bool* walls)
{
	if(!drawComponent)
		return;

    InitializeTiles(types, walls);
	//Note that this is initialized in LevelHandler for some reason...
	drawComponent->Initialize(renderer);

	if(!levelAIData)
		levelAIData = new LevelAIData;

	if(numSpawnPoints > 0)
		spawnPoints = new Vector[numSpawnPoints];
	else
		spawnPoints = NULL;
}

bool Level::IsWall(const Vector& position) const
{
    if(!tiles || position.GetX() < 0 || position.GetY() < 0)
        return false;

    unsigned int index = (unsigned int)position.GetY() * width + (unsigned int)position.GetX();

    if(index >= 0 && index < width * height)
        return tiles[index].IsWall();
    else
        return false; //Out of range!
}

void Level::InitializeTiles(unsigned int* types, bool* walls)
{
    tiles = new Tile[width * height];

    unsigned int nextIndex; //Use this to access the arrays
    for(unsigned int x = 0; x < width; ++x)
    {
        for(unsigned int y = 0; y < height; ++y)
        {
            nextIndex = y * width + x;
            tiles[nextIndex].Position().SetX(x * AEOIAF_TILE_SIZE);
            tiles[nextIndex].Position().SetY(y * AEOIAF_TILE_SIZE);
            tiles[nextIndex].SetType(types[nextIndex]);
            tiles[nextIndex].SetIsWall(walls[nextIndex]);
        }
    }
}

void Level::Display() const
{
    if(id)
        cout << "Level ID: " << id << endl;
    if(name)
        cout << "Level Name: " << name << endl;
}

void Level::Update(SDL_Event* e, float deltaTime, StreamDataHandler& streamData)
{
	scriptedEvents.Update(this, deltaTime);
    characters.Update(this, e, deltaTime);
    props.Update(this, e, deltaTime, streamData);
	particles.Update(this, e, deltaTime);

	if(levelAIData)
		levelAIData->Update();
}

//If checkWith is NULL, simply return. Find all hit actors and tiles and add them to hitActorList
//and hitTileList respectively
void Level::HitActor(Weapon* checkWith, ActorCollisionList& hitActorList) const
{
	if(!checkWith)
		return;

	//Adding to the hitActorList
	characters.FindHitCharacters(checkWith, hitActorList);
	props.FindHitProps(checkWith, hitActorList);
}

void Level::HitTile(Weapon* checkWith, TileCollisionList& hitTileList) const
{
	if(!checkWith)
		return;

	//Adding to the hitTileList
	FindHitTiles(checkWith, hitTileList);	
}

void Level::GetClosestHitWallPos(const Tracer& tracer, Vector& result) const
{
	if(!tiles)
		return;

	unsigned int numTiles = width * height;
	float currentDist = 0.0;
	float maxDist = -1.0f;
	AxisAllignedBoundingBox nextAABB;

	//If we don't hit a wall, this will tell us so
	result.SetX(-1);
	result.SetY(-1);

	for(unsigned int i = 0; i < numTiles; ++i)
	{
		if(tiles[i].IsWall())
		{
			nextAABB = CreateBoundingBox(tiles[i].Position(), AEOIAF_TILE_SIZE, AEOIAF_TILE_SIZE);
			if(tracer.Intersects(nextAABB))
			{
				currentDist = (tracer.GetStart() - tiles[i].Position()).GetMagnitude();
				if(currentDist < maxDist || maxDist == -1.0f)
				{
					result = tiles[i].Position();
					maxDist = currentDist;
				}
			}
		}
	}
}

void Level::FindHitTiles(Weapon* checkWith, TileCollisionList& result) const
{
	if(!tiles || !checkWith)
		return;

	unsigned int numTiles = width * height;
	for(unsigned int i = 0; i < numTiles; ++i)
	{
		if(tiles[i].IsWall() && checkWith->DidHit(&tiles[i]))
			result.Add(&tiles[i], checkWith);
	}
}

void Level::Draw(SDL_Renderer* renderer)
{
    if(tiles && drawCam)
    {
        unsigned int numTiles = width * height;
        for(unsigned int i = 0; i < numTiles; ++i)
            tiles[i].Draw(renderer, drawComponent, *drawCam, drawMatrix);

		props.Draw(renderer, SDL_FLIP_NONE, false, false, true, drawMatrix, drawCam);
		characters.Draw(renderer, SDL_FLIP_NONE, false, false, true, drawMatrix, drawCam);
		particles.Draw(renderer, SDL_FLIP_NONE, false, false, true, drawMatrix);
    }
}
