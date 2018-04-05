//Liam "AFishyFez" Wynn, 3/24/2016, An Engine of Ice and Fire

#include "LevelPathfinding.h"
#include <iostream>

using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

/*LEVEL PATHFINDING GRAPH IMPLEMENTATIONS*/
LevelPathfindingGraph::LevelPathfindingGraph()
{
	numNodes = 0;
	table = NULL;

	lookUp = new PathLookUpTable;
}

LevelPathfindingGraph::~LevelPathfindingGraph()
{
	if(table)
	{
		delete[] table;
		table = NULL;
	}

	if(lookUp)
	{
		delete lookUp;
		lookUp = NULL;
	}
}

void LevelPathfindingGraph::SetNumNodes(const int val)
{
	if(val <= 0)
		return;

	numNodes = val;

	if(table)
		delete[] table;

	table = new LevelPathNode[numNodes];
	for(int i = 0; i < numNodes; ++i)
		table[i].id = (unsigned int)i;
}

bool LevelPathfindingGraph::SetVertexArea(const int node, const AxisAllignedBoundingBox& area) const
{
	if(!table || !IsNodeValid(node))
		return false;

	Vector center((area.xMin + area.xMax) / 2, (area.yMin + area.yMax) / 2);

	table[node].area.bound = area;
	table[node].area.center = center;

	return true;
}

bool LevelPathfindingGraph::InsertEdge(const int nodeA, const int nodeB)
{
	if(!table || (nodeA == nodeB) || !IsNodeValid(nodeA) || !IsNodeValid(nodeB))
		return false;

	bool resultA, resultB;

	resultA = table[nodeA].adjacentNodes.Insert(nodeB);
	resultB = table[nodeB].adjacentNodes.Insert(nodeA);

	return resultA && resultB;
}

bool LevelPathfindingGraph::RemoveEdge(const int nodeA, const int nodeB)
{
	if(!table || (nodeA == nodeB) || !IsNodeValid(nodeA) || !IsNodeValid(nodeB))
		return false;

	bool resultA, resultB;

	resultA = table[nodeA].adjacentNodes.Remove(nodeB);
	resultB = table[nodeB].adjacentNodes.Remove(nodeA);

	return resultA && resultB;
}

bool LevelPathfindingGraph::EdgeExists(const int nodeA, const int nodeB) const
{
	if(!table || (nodeA == nodeB) || !IsNodeValid(nodeA) || !IsNodeValid(nodeB))
		return false;

	//When you add an edge, it does A -> B, and B -> A. Thus, if one edge exists,
	//then the other must as well.
	return table[nodeA].adjacentNodes.Contains(nodeB);
}

bool LevelPathfindingGraph::IsNodeValid(const int toCheck) const
{
	return toCheck >= 0 && toCheck < numNodes;
}

void LevelPathfindingGraph::CalculateAllPaths()
{
	if(!table || numNodes <= 0)
		return;

	Path dummy;

	for(int i = 0; i < numNodes; ++i)
	{
		for(int j = 0; j < numNodes; ++j)
		{
			if(i != j)
				GetPath(table[i].area.center, table[j].area.center, dummy);
			
			dummy.Clear();
		}
	}
}

bool LevelPathfindingGraph::GetPath(const Vector& start, const Vector& end, Path& path)
{
	if(!table)
		return false;

	int nodeStart, nodeEnd;

	nodeStart = FindAssociatedNode(start);
	nodeEnd = FindAssociatedNode(end);

	//A path cannot be made between these points!
	if(nodeStart == -1 || nodeEnd == -1)
		return false;

	path.Clear();

	if(lookUp->Contains(nodeStart, nodeEnd))
	{
		lookUp->GetPath(nodeStart, nodeEnd, path);
		return true;
	}

	else
		return DoPathSearch(nodeStart, nodeEnd, path);
}

bool LevelPathfindingGraph::DoPathSearch(const int& s, const int& e, Path& path) const
{
    bool open[numNodes]; //True is we checked
    bool closed[numNodes]; //True is we can no longer visit
    int parent[numNodes]; //denotes the parent of the node at a given index
	OpenList toCheck(numNodes); //Contains every node we still need to look at
	OpenNode current; //The current node we're examining
	AdjacencyNode* temp = NULL; //Use this to check all of current's adjacent nodes
	int tempG, tempH;
	bool result = false; //What we will return

    for(int i = 0; i < numNodes; ++i)
    {
        open[i] = false;
        closed[i] = false;
        parent[i] = -1;
    }

	toCheck.Insert(s, 0, 0);

	while(!toCheck.IsEmpty())
	{
		toCheck.GetHighestPriority(current);
		open[current.nodeIndex] = false;
		temp = table[current.nodeIndex].adjacentNodes.GetHead();

		while(temp && !result)
		{
			if(!closed[temp->nodeID])
			{
				parent[temp->nodeID] = current.nodeIndex;

				if((int)temp->nodeID == e)
				{
					BuildPath(e, parent, path);
					lookUp->Insert(s, e, path);
					result = true;
					break;
				}

				if(!open[temp->nodeID])
				{
					tempG = current.g + GetDist(temp->nodeID, e);
					tempH = current.h + 1;

					toCheck.Insert(temp->nodeID, tempG, tempH);
					open[temp->nodeID] = true;
				}
			}

			temp = temp->next;
		}

		closed[current.nodeIndex] = true;
	}

	return result;
}


