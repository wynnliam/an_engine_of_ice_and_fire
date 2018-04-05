//Liam "AFishyFez" Wynn, 10/11/2015, A Clash of Colors

#include "Shield.h"
#include "../../../Utilities/Utility_Components/Constants.h"
#include <algorithm> //For min and max functions

using namespace AEOIAF_Actor;
using namespace AEOIAF_Utilities;
using namespace AEOIAF_Level;
using namespace std;

Shield::Shield()
{
	drawRotationOffset = 0.0f;
}

Shield::Shield(const char* newID) : Item(newID)
{
	drawRotationOffset = 0.0f;
}

Shield::Shield(const Shield& toCopy)
{
	Copy(toCopy);
}

Shield::~Shield()
{
}

Shield& Shield::operator = (const Shield& toCopy)
{
	Copy(toCopy);
	return *this;
}

void Shield::Copy(const Shield& toCopy)
{
	Item::Copy(toCopy);

	offset = toCopy.offset;
	drawRotationOffset = toCopy.drawRotationOffset;
}

Shield* Shield::GetCopy()
{
	Shield* result = new Shield(*this);
	return result;
}

void Shield::Update(Level* level, SDL_Event* e, float deltaTime)
{
	if(!movableComponent || !collisionComponent)
		return;

	UpdateRotationValuesAndMatrices();
	movableComponent->SetPosition(GetTransformedPosition());
	transformedColBox = GetTransformedBoundingBox();
}

//If the owner or drawableComponent are NULL, then return. Grab the
//owner's rotation. Use the drawRotationOffset and the owner's rotation
//To get the final dtaw rotation. Convert both the drawRotation and owner
//rotation to radians. Use these radian values to create the 
//offsetRotationMatrix, and the col box's rotation matrix.
void Shield::UpdateRotationValuesAndMatrices()
{
	if(!owner || !drawableComponent)
		return;

	float ownerRot; //Used to create rotation matrix
	float drawRot; //The extra rotation added to the shield itself	
	float radiansConvert; //The formula for converting degrees to radians

	ownerRot = owner->GetRotation();
	drawRot = ownerRot + drawRotationOffset;
	radiansConvert = AEOIAF_PI / 180.0f;

	SetRotation(drawRot);

	ownerRot *= radiansConvert;
	drawRot *= radiansConvert;
	
	offsetRotationMatrix = Matrix::CreateRotation(-ownerRot);
	colBoxRotationMatrix = Matrix::CreateRotation(-drawRot);
}

//Get the owner's position. Then take the offset value
//and transform it with the offsetRotationMatrix. Then
//add this transformed offset to the owner's position,
//and return the result
Vector Shield::GetTransformedPosition()
{
	//What we will return
	Vector result;

	if(owner)
		owner->GetPosition(result);

	result += Matrix::Transform(offset, offsetRotationMatrix);

	return result;
}

//If the collision component exists, transform its 
//bounding box by the rotationMatrix. Make the final
//box's min vals (0, 0), and its max vals (width, height).
//Otherwise, return a default axis alligned bounding box
AxisAllignedBoundingBox Shield::GetTransformedBoundingBox()
{
	if(!collisionComponent)
		return AxisAllignedBoundingBox(0, 0, 0, 0);

	//What we will return
	AxisAllignedBoundingBox result;
	//A copy of the collisionComponent's rectangle
	//that we will transform
	AxisAllignedBoundingBox baseRect;
	//The four corners of the baseRectangle
	//Stores where our transformed corners will be
	//which we can use to make result
	Vector tL, bL, tR, bR;

	baseRect = collisionComponent->GetBoundingBox();

	tL = Matrix::Transform(Vector(baseRect.xMin, baseRect.yMin), colBoxRotationMatrix);
	bL = Matrix::Transform(Vector(baseRect.xMin, baseRect.yMax), colBoxRotationMatrix);
	tR = Matrix::Transform(Vector(baseRect.xMax, baseRect.yMin), colBoxRotationMatrix);
	bR = Matrix::Transform(Vector(baseRect.xMax, baseRect.yMax), colBoxRotationMatrix);

	//Since after transformation, the four points could be anywhere, so we
	//Determine the largest and smallest values for results max's and min's
	//respectively
	result.xMin = min(tL.GetX(), min(bL.GetX(), min(tR.GetX(), bR.GetX())));
	result.xMax = max(tL.GetX(), max(bL.GetX(), max(tR.GetX(), bR.GetX())));
	result.yMin = min(tL.GetY(), min(bL.GetY(), min(tR.GetY(), bR.GetY())));
	result.yMax = max(tL.GetY(), max(bL.GetY(), max(tR.GetY(), bR.GetY())));

	//Since we want the box to originate at (0, 0), the min vals will be
	//(0, 0), and the max vals will be (width, height)
	result.xMax = result.xMax - result.xMin;
	result.yMax = result.yMax - result.yMin;
	result.xMin = 0;
	result.yMin = 0;

	//Now that we've calculated the collision box dimensions,
	//we have the information needed to calculate its position
	//relative to the owner
	UpdateCollisionBoxPosition((int)result.xMax, (int)result.yMax);

	return result;
}

