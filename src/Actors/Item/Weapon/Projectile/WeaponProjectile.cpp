//Liam "AFishyFez" Wynn, 9/24/2015, A Clash of Colors

#include "WeaponProjectile.h"
#include "../../../../Utilities/Utility_Components/InputHandler.h"
#include "../../../../Utilities/Utility_Components/Constants.h"
#include "../../../../Level/WeaponCollisionDataTypes.h"
#include "../../../../Level/Level.h"
#include <iostream>

using namespace AEOIAF_Actor;
using namespace AEOIAF_Level;
using namespace AEOIAF_Utilities;
using namespace std;

/*WEAPON PROJECTILE IMPLEMENTATIONS*/
WeaponProjectile::WeaponProjectile()
{
	SetFireRate(100);
	
	weaponType = WEP_TYPE_PROJ;

	projectileType = NULL;
	projectileRenderer = NULL;
}

WeaponProjectile::WeaponProjectile(const char* newID) : Weapon(newID)
{
	SetFireRate(100);

	weaponType = WEP_TYPE_PROJ;

	projectileType = NULL;
	projectileRenderer = NULL;
}

WeaponProjectile::WeaponProjectile(const WeaponProjectile& toCopy)
{
	SetFireRate(100);

	weaponType = WEP_TYPE_PROJ;

	projectileType = NULL;
	projectileRenderer = NULL;

	Copy(toCopy);
}

WeaponProjectile::~WeaponProjectile()
{
	projectileRenderer = NULL;
	//If the projectile was set, this function will close it properly,
	//and then set it to NULL
	SetProjectileType(NULL);
}

//Because we may set the projectile type, then change it later,
//we need to deallocate the projectile when we set it
void WeaponProjectile::SetProjectileType(Projectile* val)
{
	if(projectileType)
		delete projectileType;

	projectileType = val;
}

WeaponProjectile& WeaponProjectile::operator = (const WeaponProjectile& toCopy)
{
	Copy(toCopy);
	return *this;
}

void WeaponProjectile::Copy(const WeaponProjectile& toCopy)
{
	if(this == &toCopy)
		return;

	if(toCopy.projectileType)
		projectileType = toCopy.projectileType->GetCopy();
	else
		projectileType = NULL;
}

WeaponProjectile* WeaponProjectile::GetCopy()
{
	return new WeaponProjectile(*this);
}

void WeaponProjectile::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!level)
		return;

	Weapon::Update(level, e, deltaTime);

	if(FiredWeapon())
	{
		SetWantToFire(false);
		MakeProjectile();
		StartFireRateTimer();
	}

	if(!projectiles.IsEmpty())
	{
		projectiles.Update(level, e, deltaTime);
		HandlePotentialHits(level);
	}
}

void WeaponProjectile::HandlePotentialHits(Level* level)
{
	if(!level)
		return;

	//Stores all the valid actors we hit
	ActorCollisionList hitActorList;
	//Stores all the wall tiles we hit
	TileCollisionList hitTileList;

	level->HitActor(this, hitActorList);
	level->HitTile(this, hitTileList);

	if(!hitActorList.IsEmpty())
	{
		hitActorList.DoDamageClosestActor(owner, 5.0f);
		cout << "WE HIT AN ACTOR" << endl;
	}

	else
		cout << "We did not hit an actor!" << endl;

	if(!hitTileList.IsEmpty())
		cout << "We hit a wall tile!" << endl;
	else
		cout << "We did not hit a wall tile!" << endl;
	
}

bool WeaponProjectile::DidHit(Actor* toCheck)
{
	if(owner == toCheck)
		return false;

	return projectiles.HitActor(toCheck);
}

bool WeaponProjectile::DidHit(Tile* toCheck)
{
	return projectiles.HitTile(toCheck);
}

bool WeaponProjectile::FiredWeapon()
{
	bool result; //What we will return

	if(WantToFire() && !IsRecharging())
		result = true;
	else
		result = false;

	return result;
}

