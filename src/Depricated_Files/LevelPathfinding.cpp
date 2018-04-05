//Liam "AFishyFez" Wynn, 2/25/2015, AEOIAF: Level Path finding

/*
Here I implement the walkable areas of a level (for AI)
as a node graph. The graph itself is implemented as a
matrix of length (width * height) ^ 2.
*/

#include "LevelPathfinding.h"

using namespace AEOIAF_Pathfinding;
using namespace AEOIAF_Utilities;
using namespace std;

/*LEVEL NODE GRAPH IMPLEMENTATIONS*/
LevelNodeGraph::LevelNodeGraph()
{
    width = 0;
    height = 0;
    length = 0;
    table = NULL;
}

LevelNodeGraph::~LevelNodeGraph()
{
    if(table)
    {
        EdgeNode* temp;
        for(int i = 0; i < length; ++i)
        {
            temp = table[i].head;
            while(table[i].head)
            {
                table[i].head = table[i].head->next;
                delete temp;
                temp = table[i].head;
            }
        }

        delete[] table;
    }
}

//Begins by creating our table, filling each vertex with position data,
//and then adding adjacent vertices
bool LevelNodeGraph::Initialize(int newWidth, int newHeight, bool* walls)
{
    if(!walls)
        return false; //We can't do the rest of this function safely

    width = newWidth;
    height = newHeight;
    length = width * height;
    table = new Vertex[length];

    int nextIndex; //Use this to access the current vertex we are working on
    int l, r, u, d; //Use these to access the adjacent vertices

    for(int x = 0; x < width; ++x)
    {
        for(int y = 0; y < height; ++y)
        {
            nextIndex = y * width + x;
            table[nextIndex].position.SetX(x);
            table[nextIndex].position.SetY(y);

            if(!walls[nextIndex])
            {
                l = y * width + (x - 1);
                r = y * width + (x + 1);
                u = (y - 1) * width + x;
                d = (y + 1) * width + x;

                if(l >= 0 && l < length && !walls[l]) AddEdge(nextIndex, l);
                if(r >= 0 && r < length && !walls[r]) AddEdge(nextIndex, r);
                if(u >= 0 && u < length && !walls[u]) AddEdge(nextIndex, u);
                if(d >= 0 && d < length && !walls[d]) AddEdge(nextIndex, d);
            }
        }
    }

    return true;
}

bool LevelNodeGraph::AddEdge(int vertexIndex, int adjacentIndex)
{
    if(!table)
        return false;

    EdgeNode* toAdd = new EdgeNode; //The directed edge from vertex to table[adjacentIndex]
    toAdd->vertexIndex = adjacentIndex;
    toAdd->next = table[vertexIndex].head;
    table[vertexIndex].head = toAdd;

    return false;
}

bool LevelNodeGraph::Display() const
{
    if(!table)
        return false;

    EdgeNode* current;
    for(int i = 0; i < length; ++i)
    {
        cout << "Vertex #" << i << " (" << table[i].position.GetX() << ", "
             << table[i].position.GetY() << ")";
        cout << " Adjacent to: ";

        current = table[i].head;
        while(current)
        {
            cout << "(" << table[current->vertexIndex].position.GetX() << ", "
                 << table[current->vertexIndex].position.GetY() << ") ";

            current = current->next;
        }

        cout << endl;
    }

    return true;
}

bool LevelNodeGraph::GetPath(Path& result, const Vector& s, const Vector& e) const
{
    bool* open = new bool[length]; //True is we checked
    bool* closed = new bool[length]; //True is we can no longer visit
    int* parent = new int[length]; //denotes the parent of the node at a given index
    for(int i = 0; i < length; ++i)
    {
        open[i] = false;
        closed[i] = false;
        parent[i] = -1;
    }

    int sIndex = (int)s.GetY() * width + (int)s.GetX();
    int eIndex = (int)e.GetY() * width + (int)e.GetX();

    if(sIndex < 0 || sIndex >= length)
        return false; //Out of bounds!

    OpenList toCheck(width * height); //Worst case scenario: every vertex is checked
    toCheck.AddItem(sIndex, 0, 0);

    OpenListNode current;

    while(!toCheck.IsEmpty())
    {
        toCheck.Remove(current);
        open[current.vertexIndex] = false;

        //Use this to traverse all adjacent vertecies
        EdgeNode* temp = table[current.vertexIndex].head;
        while(temp)
        {
            if(!closed[temp->vertexIndex])
            {
                parent[temp->vertexIndex] = current.vertexIndex;

                if(temp->vertexIndex == eIndex)
                {
                    BuildPath(result, eIndex, parent);
                    return true;
                }

                if(!open[temp->vertexIndex])
                {
                    int g, h;
                    g = current.g + ManhattanDist(table[temp->vertexIndex].position,
                                                   table[eIndex].position);
                    h = 1 + current.h;

                    toCheck.AddItem(temp->vertexIndex, g, h);
                    open[temp->vertexIndex] = true;
                }
            }

            temp = temp->next;
        }

        closed[current.vertexIndex] = true;
    }

    return false;
}