//If the movable component is NULL, then return. Otherwise, get
//the movable component's position, and subtract a vector
//of size (width / 2, height / 2)
void Shield::UpdateCollisionBoxPosition(int width, int height)
{
	if(!movableComponent)
		return; //No owner, can't continue

	//We need to make the box relative to
	//its center, and not the top left corner,
	//so we need this
	Vector origin(width / 2, height / 2);

	colBoxPos = movableComponent->GetPosition() - origin;
}

//If the movable or collision components are NULL, return false.
//Set the movableComponent's position to colBoxPos. Set the
//collisionComponent's box to transformedColBox. Do collision
//check. Reset values. Finally, return collision check result.
bool Shield::CollidesWith(Actor* toCheck) const
{
	if(!movableComponent || !collisionComponent)
		return false;

	//Temporarily store movable component's pos here
	Vector tempPos; 
	//Temporarily store collision comp's box here
	AxisAllignedBoundingBox tempBox;
	//What we will return
	bool result;

	//Store old values
	tempPos = movableComponent->GetPosition();
	tempBox = collisionComponent->GetBoundingBox();
	//Set new values
	movableComponent->SetPosition(colBoxPos);
	collisionComponent->SetBoundingBox(transformedColBox);

	result = Item::CollidesWith(toCheck);

	//Since, odds are, toCheck is a projectile, we will say the projectile
	//needs to be destroyed
	if(result == true)
		toCheck->SetMustDestroy(true);

	//Reset old values
	movableComponent->SetPosition(tempPos);
	collisionComponent->SetBoundingBox(tempBox);

	return result;
}

//If the movable or collision components are NULL, return false.
//Set the movableComponent's position to colBoxPos. Set the
//collisionComponent's box to transformedColBox. Do collision
//check. Reset values. Finally, return collision check result.
bool Shield::CollidesWith(AxisAllignedBoundingBox& toCheck) const
{
	if(!movableComponent || !collisionComponent)
		return false;

	//Temporarily store movable component's pos here
	Vector tempPos; 
	//Temporarily store collision comp's box here
	AxisAllignedBoundingBox tempBox;
	//What we will return
	bool result;

	//Store old values
	tempPos = movableComponent->GetPosition();
	tempBox = collisionComponent->GetBoundingBox();
	//Set new values
	movableComponent->SetPosition(colBoxPos);
	collisionComponent->SetBoundingBox(transformedColBox);

	result = Item::CollidesWith(toCheck);

	//Reset old values
	movableComponent->SetPosition(tempPos);
	collisionComponent->SetBoundingBox(tempBox);

	return result;
}

//If the movable or collision components are NULL, return false.
//Set the movableComponent's position to colBoxPos. Set the
//collisionComponent's box to transformedColBox. Do collision
//check. Reset values. Finally, return collision check result.
bool Shield::CollidesWith(const Tracer& tracer) const
{
	if(!movableComponent || !collisionComponent)
		return false;

	//Temporarily store movable component's pos here
	Vector tempPos; 
	//Temporarily store collision comp's box here
	AxisAllignedBoundingBox tempBox;
	//What we will return
	bool result;

	//Store old values
	tempPos = movableComponent->GetPosition();
	tempBox = collisionComponent->GetBoundingBox();
	//Set new values
	movableComponent->SetPosition(colBoxPos);
	collisionComponent->SetBoundingBox(transformedColBox);

	result = Item::CollidesWith(tracer);

	//Reset old values
	movableComponent->SetPosition(tempPos);
	collisionComponent->SetBoundingBox(tempBox);

	return result;
}

//Essentially set the movable component to have an offset such that
//the origin is the center of the shield, and not the top-left corner.
//Then after rendering, move the shield's position back to its original
//position
void Shield::Draw(SDL_Renderer* renderer, SDL_RendererFlip flip,
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

	Item::Draw(renderer, flip, true, false, true, matrix);

	//Reset the position
	drawPos += drawPosOffset;
	movableComponent->SetPosition(drawPos);

	//rectangleRegion->SetCenter(Vector(0, 0));
	/*rectangleRegion->SetWidth((int)transformedColBox.xMax);
	rectangleRegion->SetHeight((int)transformedColBox.yMax);
	rectangleRegion->Draw(renderer, colBoxPos, flip, false, false, true, matrix);*/
}