//An incredibly janky way to do it, but essentially just make a projectile
//and save it to the projectile queue.
void WeaponProjectile::MakeProjectile()
{
	if(!projectileType || !owner)
		return;

	Projectile* toAdd = projectileType->GetCopy();
	MovableComponent* toAddMovComp = MakeProjectileMovableComponent();

	toAdd->SetMovableComponent(toAddMovComp);
	//toAdd->Initialize(projectileRenderer);

	projectiles.Enqueue(toAdd);
}

//Essentially make a generic movable component, and set the velocity based
//off of the owner's direction
MovableComponent* WeaponProjectile::MakeProjectileMovableComponent()
{
	if(!owner)
		return NULL;

	MovableComponent* toAddMovComp = new MovableComponent();
	Vector toAddPos; //The initial position of the projectile
	Vector toAddDir; //The direction and magnitude of travel
	float ownerRot; //Use this to get the direction of travel for the bullet

	if(owner->GetPosition(toAddPos))
		toAddMovComp->SetPosition(toAddPos);

	//Essentially convert the owner's rotation into radians
	//to compute the velocity
	ownerRot = (owner->GetRotation() * AEOIAF_PI) / 180.0f;
	
	toAddDir = Vector(cos(ownerRot), sin(ownerRot));
	toAddMovComp->SetDirection(toAddDir);
	toAddMovComp->SetMagnitude(4.0f);

	return toAddMovComp;
}

void WeaponProjectile::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
							bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
							Matrix* matrix)
{
	projectiles.Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
}

/*PROJECTILE QUEUE IMPLEMENTATIONS*/
ProjectileQueue::ProjectileQueue()
{
	rear = NULL;
}

ProjectileQueue::~ProjectileQueue()
{
	Clear();
}

void ProjectileQueue::Enqueue(Projectile* toAdd)
{
	if(!rear)
	{
		rear = new ProjectileQueueNode;
		rear->projectile = toAdd;
		rear->next = rear;
	}

	else
	{
		ProjectileQueueNode* temp = rear->next;
		rear->next = new ProjectileQueueNode;
		rear->next->projectile = toAdd;
		rear = rear->next;
		rear->next = temp;
	}
}

void ProjectileQueue::Dequeue()
{
	if(!rear)
		return;

	//Special case: only rear in the queue
	if(rear->next == rear)
	{
		delete rear;
		rear = NULL;
	}

	else
	{
		ProjectileQueueNode* temp = rear->next;
		rear->next = temp->next;
		delete temp;
		temp = NULL;
	}
}

void ProjectileQueue::Clear()
{
	while(rear)
		Dequeue();
}

void ProjectileQueue::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!rear)
		return;

	//Break the queue
	ProjectileQueueNode* front = rear->next;
	ProjectileQueueNode* temp = front;
	rear->next = NULL;

	//Traverse to the end of the list
	while(temp)
	{
		if(temp->projectile)
			temp->projectile->Update(level, e, deltaTime);
		temp = temp->next;
	}

	//Fix the queue
	rear->next = front;
}

//Essentially what we will do is break the queue into
//a linear linked list, then traverse the list and determine
//if any projectile hits toCheck
bool ProjectileQueue::HitActor(Actor* toCheck)
{
	if(!toCheck || !rear)
		return false;

	bool result; //What we will return

	ProjectileQueueNode* front; //Use this to mark rear's next
	ProjectileQueueNode* temp; //Use this to traverse
	ProjectileQueueNode* prev; //Follows behind temp so we can remove nodes

	front = rear->next;
	rear->next = NULL;

	temp = front;
	prev = NULL;

	while(temp)
	{
		if(toCheck->CollidesWith(temp->projectile) || temp->projectile->MustDestroy())
		{
			//For projectiles, MustDestroy is only set true if toCheck's shield hit it,
			//instead of toCheck itself
			if(!temp->projectile->MustDestroy())
				result = true;
			else
				result = false;

			//Special case 1: Only one item in the list
			//Since rear's next is itself, then front
			//and rear point to the same place. Thus
			//temp equals both rear and front
			if(temp == rear && temp == front)
			{
				delete temp;
				temp = NULL;
				front = NULL;
				rear = NULL;
			}

			//Special case 2: The front needs to be removed.
			//We know at this point there are at least 2 items
			//in the list. As such, we set front to be front->next
			//before deleting temp and setting it to NULL
			else if(temp == front)
			{
				front = front->next;
				delete temp;
				temp = NULL;
			}

			//Special case 3: In our final special case, the
			//rear item collides with our actor. In this case,
			//We must set the previous node to be the new rear
			//before deleting temp
			else if(temp == rear)
			{
				rear = prev;
				delete temp;
				temp = NULL;
			}

			//General Case: We are somewhere in the middle.
			//Essentially, remove temp from the list and delete it
			else
			{
				prev->next = temp->next;
				delete temp;
				temp = NULL;
			}

			break;
		}

		result = false;
		prev = temp;
		temp = temp->next;
	}

	//If the first special case is met, then there are no items
	//in the list, so check for nullness here
	if(rear)
		rear->next = front;

	return result;
}

