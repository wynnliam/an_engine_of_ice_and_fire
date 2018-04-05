//Liam "AFishyFez" Wynn, 9/13/2015, A Clash of Colors

/*
 Tracer Weapons, in addition to Projectile Weapons, are
 one of the most general types of weapons in
 A Clash of Colors. Essentially, they fire a line called
 a tracer, which checks if it hit any other actors.

 Here, you will find the parent class of all Tracer Weapons.
 The core of all Tracer Weapons is handled here. However,
 this is for all Tracer Weapons that fire a single shot. If
 you want to modify this behavior to handle a shotgun-esque
 weapon, you'll have to override the update function and do
 it yourself.
*/

#ifndef ACOC_WEAPON_TRACER
#define ACOC_WEAPON_TRACER

#include "../Weapon.h"
#include "../../../../Utilities/General_Purpose/Tracer.h"

namespace AEOIAF_Actor
{
	//The node of the Tracer List
	struct TracerListNode
	{
		TracerListNode();
		TracerListNode(const AEOIAF_Utilities::Tracer& tracer);
		TracerListNode(const TracerListNode& toCopy);
		~TracerListNode();

		TracerListNode& operator= (const TracerListNode& toCopy);

		void Copy(const TracerListNode& toCopy);

		AEOIAF_Utilities::Tracer tracer;
		TracerListNode* next;
	};

	//Stores all tracers fired by a TracerWeapon
	class TracerList
	{
		public:
			TracerList();
			TracerList(const TracerList& toCopy);
			~TracerList();

			//Copy all the properties of toCopy into
			//this list
			void Copy(const TracerList& toCopy);
			//Add a tracer to the top of the list
			void Push(const AEOIAF_Utilities::Tracer& toAdd);
			//Clear the entire list
			void Clear();

			//Determines if any tracer hit this actor
			bool HitActor(Actor* toCheck) const;
			//Determines if any tracer hit this tile
			bool HitTile(AEOIAF_Level::Tile* toCheck) const;

			//Render each tracer in the list
			void Draw(SDL_Renderer* renderer, AEOIAF_Utilities::Matrix* matrix = NULL);

		private:
			/*RECURSIVE FUNCTIONS*/
			void Copy(TracerListNode*& dest, TracerListNode* source);
			void Clear(TracerListNode*& head);

			void DrawTracer(AEOIAF_Utilities::Tracer& toDraw, SDL_Renderer* renderer,
							AEOIAF_Utilities::Matrix* matrix = NULL);

			TracerListNode* head;
	};

	class WeaponTracer : public Weapon
	{
		public:
            WeaponTracer();
            WeaponTracer(const char* newID);
            WeaponTracer(const Weapon& toCopy);
            virtual ~WeaponTracer();

            virtual WeaponTracer& operator = (const WeaponTracer& toCopy);

            virtual void Copy(const WeaponTracer& toCopy);
			virtual WeaponTracer* GetCopy();

			virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
            
			virtual bool DidHit(Actor* toCheck);
			virtual bool DidHit(AEOIAF_Level::Tile* toCheck);
			
			virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);
	
		protected:
			//Determines if the conditions for firing the weapon
			//are met
			virtual bool FiredWeapon();
			//Essentially makes a tracer line. Do not handle collisions here,
			//we simply add the tracer to a list
			virtual void MakeTracer();
			//A utility function that handles our hit entities
			void HandlePotentialHits(AEOIAF_Level::Level* level);


			TracerList tracers; //Store all tracers we fired
	};
}

#endif
