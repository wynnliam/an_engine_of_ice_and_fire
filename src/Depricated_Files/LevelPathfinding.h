//Liam "AFishyFez" Wynn, 2/25/2015, AEOIAF: Level Path Finding

/*
Here I make prototypes for the Path Node, and
Level Path Graph abstract data type. As the name
implies, I am using a node graph to represent the
paths of travel for a level.
*/

#ifndef LEVELPATHFINDING_H
#define LEVELPATHFINDING_H

#include "../../Utilities/Utility_Components/Vector.h"
#include <iostream>

namespace AEOIAF_Pathfinding
{
    struct PathNode
    {
        PathNode();
        PathNode(const PathNode& p);

        PathNode& operator= (const PathNode& p);

        void Copy(const PathNode& p);

        AEOIAF_Utilities::Vector position;

        PathNode* next;
    };

    struct EdgeNode
    {
        EdgeNode();

		//Each vertex contains an LLL of vertecies adjacent to it.
		//This index is a means to store those adjacent vertecies
        int vertexIndex;
        //The next node in the list
        EdgeNode* next;
    };

    struct Vertex
    {
        Vertex();

        AEOIAF_Utilities::Vector position;
        EdgeNode* head; //The head of a LLL of adjacent nodes
    };

    struct OpenListNode
    {
        OpenListNode();
        OpenListNode(const OpenListNode& toCopy);

        int vertexIndex; //The index used in the table;
        int f, g, h; //The cost values for traveling to the vertex at vertexIndex
    };

    //Basically a queue that stores all the positions of the path.
    //Represented as a circular linked list
    class Path
    {
        public:
            Path();
            ~Path();

            //Adds a position to the stack
            bool Push(const AEOIAF_Utilities::Vector& toAdd);
            //Removes the front item. Returns false if the stack is empty
            bool Pop();
            //I'm unsure what this does...
            bool IsEmpty() const;
            //Clears the path if not empty
            bool Clear();
            //Display
            bool Display() const;

            //Returns the front item
            AEOIAF_Utilities::Vector Peek();

        private:
            PathNode* top;
    };

    //Stores the nodes that we need to examine in the
    //path finder. Stored as a binary heap
    class OpenList
    {
        public:
            OpenList(int newSize = 10);
            ~OpenList();

            bool IsEmpty() const;
            //Adds an item to the heap if we can
            int AddItem(int index, int g, int h);
            //Grab the root's item and remove it from the heap
            int Remove(OpenListNode& result);

        private:
            int Rebuild(int rootIndex);

            OpenListNode* table; //Where the data of the heap is stored
            int tableSize;
            int itemCount; //The next free index to place a node
    };

    class LevelNodeGraph
    {
        public:
            LevelNodeGraph();
            ~LevelNodeGraph();

            //All this does is traverse graph and sets all adjacencies
            //returns false if walls or the graph are not initialized
            bool Initialize(int newWidth, int newHeight, bool* walls);
            //Adds a directed adjacency that follows: vertex->adjacent
            //Returns false if the graph is empty
            bool AddEdge(int vertexIndex, int adjacentIndex);
            //Displays all nodes, returns false if the graph is empty
            bool Display() const;
            //Uses A* path finding to get a path. Returns false if no path
            //is found
            bool GetPath(Path& result, const AEOIAF_Utilities::Vector& s, const AEOIAF_Utilities::Vector& e) const;

        private:
            //Adds nodes to a path. Returns 0 if the process fails
            int BuildPath(Path& result, int endIndex, int* parent) const;
            //Calculates manhattan distance between a and b
            int ManhattanDist(const AEOIAF_Utilities::Vector& a, const AEOIAF_Utilities::Vector& b) const;

            Vertex* table; //Use this to handle adjacencies
            int width, height, length;
    };
}

#endif // LEVELPATHFINDING_H
