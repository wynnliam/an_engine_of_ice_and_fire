//Liam "AFishyFez" Wynn, 3/24/2016, An Engine of Ice and Fire

/*
 Here we store the neccessary classes for doing pathfinding.
 This essentially entails a node graph of traversable areas.
 These areas are represented by Axis Alligned Bounding Boxes.
 In addition, each area contains a Vector that represents the
 center of the AABB.

 A path will be a stack of these center position Vectors.
 However, for an entity to have traversed to a position fully,
 it needs to only be close enough to the center such that
 the entity collides with the associated AABB.

 When a path is discovered, we will store it in a table. That
 way, when the AI wants a path, we can check if the path was
 already discovered to make pathfinding easier.
*/

#ifndef AEOIAF_LEVEL_PATHFINDING
#define AEOIAF_LEVEL_PATHFINDING

#include "../../Utilities/Utility_Components/AxisAllignedBoundingBox.h"
#include "../../Utilities/Utility_Components/Vector.h"

namespace AEOIAF_Level
{
	class LevelPathfindingGraph
	{
		public:
			LevelPathfindingGraph();
			~LevelPathfindingGraph();

			int GetNumNodes() const { return numNodes; }
			void SetNumNodes(const int val);

			bool SetVertexArea(const int node, const AEOIAF_Utilities::AxisAllignedBoundingBox& area) const;

			//Precalculates every possible path for the level
			void CalculateAllPaths();

			//Builds a path bewtween start and end. Returns false if no path can be found
			bool GetPath(const AEOIAF_Utilities::Vector& start,
						 const AEOIAF_Utilities::Vector& end,
						 class Path& path);

			//Returns the id of the node whose traversal area contains
			//lookFor. Returns -1 if no node works
			int FindAssociatedNode(const AEOIAF_Utilities::Vector& lookFor) const;

			/*ADJACENCY FUNCTIONS*/
			bool InsertEdge(const int nodeA, const int nodeB);
			bool RemoveEdge(const int nodeA, const int nodeB);
			bool EdgeExists(const int nodeA, const int nodeB) const;

		private:
			/*PATHFINDING UTILITIES*/
			//Performs an A* search
			bool DoPathSearch(const int& s, const int& e, class Path& path) const;
			//Constructs the path from the end backwards
			void BuildPath(const int& endIndex, int* parent, class Path& path) const;
			//Calculates distance between two nodes
			float GetDist(const int& a, const int& b) const;

			bool IsNodeValid(const int toCheck) const;

			int numNodes;
			struct LevelPathNode* table;

			class PathLookUpTable* lookUp;
	};

	//For a given LevelPathNode, we use this
	//to contain the list of adjacent nodes
	class AdjacencyList
	{
		public:
			AdjacencyList();
			~AdjacencyList();

			//Insert ID into the list, if it isn't
			//there already
			bool Insert(const unsigned int& id);
			//Removes id from the list, if it exists
			bool Remove(const unsigned int& id);
			//Determines if toCheck is in the list
			bool Contains(const unsigned int& toCheck) const;
			//Clear the entire list
			void Clear();

			//A shitty janky function used in path finding
			struct AdjacencyNode* GetHead() { return head; }

		private:
			struct AdjacencyNode* head;
	};

	struct AdjacencyNode
	{
		AdjacencyNode();
		~AdjacencyNode();

		unsigned int nodeID;
		AdjacencyNode* next;
	};

	struct TraversalArea
	{
		TraversalArea();
		TraversalArea(const TraversalArea& toCopy);

		TraversalArea& operator = (const TraversalArea& toCopy);

		void Copy(const TraversalArea& toCopy);

		AEOIAF_Utilities::AxisAllignedBoundingBox bound;
		AEOIAF_Utilities::Vector center;
	};

	struct LevelPathNode
	{
		LevelPathNode();
		~LevelPathNode();

		unsigned int id;
		TraversalArea area;
		AdjacencyList adjacentNodes;
	};

	class Path
	{
		public:
			Path();
			~Path();

			void Copy(const Path& toCopy);

			//Pushes a traversal onto the top of the path
			bool Push(const TraversalArea& toPush);
			//Pops the top-most item off the path
			bool Pop();
			//Returns the traversal area of the top-most item
			bool Peek(TraversalArea& result) const;
			//Clears the entire path
			void Clear();

			bool IsEmpty() const { return !top; }
			void Display() const;

		private:
			void Copy(struct PathNode*& dest, const struct PathNode* src);

			struct PathNode* top;
	};

	struct PathNode
	{
		PathNode();
		~PathNode();

		TraversalArea area;
		PathNode* next;
	};

	class OpenList
	{
		public:
			OpenList(int newSize = 10);
			~OpenList();

			int Insert(const int nodeIndex, const int g, const int h);
			int GetHighestPriority(struct OpenNode& result);

			bool IsEmpty() const { return itemCount == 0 || !table; }

		private:
            int Rebuild(int rootIndex);

            struct OpenNode* table; //Where the data of the heap is stored
            int tableSize;
            int itemCount; //The next free index to place a node
	};

	struct OpenNode
	{
		OpenNode();
		~OpenNode();

		int nodeIndex;
		int f, g, h;
	};

	//Stores previously discovered paths
	class PathLookUpTable
	{
		public:
			PathLookUpTable(int newTableSize = 7);
			~PathLookUpTable();

			//Inserts a path into the table. Returns false if the
			//path already exists
			bool Insert(const int s, const int e, const Path& path);
			//Determines if a path exists with start s, and end e
			bool Contains(const int s, const int e) const;
			//Copies path in the table into result. Return false
			//if the table doesn't contain (s, e)
			bool GetPath(const int s, const int e, Path& result) const;
			//Clear the entire table
			void Clear();

		private:
			void Clear(struct LookUpNode*& toClear);

			int GetHashValue(const int s, const int e) const;

			int tableSize;
			struct LookUpNode** table;
	};

	struct LookUpNode
	{
		LookUpNode();
		~LookUpNode();

		int start, end;
		Path path;

		LookUpNode* next;
	};
}

#endif
