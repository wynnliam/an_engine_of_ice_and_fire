//Liam "AFishyFez" Wynn, 8/19/2015, A Clash of Colors

#include "../WeaponCollisionDataTypes.h"
#include "../../Actors/Actor.h"
#include "../../Utilities/General_Purpose/HelpfulMethods.h"
#include <iostream>

using namespace AEOIAF_Level;
using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace std;

ActorCollisionList::ActorCollisionList()
{
	head = NULL;
}

ActorCollisionList::ActorCollisionList(const ActorCollisionList& toCopy)
{
	Copy(toCopy);
}

ActorCollisionList::~ActorCollisionList()
{
	RemoveAll();

	head = NULL;
}

ActorCollisionList& ActorCollisionList::operator = (const ActorCollisionList& toCopy)
{
	Copy(toCopy);
	return *this;
}

void ActorCollisionList::Copy(const ActorCollisionList& toCopy)
{
	if(this == &toCopy)
		return;

	Copy(head, toCopy.head);
}

void ActorCollisionList::RemoveAll()
{
	RemoveAll(head);
}

//If toAdd or instigator are NULL, then return false.
//Grab the position of both. Then calculate the distance
//from eachother. Call the recursive function and return
//the result of that.
bool ActorCollisionList::Add(Actor* toAdd, Actor* instigator)
{
	if(!toAdd || !instigator)
		return false;

	//The distance between toAdd and instigator. Use this to determine where toAdd will be in the list
	float dist; 
	bool result; //What we will return

	dist = GetDistance(toAdd, instigator);

	if(dist == -1.0f)
		result = false;
	else
		result = Add(toAdd, dist, head, NULL);

	return result;
}

//If toAdd, or instigator are NULL, then return -1. Grab the positions
//of both. Then use that to calculate the distance between the two, and
//return the result.
float ActorCollisionList::GetDistance(Actor* toAdd, Actor* instigator)
{
	if(!toAdd || !instigator)
		return -1.0f;

	//Grab the x and y positions of toAdd and instigator
	//so that we may calculate the distance between the
	//two
	Vector toAddPos; //Position of toAdd
	Vector instPos; //Position of instigator
	float dist; //Distance between actor and instigator

	if(!toAdd->GetPosition(toAddPos) || !instigator->GetPosition(instPos))
		dist = -1.0f;
	else
		dist = (toAddPos - instPos).GetMagnitude();

	return dist;
}

//If toAdd is NULL, then return false. If head is NULL, then add toAdd and return true.
//Otherwise if dist is greater than or equal to head, then go right, otherwise go left.
bool ActorCollisionList::Add(Actor* toAdd, float dist, ColActorNode*& head, ColActorNode* parent)
{
	if(!toAdd)
		return false;

	bool result; //What we will return

	if(!head) //Reached end of tree, or tree is empty
	{
		head = new ColActorNode;
		head->hitActor = toAdd; //We don't want a copy, we want the actual thing we hit
		head->distance = dist;
		head->parent = parent;

		//We need to rebalance the tree, probably
		HandleCase1(head);

		result = true;
	}

	else
	{
		if(dist >= head->distance)
			result = Add(toAdd, dist, head->right, head);
		else
			result = Add(toAdd, dist, head->left, head);
	}

	return result;
}

//Our first case is that the node has no parent. Thus it is
//the root. For this case, we simply make sure the root is
//black.
void ActorCollisionList::HandleCase1(ColActorNode* node)
{
	if(!node)
		return; //Don't want to work with a bad node!

	if(!node->parent)
		node->bIsBlack = true;
	else
		HandleCase2(node); //We have a parent, thus must look at other cases
}

//At this point, we know node has a parent. As long as the parent is
//black, then the tree is perfectly valid. Otherwise, we need to go to
//case 3
void ActorCollisionList::HandleCase2(ColActorNode* node)
{
	if(!node)
		return;

	if(node->parent && node->parent->bIsBlack == false)
		HandleCase3(node); //The node's parent isn't black, so we need to go to case 3
}

