//Liam "AFishyFez" Wynn, 6/18/2015, A Clash of Colors

#include "MenuComponent.h"
#include "../Utilities/Utility_Components/Vector.h"

using namespace ACOC_UIElements;
using namespace AEOIAF_Utilities;

MenuComponent::MenuComponent()
{
	drawComponent = NULL;
	collideComponent = NULL;
	bIsActive = false;
}

MenuComponent::MenuComponent(DrawableComponent* drawComp, CollisionComponent* collideComp, const Vector& newOffset)
{
	drawComponent = drawComp;
	collideComponent = collideComp;
	offset = newOffset;
	bIsActive = false;
}

MenuComponent::~MenuComponent()
{
	drawComponent = NULL;
	SetCollisionComponent(NULL);
}

//Since we might override the old drawComponent, delete it if it
//is not NULL. Then assign drawComponent the value of val
void MenuComponent::SetDrawableComponent(DrawableComponent* val)
{
	drawComponent = val;
}

void MenuComponent::SetCollisionComponent(CollisionComponent* val)
{
	if(collideComponent)
		delete collideComponent;

	collideComponent = val;
}

//If the renderer or draw component are NULL, then return
//otherwise, invoke the draw component's draw function
void MenuComponent::Draw(SDL_Renderer* renderer, const Vector& containerPos)
{
	if(!renderer || !drawComponent)
		return;
	
	Vector drawPoint = containerPos + offset; //Where we will draw this component

	drawComponent->Draw(renderer, drawPoint, SDL_FLIP_NONE, false, false, false);
}
