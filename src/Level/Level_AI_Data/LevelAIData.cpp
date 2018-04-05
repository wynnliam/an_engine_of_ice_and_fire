//Liam "AFishyFez" Wynn, 3/23/2016, A Clash of Colors

#include "LevelAIData.h"
#include "../../Actors/Character/Faction.h"
#include <iostream>

using namespace AEOIAF_Level;
using namespace AEOIAF_AIBehavior;
using namespace AEOIAF_Utilities;
using namespace std;

LevelAIData::LevelAIData()
{
	numFactions = 0;
	factions = NULL;
}

LevelAIData::~LevelAIData()
{
	if(factions)
	{
		delete[] factions;
		factions = NULL;
	}
}

void LevelAIData::SetNumFactions(const int val)
{
	if(val <= 0)
		return;

	numFactions = val;
	
	if(factions)
		delete[] factions;

	factions = new Faction*[numFactions];
	for(int i = 0; i < numFactions; ++i)
		factions[i] = NULL;
}

Faction* LevelAIData::GetFaction(const int index)
{
	return factions[index];
}

bool LevelAIData::GetFactionIndexById(const int id, int& result) const
{
	if(!factions)
		return false;

	bool toReturn = false;

	for(int i = 0; i < numFactions; ++i)
	{
		if(factions[i]->GetID() == id)
		{
			result = i;
			toReturn = true;
			break;
		}
	}

	return toReturn;
}

void LevelAIData::SetFaction(Faction* val, const int index)
{
	factions[index] = val;
}

void LevelAIData::Update()
{
}

int LevelAIData::GetMapNumNodes() const
{
	return mapGraph.GetNumNodes();
}

void LevelAIData::SetMapNumNodes(const int val)
{
	mapGraph.SetNumNodes(val);
}

bool LevelAIData::SetMapVertexArea(const int node, const AxisAllignedBoundingBox& area) const
{
	return mapGraph.SetVertexArea(node, area);
}

void LevelAIData::CalculateAllMapPaths()
{
	mapGraph.CalculateAllPaths();
}

bool LevelAIData::GetPath(const Vector& start, const Vector& end, Path& path)
{
	return mapGraph.GetPath(start, end, path);
}

int LevelAIData::FindAssociatedMapNode(const Vector& lookFor) const
{
	return mapGraph.FindAssociatedNode(lookFor);
}

bool LevelAIData::InsertMapEdge(const int nodeA, const int nodeB)
{
	return mapGraph.InsertEdge(nodeA, nodeB);
}

bool LevelAIData::RemoveMapEdge(const int nodeA, const int nodeB)
{
	return mapGraph.RemoveEdge(nodeA, nodeB);
}

bool LevelAIData::MapEdgeExists(const int nodeA, const int nodeB) const
{
	return mapGraph.EdgeExists(nodeA, nodeB);
}
