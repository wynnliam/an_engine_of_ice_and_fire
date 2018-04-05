//Liam "AFishyFez" Wynn, 7/27/2015, A Clash of Colors

#include "WeaponMeleeTest.h"
#include "../../../../Level/Level.h"
#include "../../../../Level/WeaponCollisionDataTypes.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace AEOIAF_Content;
using namespace ACOC_Animation;
using namespace std;

//Define the animation states for this weapon
#define ANIM_IDLE 			0
#define ANIM_READY_RIGHT 	1
#define ANIM_READY_LEFT 	2
#define ANIM_ATTACK_RIGHT 	3
#define ANIM_ATTACK_LEFT 	4
#define ANIM_BLOCK_RIGHT	5
#define ANIM_BLOCK_LEFT		6

#define FIRE_RATE 1000

WeaponMeleeTest::WeaponMeleeTest()
{
	rectangleRegion = NULL;
	SetFireRate(FIRE_RATE);
	CreateComponents();
}

WeaponMeleeTest::WeaponMeleeTest(const char* newID) : WeaponMelee(newID)
{
	rectangleRegion = NULL;
	SetFireRate(FIRE_RATE);
	CreateComponents();
}

WeaponMeleeTest::WeaponMeleeTest(const WeaponMeleeTest& toCopy)
{
	rectangleRegion = NULL;
	SetFireRate(FIRE_RATE);

	Copy(toCopy);
}

WeaponMeleeTest::~WeaponMeleeTest()
{
	if(rectangleRegion)
	{
		delete rectangleRegion;
		rectangleRegion = NULL;
	}
}

WeaponMeleeTest& WeaponMeleeTest::operator = (const WeaponMeleeTest& toCopy)
{
	Copy(toCopy);
	return *this;
}

void WeaponMeleeTest::Copy(const WeaponMeleeTest& toCopy)
{
	if(this == &toCopy)
		return;

	WeaponMelee::Copy(toCopy);
}

void WeaponMeleeTest::CreateComponents()
{
	SetMovableComponent(new MovableComponent);
	SetCollisionComponent(new CollisionComponent);

	SetPrefMinFightDist(20.0f);
	SetPrefMaxFightDist(50.0f);

	CreateAnimationData();

	numCollisionData = 10; //5 frames for left, and right
	collisionData = new CollisionData[numCollisionData];
	//Right swing
	collisionData[0].baseBox = AxisAllignedBoundingBox(0, 0, 4, 42);
	collisionData[0].offset = Vector(2, 21);
	collisionData[0].relativeRotation = 90.0f;
	collisionData[0].distance = 32.0f;
	
	collisionData[1].baseBox = AxisAllignedBoundingBox(0, 0, 38, 38);
	collisionData[1].offset = Vector(19, 19);
	collisionData[1].relativeRotation = 45.0f;
	collisionData[1].distance = 32.0f;

	collisionData[2].baseBox = AxisAllignedBoundingBox(0, 0, 42, 4);
	collisionData[2].offset = Vector(21, 2);
	collisionData[2].relativeRotation = 0.0f;
	collisionData[2].distance = 32.0f;

	collisionData[3].baseBox = AxisAllignedBoundingBox(0, 0, 34, 34);
	collisionData[3].offset = Vector(17, -17);
	collisionData[3].relativeRotation = -45.0f;
	collisionData[3].distance = 32.0f;

	collisionData[4].baseBox = AxisAllignedBoundingBox(0, 0, 4, 34);
	collisionData[4].offset = Vector(2, -17);
	collisionData[4].relativeRotation = -90.0f;
	collisionData[4].distance = 32.0f;

	//Left swing
	collisionData[5].baseBox = AxisAllignedBoundingBox(0, 0, 4, 34);
	collisionData[5].offset = Vector(-2, -17);
	collisionData[5].relativeRotation = -90.0;
	collisionData[5].distance = 32.0f;

	collisionData[6].baseBox = AxisAllignedBoundingBox(0, 0, 34, 34);
	collisionData[6].offset = Vector(17, -17);
	collisionData[6].relativeRotation = -45.0f;
	collisionData[6].distance = 32.0f;

	collisionData[7].baseBox = AxisAllignedBoundingBox(0, 0, 34, 4);
	collisionData[7].offset = Vector(17, 2);
	collisionData[7].relativeRotation = 0.0f;
	collisionData[7].distance = 32.0f;

	collisionData[8].baseBox = AxisAllignedBoundingBox(0, 0, 38, 38);
	collisionData[8].offset = Vector(19, 19);
	collisionData[8].relativeRotation = 45.0f;
	collisionData[8].distance = 32.0f;

	collisionData[9].baseBox = AxisAllignedBoundingBox(0, 0, 4, 34);
	collisionData[9].offset = Vector(2, 17);
	collisionData[9].relativeRotation = 90.0f;
	collisionData[9].distance = 32.0f;
}

