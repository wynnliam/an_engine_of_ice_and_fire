#include "Button.h"
#include "../MenuContainer.h"
#include "../../Utilities/Utility_Components/Vector.h"
#include "../../Utilities/Utility_Components/InputHandler.h"
#include "../../Utilities/Utility_Components/AxisAllignedBoundingBox.h"

using namespace AEOIAF_Utilities;

Button::Button()
{
}

void Button::Update(MenuContainer& container)
{
	if(!collideComponent)
		return;

	//So I don't have to call GetPosition constantly,
	//and for collision checking respectively
	Vector containerPosition, currentPosition, mousePosition;
	//Used to check if the mouse in inside the collision box
	AxisAllignedBoundingBox mouseRect;

	//Get current position of component
	containerPosition = container.GetPosition();
	currentPosition = containerPosition + offset;
	mousePosition = InputHandler::GetMousePosition();

	//Create the mouseRect
	mouseRect.xMin = mousePosition.GetX();
	mouseRect.yMin = mousePosition.GetY();
	mouseRect.xMax = mouseRect.xMin + 1;
	mouseRect.yMax = mouseRect.yMin + 1;

	//We've clicked the button if the mouse button is clicked, and
	//the mouse position is within my collision component
	bIsActive = InputHandler::GetMouseLeftClickOnce() &&
				collideComponent->Contains(currentPosition, mouseRect);
}