bool ProjectileQueue::HitTile(AEOIAF_Level::Tile* toCheck)
{
	if(!rear || !toCheck || !toCheck->IsWall())
		return false;

	bool result; //What we will return

	ProjectileQueueNode* front; //Use this to mark rear's next
	ProjectileQueueNode* temp; //Use this to traverse
	ProjectileQueueNode* prev; //Follows behind temp so we can remove nodes

	//Use this to check if each projectile collides with
	//the tile
	AxisAllignedBoundingBox tileBoundBox;
	
	front = rear->next;
	rear->next = NULL;

	temp = front;
	prev = NULL;

	tileBoundBox = CreateBoundingBox(toCheck->Position(),
									 AEOIAF_TILE_SIZE, AEOIAF_TILE_SIZE);

	while(temp)
	{
		if(temp->projectile && temp->projectile->CollidesWith(tileBoundBox))
		{
			result = true;

			//Special case 1: Only one item in the list
			//Since rear's next is itself, then front
			//and rear point to the same place. Thus
			//temp equals both rear and front
			if(temp == rear && temp == front)
			{
				delete temp;
				temp = NULL;
				front = NULL;
				rear = NULL;
			}

			//Special case 2: The front needs to be removed.
			//We know at this point there are at least 2 items
			//in the list. As such, we set front to be front->next
			//before deleting temp and setting it to NULL
			else if(temp == front)
			{
				front = front->next;
				delete temp;
				temp = NULL;
			}

			//Special case 3: In our final special case, the
			//rear item collides with our actor. In this case,
			//We must set the previous node to be the new rear
			//before deleting temp
			else if(temp == rear)
			{
				rear = prev;
				delete temp;
				temp = NULL;
			}

			//General Case: We are somewhere in the middle.
			//Essentially, remove temp from the list and delete it
			else
			{
				prev->next = temp->next;
				delete temp;
				temp = NULL;
			}

			break;
		}

		result = false;
		prev = temp;
		temp = temp->next;
	}

	//If the first special case is met, then there are no items
	//in the list, so check for nullness here
	if(rear)
		rear->next = front;

	return result;
	return false;
}

void ProjectileQueue::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
						   bool bTrsfrmRot, bool bTrsfrmScale, bool bTrsfrmPos,
						   Matrix* matrix)
{
	if(!rear)
		return;

	//Break the queue
	ProjectileQueueNode* front = rear->next;
	ProjectileQueueNode* temp = front;
	rear->next = NULL;

	//Traverse to the end of the list
	while(temp)
	{
		if(temp->projectile)
			temp->projectile->Draw(renderer, flip, bTrsfrmRot, bTrsfrmScale, bTrsfrmPos, matrix);
		temp = temp->next;
	}

	//Fix the queue
	rear->next = front;
}

//PROJECTILE QUEUE NODE IMPLEMENTATIONS*/
ProjectileQueueNode::ProjectileQueueNode()
{
	projectile = NULL;
	next = NULL;
}

ProjectileQueueNode::~ProjectileQueueNode()
{
	if(projectile)
	{
		delete projectile;
		projectile = NULL;
	}
}		