void WeaponMeleeTest::CreateAnimationData()
{
	//Instead of the draw component, we use the animation handler
	animation = new AnimationHandler();
	animation->SetFrameWidth(256);
	animation->SetFrameHeight(256);
	animation->SetNumAnims(7);

	//Some of these things only work after we initialize, so we can
	//do this here
	for(int i = 0; i < 5; ++i)
	{
		animation->SetFrameRate(i, 200);
		animation->ShouldRepeat(i, false);

		if(i == 3 || i == 4)
			animation->SetNumFrames(i, 5);
		else
			animation->SetNumFrames(i, 1);
	}

	animation->SetCurrentAnim(0);
}

bool WeaponMeleeTest::IsAttackStateValid(const int toCheck)
{
	return toCheck == ANIM_ATTACK_LEFT ||
		   toCheck == ANIM_ATTACK_RIGHT;
}

void WeaponMeleeTest::GetAvailableAttackStates(int* outStates, int& outNumStates)
{
	outNumStates = 2;
	outStates[0] = 1;
	outStates[1] = 2;
}

bool WeaponMeleeTest::IsStateIdle() const
{
	return animation && animation->GetCurrentAnim() == ANIM_IDLE;
}

bool WeaponMeleeTest::IsStateReadyLeft() const
{
	return animation && animation->GetCurrentAnim() == ANIM_READY_LEFT;
}

bool WeaponMeleeTest::IsStateReadyRight() const
{
	return animation && animation->GetCurrentAnim() == ANIM_READY_RIGHT;
}

bool WeaponMeleeTest::IsStateReadyCenter() const
{
	return false;
}

bool WeaponMeleeTest::IsStateAttackLeft() const
{
	return animation && animation->GetCurrentAnim() == ANIM_ATTACK_LEFT;
}

bool WeaponMeleeTest::IsStateAttackRight() const
{
	return animation && animation->GetCurrentAnim() == ANIM_ATTACK_RIGHT;
}

bool WeaponMeleeTest::IsStateAttackCenter() const
{
	return false; //We don't have an animation for this state for this weapon
}

bool WeaponMeleeTest::IsStateBlockLeft() const
{
	return animation && animation->GetCurrentAnim() == ANIM_BLOCK_LEFT;
}

bool WeaponMeleeTest::IsStateBlockRight() const
{
	return animation && animation->GetCurrentAnim() == ANIM_BLOCK_RIGHT;
}

bool WeaponMeleeTest::IsStateBlockCenter() const
{
	return false;
}

void WeaponMeleeTest::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!owner || !animation || !level)
		return;

	//If the animation is playing, then we can use this
	//to determine what our next course of action is given
	//the current animation
	int currentAnim;

	WeaponMelee::Update(level, e, deltaTime);

	//We only want to modify the animation if we are not playing animation
	//currently. This is so that we don't cancel the fire animation midway through,
	//simply because the player let go of the fire button. However, we will
	//override this if bShouldFire is true. bShouldFire is only true when melee input
	//handlers determine so, which only happens when we are not recharging
	if(!animation->IsPlaying() || bShouldFire)
		UpdateAnimation();
	else
	{
		currentAnim = animation->GetCurrentAnim();

		if(currentAnim == ANIM_ATTACK_RIGHT || currentAnim == ANIM_ATTACK_LEFT)
			HandleSwingAnimation(currentAnim, level);
	}

	animation->Update();
}

