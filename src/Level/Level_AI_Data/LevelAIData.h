//Liam "AFishyFez" Wynn, 3/23/2016, A Clash of Colors

/*
 For the AI to make any decisions, it needs information about
 a level. The job of the LevelAIData class is to store such
 information for AI to use.

 While different games require different AI needs, there are
 still somethings you can find in this class. Namely, it holds
 pathfinding information.
*/

#ifndef AEOIAF_LEVEL_AI_DATA
#define AEOIAF_LEVEL_AI_DATA

#include "LevelPathfinding.h"

namespace AEOIAF_AIBehavior
{
	class Faction;
}

namespace AEOIAF_Level
{
	class LevelAIData
	{
		public:
			LevelAIData();
			virtual ~LevelAIData();

			int GetNumFactions() const { return numFactions; }
			void SetNumFactions(const int val);

			AEOIAF_AIBehavior::Faction* GetFaction(const int index);
			bool GetFactionIndexById(const int id, int& result) const;
			void SetFaction(AEOIAF_AIBehavior::Faction* val, const int index);

			//Called by the level, this allows properties to be updated like
			//finding a new captain or something
			virtual void Update();

			/*LEVEL PATHFINDING GRAPH WRAPPERS*/
			int GetMapNumNodes() const;
			void SetMapNumNodes(const int val);
			bool SetMapVertexArea(const int node, const AEOIAF_Utilities::AxisAllignedBoundingBox& area) const;
			void CalculateAllMapPaths();
			bool GetPath(const AEOIAF_Utilities::Vector& start,
						 const AEOIAF_Utilities::Vector& end,
						 Path& path);
			int FindAssociatedMapNode(const AEOIAF_Utilities::Vector& lookFor) const;
			bool InsertMapEdge(const int nodeA, const int nodeB);
			bool RemoveMapEdge(const int nodeA, const int nodeB);
			bool MapEdgeExists(const int nodeA, const int nodeB) const;

		private:
			int numFactions;
			AEOIAF_AIBehavior::Faction** factions;

			LevelPathfindingGraph mapGraph;
	};
}

#endif