void LevelPathfindingGraph::BuildPath(const int& endIndex, int* parent, Path& path) const
{
	int currIndex = endIndex;
	int currParent;

	while(currIndex != -1)
	{
		currParent = parent[currIndex];
		path.Push(table[currIndex].area);
		currIndex = currParent;
	}
}

float LevelPathfindingGraph::GetDist(const int& a, const int& b) const
{
	Vector vectA = table[a].area.center;
	Vector vectB = table[b].area.center;

	return (vectA - vectB).GetMagnitude();
}

int LevelPathfindingGraph::FindAssociatedNode(const Vector& lookFor) const
{
	if(!table)
		return -1;

	int result = -1;

	for(int i = 0; i < numNodes; ++i)
	{
		if(table[i].area.bound.Contains(lookFor))
		{
			result = i;
			break;
		}
	}

	return result;
}

/*PATH LOOKUP TABLE IMPLEMENTATIONS*/
PathLookUpTable::PathLookUpTable(int newTableSize)
{
	tableSize = newTableSize;

	table = new LookUpNode*[tableSize];
	for(int i = 0; i < tableSize; ++i)
		table[i] = NULL;
}

PathLookUpTable::~PathLookUpTable()
{
	Clear();
}

bool PathLookUpTable::Insert(const int s, const int e, const Path& path)
{
	if(Contains(s, e) || !table || tableSize <= 0)
		return false;

	int index = GetHashValue(s, e);
	LookUpNode* toAdd = new LookUpNode;

	toAdd->start = s;
	toAdd->end = e;
	toAdd->path.Copy(path);
	toAdd->next = table[index];
	table[index] = toAdd;

	return true;
}

bool PathLookUpTable::Contains(const int s, const int e) const
{
	int index = GetHashValue(s, e);
	LookUpNode* temp = table[index];
	bool result = false;

	while(temp)
	{
		if(temp->start == s && temp->end == e)
		{
			result = true;
			break;
		}

		else
			temp = temp->next;
	}

	return result;
}

bool PathLookUpTable::GetPath(const int s, const int e, Path& result) const
{
	if(!Contains(s, e) || !table || tableSize <= 0)
		return false;

	int index = GetHashValue(s, e);
	LookUpNode* temp = table[index];
	bool bResult = false;

	while(temp)
	{
		if(temp->start == s && temp->end == e)
		{
			result.Copy(temp->path);
			bResult = true;
			break;
		}

		else
			temp = temp->next;
	}

	return bResult;
}

void PathLookUpTable::Clear()
{
	for(int i = 0; i < tableSize; ++i)
		Clear(table[i]);

	if(table)
	{
		delete[] table;
		table = NULL;
	}
}

void PathLookUpTable::Clear(struct LookUpNode*& toClear)
{
	LookUpNode* temp = toClear;

	while(toClear)
	{
		toClear = toClear->next;
		delete temp;
		temp = toClear;
	}

	toClear = NULL;
}

int PathLookUpTable::GetHashValue(const int s, const int e) const
{
	int a, b;
	int result;

	a = s + e;
	b = s + e + 1;

	result = ((a * b) + e) / 2;
	result %= tableSize;

	return result;
}

/*LOOK UP NODE IMPLEMENTATIONS*/

LookUpNode::LookUpNode()
{
	start = -1;
	end = -1;
}

LookUpNode::~LookUpNode()
{
	next = NULL;
}

/*LEVEL PATH NODE IMPLEMENTATIONS*/
LevelPathNode::LevelPathNode()
{
	id = 0;
}

LevelPathNode::~LevelPathNode()
{
}

/*TRAVERSAL AREA IMPLEMENTATIONS*/
TraversalArea::TraversalArea()
{
}

TraversalArea::TraversalArea(const TraversalArea& toCopy)
{
	Copy(toCopy);
}

TraversalArea& TraversalArea::operator = (const TraversalArea& toCopy)
{
	Copy(toCopy);
	return *this;
}

void TraversalArea::Copy(const TraversalArea& toCopy)
{
	bound = toCopy.bound;
	center = toCopy.center;
}

/*ADJACENCY LIST IMPLEMENTATIONS*/
AdjacencyList::AdjacencyList()
{
	head = NULL;
}

AdjacencyList::~AdjacencyList()
{
	Clear();
}

bool AdjacencyList::Insert(const unsigned int& id)
{
	if(Contains(id))
		return false;

	AdjacencyNode* temp = new AdjacencyNode;
	temp->nodeID = id;
	temp->next = head;
	head = temp;

	return true;
}