//Node's parent is not black. So we need to change the colors of
//the granparent, parent, and uncle, if they exist. But because the
//Grandparent being red instead of black can violate all kinds of
//properties of the tree (its parent being red/it being the root),
//we need to call case 1 using the grand parent.
void ActorCollisionList::HandleCase3(ColActorNode* node)
{
	if(!node)
		return;

	ColActorNode* grandparent; //Need this to change it's color/go to case 1
	ColActorNode* uncle; //Need this to change color

	uncle = node->FindUncle();

	//We only need to check for nullness in the uncle. If he
	//isn't NULL, then neither must the grandparent be
	if(uncle && !uncle->bIsBlack)
	{
		//We might as well only find this if the uncle exists
		grandparent = node->FindGrandParent();

		//Flip all the colors
		node->parent->bIsBlack = true;
		uncle->bIsBlack = true;
		grandparent->bIsBlack = false;

		//Start the process of handling nodes over again
		HandleCase1(grandparent);
	}

	else
		HandleCase4(node);
}

//With Case 4, we get to do all the rotations for tree balancing.
//Essentially, if node is the left child of a left child, or the
//right child of a right child, then we need to do only one
//rotation. If it is the right of a left child, or the left of a
//right child, we need to do a double rotation. At this point,
//also, the uncle is black. As such, we change the colors of the
//parent and grandparent to maintain properties
void ActorCollisionList::HandleCase4(ColActorNode* node)
{
	if(!node)
		return; //Node is bad, so return!

	//Needed to handle all rotations
	ColActorNode* grandparent = node->FindGrandParent();
	//So we don't need to keep dereferencing to grab it
	ColActorNode* parent = node->parent;

	if(!grandparent)
		return; //Grandparent is bad, can't continue

	grandparent->bIsBlack = false;
	parent->bIsBlack = true;

	//Rotation case 1: right of a right
	//Perform a single counter-clockwise rotation
	if(node == parent->right && parent == grandparent->right)
		RotationRight(grandparent);
	
	//Rotation case 2: left of a left
	//Perform a single clockwise rotation
	else if(node == parent->left && parent == grandparent->left)
		RotationLeft(grandparent);

	//Rotation case 3: left of a right
	//Rotate node's parent counter-clockwise, then rotate
	//Grandparent clockwise
	else if(node == parent->left && parent == grandparent->right)
	{
		RotationLeft(parent);
		RotationRight(grandparent);
	}

	//Rotation case 4: right of a left
	//Rotate node's parent clockwise, then rotate grandparent
	//counter-clockwise
	else
	{
		RotationRight(parent);
		RotationLeft(grandparent);
	}
}

//First begin by making sure that node isn't NULL. Then grab node's
//right child (oldRight). If right is NULL, then return. Otherwise,
//Set node's right to oldRight's left child. Then make node the left
//child of oldRight. Next set oldRight's parent to node's parent. Then
//Set node's parent to oldRight. Then set node's right child's parent to
//node, as it still points to oldRight. Finally, if oldRight's parent
//exists, then make sure the parent properly points to oldRight 
void ActorCollisionList::RotationRight(ColActorNode* node)
{
	if(!node)
		return; //node is bad, so get out!

	ColActorNode* right = node->right;
	if(!right)
		return; //right is bad, so we cannot continue

	//Do the rotations
	node->right = right->left;
	right->left = node;

	//Now it's time to update the parents
	right->parent = node->parent;
	node->parent = right;
	
	if(node->right)
		node->right->parent = node; //Until now, node->right's parent was right

	if(right->parent)
	{
		//Making sure that node's old parent properly
		//points to right instead of node
		if(right->parent->right == node)
			right->parent->right = right;
		else
			right->parent->left = right;
	}
}

//If node is NULL, then return. Grab the left child of node.
//If it is null, then return. Set node's left to left child's
//right. Then set the left child's right to node. Finally, if
//node had a parent, set that parent to the old left child's parent,
//and then set the old left child to be node's parent.
void ActorCollisionList::RotationLeft(ColActorNode* node)
{
	if(!node)
		return;

	ColActorNode* left = node->left;
	if(!left)
		return;

	//Perform the rotation
	node->left = left->right;
	left->right = node;

	//Now update the parents of each node
	left->parent = node->parent;
	node->parent = left;

	if(node->left)
		node->left->parent = node; //Have to update this

	//Now make sure that left's new parent is updated
	if(left->parent)
	{
		if(left->parent->left == node)
			left->parent->left = left;
		else
			left->parent->right = left;
	}
}

