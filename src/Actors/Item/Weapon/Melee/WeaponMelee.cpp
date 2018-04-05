//Liam "AFishyFez" Wynn, 7/25/2015, A Clash of Colors

#include "WeaponMelee.h"
#include "../../../../Utilities/Utility_Components/InputHandler.h"
#include "../../../../Utilities/Utility_Components/Constants.h"
#include "../../../../Level/Level.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace ACOC_Animation;
using namespace std;


/*WEAPON MELEE IMPLEMENTATIONS*/

WeaponMelee::WeaponMelee()
{
	collisionData = NULL;
	numCollisionData = 0;
	currentCollisionData = 0;

	state = STATE_IDLE;

	bShouldFire = false;
	attackType = -1;

	weaponType = WEP_TYPE_MLEE;

	animation = NULL;
}

WeaponMelee::WeaponMelee(const char* newID) : Weapon(newID)
{
	collisionData = NULL;
	numCollisionData = 0;
	currentCollisionData = 0;

	state = STATE_IDLE;

	bShouldFire = false;
	attackType = -1;
	
	weaponType = WEP_TYPE_MLEE;

	animation = NULL;
}

WeaponMelee::WeaponMelee(const WeaponMelee& toCopy)
{
	Copy(toCopy);

	currentCollisionData = 0;

	state = STATE_IDLE;

	bShouldFire = false;
	attackType = -1;
	
	weaponType = WEP_TYPE_MLEE;
}

WeaponMelee::~WeaponMelee()
{
	if(collisionData)
	{
		delete[] collisionData;
		collisionData = NULL;
	}

	if(animation)
	{
		delete animation;
		animation = NULL;
	}
}

DrawableComponent* WeaponMelee::GetAnimationDrawComponent()
{
	if(animation)
		return animation->GetDrawableComponent();
	else
		return NULL;
}

void WeaponMelee::SetAnimationDrawComponent(DrawableComponent* val)
{
	if(animation)
		animation->SetDrawableComponent(val);
}

WeaponMelee& WeaponMelee::operator = (const WeaponMelee& toCopy)
{
	Copy(toCopy);
	return *this;
}

void WeaponMelee::Copy(const WeaponMelee& toCopy)
{
	if(this == &toCopy)
		return;

	if(toCopy.collisionData)
	{
		numCollisionData = toCopy.numCollisionData;
		collisionData = new CollisionData[numCollisionData];

		for(unsigned int i = 0; i < numCollisionData; ++i)
			collisionData[i] = toCopy.collisionData[i];
	}

	if(toCopy.animation)
		animation = new AnimationHandler(*toCopy.animation);

	Weapon::Copy(toCopy);
}

WeaponMelee* WeaponMelee::GetCopy()
{
	return NULL;
}

void WeaponMelee::CreateAnimationData()
{
}

unsigned int WeaponMelee::GetCurrentAnimation() const
{
	unsigned int result;

	if(animation)
		result = animation->GetCurrentAnim();
	else
		result = 10001;

	return result;
}

//This acts as the manager of determing the weapon attack type.
//That is, this will manage all components needed for the algorithm
//that determines our attack type (left, right, center).
void WeaponMelee::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!owner)
		return;

	Weapon::Update(level, e, deltaTime);

	SetRotation(owner->GetRotation());

	SetWantToFire(state == STATE_ATTK_R ||
				  state == STATE_ATTK_L ||
				  state == STATE_ATTK_C);

	//UpdateCollisionTransformMatricies();
	if(WantToFire() && !IsRecharging())
		bShouldFire = true;
}

//If toCheck is the owner or NULL, then return false.
//Otherwise return if toCheck collides with our bounding
//box, after applying the position to the col box
bool WeaponMelee::DidHit(Actor* toCheck)
{
	if(!toCheck || toCheck == owner)
		return false;

	bool result;

	Vector tempPos = movableComponent->GetPosition();
	movableComponent->SetPosition(colBoxPos);

	result = toCheck->CollidesWith(this);

	movableComponent->SetPosition(tempPos);

	return result;
}

bool WeaponMelee::DidHit(Tile* toCheck)
{
	if(!toCheck || !collisionComponent)
		return false;

	//Used to get the mins and maxes of tileBox 
	Vector tilePos;
	//The bounding box used in checking for a collision
	AxisAllignedBoundingBox tileBox;
	//A copy of the collisionComponent's aabb wherein
	//position is accounted for
	AxisAllignedBoundingBox myColBox;
	//What we will return
	bool result;

	tilePos = toCheck->Position();
	tileBox.xMin = tilePos.GetX();
	tileBox.yMin = tilePos.GetY();
	tileBox.xMax = tileBox.xMin + AEOIAF_TILE_SIZE;
	tileBox.yMax = tileBox.yMin + AEOIAF_TILE_SIZE;

	myColBox = collisionComponent->GetBoundingBox();
	myColBox.AddVector(colBoxPos);

	if(myColBox.CollidesWith(tileBox))
	{
		cout << "HIT A WALL!" << endl;
		result = true;
	}

	else
		result = false;

	return result;
}

//If the owner is NULL, or the collision data cannot be
//accessed, then return. Otherwise build a new rotation
//matrix from the owner's rotation.
void WeaponMelee::UpdateCollisionTransformMatricies()
{
	if(!owner || !collisionData || currentCollisionData >= numCollisionData)
		return;

	float ownerRotation; //Used in creating the rotation matrix

	ownerRotation = owner->GetRotation();
	ownerRotation *= AEOIAF_PI / 180.0f;

	rMatrix = Matrix::CreateRotation(-ownerRotation);
}