//Based on boolean flags set in WeaponMelee,
//we will determine what animation to play.
//Primarily, we are looking at bShouldFire, and
//the attackType
void WeaponMeleeTest::UpdateAnimation()
{
	if(!animation)
		return;

	//Index of the animation to play. Where 0 is
	//Idle, 1 is preparing to attack right, 2 is
	//preparing to attack left, 3 is attack right,
	//and 4 is attack right
	int animationToPlay;

	//We did not have an attack type, and
	//we are not clicking. Or we fired, and we need to wait to
	//fire again
	if(IsRecharging() || (!bShouldFire && state == 0))
		animationToPlay = ANIM_IDLE;

	//If we have an attack type, but did not let go of the
	//mouse
	else if(!bShouldFire && state != 0)
	{
		if(state == 1)
			animationToPlay = ANIM_READY_RIGHT;
		else if(state == 2)
			animationToPlay = ANIM_READY_LEFT;
		else if(state == 7)
			animationToPlay = ANIM_BLOCK_RIGHT;
		else if(state == 8)
			animationToPlay = ANIM_BLOCK_LEFT;
		else
			animationToPlay = ANIM_IDLE; //You would handle a center animation here, but I don't have one
	}

	else if(bShouldFire && state != 0)
	{
		if(state == 4)
		{
			animationToPlay = ANIM_ATTACK_RIGHT;
			StartFireRateTimer(); //Now that we are playing the animation, and then we fire this
		}

		else if(state == 5)
		{
			animationToPlay = ANIM_ATTACK_LEFT;
			StartFireRateTimer(); //Now that we are playing the animation, and then we fire this
		}

		else
			animationToPlay = ANIM_IDLE; //You would handle center anim here, but I don't have one
			
		Reset();

		UpdateCollisionTransformMatricies();
		UpdateCollisionComponent();
	}

	else
		animationToPlay = ANIM_IDLE; //In case some strange case happense

	animation->SetCurrentAnim(animationToPlay);
	animation->Start();
}

//If the animation, level, or collision component are NULL, then return. If
//the current Anim is neither a right or left attack, then return as well.
//Get the current collision data. Add five to if we are dealing with the
//left animation. Update the collision transform matricies and the collision
//component. Finally, check if anything collided with our weapon.
void WeaponMeleeTest::HandleSwingAnimation(int currentAnim, Level* level)
{
	if(!animation || !level || !collisionComponent)
		return;
	if(currentAnim != ANIM_ATTACK_RIGHT && currentAnim != ANIM_ATTACK_LEFT)
		return;

	currentCollisionData = animation->GetCurrentFrame(currentAnim);
	if(currentAnim == ANIM_ATTACK_LEFT)
		currentCollisionData += 5; //Left swings use the latter 5 collisionDatas

	UpdateCollisionTransformMatricies();
	UpdateCollisionComponent();

	//Find any actor/tile that we hit
	HandlePotentialHits(level);
}

//Supply a list of actors and tiles to level's HitActor function.
//If there are any hit actors, print out a message. If there are
//any hit tiles, print out a message
void WeaponMeleeTest::HandlePotentialHits(Level* level)
{
	if(!level)
		return;

	//Stores all the valid actors we hit
	ActorCollisionList hitActorList;
	//Stores all the wall tiles we hit
	TileCollisionList hitTileList;

	level->HitActor(this, hitActorList);
	level->HitTile(this, hitTileList);

	//We want to deal damage to every actor we hit, due to the
	//sweeping nature of the weapon
	//TODO: Handle redundencies
	if(!hitActorList.IsEmpty())
		hitActorList.DoDamage(owner, 1000.0f);
	else
		cout << "We did not hit an actor!" << endl;

	if(!hitTileList.IsEmpty())
		cout << "We hit a wall tile!" << endl;
	else
		cout << "We did not hit a wall tile!" << endl;
}

bool WeaponMeleeTest::DidHit(Actor* toCheck)
{
	return WeaponMelee::DidHit(toCheck);
}

void WeaponMeleeTest::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
						   bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
						   Matrix* matrix)
{
	if(!renderer || !animation || !movableComponent)
		return;

	Vector pos; //Where we will render our weapon
	//Use this to get data without having to call GetPosition a bunch
	Vector movPos = movableComponent->GetPosition();
	//{x, y} is position we will draw at.
	//Width and height are the width and height
	//of the drawableComponent divided by two
	int width, height;

	width = animation->GetFrameWidth() / 2;
	height = animation->GetFrameHeight() / 2;
	pos.SetX(movPos.GetX() - (float)width);
	pos.SetY(movPos.GetY() - (float)height);
	
	animation->Draw(renderer, pos, rotation, AEOIAFColor::White(), flip, true, false, true, matrix);
}
