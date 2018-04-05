//Liam "AFishyFez" Wynn, 8/19/2015, A Clash of Colors

/*
 Let's say we have a weapon, and it collides with a series
 of actors and tiles. We would certainly like information
 about each actor/tile that was hit. In this case, we'd probably
 like to know who the closest actor we hit was.

 That is where these two data structures come in. Essentially, they
 are both red-black trees wherein we organize by distance from the
 weapon that hit them (or in the case of projectile weapons, the distance
 to the projectile itself).

 Perhaps we'd like a weapon that hits all actors it touches? We could do
 that. Alternatively, perhaps we don't use it for weapons exclusively.
 Maybe say you'd like gravity ala Super Mario Galaxy, where we fire a tracer
 below the player to get the surface below him. This is general purpose
 enough to handle that scenario. However I sincerely doubt I'd use it for that
 in a top-down 2D engine.
*/

namespace AEOIAF_Actor
{
	//We need this for actors
	class Actor;
}

namespace AEOIAF_Level
{
	class Tile; //A forward declaration for the Tile class, so we don't include it here

	struct ColActorNode
	{
		ColActorNode();
		ColActorNode(const ColActorNode& toCopy);
		~ColActorNode();

		ColActorNode& operator = (const ColActorNode& toCopy);

		void Copy(const ColActorNode& toCopy);
		/*UTILITY FUNCTIONS*/
		//Returns the grandparent of this node
		ColActorNode* FindGrandParent();
		//Returns the uncle of this node
		ColActorNode* FindUncle();

		bool bIsBlack; //Is this a black node? False implies red

		float distance; //Distance from the hit actor
		AEOIAF_Actor::Actor* hitActor; //The actor we hit
		
		ColActorNode* parent; //Parent of this node (NULL means this is root)
		ColActorNode* left; //Left child
		ColActorNode* right; //Right child
	};

	struct ColTileNode
	{
		ColTileNode();
		ColTileNode(const ColTileNode& toCopy);
		~ColTileNode();

		ColTileNode& operator= (const ColTileNode& toCopy);

		void Copy(const ColTileNode& toCopy);
		
		/*UTILITY FUNCTIONS*/
		ColTileNode* FindGrandParent();
		//Returns the uncle of this node
		ColTileNode* FindUncle();
		bool bIsBlack;

		float distance; //Distance from the hit tile
		AEOIAF_Level::Tile* hitTile;

		ColTileNode* parent;
		ColTileNode* left;
		ColTileNode* right;
	};

	class ActorCollisionList
	{
		public:
			ActorCollisionList();
			ActorCollisionList(const ActorCollisionList& toCopy);
			~ActorCollisionList();

			ActorCollisionList& operator = (const ActorCollisionList& toCopy);

			void Copy(const ActorCollisionList& toCopy);

			bool Add(AEOIAF_Actor::Actor* toAdd, AEOIAF_Actor::Actor* instigator);
			void RemoveAll();
			bool IsEmpty() const;

			AEOIAF_Actor::Actor* FindClosestHitActor();
			//For every actor in the list, we can give them damage
			//from an instigator
			void DoDamage(AEOIAF_Actor::Actor* instigator, const float damage);
			void DoDamageClosestActor(AEOIAF_Actor::Actor* instigator, const float damage);

		private:
			/*RECURSIVE FUNCTIONS*/

			//Recursive implementation for the Copy function
			void Copy(ColActorNode*& dest, ColActorNode* source);
			//Recursive implementation for Add. Dist is used to
			//determine where we add toAdd. Returns false if toAdd
			//is NULL
			bool Add(AEOIAF_Actor::Actor* toAdd, float dist, ColActorNode*& head, ColActorNode* parent);
			//Traverses to the left of the tree until we find the closest actor
			AEOIAF_Actor::Actor* FindClosestHitActor(ColActorNode* head);
			//Calls the DoDamage function for each actor
			void DoDamage(AEOIAF_Actor::Actor* instigator, const float damage, ColActorNode* head);
			//Recursive implementation for the RemoveAllFunction
			void RemoveAll(ColActorNode*& head);

			/*RED-BLACK CASES*/
			void HandleCase1(ColActorNode* node);
			void HandleCase2(ColActorNode* node);
			void HandleCase3(ColActorNode* node);
			void HandleCase4(ColActorNode* node);

			/*BALANCED TREE ROTATIONS*/
			void RotationRight(ColActorNode* node);
			void RotationLeft(ColActorNode* node);

			/*UTILITY FUNCTIONS*/
			//Calculates the distance between toAdd, and instigator. If either are NULL, then
			//return -1
			float GetDistance(AEOIAF_Actor::Actor* toAdd, AEOIAF_Actor::Actor* instigator);

			ColActorNode* head;
	};

	class TileCollisionList
	{
		public:
			TileCollisionList();
			TileCollisionList(const TileCollisionList& toCopy);
			~TileCollisionList();

			TileCollisionList& operator = (const TileCollisionList& toCopy);

			void Copy(const TileCollisionList& toCopy);

			bool Add(Tile* toAdd, AEOIAF_Actor::Actor* instigator);

			Tile* FindClosestHitTile();

			void RemoveAll();

			bool IsEmpty() const;

		private:
			/*RECURSIVE FUNCTIONS*/

			//Recursive implementation for the Copy function
			void Copy(ColTileNode*& dest, ColTileNode* source);
			//Recursive implementation for Add. Dist is used to
			//determine where we add toAdd. Returns false if toAdd
			//is NULL
			bool Add(Tile* toAdd, float dist, ColTileNode*& head, ColTileNode* parent);
			//Traverses to the left of the tree until we find the closest tile
			Tile* FindClosestHitTile(ColTileNode* head);
			//Recursive implementation for the RemoveAllFunction
			void RemoveAll(ColTileNode*& head);

			/*RED-BLACK CASES*/
			void HandleCase1(ColTileNode* node);
			void HandleCase2(ColTileNode* node);
			void HandleCase3(ColTileNode* node);
			void HandleCase4(ColTileNode* node);

			/*BALANCED TREE ROTATIONS*/
			void RotationRight(ColTileNode* node);
			void RotationLeft(ColTileNode* node);

			/*UTILITY FUNCTIONS*/
			//Calculates the distance between toAdd, and instigator. If either are NULL, then
			//return -1
			float GetDistance(Tile* toAdd, AEOIAF_Actor::Actor* instigator);

			ColTileNode* head;
	};
}
