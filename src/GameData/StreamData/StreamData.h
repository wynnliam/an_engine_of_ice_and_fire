//Liam "AFishyFez" Wynn, 2/1/2016, A Clash of Colors

/*
 When you leave a level, the entire level is deleted. This means
 all characters, props, actors, etc are deleted. As such, when
 we leave a level, we want to save any relevent properties
 that we may want to restore.

 The StreamDataHandler is in charge of that. Once we load a level,
 we use the StreamDataHandler to update actor data.

 In addition, we also use it to hold the level draw component.
 The problem is that SDL leaks when initializing one. So everytime
 the level loads, a memory leak occurs. We can somewhat rectify
 this by having the level draw components of a level stored
 here.

 The StreamDataHandler, for anyone who might want to know, is
 represented as a hash table.
*/

#ifndef ACOC_STREAM_DATA_HANDLER
#define ACOC_STREAM_DATA_HANDLER

#include "InsertActorList.h"
#include "RemoveActorList.h"
#include <SDL2/SDL.h>

namespace AEOIAF_Level
{
	class Level;
}

namespace AEOIAF_Utilities
{
	class Vector;
}

namespace ACOC_GameDataHandling
{
	class GameDataHandler;

	//Keeps track of all level data (actors to remove,
	//actors to update, etc) for a single level
	class LevelStreamDataHandler
	{
		public:
			LevelStreamDataHandler();
			~LevelStreamDataHandler();

			/*INSERT ACTOR LIST WRAPPERS*/
			//Inserts the ID of an actor into the insert list
			int InsertActorToInsert(const char* toAdd, const AEOIAF_Utilities::Vector& pos);
			//Removes the ID of an actor from the insert list
			int RemoveActorToInsert(const char* toRemove);
			//Adds every actor in the Insert Actor List into the level
			void AddActorsToLevel(AEOIAF_Level::Level* level, const GameDataHandler& dataHandler);

			/*REMOVE ACTOR LIST WRAPPERS*/
			//Inserts the ID of an actor into the remove list
			int InsertActorToRemove(const char* toInsert);
			//Removes the ID of an actor into the remove list
			int RemoveActorToRemove(const char* toRemove);
			//Removes all actors from the level that are in actorsToRemove
			void RemoveActorsFromLevel(AEOIAF_Level::Level* level, const GameDataHandler& dataHandler);
			//Determines if the ID of an actor exists in the remove list
			bool FindActorToRemove(const char* toFind) const;
			//Clears the entire remove list
			int ClearActorsToRemove();

		private:
			//Keeps track of actors that are added to the level,
			//but not part of the actors loaded from file
			InsertActorList actorsToInsert;
			//Keeps track of actors that should not be
			//in the level
			RemoveActorList actorsToRemove;
	};

	//Manages all of the LevelStreamDataHandlers
	class StreamDataHandler
	{
		public:
			StreamDataHandler();
			StreamDataHandler(const int newTableSize);
			~StreamDataHandler();

			//Inserts a level's stream data into the table
			int InsertStreamData(const char* toInsert);
			//Remove a level's stream data from the table
			int RemoveStreamData(const char* toRemove);
			//Determines if a level's stream data exists in the table
			bool FindStreamData(const char* toFind) const;

			/*LEVEL STREAM INSERT ACTOR LIST WRAPPERS*/
			int InsertActorToInsert(const char* levelID, const char* toInsert,
									const AEOIAF_Utilities::Vector& vector);
			int RemoveActorToInsert(const char* levelID, const char* toRemove);
			//Add all the actors in the Insert Actor List into the level
			int AddActorsToLevel(AEOIAF_Level::Level* level, const GameDataHandler& dataHandler);
			/*LEVEL STREAM REMOVE ACTOR LIST WRAPPERS*/
			int InsertActorToRemove(const char* levelID, const char* toInsert);
			int RemoveActorToRemove(const char* levelID, const char* toRemove);
			//Remove all actors in the Remove Actor List from the level
			int RemoveActorsFromLevel(AEOIAF_Level::Level* level, const GameDataHandler& dataHandler);
			bool FindActorToRemove(const char* levelID, const char* toFind) const;
			int ClearActorsToRemove(const char* levelID);

		private:
			int GetHashValue(const char* toHash) const;

			class StreamDataList* table;
			int tableSize;
	};

	//Represents a single linear linked list of StreamNodes
	class StreamDataList
	{
		public:
			StreamDataList();
			~StreamDataList();

			//Inserts toAdd into the list, if it isn't there already
			int Insert(const char* toInsert);
			//Removes a stream node from the list
			int Remove(const char* toRemove);
			//Returns if a stream data node exists
			bool Find(const char* toFind) const;
			//Clears the entire list
			void Clear();

			/*LEVEL STREAM INSERT ACTOR LIST WRAPPERS*/
			int InsertActorToInsert(const char* levelID, const char* toInsert,
									const AEOIAF_Utilities::Vector& pos);
			int RemoveActorToInsert(const char* levelID, const char* toRemove);
			int AddActorsToLevel(const char* levelID, AEOIAF_Level::Level* level,
								 const GameDataHandler& dataHandler);
			/*LEVEL STREAM REMOVE ACTOR LIST WRAPPERS*/
			int InsertActorToRemove(const char* levelID, const char* toInsert);
			int RemoveActorToRemove(const char* levelID, const char* toRemove);
			int RemoveActorsFromLevel(const char* levelID, AEOIAF_Level::Level* level,
									  const GameDataHandler& dataHandler);
			bool FindActorToRemove(const char* levelID, const char* toFind) const;
			int ClearActorsToRemove(const char* levelID);

		private:
			//Recursively removes toRemove
			int Remove(const char* toRemove, struct StreamDataNode*& head);
			//Recursively finds toFind
			bool Find(struct StreamDataNode* head, const char* toFind) const;
			//Recursively clears the entire list
			void Clear(struct StreamDataNode*& head);
			
			/*LEVEL STREAM INSERT ACTOR LIST RECURSIVE WRAPPERS*/
			int InsertActorToInsert(const char* levelID, const char* toInsert,
									const AEOIAF_Utilities::Vector& pos, struct StreamDataNode* head);
			int RemoveActorToInsert(const char* levelID, const char* toRemove, struct StreamDataNode* head);
			/*LEVEL STREAM REMOVE ACTOR LIST RECURSIVE WRAPPERS*/
			int InsertActorToRemove(const char* levelID, const char* toInsert, struct StreamDataNode* head);
			int RemoveActorToRemove(const char* levelID, const char* toRemove, struct StreamDataNode* head);
			bool FindActorToRemove(const char* levelID, const char* toFind, struct StreamDataNode* head) const;
			int ClearActorsToRemove(const char* levelID, struct StreamDataNode* head);

			struct StreamDataNode* head;
	};

	//Represents a single node in a LLL of nodes
	struct StreamDataNode
	{
		StreamDataNode();
		~StreamDataNode();

		char* levelID;
		LevelStreamDataHandler levelHandler;

		StreamDataNode* next;
	};
}

#endif