bool AdjacencyList::Remove(const unsigned int& id)
{
	AdjacencyNode* prev = NULL;
	AdjacencyNode* curr = head;
	bool result = false;

	while(curr)
	{
		if(curr->nodeID == id)
		{
			if(curr == head)
				head = head->next;
			else
				prev->next = curr->next;

			delete curr;
			curr = NULL;

			result = true;
			break;
		}

		else
		{
			prev = curr;
			curr = curr->next;
		}
	}

	curr = NULL;
	prev = NULL;

	return result;
}

bool AdjacencyList::Contains(const unsigned int& toCheck) const
{
	bool result = false; //What we will return

	AdjacencyNode* temp = head;
	while(temp)
	{
		if(temp->nodeID == toCheck)
		{
			result = true;
			break;
		}

		else
			temp = temp->next;
	}

	return result;
}

void AdjacencyList::Clear()
{
	AdjacencyNode* temp = head;
	
	while(head)
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}

/*ADJACENCY NODE IMPLEMENTATIONS*/
AdjacencyNode::AdjacencyNode()
{
	nodeID = 0;
	next = NULL;
}

AdjacencyNode::~AdjacencyNode()
{
	next = NULL;
}

/*PATH IMPLEMENTATIONS*/
Path::Path()
{
	top = NULL;
}

Path::~Path()
{
	Clear();
}

void Path::Copy(const Path& toCopy)
{
	Copy(top, toCopy.top);
}

void Path::Copy(PathNode*& dest, const PathNode* src)
{
	if(!src)
	{
		dest = NULL;
		return;
	}

	dest = new PathNode;
	dest->area = src->area;

	Copy(dest->next, src->next);
}

bool Path::Push(const TraversalArea& toPush)
{
	PathNode* temp = new PathNode;
	temp->area = toPush;
	temp->next = top;
	top = temp;

	return true;
}

bool Path::Pop()
{
	if(!top)
		return false;

	PathNode* temp = top;
	top = top->next;

	delete temp;
	temp = NULL;

	return true;
}

bool Path::Peek(TraversalArea& result) const
{
	if(!top)
		return false;

	result = top->area;

	return true;
}

void Path::Clear()
{
	while(!IsEmpty())
		Pop();
}

void Path::Display() const
{
	PathNode* temp = top;

	while(temp)
	{
		cout << "(";
		cout << temp->area.bound.xMin << " " << temp->area.bound.yMin;
		cout << ")" << endl;

		temp = temp->next;
	}
}

/*PATH NODE IMPLEMENTATIONS*/
PathNode::PathNode()
{
	next = NULL;
}

PathNode::~PathNode()
{
	next = NULL;
}

/*OPEN LIST IMPLEMENTATIONS*/
OpenList::OpenList(int newSize)
{
	tableSize = newSize;
	table = new OpenNode[tableSize];
	itemCount = 0;
}

OpenList::~OpenList()
{
	if(table)
	{
		delete[] table;
		table = NULL;
	}
}

int OpenList::Insert(const int nodeIndex, const int g, const int h)
{
	if(!table || itemCount >= tableSize)
		return 0;

    table[itemCount].nodeIndex = nodeIndex;
    table[itemCount].f = g + h;
    table[itemCount].g = g;
    table[itemCount].h = h;

    int newDataIndex = itemCount; //Use this to keep track of where toAdd is
    int parentIndex; //The parent index of toAdd
    bool bInPlace = false;

	while(newDataIndex >= 0 && !bInPlace)
	{
		parentIndex = (newDataIndex - 1) / 2;

		//A smaller f means a lower cost. Therefore, it's a higher
		//priority.
		if(table[newDataIndex].f >= table[parentIndex].f)
			bInPlace = true;
		else
		{
			OpenNode temp = table[parentIndex];
			table[parentIndex] = table[newDataIndex];
			table[newDataIndex] = temp;

			newDataIndex = parentIndex;
		}
	}

	++itemCount;
	return 1;
}

int OpenList::GetHighestPriority(OpenNode& result)
{
	if(!table || itemCount == 0)
		return 0;

	result = table[0];
	table[0] = table[itemCount - 1];
	--itemCount;

	return Rebuild(0);
}

int OpenList::Rebuild(int rootIndex)
{
    int leftIndex = 2 * rootIndex + 1; //Use can use this to determine if root is a leaf
                                       //because the heap is a complete tree always
	if(leftIndex < itemCount)
	{
		int smallerIndex = leftIndex;
		int rightIndex = leftIndex + 1;

		if(rightIndex < itemCount && table[rightIndex].f < table[leftIndex].f)
			smallerIndex = rightIndex;

        if(table[smallerIndex].f < table[rootIndex].f)
        {
            //Swap the nodes
            OpenNode temp = table[rootIndex];
            table[rootIndex] = table[smallerIndex];
            table[smallerIndex] = temp;

            return  1 + Rebuild(smallerIndex); //Number of times a rebuild had to happen
        }
	}

	return 0;
}

/*OPEN NODE IMPLEMENTATIONS*/
OpenNode::OpenNode()
{
	nodeIndex = 0;
	f = 0;
	g = 0;
	h = 0;
}

OpenNode::~OpenNode()
{
}