Actor* ActorCollisionList::FindClosestHitActor()
{
	return FindClosestHitActor(head);
}

//If head is NULL, return NULL. If head's left and right children are
//NULL, then return the stored actor. Otherwise call the function again
//but go left.
Actor* ActorCollisionList::FindClosestHitActor(ColActorNode* head)
{
	if(!head)
		return NULL;

	Actor* result; //What we will return

	if(!head->left)
		result = head->hitActor;
	else
		result = FindClosestHitActor(head->left);

	return result;
}


void ActorCollisionList::DoDamageClosestActor(Actor* instigator, const float damage)
{
	Actor* closest = FindClosestHitActor();

	if(closest)
		closest->DoDamage(instigator, damage);
}

void ActorCollisionList::DoDamage(Actor* instigator, const float damage)
{
	DoDamage(instigator, damage, head);
}

void ActorCollisionList::DoDamage(Actor* instigator, const float damage, ColActorNode* head)
{
	if(!head)
		return;

	if(head->hitActor)
		head->hitActor->DoDamage(instigator, damage);

	DoDamage(instigator, damage, head->left);
	DoDamage(instigator, damage, head->right);
}

//If head is NULL, then we reached past a leaf, or the
//list is empty, so return. Call the function again for
//left and right child. Upon returning, delete it and set
//it to NULL.
void ActorCollisionList::RemoveAll(ColActorNode*& head)
{
	if(!head)
		return; //Reached end of tree, or tree is empty

	RemoveAll(head->left);
	RemoveAll(head->right);

	delete head;
	head = NULL;
}

//If source is NULL, then set dest to NULL. Otherwise copy the values of
//source into dest, and call the function again for the left and right.
void ActorCollisionList::Copy(ColActorNode*& dest, ColActorNode* source)
{
	if(!source)
	{
		dest = NULL;
		return;
	}

	dest = new ColActorNode(*source);

	Copy(dest->right, source->right);
	Copy(dest->left, source->left);
}

bool ActorCollisionList::IsEmpty() const
{
	return head == NULL;
}

/*COLLISION ACTOR NODE IMPLEMENTATIONS*/

ColActorNode::ColActorNode()
{
	bIsBlack = false; //By default, a red-black node is always red

	distance = 0.0f;
	hitActor = NULL;

	parent = NULL;
	left = NULL;
	right = NULL;
}

ColActorNode::ColActorNode(const ColActorNode& toCopy)
{
	Copy(toCopy);
}

//We don't want to delete the actor! Just set everything to NULL
//so as to protect from any potential memory leaks here
ColActorNode::~ColActorNode()
{
	hitActor = NULL;

	parent = NULL;
	left = NULL;
	right = NULL;
}

ColActorNode& ColActorNode::operator = (const ColActorNode& toCopy)
{
	Copy(toCopy);
	return *this;
}

//Copy just the actor and the distance. Set everything
//else to NULL
void ColActorNode::Copy(const ColActorNode& toCopy)
{
	if(&toCopy == this)
		return;

	hitActor = toCopy.hitActor; //We want the ACTUAL actor we hit, not a copy. So take the pointer
	distance = toCopy.distance;

	parent = NULL;
	left = NULL;
	right = NULL;
}

//If grandparent or parent is NULL, then return NULL.
//Otherwise return the parent of this node's parent.
ColActorNode* ColActorNode::FindGrandParent()
{
	if(!parent)
		return NULL;

	return parent->parent;
}

//If parent or grandparent is NULL, then return NULL.
//If the parent is the left child of grandparent, then
//return right. Otherwise, return left.
ColActorNode* ColActorNode::FindUncle()
{
	if(!parent)
		return NULL;

	ColActorNode* grandParent; //Used to find uncle
	ColActorNode* uncle; //Essentially what we are returning

	grandParent = FindGrandParent();
	if(!grandParent)
		uncle = NULL;
	else
	{
		if(parent == grandParent->left)
			uncle = grandParent->right;
		else
			uncle = grandParent->left;
	}

	return uncle;
}
