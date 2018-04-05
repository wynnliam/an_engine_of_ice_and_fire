//Liam "AFishyFez" Wynn, 2/3/2016, A Clash of Colors

#include "StreamData.h"
#include "../GameDataHandler.h"
#include "../../Level/Level.h"
#include "../../Utilities/Utility_Components/Vector.h"

using namespace ACOC_GameDataHandling;
using namespace AEOIAF_Utilities;

/*LEVEL STREAM DATA HANDLER*/
LevelStreamDataHandler::LevelStreamDataHandler()
{
}

LevelStreamDataHandler::~LevelStreamDataHandler()
{
}


int LevelStreamDataHandler::InsertActorToInsert(const char* toAdd, const Vector& pos)
{
	return actorsToInsert.Insert(toAdd, pos);
}

int LevelStreamDataHandler::RemoveActorToInsert(const char* toRemove)
{
	return actorsToInsert.Remove(toRemove);
}

void LevelStreamDataHandler::AddActorsToLevel(Level* level, const GameDataHandler& dataHandler)
{
	actorsToInsert.AddActorsToLevel(level, dataHandler);
}

int LevelStreamDataHandler::InsertActorToRemove(const char* toInsert)
{
	return actorsToRemove.Insert(toInsert);
}

int LevelStreamDataHandler::RemoveActorToRemove(const char* toRemove)
{
	return actorsToRemove.Remove(toRemove);
}

void LevelStreamDataHandler::RemoveActorsFromLevel(Level* level, const GameDataHandler& dataHandler)
{
	actorsToRemove.RemoveActorsFromLevel(level, dataHandler);
}

bool LevelStreamDataHandler::FindActorToRemove(const char* toFind) const
{
	return actorsToRemove.Find(toFind);
}

int LevelStreamDataHandler::ClearActorsToRemove()
{
	return actorsToRemove.Clear();
}