//If the collision component or collision data is NULL, then 
//return. Create an axis alligned bounding box that is
//essentially a transformed base box. The base box
//is based off of the current collision data
void WeaponMelee::UpdateCollisionComponent()
{
	if(!collisionComponent || !collisionData)
		return;

	//The new bounding box for the collisionComponent
	AxisAllignedBoundingBox boundingBox = collisionData[currentCollisionData].baseBox;
	CreateTransformedCollisionBox(boundingBox);

	collisionComponent->SetBoundingBox(boundingBox);
}

//Grab the four corners of the aabb and transform them with the rotation matrix.
//Then determine where the corners of a new axis alligned bounding box are. Since
//we want the xMin and yMin to be (0, 0), then the xMax and yMax will be
//(width, height). This makes our aabb relative to (0, 0) so that we may apply an
//offset (ie: the colBoxPos) when checking for collisions down the road. For that
//reason, we make sure we update the colBoxPos in this function
void WeaponMelee::CreateTransformedCollisionBox(AxisAllignedBoundingBox& aabb)
{
	//Transformed corners of aabb (top left, top right, bottom left, bottom right)
	Vector tL, tR, bL, bR;
	//The width and height of the box
	int width, height;

	//Transform the four corners
	tL = Matrix::Transform(Vector(aabb.xMin, aabb.yMin), rMatrix);
	tR = Matrix::Transform(Vector(aabb.xMax, aabb.yMin), rMatrix);
	bL = Matrix::Transform(Vector(aabb.xMin, aabb.yMax), rMatrix);
	bR = Matrix::Transform(Vector(aabb.xMax, aabb.yMax), rMatrix);

	//Determine the new values of the aabb
	aabb.xMin = min(tL.GetX(), min(tR.GetX(), min(bL.GetX(), bR.GetX())));
	aabb.xMax = max(tL.GetX(), max(tR.GetX(), max(bL.GetX(), bR.GetX())));
	aabb.yMin = min(tL.GetY(), min(tR.GetY(), min(bL.GetY(), bR.GetY())));
	aabb.yMax = max(tL.GetY(), max(tR.GetY(), max(bL.GetY(), bR.GetY())));

	//xMax and min, and yMax and min are coordinates of points,
	//thus the width is the difference of the maxs and mins
	width = (int)(aabb.xMax - aabb.xMin);
	height = (int)(aabb.yMax - aabb.yMin);

	//Use this to hold the position of the box, to avoid
	//baking it into the aabb itself. The rule is that
	//collision components do not hold position of an actor
	UpdateCollisionBoxPosition(width, height);

	//Since we don't want position baked into the aabb, we
	//set the xMin and yMin to 0, and the xMax and yMax to
	//the width and height respectively
	aabb.xMin = 0;
	aabb.yMin = 0;
	aabb.xMax = width;
	aabb.yMax = height;
}

//Apply the rMatrix to the current collision data's offset. Apply this
//offset to the owner's position. Finally, use width and height to make
//the box relative to the center, and not the top-left corner, so as
//to account for the origin being in the center
void WeaponMelee::UpdateCollisionBoxPosition(int width, int height)
{
	if(!owner)
		return;

	//Use this to avoid messing with the current
	//collision data's offset
	Vector offset;
	//Use this to modify a copy of the owner's
	//position, and not his actual position
	Vector position;
	
	//Determine the new offset for position
	offset = Matrix::Transform(collisionData[currentCollisionData].offset, rMatrix);
	
	//If we cannot get the owner's position, then we cannot keep going
	if(!owner->GetPosition(position))
		return;

	position += offset;

	//The final position is the position variable with an extra offset
	//added to account for the center of the box, and not it's top-left
	//corner	
	colBoxPos = position - Vector(width / 2, height / 2);
}

//Reset our flags for melee weapons
void WeaponMelee::Reset()
{
	state = 0;
	bShouldFire = false;
	attackType = -1;
	SetWantToFire(false);
}

void WeaponMelee::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
					   bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
                       Matrix* matrix)
{
	if(!drawableComponent || !movableComponent)
		return;

	//Essentially this is where we draw
	Vector drawPos;
	//An offset we apply to the drawPos (and movable component's
	//position by extension) to make sure the position is correct
	Vector drawPosOffset;

	drawPos = movableComponent->GetPosition();
	
	drawPosOffset.SetX(drawableComponent->GetWidth() / 2);
	drawPosOffset.SetY(drawableComponent->GetHeight() / 2);

	drawPos -= drawPosOffset;
	movableComponent->SetPosition(drawPos);

	Weapon::Draw(renderer, flip, true, false, true, matrix);

	//Reset the position
	drawPos += drawPosOffset;
	movableComponent->SetPosition(drawPos);
}

/*COLLISION BOX DATA HANDLER IMPLEMENTATIONS*/
CollisionData::CollisionData()
{
	relativeRotation = 0;
	distance = 0;
}

CollisionData& CollisionData::operator= (const CollisionData& toCopy)
{
	Copy(toCopy);
	return *this;
}

void CollisionData::Copy(const CollisionData& toCopy)
{
	baseBox = toCopy.baseBox;
	relativeRotation = toCopy.relativeRotation;
	distance = toCopy.distance;
}