int LevelNodeGraph::BuildPath(Path& result, int endIndex, int* parent) const
{
    if(!parent || endIndex >= width * height)
        return 0;

    Vector toAdd;
    int currentIndex = endIndex; //The current index of a vertex
    int currentParent; //The parent of currentIndex

    while(currentIndex != -1)
    {
        currentParent = parent[currentIndex];

        toAdd = table[currentIndex].position;
        result.Push(toAdd);

        currentIndex = currentParent;
    }

    return 1;
}

int LevelNodeGraph::ManhattanDist(const Vector& a, const Vector& b) const
{
    int xDiff = abs((int)(a.GetX() - b.GetX()));
    int yDiff = abs((int)(a.GetY() - b.GetY()));

    return xDiff + yDiff;
}

/*OPEN LIST IMPLEMENTATIONS*/
OpenList::OpenList(int newSize)
{
    tableSize = newSize;
    table = new OpenListNode[tableSize];
    itemCount = 0;
}

OpenList::~OpenList()
{
    if(!table)
        return;

    delete[] table;
}

bool OpenList::IsEmpty() const
{
    //If the item count is 0, then of course there is nothing in the heap
    return itemCount == 0;
}

//First check if the table is not NULL but is not full
//Then perform the item adding operation
int OpenList::AddItem(int index, int g, int h)
{
    if(!table || itemCount >= tableSize)
        return 0;

    table[itemCount].vertexIndex = index;
    table[itemCount].f = g + h;
    table[itemCount].g = g;
    table[itemCount].h = h;

    int newDataIndex = itemCount; //Use this to keep track of where toAdd is
    int parentIndex; //The parent index pf toAdd
    bool bInPlace = false;

    while(newDataIndex >= 0 && !bInPlace)
    {
        parentIndex = (newDataIndex - 1) / 2;

        if(table[newDataIndex].f >= table[parentIndex].f)
            bInPlace = true;
        else
        {
            OpenListNode temp = table[parentIndex];
            table[parentIndex] = table[newDataIndex];
            table[newDataIndex] = temp;

            newDataIndex = parentIndex;
        }
    }

    ++itemCount;
    return 1;
}

int OpenList::Remove(OpenListNode& result)
{
    if(!table || IsEmpty())
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
        int smallerIndex = leftIndex; //Use this to determine the smaller child
        int rightIndex = leftIndex + 1;

        if(rightIndex < itemCount && table[rightIndex].f < table[leftIndex].f)
            smallerIndex = rightIndex; //Get the correct child

        if(table[smallerIndex].f < table[rootIndex].f)
        {
            //Swap the nodes
            OpenListNode temp = table[rootIndex];
            table[rootIndex] = table[smallerIndex];
            table[smallerIndex] = temp;

            return  1 + Rebuild(smallerIndex); //Number of times a rebuild had to happen
        }
    }

    return 0;
}

/*PATH STACK IMPLEMENTATIONS*/
Path::Path()
{
    top = NULL;
}

Path::~Path()
{
    Clear();
}

//Always return true
bool Path::Push(const Vector& toAdd)
{
    PathNode* temp = new PathNode;
    temp->position = toAdd;
    temp->next = top;
    top = temp;

    return true;

    /*
    PathNode* temp = rear->next;
    rear->next = new PathNode;
    rear = rear->next;
    rear->position.x = toAdd.x;
    rear->position.y = toAdd.y;
    rear->next = temp;
    */
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

bool Path::Display() const
{
    PathNode* current = top;
    while(current)
    {
        cout << "(" << current->position.GetX() << ", " << current->position.GetY() << ")" << endl;
        current = current->next;
    }

    return true;
}

bool Path::IsEmpty() const
{
    return top == NULL;
}

bool Path::Clear()
{
    if(!top)
        return false;

    PathNode* temp = top;
    while(top)
    {
        top = top->next;
        delete temp;
        temp = top;
    }

    return true;
}

//Return the item at the front of the queue
Vector Path::Peek()
{
    Vector toReturn;

    if(top)
        toReturn = top->position;

    return toReturn;
}

/*VERTEX IMPLEMENTATIONS*/
Vertex::Vertex()
{
    head = NULL;
}

/*NODE IMPLEMENTATIONS*/
EdgeNode::EdgeNode()
{
    next = NULL;
    vertexIndex = -1;
}

/*OPEN LIST NODE IMPLEMENTATIONS*/
OpenListNode::OpenListNode()
{
    vertexIndex = -1;
    f = g = h = 0;
}

OpenListNode::OpenListNode(const OpenListNode& toCopy)
{
    vertexIndex = toCopy.vertexIndex;
    f = toCopy.f;
    g = toCopy.g;
    h = toCopy.h;
}

/*PATH NODE IMPLEMENTATIONS*/
PathNode::PathNode()
{
   next = NULL;
}

PathNode::PathNode(const PathNode& p)
{
    Copy(p);
    next = NULL;
}

PathNode& PathNode::operator= (const PathNode& p)
{
    Copy(p);
    next = NULL;

    return *this;
}

void PathNode::Copy(const PathNode& p)
{
    position = p.position;
}
