//Liam "AFishyFez" Wynn, 7/25/2015, A Clash of Colors

/*
 Unlike the Weapon parent class, here we will see
 some of the meat-and-potatoes of a Weapon. That is,
 we will actually implement a portion of all melee
 weapons. In this case, that will be determining
 the kind of attack type the player wishes to perform.

 This attack type is determined by the movement of the
 mouse. If the player moves the mouse left, the weapon
 will prepare for a left attack. Principally, this also
 applies to right mouse movement. If the player moves
 the mouse down, then he will prepare for forward attack.

 Ideally, I'd check if the mouse moved up, and do an attack
 for that. However, I feel like the movement would be
 kind of awkward. I think three is fine.

 Anyways, my goal with melee weapons is to make them more
 fun to have fights with. If I just had mindless clicking,
 I feel like the battles would be kind of lame.
*/

#ifndef ACOC_WEAPON_MELEE
#define ACOC_WEAPON_MELEE

#include "../Weapon.h"
#include "../../../../Utilities/Utility_Components/Vector.h"
#include "../../../../Utilities/Utility_Components/AxisAllignedBoundingBox.h"
#include "../../../../Utilities/General_Purpose/Matrix.h"
#include "../../../../Animation/Animation.h"
#include <SDL2/SDL.h>

//Define the state based on user input
#define STATE_IDLE 	 0
#define STATE_IDLE_R 1
#define STATE_IDLE_L 2
#define STATE_IDLE_C 3
#define STATE_ATTK_R 4
#define STATE_ATTK_L 5
#define STATE_ATTK_C 6

namespace AEOIAF_Actor
{
	//Holds collision data for a single frame in a melee weapon
	struct CollisionData
	{
		CollisionData();

		CollisionData& operator= (const CollisionData& toCopy);

		void Copy(const CollisionData& toCopy);

		//The bounding box around the weapon, relative to (0, 0). Apply
		//an offset to it to make it in the position you want
		AEOIAF_Utilities::AxisAllignedBoundingBox baseBox;
		//The offset to the owner's position that we apply to the base box
		//when checking for collisions
		AEOIAF_Utilities::Vector offset;
		//Describes the relative rotation of the melee weapon to the owner
		float relativeRotation;
		float distance; //The distance of the weapon from the owner's center
	};

	class WeaponMelee : public Weapon
	{
		public:
            WeaponMelee();
            WeaponMelee(const char* newID);
            WeaponMelee(const WeaponMelee& toCopy);
            virtual ~WeaponMelee();

			int GetState() const { return state; }
			void SetState(const int val) { state = val; }

			int GetAttackType() const { return attackType; }
			void SetAttackType(const int val) { attackType = val; }

			AEOIAF_Utilities::DrawableComponent* GetAnimationDrawComponent();
			void SetAnimationDrawComponent(AEOIAF_Utilities::DrawableComponent* val);

            virtual WeaponMelee& operator = (const WeaponMelee& toCopy);

            virtual void Copy(const WeaponMelee& toCopy);
			virtual WeaponMelee* GetCopy();

			virtual bool IsAttackStateValid(const int toCheck) = 0;

			//Since the attack state for the character is dependent on the animation
			//of the melee weapon, we need this. Return 10001 for failure
			unsigned int GetCurrentAnimation() const;

			//Every melee weapon has different available fighting
			//states it can be in. For the AI to pick one, it needs
			//to know which are available. So we use this function
			//for that
			virtual void GetAvailableAttackStates(int* outStates, int& outNumStates) = 0;

			//While different melee weapons will have different states it can be in,
			//the possible available states are all the same. However, these states
			//are entirely dependent on the animation the weapon is in, which varies
			//between differen weapon types. Thus, we implement these functions for
			//each melee weapons to tell us what state the weapon is in
			virtual bool IsStateIdle() const = 0;
			virtual bool IsStateReadyLeft() const = 0;
			virtual bool IsStateReadyRight() const = 0;
			virtual bool IsStateReadyCenter() const = 0;
			virtual bool IsStateAttackLeft() const = 0;
			virtual bool IsStateAttackRight() const = 0;
			virtual bool IsStateAttackCenter() const = 0;
			virtual bool IsStateBlockLeft() const = 0;
			virtual bool IsStateBlockRight() const = 0;
			virtual bool IsStateBlockCenter() const = 0;

            //For melee weapons, just check input here
            virtual void Update(AEOIAF_Level::Level* level, SDL_Event* e, float deltaTime);
			
			//Determine if the collision component of this weapon contains
			//another actor's collision component
			bool DidHit(AEOIAF_Actor::Actor* toCheck);
			bool DidHit(AEOIAF_Level::Tile* toCheck);

			//Draw the melee weapon relative to the center, not top-left corner
            virtual void Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
                              bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                              AEOIAF_Utilities::Matrix* matrix = NULL);

		protected:
			/*COLLISION HANDLING*/
			//We update the tMatrix and rMatrix so that later we may
			//apply them to the baseBoxes which we then later use in
			//Checking collisions with other actors
			void UpdateCollisionTransformMatricies();

			//Given an Axis alligned bounding box, transform it using our
			//rMatrix and tMatrix
			void CreateTransformedCollisionBox(AEOIAF_Utilities::AxisAllignedBoundingBox& aabb);

			//Updates the variable colBoxPos for collision checking
			//width and height are the width and height of the aabb used
			//in CreateTransformedCollisionBox
			void UpdateCollisionBoxPosition(int width, int height);

			//Updates the collision component with a transformed AABB
			void UpdateCollisionComponent();

			//Reset all flags
			void Reset();

			virtual void CreateAnimationData();

			//Use this stuff when checking for collisions
			//Rotation matrix, used in transforming a base
			//rectangle that we can use for collision checking
			AEOIAF_Utilities::Matrix rMatrix;

			//Melee weapons are a bit janky. Unlike other weapons/actors, the posiiton
			//of the melee weapon doesn't neccessarily correspond to the bounding box
			//position. As such, when we go to check for collisions, we need to make
			//sure we keep track of where the collision box will be
			AEOIAF_Utilities::Vector colBoxPos;
			
			CollisionData* collisionData; //Data used for collision checking for a single attack anim frame
			unsigned int numCollisionData; //Based off of the number of animations
			//When we apply an offset to the owner's pos in UpdateCollisionTransformMatrices, we need
			//to know which collisionData to use when grabing the offset. We can use this variable to
			//hold that information
			unsigned int currentCollisionData;

			//0 for idle, 1 for right idle, 2 for left idle, 3 for center idle,
			//4 for attack right, 5 for attack left, and 6 for attack center
			int state;
	
			int attackType; //0 for right, 1 for left, 2 for center, -1 for none
			bool bShouldFire; //A flag to denote that we should attempt to fire our weapon

			//Since animations are key to melee functionality, we can have this here to manage
			//the animation
			ACOC_Animation::AnimationHandler* animation;

		private:
			bool bReset; //A flag to tell the owner its internal flags were reset
	};
}

#endif
